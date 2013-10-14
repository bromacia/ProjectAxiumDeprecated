#include "ArenaSpectateMgr.h"

ArenaSpectateMgr::ArenaSpectateMgr() : CreatureScript("ArenaSpectateNPC")
{
    handler = NULL;
    page = 0;
}

bool ArenaSpectateMgr::OnGossipHello(Player* player, Creature* creature)
{
    handler = new ChatHandler(player);
    page = 1;

    CreateArenasMap();

    if (player->InBattlegroundQueue())
    {
        handler->PSendSysMessage("You can't spectate while in queue for a battleground or arena.");
        return false;
    }

    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Spectate 2v2 Matches", GOSSIP_SENDER_MAIN, ARENA_SPECTATE_MENU_2V2_MATCHES);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Spectate 3v3 Matches", GOSSIP_SENDER_MAIN, ARENA_SPECTATE_MENU_3V3_MATCHES);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Spectate 5v5 Matches", GOSSIP_SENDER_MAIN, ARENA_SPECTATE_MENU_5V5_MATCHES);
    player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_CHAT, "Spectate a Player", GOSSIP_SENDER_MAIN, ARENA_SPECTATE_MENU_SPECTATE_PLAYER, "", 0, true);
    player->SEND_GOSSIP_MENU(1, creature->GetGUID());
    return true;
}

bool ArenaSpectateMgr::OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action)
{
    player->PlayerTalkClass->ClearMenus();

    switch (sender)
    {
        case GOSSIP_SENDER_MAIN:
        {
            switch (action)
            {
                case GOSSIP_SENDER_MAIN:
                {
                    OnGossipHello(player, creature);
                    break;
                }
                case ARENA_SPECTATE_MENU_2V2_MATCHES:
                case ARENA_SPECTATE_MENU_3V3_MATCHES:
                case ARENA_SPECTATE_MENU_5V5_MATCHES:
                {
                    HandleShowMatches(player, creature, sender, action);
                    break;
                }
            }
            break;
        }
        case ARENA_SPECTATE_MENU_2V2_MATCHES:
        case ARENA_SPECTATE_MENU_3V3_MATCHES:
        case ARENA_SPECTATE_MENU_5V5_MATCHES:
        {
            switch (action)
            {
                case ARENA_SPECTATE_MENU_PAGE_NEXT:
                case ARENA_SPECTATE_MENU_PAGE_PREVIOUS:
                {
                    HandleShowMatches(player, creature, sender, action);
                    break;
                }
                default:
                {
                    AddPlayerToArena(player, action);
                    break;
                }
            }
            break;
        }
    }
    return true;
}

bool ArenaSpectateMgr::OnGossipSelectCode(Player* player, Creature* creature, uint32 sender, uint32 action, const char* code)
{
    switch (action)
    {
        case ARENA_SPECTATE_MENU_SPECTATE_PLAYER: HandleSpectatePlayer(player, code); break;
    }

    return true;
}

void ArenaSpectateMgr::HandleShowMatches(Player* player, Creature* creature, uint32 sender, uint32 action)
{
    uint8 arenaType = 0;
    uint32 gossipAction = 0;

    switch (sender)
    {
        case GOSSIP_SENDER_MAIN: arenaType = GetArenaTypeByAction(action); gossipAction = action; break;
        default:                 arenaType = GetArenaTypeByAction(sender); gossipAction = sender; break;
    }

    uint8 roomLeft = MAX_RESULTS_PER_PAGE;

    if (arenasMap.empty())
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "No Arena Matches In Progress", GOSSIP_SENDER_MAIN, gossipAction);
    else
    {
        CreateArenasMap();
        BattlegroundsMap::iterator itr = arenasMap.begin();

        switch (action)
        {
            case ARENA_SPECTATE_MENU_PAGE_NEXT:     ++page;
            case ARENA_SPECTATE_MENU_PAGE_PREVIOUS: --page;
            default:
            {
                if (page < 1)
                {
                    handler->PSendSysMessage("Something went wrong, try again.");
                    player->CLOSE_GOSSIP_MENU();
                    return;
                }

                uint16 increment = page * roomLeft;
                for (uint16 i = 0; i < increment; ++i)
                {
                    ++itr;
                    if (itr == arenasMap.end())
                        break;
                }
                break;
            }
        }

        for (; itr != arenasMap.end(); ++itr)
        {
            Battleground* arena = itr->second;
            if (!arena)
                continue;

            if (arena->GetArenaType() != arenaType)
                continue;

            if (!arena->isRated())
                continue;

            ArenaTeam* goldTeam = sArenaTeamMgr->GetArenaTeamById(arena->GetArenaTeamIdByIndex(BG_TEAM_ALLIANCE));
            if (!goldTeam)
                continue;

            if (goldTeam->GetStats().Rating < sWorld->getIntConfig(CONFIG_ARENA_SPECTATOR_MIN_RATING))
                continue;

            ArenaTeam* greenTeam = sArenaTeamMgr->GetArenaTeamById(arena->GetArenaTeamIdByIndex(BG_TEAM_HORDE));
            if (!greenTeam)
                continue;

            if (greenTeam->GetStats().Rating < sWorld->getIntConfig(CONFIG_ARENA_SPECTATOR_MIN_RATING))
                continue;

            std::stringstream gossipText;
            // GoldTeamName[GoldTeamRating] vs GreenTeamName[GreenTeamRating]
            gossipText << goldTeam->GetName() << "[" << goldTeam->GetRating() << "] vs " << greenTeam->GetName() << "[" << greenTeam->GetRating() << "]";
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, gossipText.str(), gossipAction, itr->first);

            --roomLeft;

            if (!roomLeft)
                break;
        }

        if (roomLeft == MAX_RESULTS_PER_PAGE)
        {
            std::stringstream gossipText;
            gossipText << "No Arena Matches Above " << sWorld->getIntConfig(CONFIG_ARENA_SPECTATOR_MIN_RATING) << " Rating In Progress";
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, gossipText.str(), GOSSIP_SENDER_MAIN, gossipAction);
        }

        if (itr != arenasMap.end())
        {
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Next Page", gossipAction, ARENA_SPECTATE_MENU_PAGE_NEXT);

            if (sender != GOSSIP_SENDER_MAIN)
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Previous Page", gossipAction, ARENA_SPECTATE_MENU_PAGE_PREVIOUS);
        }
    }

    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Refresh", GOSSIP_SENDER_MAIN, gossipAction);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Back", GOSSIP_SENDER_MAIN, GOSSIP_SENDER_MAIN);
    player->SEND_GOSSIP_MENU(1, creature->GetGUID());
}

void ArenaSpectateMgr::HandleSpectatePlayer(Player* player, const char* cPlayerName)
{
    uint32 arenaId = 0;
    Player* target = NULL;

    uint32 guidLow = GUID_LOPART(sObjectMgr->GetPlayerGUIDByName(cPlayerName));
    if (!guidLow)
    {
        handler->PSendSysMessage("Unable to find a player with that name.");
        player->CLOSE_GOSSIP_MENU();
        return;
    }

    target = sObjectMgr->GetPlayerByLowGUID(guidLow);
    if (!target)
    {
        handler->PSendSysMessage("The player you're trying to spectate is offline.");
        player->CLOSE_GOSSIP_MENU();
        return;
    }

    arenaId = target->GetBattlegroundId();
    if (!arenaId)
    {
        handler->PSendSysMessage("The player you're trying to spectate isn't in a arena.");
        player->CLOSE_GOSSIP_MENU();
        return;
    }

    if (!arenasMap[arenaId])
    {
        handler->PSendSysMessage("The arena match of the player you're trying to spectate no longer exists.");
        player->CLOSE_GOSSIP_MENU();
        return;
    }

    AddPlayerToArena(player, arenaId);
}

void ArenaSpectateMgr::AddPlayerToArena(Player* player, uint32 action)
{
    player->CLOSE_GOSSIP_MENU();

    if (player->InBattlegroundQueue())
    {
        handler->PSendSysMessage("You can't spectate while in queue for a battleground or arena.");
        return;
    }

    Battleground* arena = sBattlegroundMgr->GetBattleground(action, arenasMap[action]->GetTypeID(false));
    if (!arena)
    {
        handler->PSendSysMessage("The arena match of the player you're trying to spectate no longer exists.");
        return;
    }

    player->SetArenaSpectatorState(true);
    player->SetBattlegroundId(action, arena->GetTypeID(false));
    player->SetBattlegroundEntryPoint();
    arena->HandlePlayerUnderMap(player);
}

bool ArenaSpectateMgr::CheckBattleground(Battleground* bg)
{
    if (bg->GetStatus() != STATUS_IN_PROGRESS)
        return false;

    if (!bg->GetPlayersCountByTeam(ALLIANCE) || !bg->GetPlayersCountByTeam(HORDE))
        return false;

    return true;
}

void ArenaSpectateMgr::CreateArenasMap()
{
    arenasMap.clear();

    BattlegroundsMap tempMap;

    // Nagrand Arena
    tempMap = sBattlegroundMgr->GetAllBattlegroundsWithTypeId(BATTLEGROUND_NA);
    for (BattlegroundsMap::iterator itr = tempMap.begin(); itr != tempMap.end(); ++itr)
        if (CheckBattleground(itr->second))
            arenasMap[itr->first] = itr->second;

    // Blade's Edge Arena
    tempMap = sBattlegroundMgr->GetAllBattlegroundsWithTypeId(BATTLEGROUND_BE);
    for (BattlegroundsMap::iterator itr = tempMap.begin(); itr != tempMap.end(); ++itr)
        if (CheckBattleground(itr->second))
            arenasMap[itr->first] = itr->second;

    // Ruins of Lordaeran
    tempMap = sBattlegroundMgr->GetAllBattlegroundsWithTypeId(BATTLEGROUND_RL);
    for (BattlegroundsMap::iterator itr = tempMap.begin(); itr != tempMap.end(); ++itr)
        if (CheckBattleground(itr->second))
            arenasMap[itr->first] = itr->second;

    // Dalaran Sewers
    tempMap = sBattlegroundMgr->GetAllBattlegroundsWithTypeId(BATTLEGROUND_DS);
    for (BattlegroundsMap::iterator itr = tempMap.begin(); itr != tempMap.end(); ++itr)
        if (CheckBattleground(itr->second))
            arenasMap[itr->first] = itr->second;

    // Ring of Valor
    tempMap = sBattlegroundMgr->GetAllBattlegroundsWithTypeId(BATTLEGROUND_RV);
    for (BattlegroundsMap::iterator itr = tempMap.begin(); itr != tempMap.end(); ++itr)
        if (CheckBattleground(itr->second))
            arenasMap[itr->first] = itr->second;
}

void AddSC_ArenaSpectateMgr()
{
    new ArenaSpectateMgr();
}
