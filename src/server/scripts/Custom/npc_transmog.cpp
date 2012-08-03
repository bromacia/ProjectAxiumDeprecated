#include "ScriptMgr.h"

enum Slots
{
    head     = PLAYER_VISIBLE_ITEM_1_ENTRYID,
    shoulder = PLAYER_VISIBLE_ITEM_3_ENTRYID,
    chest    = PLAYER_VISIBLE_ITEM_5_ENTRYID,
    shirt    = PLAYER_VISIBLE_ITEM_4_ENTRYID,
    tabard   = PLAYER_VISIBLE_ITEM_19_ENTRYID,
    wrist    = PLAYER_VISIBLE_ITEM_9_ENTRYID,
    gloves   = PLAYER_VISIBLE_ITEM_10_ENTRYID,
    belt     = PLAYER_VISIBLE_ITEM_6_ENTRYID,
    legs     = PLAYER_VISIBLE_ITEM_7_ENTRYID,
    boots    = PLAYER_VISIBLE_ITEM_8_ENTRYID,
    back     = PLAYER_VISIBLE_ITEM_15_ENTRYID,
    mainhand = PLAYER_VISIBLE_ITEM_16_ENTRYID,
    offhand  = PLAYER_VISIBLE_ITEM_17_ENTRYID,
    ranged   = PLAYER_VISIBLE_ITEM_18_ENTRYID,
};

enum TransmogTeam
{
    Alliance            = 469,
    Horde               = 67,
};

class npc_transmog : public CreatureScript
{
    public:
        npc_transmog() : CreatureScript("npc_transmog") {}

    bool OnGossipHello(Player* player, Creature* creature)
    {
        player->ADD_GOSSIP_ITEM(8, "Armor Sets", GOSSIP_SENDER_MAIN, 1);
        player->ADD_GOSSIP_ITEM(9, "Weapons", GOSSIP_SENDER_MAIN, 2);

        player->SEND_GOSSIP_MENU(50055, creature->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action)
    {
        player->PlayerTalkClass->ClearMenus();
        if (action == 1) // Armor Sets
        {
            QueryResult result = WorldDatabase.PQuery("SELECT option_name, id, team_id, account_id FROM transmog_armor_sets WHERE class='%d' OR class='0' ORDER BY id ASC", player->getClass());

            if (!result)
            {
                ChatHandler(player).PSendSysMessage("Unable to find transmog armor set data.");
                player->CLOSE_GOSSIP_MENU();
                return false;
            }

            do
            {
                Field* fields = result->Fetch();
                if (fields[2].GetUInt32() == player->GetTeam() || fields[2].GetUInt32() == 0)
                    if (fields[3].GetUInt32() == player->GetSession()->GetAccountId() || fields[3].GetUInt32() == 0)
                        player->ADD_GOSSIP_ITEM(4, fields[0].GetString(), 1, fields[1].GetUInt32());
            }
            while (result->NextRow());

            player->ADD_GOSSIP_ITEM(4, "Remove Transmogrifications", GOSSIP_SENDER_MAIN, 100000);
            player->ADD_GOSSIP_ITEM(7, "Back", GOSSIP_SENDER_MAIN, 3);

            player->SEND_GOSSIP_MENU(50055, creature->GetGUID());
            return true;
        }
        else if (action == 2) // Weapons
        {
            QueryResult result = WorldDatabase.PQuery("SELECT option_name, id, team_id, account_id, mainhand_id, offhand_id, ranged_id FROM transmog_weapons WHERE class='%d' OR class='0' ORDER BY id ASC", player->getClass());

            if (!result)
            {
                ChatHandler(player).PSendSysMessage("Unable to find transmog weapon data.");
                player->CLOSE_GOSSIP_MENU();
                return false;
            }

            do
            {
                Field* fields = result->Fetch();
                if (fields[2].GetUInt32() == player->GetTeam() || fields[2].GetUInt32() == 0)
                    if (fields[3].GetUInt32() == player->GetSession()->GetAccountId() || fields[3].GetUInt32() == 0)
                        player->ADD_GOSSIP_ITEM(4, fields[0].GetString(), 2, fields[1].GetUInt32());
            }
            while (result->NextRow());

            player->ADD_GOSSIP_ITEM(4, "Remove Transmogrifications", 2, 100001);
            player->ADD_GOSSIP_ITEM(7, "Back", GOSSIP_SENDER_MAIN, 3);

            player->SEND_GOSSIP_MENU(50055, creature->GetGUID());
            return true;
        }
        else if (action == 3)
        {
            OnGossipHello(player, creature);
        }
        else
        {
            if (sender == 1) // Armor Sets
            {
                if (player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD) == 0
                    || player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS) == 0
                    || player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST) == 0
                    || player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS) == 0
                    || player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS) == 0
                    || player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST) == 0
                    || player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET) == 0)
                {
                    ChatHandler(player).PSendSysMessage("You need to have a head, shoulders, chest, gloves, legs, belt and boots equipped to transmogrify.");
                    player->CLOSE_GOSSIP_MENU();
                    return false;
                }

                if (action == 100000)
                {
                    for (uint8 Slot = EQUIPMENT_SLOT_START; Slot < EQUIPMENT_SLOT_END; Slot++)
                    {
                        if (Item* item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, Slot))
                        {
                            if (Slot != EQUIPMENT_SLOT_MAINHAND
                                && Slot != EQUIPMENT_SLOT_OFFHAND
                                && Slot != EQUIPMENT_SLOT_RANGED)
                            {
                                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = 0 WHERE guid = %u", item->GetGUIDLow());
                                item->TransmogEntry = 0;
                                player->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_ENTRYID + (Slot * 2), item->GetEntry());
                            }
                        }
                    }

                    player->CLOSE_GOSSIP_MENU();
                    return true;
                }

                TransmogArmor const* transmog = sObjectMgr->GetTransmogArmorEntry(action);
                if (!transmog)
                {
                    ChatHandler(player).PSendSysMessage("Unable to find transmog armor set.");
                    player->CLOSE_GOSSIP_MENU();
                    return false;
                }

                if (transmog->head_id != 0)
                {
                    Item* item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD);
                    CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u WHERE guid = %u", transmog->head_id, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD)->GetGUIDLow());
                    item->TransmogEntry = transmog->head_id;
                    player->SetUInt32Value(head, transmog->head_id);
                }
                if (transmog->shoulder_id != 0)
                {
                    Item* item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS);
                    CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u WHERE guid = %u", transmog->shoulder_id, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS)->GetGUIDLow());
                    item->TransmogEntry = transmog->shoulder_id;
                    player->SetUInt32Value(shoulder, transmog->shoulder_id);
                }
                if (transmog->chest_id != 0)
                {
                    Item* item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST);
                    CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u WHERE guid = %u", transmog->chest_id, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST)->GetGUIDLow());
                    item->TransmogEntry = transmog->chest_id;
                    player->SetUInt32Value(chest, transmog->chest_id);
                }
                if (transmog->gloves_id != 0)
                {
                    Item* item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS);
                    CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u WHERE guid = %u", transmog->gloves_id, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS)->GetGUIDLow());
                    item->TransmogEntry = transmog->gloves_id;
                    player->SetUInt32Value(gloves, transmog->gloves_id);
                }
                if (transmog->legs_id != 0)
                {
                    Item* item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS);
                    CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u WHERE guid = %u", transmog->legs_id, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS)->GetGUIDLow());
                    item->TransmogEntry = transmog->legs_id;
                    player->SetUInt32Value(legs, transmog->legs_id);
                }
                if (transmog->belt_id != 0)
                {
                    Item* item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST);
                    CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u WHERE guid = %u", transmog->belt_id, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST)->GetGUIDLow());
                    item->TransmogEntry = transmog->belt_id;
                    player->SetUInt32Value(belt, transmog->belt_id);
                }
                if (transmog->boots_id != 0)
                {
                    Item* item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET);
                    CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u WHERE guid = %u", transmog->boots_id, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET)->GetGUIDLow());
                    item->TransmogEntry = transmog->boots_id;
                    player->SetUInt32Value(boots, transmog->boots_id);
                }

                player->CLOSE_GOSSIP_MENU();
                return true;
            }
            else if (sender == 2) // Weapons
            {
                if (action == 100001)
                {
                    for (uint8 Slot = EQUIPMENT_SLOT_START; Slot < EQUIPMENT_SLOT_END; Slot++)
                    {
                        if (Item* item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, Slot))
                        {
                            if (Slot != EQUIPMENT_SLOT_HEAD
                                && Slot != EQUIPMENT_SLOT_SHOULDERS
                                && Slot != EQUIPMENT_SLOT_CHEST
                                && Slot != EQUIPMENT_SLOT_HANDS
                                && Slot != EQUIPMENT_SLOT_LEGS
                                && Slot != EQUIPMENT_SLOT_WAIST
                                && Slot != EQUIPMENT_SLOT_FEET)
                            {
                                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = 0 WHERE guid = %u", item->GetGUIDLow());
                                item->TransmogEntry = 0;
                                player->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_ENTRYID + (Slot * 2), item->GetEntry());
                            }
                        }
                    }

                    player->CLOSE_GOSSIP_MENU();
                    return true;
                }

                TransmogWeapon const* transmog = sObjectMgr->GetTransmogWeaponEntry(action);
                if (!transmog)
                {
                    ChatHandler(player).PSendSysMessage("Unable to find transmog weapon.");
                    player->CLOSE_GOSSIP_MENU();
                    return false;
                }

                if (player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND) == 0 && transmog->mainhand_id != 0
                    || player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND) == 0 && transmog->offhand_id != 0
                    || player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_RANGED) == 0 && transmog->ranged_id != 0)
                {
                    ChatHandler(player).PSendSysMessage("You need to have a main hand, off hand and ranged weapon equipped to transmogrify.");
                    player->CLOSE_GOSSIP_MENU();
                    return false;
                }

                if (transmog->mainhand_id != 0)
                {
                    ItemTemplate const* item = sObjectMgr->GetItemTemplate(transmog->mainhand_id);
                    if (item->InventoryType == player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND)->GetTemplate()->InventoryType
                        || item->InventoryType == 13 && player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND)->GetTemplate()->InventoryType == 21
                        || item->InventoryType == 21 && player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND)->GetTemplate()->InventoryType == 13)
                    {
                        if (item->SubClass == player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND)->GetTemplate()->SubClass)
                        {
                            Item* item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND);
                            CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u WHERE guid = %u", transmog->mainhand_id, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND)->GetGUIDLow());
                            item->TransmogEntry = transmog->mainhand_id;
                            player->SetUInt32Value(mainhand, transmog->mainhand_id);
                        }
                        else
                        {
                            player->CLOSE_GOSSIP_MENU();
                            ChatHandler(player).PSendSysMessage("Your weapon class does not match the transmogs weapons class.");
                            return false;
                        }
                    }
                    else
                    {
                        player->CLOSE_GOSSIP_MENU();
                        ChatHandler(player).PSendSysMessage("Your weapon type does not match the transmog weapons type.");
                        return false;
                    }
                }
                if (transmog->offhand_id != 0)
                {
                    ItemTemplate const* item = sObjectMgr->GetItemTemplate(transmog->offhand_id);
                    if (item->InventoryType == player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND)->GetTemplate()->InventoryType)
                    {
                        if (item->SubClass == player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND)->GetTemplate()->SubClass)
                        {
                            Item* item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND);
                            CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u WHERE guid = %u", transmog->offhand_id, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND)->GetGUIDLow());
                            item->TransmogEntry = transmog->offhand_id;
                            player->SetUInt32Value(offhand, transmog->offhand_id);
                        }
                        else
                        {
                            player->CLOSE_GOSSIP_MENU();
                            ChatHandler(player).PSendSysMessage("Your weapon class does not match the transmogs weapons class.");
                            return false;
                        }
                    }
                    else
                    {
                        player->CLOSE_GOSSIP_MENU();
                        ChatHandler(player).PSendSysMessage("Your weapon type does not match the transmog weapons type.");
                        return false;
                    }
                }
                if (transmog->ranged_id != 0)
                {
                    ItemTemplate const* item = sObjectMgr->GetItemTemplate(transmog->ranged_id);
                    if (item->InventoryType == player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_RANGED)->GetTemplate()->InventoryType)
                    {
                        if (item->SubClass == player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_RANGED)->GetTemplate()->SubClass)
                        {
                            Item* item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_RANGED);
                            CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u WHERE guid = %u", transmog->ranged_id, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_RANGED)->GetGUIDLow());
                            item->TransmogEntry = transmog->ranged_id;
                            player->SetUInt32Value(ranged, transmog->ranged_id);
                        }
                        else
                        {
                            player->CLOSE_GOSSIP_MENU();
                            ChatHandler(player).PSendSysMessage("Your weapon class does not match the transmogs weapons class.");
                            return false;
                        }
                    }
                    else
                    {
                        player->CLOSE_GOSSIP_MENU();
                        ChatHandler(player).PSendSysMessage("Your weapon type does not match the transmog weapons type.");
                        return false;
                    }
                }

                player->CLOSE_GOSSIP_MENU();
                return true;
            }
        }
        return false;
    }
};

void AddSC_npc_transmog()
{
    new npc_transmog();
}