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

    Player *players[2] = { GetPlayer(), GetPlayer()->duel->opponent };

    if (!players[0] || !players[1] || players[0] == players[1] || players[0] == players[0]->duel->initiator || players[0]->duel->startTime != 0 || players[1]->duel->startTime != 0)
        return;

    sLog->outStaticDebug("Player 1 is: %u (%s)", players[0]->GetGUIDLow(), players[0]->GetName());
    sLog->outStaticDebug("Player 2 is: %u (%s)", players[1]->GetGUIDLow(), players[1]->GetName());

    time_t now = time(NULL);

    for (uint8 i = 0; i < 2; ++i)
    {
        players[i]->duel->startTimer = now;
        players[i]->SendDuelCountdown(3000);
        players[i]->SetIsDueling(true);

        bool reset = false;

        if (players[0]->GetAreaId() == 85 || players[1]->GetAreaId() == 85)
            reset = true;

        if (reset)
        {
            players[i]->RemoveAllNegativeAuras();
            players[i]->SetHealth(players[i]->GetMaxHealth());
            players[i]->SetPower(POWER_MANA, players[i]->GetMaxPower(POWER_MANA));
            players[i]->SetPower(POWER_ENERGY, players[i]->GetMaxPower(POWER_ENERGY));
            players[i]->SetPower(POWER_RAGE, 0);
            players[i]->SetPower(POWER_RUNIC_POWER, 0);
            players[i]->RemoveAllPlayerSpellCooldowns();
            players[i]->ClearDiminishings();
            players[i]->ClearComboPoints();
            players[i]->ClearInCombat();
            players[i]->getHostileRefManager().deleteReferences();
            players[i]->RemoveAllTempSummons();

            if (Pet* playerPet = players[i]->GetPet())
            {
                playerPet->SetIsDueling(true);

                if (reset)
                {
                    playerPet->RemoveAllNegativeAuras();
                    playerPet->SetHealth(playerPet->GetMaxHealth());
                    playerPet->SetPower(POWER_MANA, playerPet->GetMaxPower(POWER_MANA));
                    playerPet->SetPower(POWER_FOCUS, playerPet->GetMaxPower(POWER_FOCUS));
                    playerPet->RemoveAllPetSpellCooldowns(players[i]);
                    playerPet->ClearDiminishings();
                    playerPet->ClearInCombat();
                    playerPet->getHostileRefManager().deleteReferences();
                }
            }
        }
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
