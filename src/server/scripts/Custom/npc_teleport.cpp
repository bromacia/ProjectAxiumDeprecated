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
                    player->TeleportTo(530, -389.221f, 7257.6f, 54.774f, 3.0f);
                    break;
                case TELEPORT_DUEL:
                    player->TeleportTo(603, 72.9814f, 47.8922f, 409.802f, 4.7f);
                    break;
            }
            return true;
        }
};

void AddSC_npc_teleport()
{
    new npc_teleport;
}
