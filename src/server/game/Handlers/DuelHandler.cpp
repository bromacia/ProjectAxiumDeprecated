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
#include "DuelMgr.h"

void WorldSession::HandleDuelAcceptedOpcode(WorldPacket& recvPacket)
{
    uint64 guid;

    recvPacket >> guid;

    if (!_player)
        return;

    if (!_player->duel)
        return;

    Player* players[2] = { _player, _player->duel->opponent };

    if (!players[0] || !players[1])
        return;

    if (players[0] == players[0]->duel->initiator)
        return;

    if (players[0] == players[1])
        return;

    if (players[0]->duel->startTime != 0 || players[1]->duel->startTime != 0)
        return;

    sLog->outStaticDebug("Player 1 is: %u (%s)", players[0]->GetGUIDLow(), players[0]->GetName());
    sLog->outStaticDebug("Player 2 is: %u (%s)", players[1]->GetGUIDLow(), players[1]->GetName());

    time_t now = time(NULL);

    for (uint8 i = 0; i < 2; ++i)
    {
        players[i]->duel->startTimer = now;
        players[i]->SendDuelCountdown(3000);
    }

    sDuelMgr->HandleDuelStart(players[0], players[1]);
}

void WorldSession::HandleDuelCancelledOpcode(WorldPacket& recvPacket)
{
    sLog->outDebug(LOG_FILTER_NETWORKIO, "WORLD: Received CMSG_DUEL_CANCELLED");

    uint64 guid;
    recvPacket >> guid;

    if (!_player)
        return;

    if (!_player->duel)
        return;

    // player surrendered in a duel using /forfeit
    if (_player->duel->startTime != 0)
    {
        _player->CombatStopWithPets(true);
        if (_player->duel->opponent)
            _player->duel->opponent->CombatStopWithPets(true);

        _player->CastSpell(GetPlayer(), 7267, true); // Grovel
        _player->DuelComplete(DUEL_WON);
        return;
    }

    _player->DuelComplete(DUEL_INTERRUPTED);
}
