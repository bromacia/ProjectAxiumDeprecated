#include "ScriptMgr.h"

enum TransmogSlots
{
    TRANSMOG_SLOT_HEAD             = PLAYER_VISIBLE_ITEM_1_ENTRYID,
    TRANSMOG_SLOT_SHOULDER         = PLAYER_VISIBLE_ITEM_3_ENTRYID,
    TRANSMOG_SLOT_CHEST            = PLAYER_VISIBLE_ITEM_5_ENTRYID,
    TRANSMOG_SLOT_WRIST            = PLAYER_VISIBLE_ITEM_9_ENTRYID,
    TRANSMOG_SLOT_GLOVES           = PLAYER_VISIBLE_ITEM_10_ENTRYID,
    TRANSMOG_SLOT_BELT             = PLAYER_VISIBLE_ITEM_6_ENTRYID,
    TRANSMOG_SLOT_LEGS             = PLAYER_VISIBLE_ITEM_7_ENTRYID,
    TRANSMOG_SLOT_BOOTS            = PLAYER_VISIBLE_ITEM_8_ENTRYID,
    TRANSMOG_SLOT_MAINHAND         = PLAYER_VISIBLE_ITEM_16_ENTRYID,
    TRANSMOG_SLOT_OFFHAND          = PLAYER_VISIBLE_ITEM_17_ENTRYID,
    TRANSMOG_SLOT_RANGED           = PLAYER_VISIBLE_ITEM_18_ENTRYID,
    TRANSMOG_SLOT_BACK             = PLAYER_VISIBLE_ITEM_15_ENTRYID,
    TRANSMOG_SLOT_SHIRT            = PLAYER_VISIBLE_ITEM_4_ENTRYID,
    TRANSMOG_SLOT_TABARD           = PLAYER_VISIBLE_ITEM_19_ENTRYID,
    TRANSMOG_SLOT_MAINHAND_ENCHANT = PLAYER_VISIBLE_ITEM_16_ENCHANTMENT,
    TRANSMOG_SLOT_OFFHAND_ENCHANT  = PLAYER_VISIBLE_ITEM_17_ENCHANTMENT,
    TRANSMOG_SLOT_RANGED_ENCHANT   = PLAYER_VISIBLE_ITEM_18_ENCHANTMENT,
};

enum TransmogOptions
{
    TRANSMOG_ACTION_SHOW_ARMOR = 1,
    TRANSMOG_ACTION_SHOW_WEAPONS,
    TRANSMOG_ACTION_SHOW_ENCHANTS,
    TRANSMOG_ACTION_MAIN_MENU,
    TRANSMOG_ACTION_REMOVE_ARMOR,
    TRANSMOG_ACTION_REMOVE_WEAPONS,
    TRANSMOG_ACTION_REMOVE_ENCHANTS,
};

class npc_transmog : public CreatureScript
{
    public:
        npc_transmog() : CreatureScript("npc_transmog") {}

        bool OnGossipHello(Player* player, Creature* creature)
        {
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TABARD, "|TInterface\\icons\\inv_shoulder_66:30|t Armor Sets", GOSSIP_SENDER_MAIN, TRANSMOG_ACTION_SHOW_ARMOR);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "|TInterface\\icons\\inv_sword_70:30|t Weapons", GOSSIP_SENDER_MAIN, TRANSMOG_ACTION_SHOW_WEAPONS);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TRAINER, "|TInterface\\icons\\spell_holy_blessingofstrength:30|t Enchants", GOSSIP_SENDER_MAIN, TRANSMOG_ACTION_SHOW_ENCHANTS);

            player->SEND_GOSSIP_MENU(1, creature->GetGUID());
            return true;
        }

        bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action)
        {
            player->PlayerTalkClass->ClearMenus();

            if (action == TRANSMOG_ACTION_SHOW_ARMOR)
                ShowTransmogArmorSets(player, creature);
            else if (action == TRANSMOG_ACTION_SHOW_WEAPONS)
                ShowTransmogWeapons(player, creature);
            else if (action == TRANSMOG_ACTION_SHOW_ENCHANTS)
                ShowTransmogEnchants(player, creature);
            else if (action == TRANSMOG_ACTION_MAIN_MENU)
                OnGossipHello(player, creature);
            else
            {
                if (sender == TRANSMOG_ACTION_SHOW_ARMOR)
                {
                    if (action == TRANSMOG_ACTION_REMOVE_ARMOR)
                    {
                        RemoveArmorTransmog(player);
                        return true;
                    }

                    TransmogrifyArmor(player, action);
                }
                else if (sender == TRANSMOG_ACTION_SHOW_WEAPONS)
                {
                    if (action == TRANSMOG_ACTION_REMOVE_WEAPONS)
                    {
                        RemoveWeaponTransmog(player);
                        return true;
                    }

                    TransmogrifyWeapon(player, action);
                }
                else if (sender == TRANSMOG_ACTION_SHOW_ENCHANTS)
                {
                    if (action == TRANSMOG_ACTION_REMOVE_ENCHANTS)
                    {
                        RemoveEnchantTransmog(player);
                        return true;
                    }

                    TransmogrifyEnchant(player, action);
                }
            }
            return false;
        }

        bool ShowTransmogArmorSets(Player* player, Creature* creature)
        {
            QueryResult result = WorldDatabase.PQuery("SELECT option_name, id, team_id, account_id "
            "FROM transmog_armor_sets WHERE class = '%d' OR class = '0' ORDER BY id ASC", player->getClass());

            if (!result)
            {
                ChatHandler(player).PSendSysMessage("Unable to find Transmog armor set data");
                player->CLOSE_GOSSIP_MENU();
                return false;
            }

            do
            {
                Field* fields = result->Fetch();
                if (fields[2].GetUInt32() == player->GetTeam() || fields[2].GetUInt32() == 0)
                    if (fields[3].GetUInt32() == player->GetSession()->GetAccountId() || fields[3].GetUInt32() == 0)
                        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, fields[0].GetString(), TRANSMOG_ACTION_SHOW_ARMOR, fields[1].GetUInt32());
            }
            while (result->NextRow());

            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Remove Armor Transmogrifications", TRANSMOG_ACTION_SHOW_ARMOR, TRANSMOG_ACTION_REMOVE_ARMOR);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Back", GOSSIP_SENDER_MAIN, TRANSMOG_ACTION_MAIN_MENU);

            player->SEND_GOSSIP_MENU(1, creature->GetGUID());
            return true;
        }

        bool ShowTransmogWeapons(Player* player, Creature* creature)
        {
            QueryResult result = WorldDatabase.PQuery("SELECT option_name, id, team_id, account_id "
            "FROM transmog_weapons WHERE class = '%d' OR class = '0' ORDER BY id ASC", player->getClass());

            if (!result)
            {
                ChatHandler(player).PSendSysMessage("Unable to find Transmog weapon data");
                player->CLOSE_GOSSIP_MENU();
                return false;
            }

            do
            {
                Field* fields = result->Fetch();
                if (fields[2].GetUInt32() == player->GetTeam() || fields[2].GetUInt32() == 0)
                    if (fields[3].GetUInt32() == player->GetSession()->GetAccountId() || fields[3].GetUInt32() == 0)
                        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, fields[0].GetString(), TRANSMOG_ACTION_SHOW_WEAPONS, fields[1].GetUInt32());
            }
            while (result->NextRow());

            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Remove Weapon Transmogrifications", TRANSMOG_ACTION_SHOW_WEAPONS, TRANSMOG_ACTION_REMOVE_WEAPONS);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Back", GOSSIP_SENDER_MAIN, TRANSMOG_ACTION_MAIN_MENU);

            player->SEND_GOSSIP_MENU(1, creature->GetGUID());
            return true;
        }

        bool ShowTransmogEnchants(Player* player, Creature* creature)
        {
            QueryResult result = WorldDatabase.PQuery("SELECT option_name, id FROM transmog_enchants ORDER BY id ASC");

            if (!result)
            {
                ChatHandler(player).PSendSysMessage("Unable to find Transmog enchant data");
                player->CLOSE_GOSSIP_MENU();
                return false;
            }

            do
            {
                Field* fields = result->Fetch();
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, fields[0].GetString(), TRANSMOG_ACTION_SHOW_ENCHANTS, fields[1].GetUInt32());
            }
            while (result->NextRow());

            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Remove Enchant Transmogrifications", TRANSMOG_ACTION_SHOW_ENCHANTS, TRANSMOG_ACTION_REMOVE_ENCHANTS);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Back", GOSSIP_SENDER_MAIN, TRANSMOG_ACTION_MAIN_MENU);

            player->SEND_GOSSIP_MENU(1, creature->GetGUID());
            return true;
        }

        bool TransmogrifyArmor(Player* player, uint32 action)
        {
            TransmogArmor const* transmog = sObjectMgr->GetTransmogArmorEntry(action);
            if (!transmog)
            {
                ChatHandler(player).PSendSysMessage("Unable to find Transmog data for that armor set");
                player->CLOSE_GOSSIP_MENU();
                return false;
            }

            if (transmog->head_id != 0 && player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD) != 0)
            {
                Item* item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD);
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u WHERE guid = %u",
                transmog->head_id, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD)->GetGUIDLow());

                item->TransmogEntry = transmog->head_id;
                player->SetUInt32Value(TRANSMOG_SLOT_HEAD, transmog->head_id);
            }

            if (transmog->shoulder_id != 0 && player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS) != 0)
            {
                Item* item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS);
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u WHERE guid = %u",
                transmog->shoulder_id, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS)->GetGUIDLow());

                item->TransmogEntry = transmog->shoulder_id;
                player->SetUInt32Value(TRANSMOG_SLOT_SHOULDER, transmog->shoulder_id);
            }

            if (transmog->chest_id != 0 && player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST) != 0)
            {
                Item* item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST);
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u WHERE guid = %u",
                transmog->chest_id, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST)->GetGUIDLow());

                item->TransmogEntry = transmog->chest_id;
                player->SetUInt32Value(TRANSMOG_SLOT_CHEST, transmog->chest_id);
            }

            if (transmog->gloves_id != 0 && player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS) != 0)
            {
                Item* item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS);
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u WHERE guid = %u",
                transmog->gloves_id, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS)->GetGUIDLow());

                item->TransmogEntry = transmog->gloves_id;
                player->SetUInt32Value(TRANSMOG_SLOT_GLOVES, transmog->gloves_id);
            }

            if (transmog->legs_id != 0 && player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS) != 0)
            {
                Item* item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS);
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u WHERE guid = %u",
                transmog->legs_id, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS)->GetGUIDLow());

                item->TransmogEntry = transmog->legs_id;
                player->SetUInt32Value(TRANSMOG_SLOT_LEGS, transmog->legs_id);
            }

            if (transmog->belt_id != 0 && player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST) != 0)
            {
                Item* item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST);
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u WHERE guid = %u",
                transmog->belt_id, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST)->GetGUIDLow());

                item->TransmogEntry = transmog->belt_id;
                player->SetUInt32Value(TRANSMOG_SLOT_BELT, transmog->belt_id);
            }

            if (transmog->boots_id != 0 && player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET) != 0)
            {
                Item* item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET);
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u WHERE guid = %u",
                transmog->boots_id, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET)->GetGUIDLow());

                item->TransmogEntry = transmog->boots_id;
                player->SetUInt32Value(TRANSMOG_SLOT_BOOTS, transmog->boots_id);
            }

            player->CLOSE_GOSSIP_MENU();
            return true;
        }

        bool TransmogrifyWeapon(Player* player, uint32 action)
        {
            TransmogWeapon const* transmog = sObjectMgr->GetTransmogWeaponEntry(action);
            if (!transmog)
            {
                ChatHandler(player).PSendSysMessage("Unable to find Transmog data for that item");
                player->CLOSE_GOSSIP_MENU();
                return false;
            }

            if (transmog->mainhand_id != 0 && player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND) != 0)
            {
                ItemTemplate const* transmogItem = sObjectMgr->GetItemTemplate(transmog->mainhand_id);
                ItemTemplate const* inventoryItem = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND)->GetTemplate();
                if (transmogItem->SubClass == inventoryItem->SubClass)
                {
                    CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u WHERE guid = %u",
                    transmog->mainhand_id, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND)->GetGUIDLow());

                    player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND)->TransmogEntry = transmog->mainhand_id;
                    player->SetUInt32Value(TRANSMOG_SLOT_MAINHAND, transmog->mainhand_id);
                }
            }

            if (transmog->offhand_id != 0 && player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND) != 0)
            {
                ItemTemplate const* transmogItem = sObjectMgr->GetItemTemplate(transmog->offhand_id);
                ItemTemplate const* inventoryItem = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND)->GetTemplate();
                if (transmogItem->SubClass == inventoryItem->SubClass)
                {
                    CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u WHERE guid = %u",
                    transmog->offhand_id, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND)->GetGUIDLow());

                    player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND)->TransmogEntry = transmog->offhand_id;
                    player->SetUInt32Value(TRANSMOG_SLOT_OFFHAND, transmog->offhand_id);
                }
            }

            if (transmog->ranged_id != 0 && player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_RANGED) != 0)
            {
                ItemTemplate const* transmogItem = sObjectMgr->GetItemTemplate(transmog->ranged_id);
                ItemTemplate const* inventoryItem = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_RANGED)->GetTemplate();
                if (transmogItem->SubClass == inventoryItem->SubClass)
                {
                    CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u WHERE guid = %u",
                    transmog->ranged_id, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_RANGED)->GetGUIDLow());

                    player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_RANGED)->TransmogEntry = transmog->ranged_id;
                    player->SetUInt32Value(TRANSMOG_SLOT_RANGED, transmog->ranged_id);
                }
            }

            player->CLOSE_GOSSIP_MENU();
            return true;
        }

        bool TransmogrifyEnchant(Player* player, uint32 action)
        {
            TransmogEnchant const* transmog = sObjectMgr->GetTransmogEnchantEntry(action);
            if (!transmog)
            {
                ChatHandler(player).PSendSysMessage("Unable to find Transmog data for that enchant");
                player->CLOSE_GOSSIP_MENU();
                return false;
            }

            if (transmog->enchant_id != 0 && player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND) != 0)
            {
                ItemTemplate const* inventoryItem = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND)->GetTemplate();
                if (inventoryItem->Class == ITEM_CLASS_WEAPON)
                {
                    CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEnchant = %u WHERE guid = %u",
                    transmog->enchant_id, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND)->GetGUIDLow());

                    player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND)->TransmogEnchant = transmog->enchant_id;
                    player->SetUInt16Value(TRANSMOG_SLOT_MAINHAND_ENCHANT, 0, transmog->enchant_id);
                    player->SetUInt16Value(TRANSMOG_SLOT_MAINHAND_ENCHANT, 1, transmog->enchant_id);
                }
            }

            if (transmog->enchant_id != 0 && player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND) != 0)
            {
                ItemTemplate const* inventoryItem = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND)->GetTemplate();
                if (inventoryItem->Class == ITEM_CLASS_WEAPON)
                {
                    CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEnchant = %u WHERE guid = %u",
                    transmog->enchant_id, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND)->GetGUIDLow());

                    player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND)->TransmogEnchant = transmog->enchant_id;
                    player->SetUInt16Value(TRANSMOG_SLOT_OFFHAND_ENCHANT, 0, transmog->enchant_id);
                    player->SetUInt16Value(TRANSMOG_SLOT_OFFHAND_ENCHANT, 1, transmog->enchant_id);
                }
            }

            player->CLOSE_GOSSIP_MENU();
            return true;
        }

        bool RemoveArmorTransmog(Player* player)
        {
            for (uint8 slot = EQUIPMENT_SLOT_START; slot < EQUIPMENT_SLOT_END; slot++)
            {
                if (Item* item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, slot))
                {
                    if (slot == EQUIPMENT_SLOT_HEAD ||
                        slot == EQUIPMENT_SLOT_SHOULDERS ||
                        slot == EQUIPMENT_SLOT_CHEST ||
                        slot == EQUIPMENT_SLOT_HANDS ||
                        slot == EQUIPMENT_SLOT_LEGS ||
                        slot == EQUIPMENT_SLOT_WAIST ||
                        slot == EQUIPMENT_SLOT_FEET)
                    {
                        CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = 0 WHERE guid = %u", item->GetGUIDLow());
                        item->TransmogEntry = 0;
                        player->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_ENTRYID + (slot * 2), item->GetEntry());
                    }
                }
            }

            player->CLOSE_GOSSIP_MENU();
            return true;
        }

        bool RemoveWeaponTransmog(Player* player)
        {
            for (uint8 slot = EQUIPMENT_SLOT_START; slot < EQUIPMENT_SLOT_END; slot++)
            {
                if (Item* item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, slot))
                {
                    if (slot == EQUIPMENT_SLOT_MAINHAND ||
                        slot == EQUIPMENT_SLOT_OFFHAND ||
                        slot == EQUIPMENT_SLOT_RANGED)
                    {
                        CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = 0 WHERE guid = %u", item->GetGUIDLow());
                        item->TransmogEntry = 0;
                        player->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_ENTRYID + (slot * 2), item->GetEntry());
                    }
                }
            }

            player->CLOSE_GOSSIP_MENU();
            return true;
        }

        bool RemoveEnchantTransmog(Player* player)
        {
            for (uint8 slot = EQUIPMENT_SLOT_START; slot < EQUIPMENT_SLOT_END; slot++)
            {
                if (Item* item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, slot))
                {
                    if (slot == EQUIPMENT_SLOT_MAINHAND ||
                        slot == EQUIPMENT_SLOT_OFFHAND ||
                        slot == EQUIPMENT_SLOT_RANGED)
                    {
                        CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEnchant = 0 WHERE guid = %u", item->GetGUIDLow());
                        item->TransmogEnchant = 0;
                        player->SetUInt16Value(PLAYER_VISIBLE_ITEM_1_ENCHANTMENT + (slot * 2), 0, item->GetEnchantmentId(PERM_ENCHANTMENT_SLOT));
                        player->SetUInt16Value(PLAYER_VISIBLE_ITEM_1_ENCHANTMENT + (slot * 2), 1, item->GetEnchantmentId(TEMP_ENCHANTMENT_SLOT));
                    }
                }
            }

            player->CLOSE_GOSSIP_MENU();
            return true;
        }
};

void AddSC_npc_transmog()
{
    new npc_transmog();
}