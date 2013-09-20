#include "PvPMgr.h"
#include "Player.h"
#include "ObjectMgr.h"
#include "Chat.h"

PvPMgr::PvPMgr()
{
    handler = NULL;
}

PvPMgr::~PvPMgr()
{
}

void PvPMgr::HandleDealDamage(Player* attacker, Player* victim, uint32 damage)
{
    if (!attacker || !victim || !damage)
        return;

    // Both the attacker and the victim must be in either a Battleground or the World PvP Zone
    if ((!attacker->InBattleground() || !victim->InBattleground()) && (!attacker->IsInWorldPvPZone() || !victim->IsInWorldPvPZone()))
        return;

    // Both the attacker and the victim can't be dueling
    if (attacker->IsDueling() || victim->IsDueling())
        return;

    uint32 LastDamageDeltCountdownTime = getMSTime() + DAMAGE_RESET_TIME_MS;

    // Attacker already exists; update information
    if (!victim->PvPTargetDamageInfo.empty())
    {
        for (std::list<PvPTargetDamageInformation>::iterator itr = victim->PvPTargetDamageInfo.begin(); itr != victim->PvPTargetDamageInfo.end(); ++itr)
        {
            if (attacker->GetGUIDLow() == itr->AttackerGUIDLow)
            {
                itr->DamageDoneToVictim += damage;
                itr->LastDamageDeltTimer = LastDamageDeltCountdownTime;
                return;
            }
        }
    }

    // Attacker doesn't already exist; create new information
    PvPTargetDamageInformation m_PvPTargetDamageInfo;
    m_PvPTargetDamageInfo.AttackerGUIDLow = attacker->GetGUIDLow();
    m_PvPTargetDamageInfo.DamageDoneToVictim += damage;
    m_PvPTargetDamageInfo.LastDamageDeltTimer = LastDamageDeltCountdownTime;
    victim->PvPTargetDamageInfo.push_back(m_PvPTargetDamageInfo);
}

void PvPMgr::HandlePvPKill(Player* victim, Player* pwner /*= NULL*/)
{
    if (!victim)
        return;

    uint32 currentMSTime = getMSTime();
    uint32 chosenAttackerGUIDLow = 0;
    uint32 HighestDamageDoneToVictim = 0;
    uint32 chosenAttackerLastDamageDeltTime = 0;

    // If pwner exists it means the victim was one shotted
    if (pwner)
    {
        chosenAttackerGUIDLow = pwner->GetGUIDLow();
        victim->PvPTargetDamageInfo.clear();
    }
    else
    {
        if (!victim->PvPTargetDamageInfo.empty())
        {
            for (std::list<PvPTargetDamageInformation>::iterator itr = victim->PvPTargetDamageInfo.begin(); itr != victim->PvPTargetDamageInfo.end(); ++itr)
            {
                // The attacker must have done done damage to the victim in the last 30 seconds
                if (itr->LastDamageDeltTimer > currentMSTime)
                {
                    // Damage done by the current attacker must be more than the damage done of the previous attacker
                    if (itr->DamageDoneToVictim > HighestDamageDoneToVictim)
                    {
                        chosenAttackerGUIDLow = itr->AttackerGUIDLow;
                        HighestDamageDoneToVictim = itr->DamageDoneToVictim;
                        chosenAttackerLastDamageDeltTime = itr->LastDamageDeltTimer;
                    }
                    // Damage done by both attackers is the same
                    else if (itr->DamageDoneToVictim = HighestDamageDoneToVictim)
                    {
                        // Check if the current attacker dealt damage after the previous attacker
                        if (itr->LastDamageDeltTimer > chosenAttackerLastDamageDeltTime)
                        {
                            chosenAttackerGUIDLow = itr->AttackerGUIDLow;
                            HighestDamageDoneToVictim = itr->DamageDoneToVictim;
                            chosenAttackerLastDamageDeltTime = itr->LastDamageDeltTimer;
                        }
                        // Damage dealt times of both attackers are the same
                        else if (itr->LastDamageDeltTimer = chosenAttackerLastDamageDeltTime)
                        {
                            // Set the chosen attacker to whichever attacker has higher PvP rating
                            if (sObjectMgr->GetPlayerByLowGUID(itr->AttackerGUIDLow)->GetPvPRating() >= sObjectMgr->GetPlayerByLowGUID(chosenAttackerGUIDLow)->GetPvPRating())
                            {
                                chosenAttackerGUIDLow = itr->AttackerGUIDLow;
                                HighestDamageDoneToVictim = itr->DamageDoneToVictim;
                                chosenAttackerLastDamageDeltTime = itr->LastDamageDeltTimer;
                            }
                        }
                    }
                }

                victim->PvPTargetDamageInfo.erase(itr);
            }
        }

        // If for some reason there was no attacker chosen to be rewarded; don't continue
        if (!chosenAttackerGUIDLow || !HighestDamageDoneToVictim || !chosenAttackerLastDamageDeltTime)
            return;
    }

    uint32 victimGUIDLow = victim->GetGUIDLow();
    uint8 ratingGain = 0;
    uint16 chosenAttackerPvPRating = GetPvPRatingByGUIDLow(chosenAttackerGUIDLow);
    uint16 victimPvPRating = GetPvPRatingByGUIDLow(victimGUIDLow);

    // Get rating gain based on victim PvP rating
    ratingGain = victimPvPRating / 100;

    // Rating gain can't be less than 10
    if (ratingGain < 10)
        ratingGain = 10;

    // Apply attacker PvP rating diminishing returns if the attacker has more than 2000 PvP rating
    if (chosenAttackerPvPRating > 2000)
        ratingGain *= ((100 - (chosenAttackerPvPRating / 100)) / 100);

    // Rating gain can't be higher than 100
    if (ratingGain > 100)
        ratingGain = 100;

    SetPvPRatingByGUIDLow(chosenAttackerGUIDLow, chosenAttackerPvPRating + ratingGain);

    // Only reduce PvP rating of the victim if the victim has more than 1000 PvP rating
    if (victimPvPRating > 1000)
        SetPvPRatingByGUIDLow(victimGUIDLow, victimPvPRating - 5);

    // Send kill message to the attacker if the attacker is online
    if (Player* chosenAttacker = sObjectMgr->GetPlayerByLowGUID(chosenAttackerGUIDLow))
    {
        handler = new ChatHandler(chosenAttacker);
        std::string victimName = "";
        sObjectMgr->GetPlayerNameByGUID(GUID_HIPART(victimGUIDLow), victimName);
        handler->PSendSysMessage("You have been awarded %u PvP rating for killing %s.", ratingGain, victim->GetName());
    }
}

void PvPMgr::HandleBattlegroundEnd(Battleground* bg)
{
    if (!bg)
        return;
}

void PvPMgr::HandleTwinSpireCapture(Team faction)
{
}

uint16 PvPMgr::Get2v2MMRByGUIDLow(uint32 GUIDLow) const
{
    if (Player* player = sObjectMgr->GetPlayerByLowGUID(GUIDLow))
        return player->Get2v2MMR();
    else
    {
        QueryResult result = CharacterDatabase.PQuery("SELECT matchMakerRating FROM character_arena_stats WHERE slot = 0 AND guid = '%u'", GUIDLow);
        if (!result)
            return 0;

        Field* fields = result->Fetch();
        return fields[0].GetUInt16();
    }
}

void PvPMgr::Set2v2MMRByGUIDLow(uint32 GUIDLow, uint16 mmr)
{
    if (Player* player = sObjectMgr->GetPlayerByLowGUID(GUIDLow))
        player->Set2v2MMR(mmr);

    CharacterDatabase.PExecute("UPDATE character_arena_stats SET matchMakerRating = '%u' WHERE slot = 0 AND guid = '%u'", mmr, GUIDLow);

    if (mmr > GetLifetime2v2MMRByGUIDLow(GUIDLow))
        SetLifetime2v2MMRByGUIDLow(GUIDLow, mmr);
        
}

uint16 PvPMgr::Get3v3MMRByGUIDLow(uint32 GUIDLow) const
{
    if (Player* player = sObjectMgr->GetPlayerByLowGUID(GUIDLow))
        return player->Get3v3MMR();
    else
    {
        QueryResult result = CharacterDatabase.PQuery("SELECT matchMakerRating FROM character_arena_stats WHERE slot = 1 AND guid = '%u'", GUIDLow);
        if (!result)
            return 0;

        Field* fields = result->Fetch();
        return fields[0].GetUInt16();
    }
}

void PvPMgr::Set3v3MMRByGUIDLow(uint32 GUIDLow, uint16 mmr)
{
    if (Player* player = sObjectMgr->GetPlayerByLowGUID(GUIDLow))
        player->Set3v3MMR(mmr);

    CharacterDatabase.PExecute("UPDATE character_arena_stats SET matchMakerRating = '%u' WHERE slot = 1 AND guid = '%u'", mmr, GUIDLow);

    if (mmr > GetLifetime3v3MMRByGUIDLow(GUIDLow))
        SetLifetime3v3MMRByGUIDLow(GUIDLow, mmr);
}

uint16 PvPMgr::Get5v5MMRByGUIDLow(uint32 GUIDLow) const
{
    if (Player* player = sObjectMgr->GetPlayerByLowGUID(GUIDLow))
        return player->Get5v5MMR();
    else
    {
        QueryResult result = CharacterDatabase.PQuery("SELECT matchMakerRating FROM character_arena_stats WHERE slot = 2 AND guid = '%u'", GUIDLow);
        if (!result)
            return 0;

        Field* fields = result->Fetch();
        return fields[0].GetUInt16();
    }
}

void PvPMgr::Set5v5MMRByGUIDLow(uint32 GUIDLow, uint16 mmr)
{
    if (Player* player = sObjectMgr->GetPlayerByLowGUID(GUIDLow))
        player->Set5v5MMR(mmr);

    CharacterDatabase.PExecute("UPDATE character_arena_stats SET matchMakerRating = '%u' WHERE slot = 2 AND guid = '%u'", mmr, GUIDLow);

    if (mmr > GetLifetime5v5MMRByGUIDLow(GUIDLow))
        SetLifetime5v5MMRByGUIDLow(GUIDLow, mmr);
}


uint16 PvPMgr::GetPvPRatingByGUIDLow(uint32 GUIDLow) const
{
    if (Player* player = sObjectMgr->GetPlayerByLowGUID(GUIDLow))
        return player->GetPvPRating();
    else
    {
        QueryResult result = CharacterDatabase.PQuery("SELECT PvPRating FROM character_pvp_stats WHERE guid = '%u'", GUIDLow);
        if (!result)
            return 0;

        Field* fields = result->Fetch();
        return fields[0].GetUInt16();
    }
}

void PvPMgr::SetPvPRatingByGUIDLow(uint32 GUIDLow, uint16 rating)
{
    if (Player* player = sObjectMgr->GetPlayerByLowGUID(GUIDLow))
        player->SetPvPRating(rating);

    CharacterDatabase.PExecute("UPDATE character_pvp_stats SET PvPRating = '%u' WHERE guid = '%u'", rating, GUIDLow);
}

uint16 PvPMgr::GetLifetimePvPRatingByGUIDLow(uint32 GUIDLow) const
{
    if (Player* player = sObjectMgr->GetPlayerByLowGUID(GUIDLow))
        return player->GetLifetimePvPRating();
    else
    {
        QueryResult result = CharacterDatabase.PQuery("SELECT LifetimePvPRating FROM character_pvp_stats WHERE guid = '%u'", GUIDLow);
        if (!result)
            return 0;

        Field* fields = result->Fetch();
        return fields[0].GetUInt16();
    }
}

void PvPMgr::SetLifetimePvPRatingByGUIDLow(uint32 GUIDLow, uint16 rating)
{
    if (Player* player = sObjectMgr->GetPlayerByLowGUID(GUIDLow))
        player->SetLifetimePvPRating(rating);

    CharacterDatabase.PExecute("UPDATE character_pvp_stats SET LifetimePvPRating = '%u' WHERE guid = '%u'", rating, GUIDLow);
}

uint16 PvPMgr::GetLifetime2v2RatingByGUIDLow(uint32 GUIDLow) const
{
    if (Player* player = sObjectMgr->GetPlayerByLowGUID(GUIDLow))
        return player->GetLifetime2v2Rating();
    else
    {
        QueryResult result = CharacterDatabase.PQuery("SELECT Lifetime2v2Rating FROM character_pvp_stats WHERE guid = '%u'", GUIDLow);
        if (!result)
            return 0;

        Field* fields = result->Fetch();
        return fields[0].GetUInt16();
    }
}

void PvPMgr::SetLifetime2v2RatingByGUIDLow(uint32 GUIDLow, uint16 rating)
{
    if (Player* player = sObjectMgr->GetPlayerByLowGUID(GUIDLow))
        player->SetLifetime2v2Rating(rating);

    CharacterDatabase.PExecute("UPDATE character_pvp_stats SET Lifetime2v2Rating = '%u' WHERE guid = '%u'", rating, GUIDLow);
}

uint16 PvPMgr::GetLifetime2v2MMRByGUIDLow(uint32 GUIDLow) const
{
    if (Player* player = sObjectMgr->GetPlayerByLowGUID(GUIDLow))
        return player->GetLifetime2v2MMR();
    else
    {
        QueryResult result = CharacterDatabase.PQuery("SELECT Lifetime2v2MMR FROM character_pvp_stats WHERE guid = '%u'", GUIDLow);
        if (!result)
            return 0;

        Field* fields = result->Fetch();
        return fields[0].GetUInt16();
    }
}

void PvPMgr::SetLifetime2v2MMRByGUIDLow(uint32 GUIDLow, uint16 mmr)
{
    if (Player* player = sObjectMgr->GetPlayerByLowGUID(GUIDLow))
        player->SetLifetime2v2MMR(mmr);

    CharacterDatabase.PExecute("UPDATE character_pvp_stats SET Lifetime2v2MMR = '%u' WHERE guid = '%u'", mmr, GUIDLow);
}

uint16 PvPMgr::GetLifetime2v2WinsByGUIDLow(uint32 GUIDLow) const
{
    if (Player* player = sObjectMgr->GetPlayerByLowGUID(GUIDLow))
        return player->GetLifetime2v2Wins();
    else
    {
        QueryResult result = CharacterDatabase.PQuery("SELECT Lifetime2v2Wins FROM character_pvp_stats WHERE guid = '%u'", GUIDLow);
        if (!result)
            return 0;

        Field* fields = result->Fetch();
        return fields[0].GetUInt16();
    }
}

void PvPMgr::SetLifetime2v2WinsByGUIDLow(uint32 GUIDLow, uint16 wins)
{
    if (Player* player = sObjectMgr->GetPlayerByLowGUID(GUIDLow))
        player->SetLifetime2v2Wins(wins);

    CharacterDatabase.PExecute("UPDATE character_pvp_stats SET Lifetime2v2Wins = '%u' WHERE guid = '%u'", wins, GUIDLow);
}

uint16 PvPMgr::GetLifetime2v2GamesByGUIDLow(uint32 GUIDLow) const
{
    if (Player* player = sObjectMgr->GetPlayerByLowGUID(GUIDLow))
        return player->GetLifetime2v2Games();
    else
    {
        QueryResult result = CharacterDatabase.PQuery("SELECT Lifetime2v2Games FROM character_pvp_stats WHERE guid = '%u'", GUIDLow);
        if (!result)
            return 0;

        Field* fields = result->Fetch();
        return fields[0].GetUInt16();
    }
}

void PvPMgr::SetLifetime2v2GamesByGUIDLow(uint32 GUIDLow, uint16 games)
{
    if (Player* player = sObjectMgr->GetPlayerByLowGUID(GUIDLow))
        player->SetLifetime2v2Games(games);

    CharacterDatabase.PExecute("UPDATE character_pvp_stats SET Lifetime2v2Games = '%u' WHERE guid = '%u'", games, GUIDLow);
}

uint16 PvPMgr::GetLifetime3v3RatingByGUIDLow(uint32 GUIDLow) const
{
    if (Player* player = sObjectMgr->GetPlayerByLowGUID(GUIDLow))
        return player->GetLifetime3v3Rating();
    else
    {
        QueryResult result = CharacterDatabase.PQuery("SELECT Lifetime3v3Rating FROM character_pvp_stats WHERE guid = '%u'", GUIDLow);
        if (!result)
            return 0;

        Field* fields = result->Fetch();
        return fields[0].GetUInt16();
    }
}

void PvPMgr::SetLifetime3v3RatingByGUIDLow(uint32 GUIDLow, uint16 rating)
{
    if (Player* player = sObjectMgr->GetPlayerByLowGUID(GUIDLow))
        player->SetLifetime3v3Rating(rating);

    CharacterDatabase.PExecute("UPDATE character_pvp_stats SET Lifetime3v3Rating = '%u' WHERE guid = '%u'", rating, GUIDLow);
}

uint16 PvPMgr::GetLifetime3v3MMRByGUIDLow(uint32 GUIDLow) const
{
    if (Player* player = sObjectMgr->GetPlayerByLowGUID(GUIDLow))
        return player->GetLifetime3v3MMR();
    else
    {
        QueryResult result = CharacterDatabase.PQuery("SELECT Lifetime3v3MMR FROM character_pvp_stats WHERE guid = '%u'", GUIDLow);
        if (!result)
            return 0;

        Field* fields = result->Fetch();
        return fields[0].GetUInt16();
    }
}

void PvPMgr::SetLifetime3v3MMRByGUIDLow(uint32 GUIDLow, uint16 mmr)
{
    if (Player* player = sObjectMgr->GetPlayerByLowGUID(GUIDLow))
        player->SetLifetime3v3MMR(mmr);

    CharacterDatabase.PExecute("UPDATE character_pvp_stats SET Lifetime3v3MMR = '%u' WHERE guid = '%u'", mmr, GUIDLow);
}

uint16 PvPMgr::GetLifetime3v3WinsByGUIDLow(uint32 GUIDLow) const
{
    if (Player* player = sObjectMgr->GetPlayerByLowGUID(GUIDLow))
        return player->GetLifetime3v3Wins();
    else
    {
        QueryResult result = CharacterDatabase.PQuery("SELECT Lifetime3v3Wins FROM character_pvp_stats WHERE guid = '%u'", GUIDLow);
        if (!result)
            return 0;

        Field* fields = result->Fetch();
        return fields[0].GetUInt16();
    }
}

void PvPMgr::SetLifetime3v3WinsByGUIDLow(uint32 GUIDLow, uint16 wins)
{
    if (Player* player = sObjectMgr->GetPlayerByLowGUID(GUIDLow))
        player->SetLifetime3v3Wins(wins);

    CharacterDatabase.PExecute("UPDATE character_pvp_stats SET Lifetime3v3Wins = '%u' WHERE guid = '%u'", wins, GUIDLow);
}

uint16 PvPMgr::GetLifetime3v3GamesByGUIDLow(uint32 GUIDLow) const
{
    if (Player* player = sObjectMgr->GetPlayerByLowGUID(GUIDLow))
        return player->GetLifetime3v3Games();
    else
    {
        QueryResult result = CharacterDatabase.PQuery("SELECT Lifetime3v3Games FROM character_pvp_stats WHERE guid = '%u'", GUIDLow);
        if (!result)
            return 0;

        Field* fields = result->Fetch();
        return fields[0].GetUInt16();
    }
}

void PvPMgr::SetLifetime3v3GamesByGUIDLow(uint32 GUIDLow, uint16 games)
{
    if (Player* player = sObjectMgr->GetPlayerByLowGUID(GUIDLow))
        player->SetLifetime3v3Games(games);

    CharacterDatabase.PExecute("UPDATE character_pvp_stats SET Lifetime3v3Games = '%u' WHERE guid = '%u'", games, GUIDLow);
}

uint16 PvPMgr::GetLifetime5v5RatingByGUIDLow(uint32 GUIDLow) const
{
    if (Player* player = sObjectMgr->GetPlayerByLowGUID(GUIDLow))
        return player->GetLifetime5v5Rating();
    else
    {
        QueryResult result = CharacterDatabase.PQuery("SELECT Lifetime5v5Rating FROM character_pvp_stats WHERE guid = '%u'", GUIDLow);
        if (!result)
            return 0;

        Field* fields = result->Fetch();
        return fields[0].GetUInt16();
    }
}

void PvPMgr::SetLifetime5v5RatingByGUIDLow(uint32 GUIDLow, uint16 rating)
{
    if (Player* player = sObjectMgr->GetPlayerByLowGUID(GUIDLow))
        player->SetLifetime5v5Rating(rating);

    CharacterDatabase.PExecute("UPDATE character_pvp_stats SET Lifetime5v5Rating = '%u' WHERE guid = '%u'", rating, GUIDLow);
}

uint16 PvPMgr::GetLifetime5v5MMRByGUIDLow(uint32 GUIDLow) const
{
    if (Player* player = sObjectMgr->GetPlayerByLowGUID(GUIDLow))
        return player->GetLifetime5v5MMR();
    else
    {
        QueryResult result = CharacterDatabase.PQuery("SELECT Lifetime5v5MMR FROM character_pvp_stats WHERE guid = '%u'", GUIDLow);
        if (!result)
            return 0;

        Field* fields = result->Fetch();
        return fields[0].GetUInt16();
    }
}

void PvPMgr::SetLifetime5v5MMRByGUIDLow(uint32 GUIDLow, uint16 mmr)
{
    if (Player* player = sObjectMgr->GetPlayerByLowGUID(GUIDLow))
        player->SetLifetime5v5MMR(mmr);

    CharacterDatabase.PExecute("UPDATE character_pvp_stats SET Lifetime5v5MMR = '%u' WHERE guid = '%u'", mmr, GUIDLow);
}

uint16 PvPMgr::GetLifetime5v5WinsByGUIDLow(uint32 GUIDLow) const
{
    if (Player* player = sObjectMgr->GetPlayerByLowGUID(GUIDLow))
        return player->GetLifetime5v5Wins();
    else
    {
        QueryResult result = CharacterDatabase.PQuery("SELECT Lifetime5v5Wins FROM character_pvp_stats WHERE guid = '%u'", GUIDLow);
        if (!result)
            return 0;

        Field* fields = result->Fetch();
        return fields[0].GetUInt16();
    }
}

void PvPMgr::SetLifetime5v5WinsByGUIDLow(uint32 GUIDLow, uint16 wins)
{
    if (Player* player = sObjectMgr->GetPlayerByLowGUID(GUIDLow))
        player->SetLifetime5v5Wins(wins);

    CharacterDatabase.PExecute("UPDATE character_pvp_stats SET Lifetime5v5Wins = '%u' WHERE guid = '%u'", wins, GUIDLow);
}

uint16 PvPMgr::GetLifetime5v5GamesByGUIDLow(uint32 GUIDLow) const
{
    if (Player* player = sObjectMgr->GetPlayerByLowGUID(GUIDLow))
        return player->GetLifetime5v5Games();
    else
    {
        QueryResult result = CharacterDatabase.PQuery("SELECT Lifetime5v5Games FROM character_pvp_stats WHERE guid = '%u'", GUIDLow);
        if (!result)
            return 0;

        Field* fields = result->Fetch();
        return fields[0].GetUInt16();
    }
}

void PvPMgr::SetLifetime5v5GamesByGUIDLow(uint32 GUIDLow, uint16 games)
{
    if (Player* player = sObjectMgr->GetPlayerByLowGUID(GUIDLow))
        player->SetLifetime5v5Games(games);

    CharacterDatabase.PExecute("UPDATE character_pvp_stats SET Lifetime5v5Games = '%u' WHERE guid = '%u'", games, GUIDLow);
}
