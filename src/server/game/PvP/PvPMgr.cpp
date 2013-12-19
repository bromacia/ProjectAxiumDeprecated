#include "PvPMgr.h"
#include "Player.h"
#include "Battleground.h"
#include "ObjectMgr.h"
#include "Chat.h"

PvPMgr::PvPMgr()
{
}

PvPMgr::~PvPMgr()
{
}

uint8 PvPMgr::CalculatePvPRating(uint16 attackerRating, uint16 victimRating, bool gain)
{
    uint8 ratingChange = 0;

    if (gain)
    {
        if (victimRating)
            ratingChange = victimRating / 100;
        else
            ratingChange = 10;

        if (ratingChange < 10)
            ratingChange = 10;

        if (attackerRating > 2000)
            ratingChange = ApplyPvPRatingMultipliers((float)attackerRating, ratingChange, true);
    }
    else
    {
        if (victimRating <= 1000)
            return 0;

        if (victimRating)
            ratingChange = victimRating / 100;
        else
            ratingChange = 5;

        if (ratingChange < 5)
            ratingChange = 5;

        ratingChange = ApplyPvPRatingMultipliers((float)victimRating, ratingChange, false);
    }

    if (ratingChange > 100)
        ratingChange = 100;

    return ratingChange;
}

uint8 PvPMgr::ApplyPvPRatingMultipliers(float rating, uint8 ratingChange, bool gain)
{
    float ratingMod = 0;

    if (gain)
    {
        if (rating >= 10000)
            return 0;

        ratingMod = ((100 - (rating / 100)) / 100);
        return ratingChange *= ratingMod;
    }
    else
    {
        ratingMod = rating / 10000;
        return ratingChange *= ratingMod;
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
