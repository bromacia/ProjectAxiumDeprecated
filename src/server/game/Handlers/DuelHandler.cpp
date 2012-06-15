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

#include "Common.h"
#include "WorldPacket.h"
#include "WorldSession.h"
#include "Log.h"
#include "Opcodes.h"
#include "UpdateData.h"
#include "Player.h"

void WorldSession::HandleDuelAcceptedOpcode(WorldPacket& recvPacket)
{
    uint64 guid;
    Player* player;
    Player* plTarget;

    recvPacket >> guid;

    if (!GetPlayer()->duel)                                  // ignore accept from duel-sender
        return;

    player       = GetPlayer();
    plTarget = player->duel->opponent;

    if (player == player->duel->initiator || !plTarget || player == plTarget || player->duel->startTime != 0 || plTarget->duel->startTime != 0)
        return;

    //sLog->outDebug(LOG_FILTER_PACKETIO, "WORLD: Received CMSG_DUEL_ACCEPTED");
    sLog->outStaticDebug("Player 1 is: %u (%s)", player->GetGUIDLow(), player->GetName());
    sLog->outStaticDebug("Player 2 is: %u (%s)", plTarget->GetGUIDLow(), plTarget->GetName());

    time_t now = time(NULL);
    player->duel->startTimer = now;
    plTarget->duel->startTimer = now;

    player->SendDuelCountdown(3000);
    plTarget->SendDuelCountdown(3000);
    if (player->GetMapId() == 530 || plTarget->GetMapId() == 530)
        return;
    player->RemoveAura(41425); // Remove Hypothermia Debuff
    plTarget->RemoveAura(41425);
    player->RemoveAura(25771); // Remove Forbearance Debuff
    plTarget->RemoveAura(25771);
    player->RemoveAura(57724); // Remove Sated Debuff
    plTarget->RemoveAura(57724);
    player->RemoveAura(57723); // Remove Exhaustion Debuff
    plTarget->RemoveAura(57723);
    player->RemoveAura(66233); // Remove Ardent Defender Debuff
    plTarget->RemoveAura(66233);
    player->RemoveAura(11196); // Remove Recently Bandaged Debuff
    plTarget->RemoveAura(11196);
    player->SetHealth(player->GetMaxHealth());
    player->SetPower(POWER_MANA, player->GetMaxPower(POWER_MANA));
    plTarget->SetHealth(plTarget->GetMaxHealth());
    plTarget->SetPower(POWER_MANA,  plTarget->GetMaxPower(POWER_MANA));
    player->SetPower(POWER_RAGE, 0);
    plTarget->SetPower(POWER_RAGE, 0);
    player->RemoveArenaSpellCooldowns();
    plTarget->RemoveArenaSpellCooldowns();
    player->AddAura(80864, player);
    plTarget->AddAura(80864, plTarget);
    if (player->getClass() == CLASS_WARLOCK && !player->HasItemCount(36892, 1, true))
        player->AddItem(36892, 1);
    if (plTarget->getClass() == CLASS_WARLOCK && !plTarget->HasItemCount(36892, 1, true))
        plTarget->AddItem(36892, 1);
}

void WorldSession::HandleDuelCancelledOpcode(WorldPacket& recvPacket)
{
    sLog->outDebug(LOG_FILTER_NETWORKIO, "WORLD: Received CMSG_DUEL_CANCELLED");
    uint64 guid;
    recvPacket >> guid;

    // no duel requested
    if (!GetPlayer()->duel)
        return;

    // player surrendered in a duel using /forfeit
    if (GetPlayer()->duel->startTime != 0)
    {
        GetPlayer()->CombatStopWithPets(true);
        if (GetPlayer()->duel->opponent)
            GetPlayer()->duel->opponent->CombatStopWithPets(true);

        GetPlayer()->CastSpell(GetPlayer(), 7267, true);    // beg
        GetPlayer()->DuelComplete(DUEL_WON);
        return;
    }

    GetPlayer()->DuelComplete(DUEL_INTERRUPTED);
}
