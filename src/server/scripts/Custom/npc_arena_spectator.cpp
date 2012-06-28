#include "Player.h"
#include "BattlegroundMgr.h"
#include "Battleground.h"
#include "ArenaTeamMgr.h"
#include "ArenaTeam.h"

enum SpectatorData
{
    GOSSIP_OFFSET = GOSSIP_ACTION_INFO_DEF + 5,
};

class npc_arena_spectator : public CreatureScript
{
public:
    npc_arena_spectator() : CreatureScript("npc_arena_spectator") {}
    
    BattlegroundSet GetAllBattlegroundsWithAllTypeIds()
    {
        BattlegroundSet arenasSet, tmpSet;
        arenasSet = sBattlegroundMgr->GetAllBattlegroundsWithTypeId(BATTLEGROUND_NA);
        tmpSet = sBattlegroundMgr->GetAllBattlegroundsWithTypeId(BATTLEGROUND_RL);
        for (BattlegroundSet::const_iterator itr = tmpSet.begin(); itr != tmpSet.end(); ++itr)
            arenasSet.insert(*itr);
        tmpSet = sBattlegroundMgr->GetAllBattlegroundsWithTypeId(BATTLEGROUND_BE);
        for (BattlegroundSet::const_iterator itr = tmpSet.begin(); itr != tmpSet.end(); ++itr)
            arenasSet.insert(*itr);
        tmpSet = sBattlegroundMgr->GetAllBattlegroundsWithTypeId(BATTLEGROUND_DS);
        for (BattlegroundSet::const_iterator itr = tmpSet.begin(); itr != tmpSet.end(); ++itr)
            arenasSet.insert(*itr);
        tmpSet = sBattlegroundMgr->GetAllBattlegroundsWithTypeId(BATTLEGROUND_RV);
        for (BattlegroundSet::const_iterator itr = tmpSet.begin(); itr != tmpSet.end(); ++itr)
            arenasSet.insert(*itr);

        return arenasSet;
    }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        BattlegroundSet arenasSet = GetAllBattlegroundsWithAllTypeIds();
        uint32 arenasQty[3] = {0, 0, 0};
        std::stringstream gossip2;
        std::stringstream gossip3;
        std::stringstream gossip5;

        for (BattlegroundSet::const_iterator itr = arenasSet.begin(); itr != arenasSet.end(); ++itr)
            if (Battleground* bg = itr->second)
                if (bg->isRated())
                    switch (bg->GetArenaType())
                    {
                        case ARENA_TYPE_2v2:  arenasQty[0]++; break;
                        case ARENA_TYPE_3v3:  arenasQty[1]++; break;
                        case ARENA_TYPE_5v5:  arenasQty[2]++; break;
                    }

        gossip2 << "Observe a 2v2 match. (" << arenasQty[0] << " match(s) in progress)";
        gossip3 << "Observe a 3v3 match. (" << arenasQty[1] << " match(s) in progress)";
        gossip5 << "Observe a 5v5 match. (" << arenasQty[2] << " match(s) in progress)";

        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, gossip2.str(), GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, gossip3.str(), GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, gossip5.str(), GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 5);
        player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_CHAT, "Observe a player.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4, "", 0, true);
        player->PlayerTalkClass->SendGossipMenu(player->GetGossipTextId(creature), creature->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action)
    {
        player->PlayerTalkClass->ClearMenus();
        uint8 mode = ARENA_TYPE_2v2;
        if (action == (GOSSIP_ACTION_INFO_DEF + 3))
            mode = ARENA_TYPE_3v3;
        if (action == (GOSSIP_ACTION_INFO_DEF + 5))
            mode = ARENA_TYPE_5v5;

        if (action <= GOSSIP_OFFSET)
        {
            BattlegroundSet arenasSet = GetAllBattlegroundsWithAllTypeIds();
            bool bracketMatchs = false;

            for (BattlegroundSet::const_iterator itr = arenasSet.begin(); itr != arenasSet.end(); ++itr)
            {
                if (Battleground* bg = itr->second)
                {
                    if (bg->GetArenaType() == mode)
                        if (bg->isRated())
                        {
                            ArenaTeam* teamOne = sArenaTeamMgr->GetArenaTeamById(bg->GetArenaTeamIdByIndex(0));
                            ArenaTeam* teamTwo = sArenaTeamMgr->GetArenaTeamById(bg->GetArenaTeamIdByIndex(1));

                            if (teamOne && teamTwo)
                            {
                                std::stringstream class_teamOne;
                                std::stringstream class_teamTwo;
                                for (Battleground::BattlegroundPlayerMap::const_iterator itr_class = bg->GetPlayers().begin(); itr_class != bg->GetPlayers().end(); ++itr_class)
                                {
                                    if (Player* player = ObjectAccessor::FindPlayer(itr_class->first))
                                    {
                                        if (teamOne->IsMember(player->GetGUIDLow()))
                                        {
                                            switch (player->getClass())
                                            {
                                                case CLASS_WARRIOR:         class_teamOne << " Warrior ";      break;
                                                case CLASS_DEATH_KNIGHT:    class_teamOne << " Death Knight "; break;
                                                case CLASS_PALADIN:         class_teamOne << " Paladin ";      break;
                                                case CLASS_HUNTER:          class_teamOne << " Hunter ";       break;
                                                case CLASS_SHAMAN:          class_teamOne << " Shaman ";       break;
                                                case CLASS_ROGUE:           class_teamOne << " Rogue ";        break;
                                                case CLASS_DRUID:           class_teamOne << " Druid ";        break;
                                                case CLASS_PRIEST:          class_teamOne << " Priest ";       break;
                                                case CLASS_MAGE:            class_teamOne << " Mage ";         break;
                                                case CLASS_WARLOCK:         class_teamOne << " Warlock ";      break;
                                            }
                                        }
                                        else if (teamTwo->IsMember(player->GetGUIDLow()))
                                        {
                                            switch (player->getClass())
                                            {
                                                case CLASS_WARRIOR:         class_teamTwo << " Warrior ";      break;
                                                case CLASS_DEATH_KNIGHT:    class_teamTwo << " Death Knight "; break;
                                                case CLASS_PALADIN:         class_teamTwo << " Paladin ";      break;
                                                case CLASS_HUNTER:          class_teamTwo << " Hunter ";       break;
                                                case CLASS_SHAMAN:          class_teamTwo << " Shaman ";       break;
                                                case CLASS_ROGUE:           class_teamTwo << " Rogue ";        break;
                                                case CLASS_DRUID:           class_teamTwo << " Druid ";        break;
                                                case CLASS_PRIEST:          class_teamTwo << " Priest ";       break;
                                                case CLASS_MAGE:            class_teamTwo << " Mage ";         break;
                                                case CLASS_WARLOCK:         class_teamTwo << " Warlock ";      break;
                                            }
                                        }
                                    }
                                }
                                std::stringstream gossipItem;
                                gossipItem << teamOne->GetName() << " (";
                                gossipItem << teamOne->GetRating() << ") [";
                                gossipItem << class_teamOne.str() << "] -VS- ";
                                gossipItem << teamTwo->GetName() << " (";
                                gossipItem << teamTwo->GetRating() << ") [";
                                gossipItem << class_teamTwo.str() << "]";
                                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, gossipItem.str(), GOSSIP_SENDER_MAIN + 1, itr->first + GOSSIP_OFFSET);
                                bracketMatchs = true;
                            }
                        }
                }
            }
            if (!bracketMatchs)
            {
                std::stringstream errMsg;
                errMsg << "There are currently no arena matches being played in that bracket.";
                creature->MonsterWhisper(errMsg.str().c_str(), player->GetGUID());
                player->PlayerTalkClass->ClearMenus();
                player->CLOSE_GOSSIP_MENU();
                return false;
            }
            player->PlayerTalkClass->SendGossipMenu(player->GetGossipTextId(creature), creature->GetGUID());
            
        }
        else
        {
            uint32 arenaId = action - GOSSIP_OFFSET;
            BattlegroundSet arenasSet = GetAllBattlegroundsWithAllTypeIds();

            if (arenasSet[arenaId] != NULL)
            {
                Battleground* arenaChosen = arenasSet[arenaId];
                if (arenaChosen->GetStatus() != STATUS_NONE && arenaChosen->GetStatus() != STATUS_IN_PROGRESS)
                {
                    std::stringstream errMsg;
                    errMsg << "The arena match you have chosen is in preperation stage or is over.";
                    creature->MonsterWhisper(errMsg.str().c_str(), player->GetGUID());
                    player->PlayerTalkClass->ClearMenus();
                    player->CLOSE_GOSSIP_MENU();
                    return false;
                }

                player->SetBattlegroundId(arenaChosen->GetInstanceID(), arenaChosen->GetTypeID());
                player->SetBattlegroundEntryPoint();
                float x, y, z;
                switch (arenaChosen->GetMapId())
                {
                    case 617: x = 1299.046f;    y = 784.825f;     z = 9.338f;     break;
                    case 618: x = 763.5f;       y = -284;         z = 28.276f;    break;
                    case 572: x = 1285.810547f; y = 1667.896851f; z = 39.957642f; break;
                    case 562: x = 6238.930176f; y = 262.963470f;  z = 0.889519f;  break;
                    case 559: x = 4055.504395f; y = 2919.660645f; z = 13.611241f; break;
                }
                player->SaveRecallPosition();
                player->SetSpectator(true);
                player->TeleportTo(arenaChosen->GetMapId(), x, y, z, player->GetOrientation());
            }
        }
        return true;
    }

    bool OnGossipSelectCode(Player* player, Creature* creature, uint32 uiSender, uint32 uiAction, const char* code)
    {
        player->PlayerTalkClass->ClearMenus();
        player->CLOSE_GOSSIP_MENU();
        if (uiSender == GOSSIP_SENDER_MAIN)
        {
            switch (uiAction)
            {
                case GOSSIP_ACTION_INFO_DEF + 4:
                {
                    const char* plrName = code;
                    if (Player* target = sObjectAccessor->FindPlayerByName(plrName))
                    {
                        if (!target->IsInWorld())
                        {
                            creature->MonsterWhisper("The player you are trying to spectate is currently being teleported.", player->GetGUID());
                            return true;
                        }
                        else if (!target->InArena())
                        {
                            creature->MonsterWhisper("The player you are trying to spectate not in any arena matches.", player->GetGUID());
                            return true;
                        }
                        else if (target->isGameMaster())
                        {
                            creature->MonsterWhisper("The player you are trying to spectate is a Gamemaster.", player->GetGUID());
                            return true;
                        }
                        else if (target->HasAura(32727))
                        {
                            creature->MonsterWhisper("The player you are trying to spectate is in an arena match that has not started yet.", player->GetGUID());
                            return true;
                        }
                        if (target->IsSpectator())
                        {
                            creature->MonsterWhisper("The player you are trying to spectate is already spectating an arena match.", player->GetGUID());
                            return true;
                        }
                        else
                        {
                            BattlegroundSet arenasSet = GetAllBattlegroundsWithAllTypeIds();
                            for (BattlegroundSet::const_iterator itr = arenasSet.begin(); itr != arenasSet.end(); ++itr)
                                if (Battleground* bg = itr->second)
                                    for (Battleground::BattlegroundPlayerMap::const_iterator itr_guid = bg->GetPlayers().begin(); itr_guid != bg->GetPlayers().end(); ++itr_guid)
                                        if (target == ObjectAccessor::FindPlayer(itr_guid->first))
                                        {
                                            if (bg->GetStatus() != STATUS_NONE && bg->GetStatus() != STATUS_IN_PROGRESS)
                                            {
                                                std::stringstream errMsg;
                                                errMsg << "The player you are trying to spectate is in an arena which is in preperation stage or is over.";
                                                creature->MonsterWhisper(errMsg.str().c_str(), player->GetGUID());
                                                return true;
                                            }
                                            else
                                            {
                                                player->SetBattlegroundId(target->GetBattleground()->GetInstanceID(), target->GetBattleground()->GetTypeID());
                                                player->SetBattlegroundEntryPoint();
                                                float x, y, z;
                                                target->GetContactPoint(player, x, y, z);
                                                player->SaveRecallPosition();
                                                player->SetSpectator(true);
                                                player->TeleportTo(target->GetMapId(), x, y, z, player->GetAngle(target));
                                            }
                                        }
                        }
                    }
                    else
                    {
                        creature->MonsterWhisper("The player you are trying to spectate is not in an arena or you have mistyped the name. Remember that names are case sensitive.", player->GetGUID());
                        return true;
                    }
                    break;
                }
            }
        }
        return false;
    }
};

void AddSC_npc_arena_spectator()
{
    new npc_arena_spectator;
}
