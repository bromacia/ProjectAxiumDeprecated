#include "ScriptPCH.h"

enum TeleportOption
{
    TELEPORT_MALL = 2,
    TELEPORT_DUEL,
};

class TeleportNPC : public CreatureScript
{
    public:
        TeleportNPC() : CreatureScript("TeleportNPC") {}

        bool OnGossipHello(Player* player, Creature* creature)
        {
            player->PlayerTalkClass->ClearMenus();

            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "|TInterface\\icons\\achievement_boss_zuramat:30|t Mall", GOSSIP_SENDER_MAIN, TELEPORT_MALL);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "|TInterface\\icons\\achievement_zone_howlingfjord_03:30|t Dueling Zone", GOSSIP_SENDER_MAIN, TELEPORT_DUEL);
            player->SEND_GOSSIP_MENU(1, creature->GetGUID());
            return true;
        }

        bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action)
        {
            switch (action)
            {
                case TELEPORT_MALL:
                {
                    player->TeleportTo(558, 72.5f, -163.0f, 15.5f, 3.1f);
                    break;
                }
                case TELEPORT_DUEL:
                {
                    player->TeleportTo(571, 524.0f, -3237.0f, 27.5f, 3.3f);
                    break;
                }
            }

            return true;
        }
};

void AddSC_TeleportNPC()
{
    new TeleportNPC();
}
