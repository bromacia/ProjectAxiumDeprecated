#include "PvPMgr.h"
#include "Player.h"
#include "Battleground.h"
#include "ObjectMgr.h"
#include "Chat.h"

PvPMgr::PvPMgr()
{
    handler = NULL;
}

PvPMgr::~PvPMgr()
{
}

void PvPMgr::HandleDealDamage(Unit* attacker, Player* victim, uint32 damage)
{
    if (!attacker || !victim || !damage)
        return;

    if (attacker == victim)
        return;

    Player* pAttacker = NULL;

    if (Player* player = attacker->ToPlayer())
        pAttacker = player;
    else if (Unit* owner = attacker->GetCharmerOrOwner())
        if (Player* pOwner = owner->ToPlayer())
            pAttacker = pOwner;

    if (!pAttacker)
        return;

    if (pAttacker->IsHealingSpec())
        return;

    if ((!pAttacker->InBattleground() || !victim->InBattleground()) && (!pAttacker->IsInWorldPvPZone() || !victim->IsInWorldPvPZone()))
        return;

    if (pAttacker->IsDueling() || victim->IsDueling())
        return;

    uint32 LastDamageDealtCountdownTime = getMSTime() + DAMAGE_RESET_TIME_MS;

    if (victim->PvPTargetDamageInfo.empty())
    {
        PvPTargetDamageInformation m_PvPTargetDamageInfo;
        m_PvPTargetDamageInfo.DamageDoneToVictim += damage;
        m_PvPTargetDamageInfo.LastDamageDealtTimer = LastDamageDealtCountdownTime;
        victim->PvPTargetDamageInfo[pAttacker->GetGUIDLow()] = m_PvPTargetDamageInfo;
        return;
    }

    Player::PvPTargetDamageInformationMap pvpTargetDmgInfo = victim->PvPTargetDamageInfo;
    for (Player::PvPTargetDamageInformationMap::iterator itr = pvpTargetDmgInfo.begin(); itr != pvpTargetDmgInfo.end(); ++itr)
    {
        if (pAttacker->GetGUIDLow() == itr->first)
        {
            itr->second.DamageDoneToVictim += damage;
            itr->second.LastDamageDealtTimer = LastDamageDealtCountdownTime;
            return;
        }
    }
}

void PvPMgr::HandleNormalPvPKill(Player* victim)
{
    if (!victim)
        return;

    uint32 currentMSTime = getMSTime();
    uint32 attackerGUIDLow = 0;
    uint32 highestDamageDoneToVictim = 0;
    uint32 lastDamageDealtTime = 0;

    if (victim->PvPTargetDamageInfo.empty())
        return;

    Player::PvPTargetDamageInformationMap pvpTargetDmgInfo = victim->PvPTargetDamageInfo;
    for (Player::PvPTargetDamageInformationMap::iterator itr = pvpTargetDmgInfo.begin(); itr != pvpTargetDmgInfo.end(); ++itr)
    {
        if (itr->second.LastDamageDealtTimer > currentMSTime)
        {
            if (itr->second.DamageDoneToVictim > highestDamageDoneToVictim)
            {
                attackerGUIDLow = itr->first;
                highestDamageDoneToVictim = itr->second.DamageDoneToVictim;
                lastDamageDealtTime = itr->second.LastDamageDealtTimer;
            }
            else if (itr->second.DamageDoneToVictim = highestDamageDoneToVictim)
            {
                if (itr->second.LastDamageDealtTimer > lastDamageDealtTime)
                {
                    attackerGUIDLow = itr->first;
                    highestDamageDoneToVictim = itr->second.DamageDoneToVictim;
                    lastDamageDealtTime = itr->second.LastDamageDealtTimer;
                }
                else if (itr->second.LastDamageDealtTimer = lastDamageDealtTime)
                {
                    if (sObjectMgr->GetPlayerByLowGUID(itr->first)->GetPvPRating() >= sObjectMgr->GetPlayerByLowGUID(attackerGUIDLow)->GetPvPRating())
                    {
                        attackerGUIDLow = itr->first;
                        highestDamageDoneToVictim = itr->second.DamageDoneToVictim;
                        lastDamageDealtTime = itr->second.LastDamageDealtTimer;
                    }
                }
            }
        }

        victim->PvPTargetDamageInfo.erase(itr->first);
    }

    if (!attackerGUIDLow || !highestDamageDoneToVictim || !lastDamageDealtTime)
        return;

    uint8 ratingGain = 0;
    uint8 ratingLoss = 0;
    uint32 victimGUIDLow = victim->GetGUIDLow();
    uint16 attackerPvPRating = GetPvPRatingByGUIDLow(attackerGUIDLow);
    uint16 victimPvPRating = GetPvPRatingByGUIDLow(victimGUIDLow);

    if (victimPvPRating)
        ratingGain = victimPvPRating / 100;
    else
        ratingGain = 10;

    if (ratingGain < 10)
        ratingGain = 10;

    if (attackerPvPRating > 2000)
        ApplyRatingMultipliers(attackerPvPRating, ratingGain, true);

    if (ratingGain > 100)
        ratingGain = 100;

    if (ratingGain)
    {
        SetPvPRatingByGUIDLow(attackerGUIDLow, attackerPvPRating + ratingGain);

        if (Player* attacker = sObjectMgr->GetPlayerByLowGUID(attackerGUIDLow))
            if (attacker->HasPvPNotificationsEnabled())
            {
                handler = new ChatHandler(attacker);
                handler->PSendSysMessage("You have been awarded %u PvP rating for killing %s.", ratingGain, victim->GetName());
            }
    }

    if (victimPvPRating > 1000)
    {
        if (attackerPvPRating)
        {
            float fRatingLoss = attackerPvPRating - victimPvPRating;
            fRatingLoss = fabs(fRatingLoss);
            fRatingLoss /= 100;
            ratingLoss = fRatingLoss;
        }
        else
            ratingLoss = 5;

        if (ratingLoss < 5)
            ratingLoss = 5;

        ApplyRatingMultipliers(victimPvPRating, ratingLoss, false);

        if (ratingLoss > 100)
            ratingLoss = 100;

        if (ratingLoss)
        {
            SetPvPRatingByGUIDLow(victimGUIDLow, victimPvPRating - ratingLoss);

            if (victim->HasPvPNotificationsEnabled())
            {
                std::string attackerName = "";
                sObjectMgr->GetPlayerNameByGUIDLow(attackerGUIDLow, attackerName);
                handler = new ChatHandler(victim);
                handler->PSendSysMessage("You have been deducted %u PvP rating for being killed by %s.", ratingLoss, attackerName);
            }
        }
    }
}

void PvPMgr::HandleOneShotPvPKill(Unit* attacker, Player* victim)
{
    if (!attacker || !victim)
        return;

    if (attacker->GetGUID() == victim->GetGUID())
    {
        HandleNormalPvPKill(victim);
        return;
    }

    Player* pAttacker = NULL;

    if (Player* player = attacker->ToPlayer())
        pAttacker = player;
    else if (Unit* owner = attacker->GetCharmerOrOwner())
        if (Player* pOwner = owner->ToPlayer())
            pAttacker = pOwner;

    if (!pAttacker)
        return;

    if (pAttacker->IsHealingSpec())
    {
        HandleNormalPvPKill(victim);
        return;
    }

    victim->PvPTargetDamageInfo.clear();

    uint8 ratingGain = 0;
    uint8 ratingLoss = 0;
    uint32 attackerGUIDLow = pAttacker->GetGUIDLow();
    uint32 victimGUIDLow = victim->GetGUIDLow();
    uint16 attackerPvPRating = GetPvPRatingByGUIDLow(attackerGUIDLow);
    uint16 victimPvPRating = GetPvPRatingByGUIDLow(victimGUIDLow);

    if (victimPvPRating)
        ratingGain = victimPvPRating / 100;
    else
        ratingGain = 10;

    if (ratingGain < 10)
        ratingGain = 10;

    if (attackerPvPRating > 2000)
        ApplyRatingMultipliers(attackerPvPRating, ratingGain, true);

    if (ratingGain > 100)
        ratingGain = 100;

    if (ratingGain)
    {
        SetPvPRatingByGUIDLow(attackerGUIDLow, attackerPvPRating + ratingGain);

        if (pAttacker->HasPvPNotificationsEnabled())
        {
            handler = new ChatHandler(pAttacker);
            handler->PSendSysMessage("You have been awarded %u PvP rating for killing %s.", ratingGain, victim->GetName());
        }
    }

    if (victimPvPRating > 1000)
    {
        if (attackerPvPRating)
        {
            float fRatingLoss = attackerPvPRating - victimPvPRating;
            fRatingLoss = fabs(fRatingLoss);
            fRatingLoss /= 100;
            ratingLoss = fRatingLoss;
        }
        else
            ratingLoss = 5;

        if (ratingLoss < 5)
            ratingLoss = 5;

        ApplyRatingMultipliers(victimPvPRating, ratingLoss, false);

        if (ratingLoss > 100)
            ratingLoss = 100;

        if (ratingLoss)
        {
            SetPvPRatingByGUIDLow(victimGUIDLow, victimPvPRating - ratingLoss);

            if (victim->HasPvPNotificationsEnabled())
            {
                std::string attackerName = "";
                sObjectMgr->GetPlayerNameByGUIDLow(attackerGUIDLow, attackerName);
                handler = new ChatHandler(victim);
                handler->PSendSysMessage("You have been deducted %u PvP rating for being killed by %s.", ratingLoss, attackerName);
            }
        }
    }
}

void PvPMgr::HandleBattlegroundHonorableKill(Player* player)
{
    if (!player->IsHealingSpec())
        return;

    uint16 pvpRating = player->GetPvPRating();
    SetPvPRatingByGUIDLow(player->GetGUIDLow(), ++pvpRating);

    if (player->HasPvPNotificationsEnabled())
    {
        handler = new ChatHandler(player);
        handler->PSendSysMessage("You have been awarded 1 PvP rating for assisting in an honorable kill.");
    }
}

void PvPMgr::HandleBattlegroundEnd(Battleground* bg)
{
    if (!bg)
        return;

    TeamId winningTeam = GetWinningTeamIdByBGWinner(bg->GetWinner());
    if (winningTeam == TEAM_NEUTRAL)
        return;

    Battleground::BattlegroundPlayerMap m_Players = bg->GetPlayers();
    for (Battleground::BattlegroundPlayerMap::iterator itr = m_Players.begin(); itr != m_Players.end(); ++itr)
    {
        if (Player* player = ObjectAccessor::FindPlayer(itr->first))
        {
            uint16 pvpRating = player->GetPvPRating();

            if (player->GetTeamId() == winningTeam)
            {
                uint8 ratingGain = BG_RATING_GAIN;
                if (pvpRating > 2000)
                    ApplyRatingMultipliers(pvpRating, ratingGain, true);
                SetPvPRatingByGUIDLow(player->GetGUIDLow(), pvpRating + ratingGain);

                if (player->HasPvPNotificationsEnabled())
                {
                    handler = new ChatHandler(player);
                    handler->PSendSysMessage("You have been awarded %u PvP rating for winning the battleground.", ratingGain);
                }
            }
            else if (pvpRating > 1000)
            {
                uint8 ratingLoss = BG_RATING_LOSS;
                ApplyRatingMultipliers(pvpRating, ratingLoss, false);
                SetPvPRatingByGUIDLow(player->GetGUIDLow(), pvpRating - ratingLoss);

                if (player->HasPvPNotificationsEnabled())
                {
                    handler = new ChatHandler(player);
                    handler->PSendSysMessage("You have been deducted %u PvP rating for losing the battleground.", ratingLoss);
                }
            }
        }
    }
}

void PvPMgr::HandleTwinSpireCapture(TeamId team)
{
}

void PvPMgr::ApplyRatingMultipliers(uint16 pvpRating, uint8 &ratingChange, bool gain)
{
    uint8 uChange = ratingChange;
    float fChange = 0;

    if (gain)
    {
        if (pvpRating >= 10000)
        {
            ratingChange = 0;
            return;
        }

        fChange = pvpRating;
        fChange /= 100;
        fChange -= 100;
        fChange = fabs(fChange);
        fChange /= 100;
        fChange *= uChange;
        ratingChange = fChange;
    }
    else
    {
        fChange = pvpRating;
        fChange /= 10000;
        fChange *= uChange;
        ratingChange = fChange;
    }
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

        return (*result)[0].GetUInt16();
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

        return (*result)[0].GetUInt16();
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

        return (*result)[0].GetUInt16();
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

        return (*result)[0].GetUInt16();
    }
}

void PvPMgr::SetPvPRatingByGUIDLow(uint32 GUIDLow, uint16 rating)
{
    if (Player* player = sObjectMgr->GetPlayerByLowGUID(GUIDLow))
        player->SetPvPRating(rating);

    CharacterDatabase.PExecute("UPDATE character_pvp_stats SET PvPRating = '%u' WHERE guid = '%u'", rating, GUIDLow);

    if (rating > GetLifetimePvPRatingByGUIDLow(GUIDLow))
        SetLifetimePvPRatingByGUIDLow(GUIDLow, rating);
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

        return (*result)[0].GetUInt16();
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

        return (*result)[0].GetUInt16();
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

        return (*result)[0].GetUInt16();
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

        return (*result)[0].GetUInt16();
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

        return (*result)[0].GetUInt16();
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

        return (*result)[0].GetUInt16();
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

        return (*result)[0].GetUInt16();
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

        return (*result)[0].GetUInt16();
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

        return (*result)[0].GetUInt16();
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

        return (*result)[0].GetUInt16();
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

        return (*result)[0].GetUInt16();
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

        return (*result)[0].GetUInt16();
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

        return (*result)[0].GetUInt16();
    }
}

void PvPMgr::SetLifetime5v5GamesByGUIDLow(uint32 GUIDLow, uint16 games)
{
    if (Player* player = sObjectMgr->GetPlayerByLowGUID(GUIDLow))
        player->SetLifetime5v5Games(games);

    CharacterDatabase.PExecute("UPDATE character_pvp_stats SET Lifetime5v5Games = '%u' WHERE guid = '%u'", games, GUIDLow);
}
