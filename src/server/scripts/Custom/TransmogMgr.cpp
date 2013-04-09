#include "TransmogMgr.h"

static uint8 itemSlot;

bool Transmogrification::OnGossipHello(Player* player, Creature* creature)
{
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TRAINER, "|TInterface\\icons\\Inv_Chest_Leather_13:30|t Armor Sets", GOSSIP_SENDER_MAIN, TRANSMOG_ACTION_SHOW_ARMOR);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TRAINER, "|TInterface\\icons\\Inv_Shoulder_66:30|t Individual", GOSSIP_SENDER_MAIN, TRANSMOG_ACTION_SHOW_INDIVIDUAL);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TRAINER, "|TInterface\\icons\\Spell_Holy_BlessingOfStrength:30|t Enchants", GOSSIP_SENDER_MAIN, TRANSMOG_ACTION_SHOW_ENCHANTS);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TRAINER, "|TInterface\\icons\\Inv_Enchant_Disenchant:30|t Remove Item Transmogrifications", GOSSIP_SENDER_MAIN, TRANSMOG_ACTION_SHOW_REMOVE_ITEM_TRANSMOG_OPTIONS);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TRAINER, "|TInterface\\icons\\Ability_DualWieldSpecialization:30|t Remove Enchant Transmogrifications", GOSSIP_SENDER_MAIN, TRANSMOG_ACTION_SHOW_REMOVE_ENCHANT_TRANSMOG_OPTIONS);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TRAINER, "|TInterface\\icons\\Spell_Shadow_SacrificialShield:30|t Remove All Transmogrifications", GOSSIP_SENDER_MAIN, TRANSMOG_ACTION_SELECT_REMOVE_EVERYTHING);

    player->SEND_GOSSIP_MENU(1, creature->GetGUID());
    return true;
}

bool Transmogrification::OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action)
{
    player->PlayerTalkClass->ClearMenus();

        if (action == TRANSMOG_ACTION_SHOW_ARMOR)
            ShowTransmogArmorSets(player, creature);
        else if (action == TRANSMOG_ACTION_SHOW_INDIVIDUAL)
            ShowIndividualTransmogOptions(player, creature);
        else if (action == TRANSMOG_ACTION_SHOW_ENCHANTS)
            ShowTransmogEnchants(player, creature);
        else if (action == TRANSMOG_ACTION_SHOW_REMOVE_ITEM_TRANSMOG_OPTIONS)
            ShowRemoveTransmogItemOptions(player, creature);
        else if (action == TRANSMOG_ACTION_SHOW_REMOVE_ENCHANT_TRANSMOG_OPTIONS)
            ShowRemoveTransmogEnchantOptions(player, creature);
        else if (action == TRANSMOG_ACTION_SELECT_REMOVE_EVERYTHING)
            RemoveAllTransmog(player);
        else if (action == TRANSMOG_ACTION_MAIN_MENU)
            OnGossipHello(player, creature);
        else if (sender == TRANSMOG_ACTION_SHOW_ARMOR)
            TransmogrifyArmor(player, action);
        else if (sender == TRANSMOG_ACTION_SHOW_INDIVIDUAL)
            SelectIndividualTransmog(player, creature, action);
        else if (sender == TRANSMOG_ACTION_SHOW_ENCHANTS)
            TransmogrifyEnchant(player, action);
        else if (sender == TRANSMOG_ACTION_SHOW_REMOVE_ITEM_TRANSMOG_OPTIONS)
            if (action == TRANSMOG_ACTION_SELECT_REMOVE_ALL_ARMOR)
                RemoveAllArmorTransmog(player);
            else if (action == TRANSMOG_ACTION_SELECT_REMOVE_ALL_WEAPON)
                RemoveAllWeaponTransmog(player);
            else
                RemoveItemTransmog(player, action);
        else if (sender == TRANSMOG_ACTION_SHOW_REMOVE_ENCHANT_TRANSMOG_OPTIONS)
            if (action == TRANSMOG_ACTION_SELECT_REMOVE_ALL_ENCHANT)
                RemoveAllEnchantTransmog(player);
            else
                RemoveEnchantTransmog(player, action);
    return false;
}

bool Transmogrification::ShowTransmogArmorSets(Player* player, Creature* creature)
{
    QueryResult result = WorldDatabase.PQuery("SELECT option_name, id, required_faction, account "
    "FROM transmog_armor_sets WHERE required_class = '%d' OR required_class = '0' ORDER BY id ASC", player->getClass());

    if (!result)
    {
        ChatHandler(player).PSendSysMessage("Unable to find Transmog armor set data");
        player->CLOSE_GOSSIP_MENU();
        return false;
    }

    do
    {
        Field* fields = result->Fetch();
        if (GetTeamById(fields[2].GetUInt32()) == player->GetTeam() || !fields[2].GetUInt32())
            if (fields[3].GetUInt32() == player->GetSession()->GetAccountId() || fields[3].GetUInt32() == 0)
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, fields[0].GetString(), TRANSMOG_ACTION_SHOW_ARMOR, fields[1].GetUInt32());
    }
    while (result->NextRow());

    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Back", TRANSMOG_ACTION_SHOW_ARMOR, TRANSMOG_ACTION_MAIN_MENU);

    player->SEND_GOSSIP_MENU(1, creature->GetGUID());
    return true;
}

bool Transmogrification::ShowIndividualTransmogOptions(Player* player, Creature* creature)
{
    if (player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD))
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Head", TRANSMOG_ACTION_SHOW_INDIVIDUAL, TRANSMOG_ACTION_SHOW_INDIVIDUAL_HEAD);

    if (player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS))
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Shoulders", TRANSMOG_ACTION_SHOW_INDIVIDUAL, TRANSMOG_ACTION_SHOW_INDIVIDUAL_SHOULDERS);

    if (player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST))
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Chest", TRANSMOG_ACTION_SHOW_INDIVIDUAL, TRANSMOG_ACTION_SHOW_INDIVIDUAL_CHEST);

    if (player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS))
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Hands", TRANSMOG_ACTION_SHOW_INDIVIDUAL, TRANSMOG_ACTION_SHOW_INDIVIDUAL_HANDS);

    if (player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS))
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Legs", TRANSMOG_ACTION_SHOW_INDIVIDUAL, TRANSMOG_ACTION_SHOW_INDIVIDUAL_LEGS);

    if (player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WRISTS))
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Wrists", TRANSMOG_ACTION_SHOW_INDIVIDUAL, TRANSMOG_ACTION_SHOW_INDIVIDUAL_WRISTS);

    if (player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST))
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Waist", TRANSMOG_ACTION_SHOW_INDIVIDUAL, TRANSMOG_ACTION_SHOW_INDIVIDUAL_WAIST);

    if (player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET))
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Boots", TRANSMOG_ACTION_SHOW_INDIVIDUAL, TRANSMOG_ACTION_SHOW_INDIVIDUAL_BOOTS);

    if (player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND))
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Main Hand", TRANSMOG_ACTION_SHOW_INDIVIDUAL, TRANSMOG_ACTION_SHOW_INDIVIDUAL_MAINHAND);

    if (player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND))
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Off Hand", TRANSMOG_ACTION_SHOW_INDIVIDUAL, TRANSMOG_ACTION_SHOW_INDIVIDUAL_OFFHAND);

    if (Item* item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_RANGED))
        if (item->GetTemplate()->InventoryType != INVTYPE_RELIC)
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Ranged", TRANSMOG_ACTION_SHOW_INDIVIDUAL, TRANSMOG_ACTION_SHOW_INDIVIDUAL_RANGED);

    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Back", TRANSMOG_ACTION_SHOW_INDIVIDUAL, TRANSMOG_ACTION_MAIN_MENU);

    player->SEND_GOSSIP_MENU(1, creature->GetGUID());

    itemSlot = 0;
    return true;
}

bool Transmogrification::ShowTransmogEnchants(Player* player, Creature* creature)
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

    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Back", TRANSMOG_ACTION_SHOW_ENCHANTS, TRANSMOG_ACTION_MAIN_MENU);

    player->SEND_GOSSIP_MENU(1, creature->GetGUID());
    return true;
}

bool Transmogrification::ShowRemoveTransmogItemOptions(Player* player, Creature* creature)
{
    if (player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD))
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Head", TRANSMOG_ACTION_SHOW_REMOVE_ITEM_TRANSMOG_OPTIONS, TRANSMOG_ACTION_SELECT_REMOVE_HEAD);

    if (player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS))
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Shoulders", TRANSMOG_ACTION_SHOW_REMOVE_ITEM_TRANSMOG_OPTIONS, TRANSMOG_ACTION_SELECT_REMOVE_SHOULDERS);

    if (player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST))
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Chest", TRANSMOG_ACTION_SHOW_REMOVE_ITEM_TRANSMOG_OPTIONS, TRANSMOG_ACTION_SELECT_REMOVE_CHEST);

    if (player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS))
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Hands", TRANSMOG_ACTION_SHOW_REMOVE_ITEM_TRANSMOG_OPTIONS, TRANSMOG_ACTION_SELECT_REMOVE_HANDS);

    if (player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS))
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Legs", TRANSMOG_ACTION_SHOW_REMOVE_ITEM_TRANSMOG_OPTIONS, TRANSMOG_ACTION_SELECT_REMOVE_LEGS);

    if (player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WRISTS))
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Wrists", TRANSMOG_ACTION_SHOW_REMOVE_ITEM_TRANSMOG_OPTIONS, TRANSMOG_ACTION_SELECT_REMOVE_WRISTS);

    if (player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST))
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Waist", TRANSMOG_ACTION_SHOW_REMOVE_ITEM_TRANSMOG_OPTIONS, TRANSMOG_ACTION_SELECT_REMOVE_WAIST);

    if (player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET))
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Boots", TRANSMOG_ACTION_SHOW_REMOVE_ITEM_TRANSMOG_OPTIONS, TRANSMOG_ACTION_SELECT_REMOVE_BOOTS);

    if (player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND))
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Main Hand", TRANSMOG_ACTION_SHOW_REMOVE_ITEM_TRANSMOG_OPTIONS, TRANSMOG_ACTION_SELECT_REMOVE_MAINHAND);

    if (player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND))
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Off Hand", TRANSMOG_ACTION_SHOW_REMOVE_ITEM_TRANSMOG_OPTIONS, TRANSMOG_ACTION_SELECT_REMOVE_OFFHAND);

    if (Item* item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_RANGED))
        if (item->GetTemplate()->InventoryType != INVTYPE_RELIC)
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Ranged", TRANSMOG_ACTION_SHOW_REMOVE_ITEM_TRANSMOG_OPTIONS, TRANSMOG_ACTION_SELECT_REMOVE_RANGED);

    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Remove All Armor Transmogrifications", TRANSMOG_ACTION_SHOW_REMOVE_ITEM_TRANSMOG_OPTIONS, TRANSMOG_ACTION_SELECT_REMOVE_ALL_ARMOR);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Remove All Weapon Transmogrifications", TRANSMOG_ACTION_SHOW_REMOVE_ITEM_TRANSMOG_OPTIONS, TRANSMOG_ACTION_SELECT_REMOVE_ALL_WEAPON);

    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Back", TRANSMOG_ACTION_SHOW_REMOVE_ITEM_TRANSMOG_OPTIONS, TRANSMOG_ACTION_MAIN_MENU);

    player->SEND_GOSSIP_MENU(1, creature->GetGUID());
    return true;
}

bool Transmogrification::ShowRemoveTransmogEnchantOptions(Player* player, Creature* creature)
{
    if (player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND))
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Main Hand", TRANSMOG_ACTION_SHOW_REMOVE_ENCHANT_TRANSMOG_OPTIONS, TRANSMOG_ACTION_SELECT_REMOVE_MAINHAND_ENCHANT);

    if (Item* item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND))
        if (IsWeapon(item->GetTemplate()))
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Off Hand", TRANSMOG_ACTION_SHOW_REMOVE_ENCHANT_TRANSMOG_OPTIONS, TRANSMOG_ACTION_SELECT_REMOVE_OFFHAND_ENCHANT);

    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Remove All Enchant Transmogrifications", TRANSMOG_ACTION_SHOW_REMOVE_ENCHANT_TRANSMOG_OPTIONS, TRANSMOG_ACTION_SELECT_REMOVE_ALL_ENCHANT);

    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Back", TRANSMOG_ACTION_SHOW_REMOVE_ENCHANT_TRANSMOG_OPTIONS, TRANSMOG_ACTION_MAIN_MENU);

    player->SEND_GOSSIP_MENU(1, creature->GetGUID());
    return true;
}

bool Transmogrification::SelectIndividualTransmog(Player* player, Creature* creature, uint16 action)
{
    itemSlot = GetItemSlotByAction(action);
    ItemTemplate const* pItemTemplate = player->GetItemByPos(INVENTORY_SLOT_BAG_0, itemSlot)->GetTemplate();
    WorldSession* m_session = player->GetSession();
    uint64 creatureGUID = creature->GetGUID();
    VendorItemData const* items = creature->GetVendorItems();
    if (!items)
    {
        ChatHandler(player).PSendSysMessage("Unable to find item data");
        player->CLOSE_GOSSIP_MENU();
        return false;
    }

    player->CLOSE_GOSSIP_MENU();

    uint16 itemCount = items->GetItemCount();
    uint8 count = 0;
    uint8 slot = 0;

    WorldPacket data(SMSG_LIST_INVENTORY, 8 + 1 + itemCount * 8 * 4);
    data << uint64(creatureGUID);
    size_t countPos = data.wpos();
    data << uint8(count);

    for (uint16 slot = 0; slot < itemCount; ++slot)
    {
        if (VendorItem const* vItem = items->GetItem(slot))
        {
            if (ItemTemplate const* vItemTemplate = sObjectMgr->GetItemTemplate(vItem->item))
            {
                if (!CheckItem(player, vItemTemplate, pItemTemplate))
                    continue;

                ++count;
                data << uint32(count + 1);                       // Client expects counting to start at 1
                data << uint32(vItem->item);                    // Entry ?
                data << uint32(vItemTemplate->DisplayInfoID);   // DisplayId
                data << int32(0xFFFFFFFF);                      // Left in stock
                data << uint32(0);                              // Price
                data << uint32(vItemTemplate->MaxDurability);   // Durability
                data << uint32(vItemTemplate->BuyCount);        // Buy Count
                data << uint32(0);                              // Extended Cost
            }
        }
    }

    if (!count)
    {
        itemSlot = 0;
        ChatHandler(player).PSendSysMessage("Unable to find item data");
        player->CLOSE_GOSSIP_MENU();
        return false;
    }

    data.put<uint8>(countPos, count);
    m_session->SendPacket(&data);
    return true;
}

bool Transmogrification::TransmogrifyArmor(Player* player, uint16 action)
{
    TransmogArmor const* transmog = sObjectMgr->GetTransmogArmorEntry(action);
    if (!transmog)
    {
        ChatHandler(player).PSendSysMessage("Unable to find Transmog data for that armor set");
        player->CLOSE_GOSSIP_MENU();
        return false;
    }

    if (transmog->head_id != 0 && player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD))
    {
        Item* item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD);
        CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u WHERE guid = %u",
        transmog->head_id, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD)->GetGUIDLow());

        item->TransmogEntry = transmog->head_id;
        player->SetUInt32Value(TRANSMOG_SLOT_HEAD, transmog->head_id);
    }

    if (transmog->shoulders_id != 0 && player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS))
    {
        Item* item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS);
        CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u WHERE guid = %u",
        transmog->shoulders_id, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS)->GetGUIDLow());

        item->TransmogEntry = transmog->shoulders_id;
        player->SetUInt32Value(TRANSMOG_SLOT_SHOULDERS, transmog->shoulders_id);
    }

    if (transmog->chest_id != 0 && player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST))
    {
        Item* item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST);
        CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u WHERE guid = %u",
        transmog->chest_id, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST)->GetGUIDLow());

        item->TransmogEntry = transmog->chest_id;
        player->SetUInt32Value(TRANSMOG_SLOT_CHEST, transmog->chest_id);
    }

    if (transmog->gloves_id != 0 && player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS))
    {
        Item* item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS);
        CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u WHERE guid = %u",
        transmog->gloves_id, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS)->GetGUIDLow());

        item->TransmogEntry = transmog->gloves_id;
        player->SetUInt32Value(TRANSMOG_SLOT_HANDS, transmog->gloves_id);
    }

    if (transmog->legs_id != 0 && player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS))
    {
        Item* item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS);
        CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u WHERE guid = %u",
        transmog->legs_id, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS)->GetGUIDLow());

        item->TransmogEntry = transmog->legs_id;
        player->SetUInt32Value(TRANSMOG_SLOT_LEGS, transmog->legs_id);
    }

    if (transmog->waist_id != 0 && player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST))
    {
        Item* item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST);
        CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u WHERE guid = %u",
        transmog->waist_id, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST)->GetGUIDLow());

        item->TransmogEntry = transmog->waist_id;
        player->SetUInt32Value(TRANSMOG_SLOT_WAIST, transmog->waist_id);
    }

    if (transmog->boots_id != 0 && player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET))
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

bool Transmogrification::TransmogrifyIndividual(Player* player, Creature* creature, uint32 item)
{
    ItemTemplate const* vItemTemplate = sObjectMgr->GetItemTemplate(item);
    uint16 transmogSlot = GetTransmogSlotByEquipSlot(itemSlot);
    if (player->GetItemByPos(INVENTORY_SLOT_BAG_0, itemSlot))
    {
        Item* item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, itemSlot);
        ItemTemplate const* pItemTemplate = player->GetItemByPos(INVENTORY_SLOT_BAG_0, itemSlot)->GetTemplate();

        if (!CheckItem(player, vItemTemplate, pItemTemplate))
        {
            player->SEND_GOSSIP_MENU(1, creature->GetGUID());
            player->CLOSE_GOSSIP_MENU();
            return false;
        }

        CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u WHERE guid = %u", vItemTemplate->ItemId, item->GetGUIDLow());
        item->TransmogEntry = vItemTemplate->ItemId;
        player->SetUInt32Value(transmogSlot, vItemTemplate->ItemId);
        player->SEND_GOSSIP_MENU(1, creature->GetGUID());
        player->CLOSE_GOSSIP_MENU();
    }

    return true;
}

bool Transmogrification::TransmogrifyEnchant(Player* player, uint16 action)
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

bool Transmogrification::RemoveItemTransmog(Player* player, uint16 action)
{
    itemSlot = GetItemSlotByAction(action);
    if (Item* item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, itemSlot))
    {
        CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = 0 WHERE guid = %u", item->GetGUIDLow());
        item->TransmogEntry = 0;
        player->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_ENTRYID + (itemSlot * 2), item->GetEntry());
    }
    player->CLOSE_GOSSIP_MENU();
    return true;
}

bool Transmogrification::RemoveEnchantTransmog(Player* player, uint16 action)
{
    itemSlot = GetItemSlotByAction(action);
    if (Item* item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, itemSlot))
    {
        CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEnchant = 0 WHERE guid = %u", item->GetGUIDLow());
        item->TransmogEnchant = 0;
        player->SetUInt16Value(PLAYER_VISIBLE_ITEM_1_ENCHANTMENT + (itemSlot * 2), 0, item->GetEnchantmentId(PERM_ENCHANTMENT_SLOT));
        player->SetUInt16Value(PLAYER_VISIBLE_ITEM_1_ENCHANTMENT + (itemSlot * 2), 1, item->GetEnchantmentId(TEMP_ENCHANTMENT_SLOT));
    }
    player->CLOSE_GOSSIP_MENU();
    return true;
}

bool Transmogrification::RemoveAllArmorTransmog(Player* player)
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

bool Transmogrification::RemoveAllWeaponTransmog(Player* player)
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

bool Transmogrification::RemoveAllEnchantTransmog(Player* player)
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

bool Transmogrification::RemoveAllTransmog(Player* player)
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
                slot == EQUIPMENT_SLOT_FEET ||
                slot == EQUIPMENT_SLOT_MAINHAND ||
                slot == EQUIPMENT_SLOT_OFFHAND ||
                slot == EQUIPMENT_SLOT_RANGED)
            {
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = 0 WHERE guid = %u", item->GetGUIDLow());
                item->TransmogEntry = 0;
                player->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_ENTRYID + (slot * 2), item->GetEntry());
            }
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

bool Transmogrification::CheckItem(Player* player, ItemTemplate const* vItemTemplate, ItemTemplate const* pItemTemplate)
{
    if (IsArmor(vItemTemplate))
        if (vItemTemplate->Class == pItemTemplate->Class && vItemTemplate->Material == pItemTemplate->Material && (vItemTemplate->InventoryType == pItemTemplate->InventoryType ||
            // Special case for Chest/Robe InventoryTypes because for some reason they are the same thing but handled differently
            (vItemTemplate->InventoryType == INVTYPE_CHEST && pItemTemplate->InventoryType == INVTYPE_ROBE) ||
            (vItemTemplate->InventoryType == INVTYPE_ROBE && pItemTemplate->InventoryType == INVTYPE_CHEST)))
            return true;

    if (IsWeapon(vItemTemplate))
    {
        if (vItemTemplate->Class == pItemTemplate->Class && vItemTemplate->SubClass == pItemTemplate->SubClass)
            return true;
        // Special case for Fist Weapons because the models for the right hand and left hand are different
        if (vItemTemplate->SubClass == ITEM_SUBCLASS_WEAPON_FIST && vItemTemplate->InventoryType == pItemTemplate->InventoryType)
            return true;
    }

    // Faction specific items
    if ((vItemTemplate->Flags2 == ITEM_FLAGS_EXTRA_ALLIANCE_ONLY && player->GetTeam() == ALLIANCE) &&
        (vItemTemplate->Flags2 & ITEM_FLAGS_EXTRA_HORDE_ONLY && player->GetTeam() == HORDE))
        return true;

    return false;
}

void AddSC_Transmogrification()
{
    new Transmogrification();
}
