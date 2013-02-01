#include "ScriptPCH.h"

enum TeleportOptions
{
    TELEPORT_MALL = 1,
    TELEPORT_DUEL,
};

class npc_teleport : public CreatureScript
{
    public:
        npc_teleport() : CreatureScript("npc_teleport") {}

        bool OnGossipHello(Player* player, Creature* creature)
        {
            player->PlayerTalkClass->ClearMenus();

            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "|TInterface\\icons\\spell_holy_summonchampion:30|t Mall", GOSSIP_SENDER_MAIN, TELEPORT_MALL);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "|TInterface\\icons\\ability_dualwield:30|t Duel", GOSSIP_SENDER_MAIN, TELEPORT_DUEL);

            player->SEND_GOSSIP_MENU(1, creature->GetGUID());
            return true;
        }

        bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action)
        {
            switch (action)
            {
                case TELEPORT_MALL:
                    if (player->GetTeam() == ALLIANCE)
                        player->TeleportTo(530, -213.4f, 5489.9f, 21.9f, 4.5f);
                    else
                        player->TeleportTo(530, 1007.7f, 7375.2f, 36.3f, 2.0f);
                    break;
                case TELEPORT_DUEL:
                    player->TeleportTo(0, 1976.650024f, 2546.169922f, 131.251999f, 4.738480f);
                    break;
            }
            return true;
        }
};

void AddSC_npc_teleport()
{
    new npc_teleport;
}
