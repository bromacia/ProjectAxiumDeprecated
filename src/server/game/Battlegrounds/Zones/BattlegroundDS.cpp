/*
 * Copyright (C) 2008-2012 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2005-2009 MaNGOS <http://getmangos.com/>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "Battleground.h"
#include "BattlegroundDS.h"
#include "Language.h"
#include "Player.h"
#include "Object.h"
#include "ObjectMgr.h"
#include "WorldPacket.h"

BattlegroundDS::BattlegroundDS()
{
    m_BgObjects.resize(BG_DS_OBJECT_MAX);

    m_StartDelayTimes[BG_STARTING_EVENT_FIRST]  = BG_START_DELAY_1M;
    m_StartDelayTimes[BG_STARTING_EVENT_SECOND] = BG_START_DELAY_30S;
    m_StartDelayTimes[BG_STARTING_EVENT_THIRD]  = BG_START_DELAY_15S;
    m_StartDelayTimes[BG_STARTING_EVENT_FOURTH] = BG_START_DELAY_NONE;
    //we must set messageIds
    m_StartMessageIds[BG_STARTING_EVENT_FIRST]  = LANG_ARENA_ONE_MINUTE;
    m_StartMessageIds[BG_STARTING_EVENT_SECOND] = LANG_ARENA_THIRTY_SECONDS;
    m_StartMessageIds[BG_STARTING_EVENT_THIRD]  = LANG_ARENA_FIFTEEN_SECONDS;
    m_StartMessageIds[BG_STARTING_EVENT_FOURTH] = LANG_ARENA_HAS_BEGUN;
}

BattlegroundDS::~BattlegroundDS()
{

}

void BattlegroundDS::PostUpdateImpl(uint32 diff)
{
}

void BattlegroundDS::StartingEventCloseDoors()
{
    for (uint8 i = BG_DS_OBJECT_DOOR_1; i <= BG_DS_OBJECT_DOOR_2; ++i)
        SpawnBGObject(i, RESPAWN_IMMEDIATELY);
}

void BattlegroundDS::StartingEventOpenDoors()
{
    for (uint8 i = BG_DS_OBJECT_DOOR_1; i <= BG_DS_OBJECT_DOOR_2; ++i)
        DoorOpen(i);

    for (uint8 i = BG_DS_OBJECT_BUFF_1; i <= BG_DS_OBJECT_BUFF_2; ++i)
        SpawnBGObject(i, 60);
}

void BattlegroundDS::AddPlayer(Player* player)
{
    Battleground::AddPlayer(player);
    //create score and add it to map, default values are set in constructor
    BattlegroundDSScore* sc = new BattlegroundDSScore;

    m_PlayerScores[player->GetGUID()] = sc;

    UpdateArenaWorldState();
}

void BattlegroundDS::RemovePlayer(Player* /*player*/, uint64 /*guid*/, uint32 /*team*/)
{
    if (GetStatus() == STATUS_WAIT_LEAVE)
        return;

    UpdateArenaWorldState();
    CheckArenaWinConditions();
}

void BattlegroundDS::HandleKillPlayer(Player* player, Player* killer)
{
    if (GetStatus() != STATUS_IN_PROGRESS)
        return;

    if (!killer)
    {
        sLog->outError("BattlegroundDS: Killer player not found");
        return;
    }

    Battleground::HandleKillPlayer(player, killer);

    UpdateArenaWorldState();
    CheckArenaWinConditions();
}

void BattlegroundDS::HandleAreaTrigger(Player* Source, uint32 Trigger)
{
    if (GetStatus() != STATUS_IN_PROGRESS)
        return;

    switch (Trigger)
    {
        case 5347:
        case 5348:
            break;
        default:
            sLog->outError("WARNING: Unhandled AreaTrigger in Battleground: %u", Trigger);
            Source->GetSession()->SendAreaTriggerMessage("Warning: Unhandled AreaTrigger in Battleground: %u", Trigger);
            break;
    }
}

bool BattlegroundDS::HandlePlayerUnderMap(Player* player)
{
    player->TeleportTo(GetMapId(), 1299.046f, 784.825f, 9.338f, 2.422f, false);
    return true;
}

void BattlegroundDS::FillInitialWorldStates(WorldPacket &data)
{
    data << uint32(3610) << uint32(1);                                              // 9 show
    UpdateArenaWorldState();
}

void BattlegroundDS::Reset()
{
    //call parent's class reset
    Battleground::Reset();
}

bool BattlegroundDS::SetupBattleground()
{
    // Gates
    if (!AddObject(BG_DS_OBJECT_DOOR_1, BG_DS_OBJECT_TYPE_DOOR_1, 1350.95f, 817.2f, 20.8096f, 3.15f, 0, 0, 0.99627f, 0.0862864f, RESPAWN_IMMEDIATELY) ||
        !AddObject(BG_DS_OBJECT_DOOR_2, BG_DS_OBJECT_TYPE_DOOR_2, 1232.65f, 764.913f, 20.0729f, 6.3f, 0, 0, 0.0310211f, -0.999519f, RESPAWN_IMMEDIATELY) ||
    // Buffs
        !AddObject(BG_DS_OBJECT_BUFF_1, BG_DS_OBJECT_TYPE_BUFF_1, 1330.056763f, 765.579285f, 3.159700f, 0, 0, 0, 0.730314f, -0.683111f, 120) ||
        !AddObject(BG_DS_OBJECT_BUFF_2, BG_DS_OBJECT_TYPE_BUFF_2, 1254.318237f, 816.529175f, 3.158578f, 0, 0, 0, 0.700409f, 0.713742f, 120) ||
    // Ready Markers
        !AddObject(BG_DS_OBJECT_READY_MARKER_A, BG_OBJECTID_READY_MARKER, 1230.58f, 760.11f, 17.06f, 3.11f, 0, 0, 0, 0, RESPAWN_IMMEDIATELY) ||
        !AddObject(BG_DS_OBJECT_READY_MARKER_B, BG_OBJECTID_READY_MARKER, 1352.74f, 822.0f, 17.17f, 6.26f, 0, 0, 0, 0, RESPAWN_IMMEDIATELY))
    {
        sLog->outErrorDb("BatteGroundDS: Failed to spawn some object!");
        return false;
    }

    return true;
}
