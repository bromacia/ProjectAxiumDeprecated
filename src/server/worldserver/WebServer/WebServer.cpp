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

#include "WebServer.h"
#include "mongoose.h"
#include "World.h"

//@todo: Add json lib

static int index_html(struct mg_connection *conn) {
    mg_printf_data(conn, "World server uptime: %u", sWorld->GetUptime());

    return 0;
}

void WebServer::run()
{
    struct mg_server *server;

    // Create and configure the server
    server = mg_create_server(NULL);
    mg_set_option(server, "listening_port", "8080");
    mg_add_uri_handler(server, "/", index_html);

    // Serve request
    printf("Starting WebServer on port %s\n", mg_get_option(server, "listening_port"));
    for (;;) {
        mg_poll_server(server, 1000);
    }

    // Cleanup, and free server instance
    mg_destroy_server(&server);
}
