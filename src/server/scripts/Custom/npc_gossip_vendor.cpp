#include "ScriptPCH.h"

class npc_gossip_vendor : public CreatureScript
{
    public:
        npc_gossip_vendor() : CreatureScript("npc_gossip_vendor") {}

        bool OnGossipHello(Player* player, Creature* creature)
        {
            player->PlayerTalkClass->ClearMenus();

            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TABARD, "|TInterface\\icons\\_:30|t ", GOSSIP_SENDER_MAIN, 1);

            player->SEND_GOSSIP_MENU(1, creature->GetGUID());
            return true;
        }

        bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action)
        {
            player->PlayerTalkClass->ClearMenus();
            return false;
        }
};

void AddSC_npc_gossip_vendor()
{
    new npc_gossip_vendor();
}
