#include "ScriptPCH.h"

enum TeleportOptions
{
    TELEPORT_STORMWIND = 1, 
    TELEPORT_IRONFORGE,
    TELEPORT_DARNASSUS,
    TELEPORT_THE_EXODAR,
    TELEPORT_ORGRIMMAR,
    TELEPORT_UNDERCITY,
    TELEPORT_THUNDERBLUFF,
    TELEPORT_SILVERMOON,
    TELEPORT_WORLD_PVP_ZONE,
};

class npc_teleport : public CreatureScript
{
    public:
        npc_teleport() : CreatureScript("npc_teleport") {}

        bool OnGossipHello(Player* player, Creature* creature)
        {
            player->PlayerTalkClass->ClearMenus();

            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "|TInterface\\icons\\Spell_Arcane_TeleportStormWind:30|t Stormwind", GOSSIP_SENDER_MAIN, TELEPORT_STORMWIND);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "|TInterface\\icons\\Spell_Arcane_TeleportIronForge:30|t Ironforge", GOSSIP_SENDER_MAIN, TELEPORT_IRONFORGE);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "|TInterface\\icons\\Spell_Arcane_TeleportDarnassus:30|t Darnassus", GOSSIP_SENDER_MAIN, TELEPORT_DARNASSUS);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "|TInterface\\icons\\Spell_Arcane_TeleportExodar:30|t The Exodar", GOSSIP_SENDER_MAIN, TELEPORT_THE_EXODAR);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "|TInterface\\icons\\Spell_Arcane_TeleportOrgrimmar:30|t Orgrimmar", GOSSIP_SENDER_MAIN, TELEPORT_ORGRIMMAR);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "|TInterface\\icons\\Spell_Arcane_TeleportUnderCity:30|t Undercity", GOSSIP_SENDER_MAIN, TELEPORT_UNDERCITY);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "|TInterface\\icons\\Spell_Arcane_TeleportThunderBluff:30|t Thunderbluff", GOSSIP_SENDER_MAIN, TELEPORT_THUNDERBLUFF);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "|TInterface\\icons\\Spell_Arcane_TeleportSilvermoon:30|t Silvermoon", GOSSIP_SENDER_MAIN, TELEPORT_SILVERMOON);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "|TInterface\\icons\\Inv_bannerpvp_03:30|t World PvP Zone", GOSSIP_SENDER_MAIN, TELEPORT_WORLD_PVP_ZONE);
            player->SEND_GOSSIP_MENU(1, creature->GetGUID());
            return true;
        }

        bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action)
        {
            switch (action)
            {
                case TELEPORT_STORMWIND:
                    player->TeleportTo(0, -8962.14f, 514.4f, 96.3552f, 0.68f);
                    break;
                case TELEPORT_IRONFORGE:
                    player->TeleportTo(0, -4982.27f, -882.0f, 501.659f, 5.4f);
                    break;
                case TELEPORT_DARNASSUS:
                    player->TeleportTo(1, 9952.18f, 2273.32f, 1341.39f, 1.6f);
                    break;
                case TELEPORT_THE_EXODAR:
                    player->TeleportTo(530, -4002.2f, -11873.7f, -0.623776f, 1.0f);
                    break;
                case TELEPORT_ORGRIMMAR:
                    player->TeleportTo(1, 1420.9f, -4365.22f, 25.46f, 0.13f);
                    break;
                case TELEPORT_UNDERCITY:
                    player->TeleportTo(0, 1823.81f, 238.781f, 60.741f, 3.13f);
                    break;
                case TELEPORT_THUNDERBLUFF:
                    player->TeleportTo(1, -1304.18f, 205.8f, 68.6814f, 5.0f);
                    break;
                case TELEPORT_SILVERMOON:
                    player->TeleportTo(530, 9332.0f, -7277.26f, 13.4651f, 6.25f);
                    break;
                case TELEPORT_WORLD_PVP_ZONE:
                    player->TeleportTo(530, -389.221f, 7257.6f, 54.774f, 3.0f);
                    break;
            }

            return true;
        }
};

void AddSC_npc_teleport()
{
    new npc_teleport;
}
