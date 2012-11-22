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

    recvPacket >> guid;

    if (!GetPlayer()->duel)
        return;

    Player* player = GetPlayer();
    Player* plTarget = GetPlayer()->duel->opponent;

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

    if (player->GetAreaId() != 85 || plTarget->GetAreaId() != 85)
        return;

    player->RemoveAllNegativeAuras();
    plTarget->RemoveAllNegativeAuras();
    player->SetHealth(player->GetMaxHealth());
    plTarget->SetHealth(plTarget->GetMaxHealth());
    player->SetPower(POWER_MANA, player->GetMaxPower(POWER_MANA));
    plTarget->SetPower(POWER_MANA,  plTarget->GetMaxPower(POWER_MANA));
    player->SetPower(POWER_ENERGY, player->GetMaxPower(POWER_ENERGY));
    plTarget->SetPower(POWER_ENERGY,  plTarget->GetMaxPower(POWER_ENERGY));
    player->SetPower(POWER_RAGE, 0);
    plTarget->SetPower(POWER_RAGE, 0);
    player->SetPower(POWER_RUNIC_POWER, 0);
    plTarget->SetPower(POWER_RUNIC_POWER, 0);
    player->RemoveAllPlayerSpellCooldowns();
    plTarget->RemoveAllPlayerSpellCooldowns();
    player->AddAura(80864, player);
    plTarget->AddAura(80864, plTarget);
    player->ClearDiminishings();
    plTarget->ClearDiminishings();
    player->ClearComboPoints();
    plTarget->ClearComboPoints();
    player->ClearInCombat();
    plTarget->ClearInCombat();
    player->getHostileRefManager().deleteReferences();
    plTarget->getHostileRefManager().deleteReferences();

    if (Pet* playerPet = player->GetPet())
    {
        playerPet->RemoveAllNegativeAuras();
        playerPet->SetHealth(playerPet->GetMaxHealth());
        playerPet->SetPower(POWER_MANA, playerPet->GetMaxPower(POWER_MANA));
        playerPet->SetPower(POWER_FOCUS, playerPet->GetMaxPower(POWER_FOCUS));
        playerPet->RemoveAllPetSpellCooldowns(player);
        playerPet->ClearDiminishings();
        playerPet->ClearInCombat();
        playerPet->getHostileRefManager().deleteReferences();
    }

    if (Pet* plTargetPet = plTarget->GetPet())
    {
        plTargetPet->RemoveAllNegativeAuras();
        plTargetPet->SetHealth(plTargetPet->GetMaxHealth());
        plTargetPet->SetPower(POWER_MANA, plTargetPet->GetMaxPower(POWER_MANA));
        plTargetPet->SetPower(POWER_FOCUS, plTargetPet->GetMaxPower(POWER_FOCUS));
        plTargetPet->RemoveAllPetSpellCooldowns(plTarget);
        plTargetPet->ClearDiminishings();
        plTargetPet->ClearInCombat();
        plTargetPet->getHostileRefManager().deleteReferences();
    }
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

        GetPlayer()->CastSpell(GetPlayer(), 7267, true); // Grovel
        GetPlayer()->DuelComplete(DUEL_WON);
        return;
    }

    GetPlayer()->DuelComplete(DUEL_INTERRUPTED);
}
