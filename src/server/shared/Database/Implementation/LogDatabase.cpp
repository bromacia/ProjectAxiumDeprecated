/*
 * Copyright (C) 2008-2012 TrinityCore <http://www.trinitycore.org/>
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

#include "LogDatabase.h"

void LogDatabaseConnection::DoPrepareStatements()
{
    if (!m_reconnecting)
        m_stmts.resize(MAX_LOGDATABASE_STATEMENTS);

    PREPARE_STATEMENT(LOG_INS_COMMAND_LOG, "INSERT INTO command_logs (sender_accid, sender_guid, target_accid, target_guid, target_typeid, command) VALUES (?, ?, ?, ?, ?, ?)", CONNECTION_ASYNC)
    PREPARE_STATEMENT(LOG_INS_CHAT_LOG, "INSERT INTO chat_logs (sender_accid, sender_guid, text, receiver_accid, receiver_guid, type) VALUES (?, ?, ?, ?, ?, ?)", CONNECTION_ASYNC)
}
