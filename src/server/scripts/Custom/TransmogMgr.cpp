#include "TransmogMgr.h"

bool Transmogrification::OnGossipHello(Player *player, Creature *creature)
{
    player->SetSelectedTransmogItemSlot(0);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TRAINER, "|TInterface\\icons\\Inv_Shoulder_66:30|t Individual", GOSSIP_SENDER_MAIN, TRANSMOG_ACTION_SHOW_INDIVIDUAL);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TRAINER, "|TInterface\\icons\\Spell_Holy_BlessingOfStrength:30|t Enchants", GOSSIP_SENDER_MAIN, TRANSMOG_ACTION_SHOW_ENCHANTS);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TRAINER, "|TInterface\\icons\\Inv_Enchant_Disenchant:30|t Remove Item Transmogrifications", GOSSIP_SENDER_MAIN, TRANSMOG_ACTION_SHOW_REMOVE_ITEM_TRANSMOG_OPTIONS);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TRAINER, "|TInterface\\icons\\Ability_DualWieldSpecialization:30|t Remove Enchant Transmogrifications", GOSSIP_SENDER_MAIN, TRANSMOG_ACTION_SHOW_REMOVE_ENCHANT_TRANSMOG_OPTIONS);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TRAINER, "|TInterface\\icons\\Spell_Shadow_SacrificialShield:30|t Remove All Transmogrifications", GOSSIP_SENDER_MAIN, TRANSMOG_ACTION_SELECT_REMOVE_EVERYTHING);

    player->SEND_GOSSIP_MENU(1, creature->GetGUID());
    return true;
}

bool Transmogrification::OnGossipSelect(Player *player, Creature *creature, uint32 sender, uint32 action)
{
    player->PlayerTalkClass->ClearMenus();

    if (action == TRANSMOG_ACTION_SHOW_INDIVIDUAL)
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

bool Transmogrification::ShowIndividualTransmogOptions(Player *player, Creature *creature)
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
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Boots", TRANSMOG_ACTION_SHOW_INDIVIDUAL, TRANSMOG_ACTION_SHOW_INDIVIDUAL_FEET);

    if (player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND))
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Main Hand", TRANSMOG_ACTION_SHOW_INDIVIDUAL, TRANSMOG_ACTION_SHOW_INDIVIDUAL_MAINHAND);

    if (player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND))
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Off Hand", TRANSMOG_ACTION_SHOW_INDIVIDUAL, TRANSMOG_ACTION_SHOW_INDIVIDUAL_OFFHAND);

    if (Item* item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_RANGED))
        if (item->GetTemplate()->InventoryType != INVTYPE_RELIC)
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Ranged", TRANSMOG_ACTION_SHOW_INDIVIDUAL, TRANSMOG_ACTION_SHOW_INDIVIDUAL_RANGED);

    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Back", TRANSMOG_ACTION_SHOW_INDIVIDUAL, TRANSMOG_ACTION_MAIN_MENU);

    player->SEND_GOSSIP_MENU(1, creature->GetGUID());

    player->SetSelectedTransmogItemSlot(0);
    return true;
}

bool Transmogrification::ShowTransmogEnchants(Player *player, Creature *creature)
{
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Mongoose", TRANSMOG_ACTION_SHOW_ENCHANTS, TRANSMOG_ENCHANT_MONGOOSE);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Executioner", TRANSMOG_ACTION_SHOW_ENCHANTS, TRANSMOG_ENCHANT_EXECUTIONER);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Sunfire", TRANSMOG_ACTION_SHOW_ENCHANTS, TRANSMOG_ENCHANT_SUNFIRE);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Soulfrost", TRANSMOG_ACTION_SHOW_ENCHANTS, TRANSMOG_ENCHANT_SOULFROST);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Blood Draining", TRANSMOG_ACTION_SHOW_ENCHANTS, TRANSMOG_ENCHANT_BLOOD_DRAINING);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Razorice", TRANSMOG_ACTION_SHOW_ENCHANTS, TRANSMOG_ENCHANT_RAZORICE);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Berserking", TRANSMOG_ACTION_SHOW_ENCHANTS, TRANSMOG_ENCHANT_BERSERKING);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Spellsurge", TRANSMOG_ACTION_SHOW_ENCHANTS, TRANSMOG_ENCHANT_SPELLSURGE);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Deathfrost", TRANSMOG_ACTION_SHOW_ENCHANTS, TRANSMOG_ENCHANT_DEATHFROST);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Sparkles", TRANSMOG_ACTION_SHOW_ENCHANTS, TRANSMOG_ENCHANT_SPARKLES);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Red Glow", TRANSMOG_ACTION_SHOW_ENCHANTS, TRANSMOG_ENCHANT_GLOW_RED);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Yellow Glow", TRANSMOG_ACTION_SHOW_ENCHANTS, TRANSMOG_ENCHANT_GLOW_YELLOW);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Blue Glow", TRANSMOG_ACTION_SHOW_ENCHANTS, TRANSMOG_ENCHANT_GLOW_BLUE);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Purple Glow", TRANSMOG_ACTION_SHOW_ENCHANTS, TRANSMOG_ENCHANT_GLOW_PURPLE);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Orange Glow", TRANSMOG_ACTION_SHOW_ENCHANTS, TRANSMOG_ENCHANT_GLOW_ORANGE);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Green Glow", TRANSMOG_ACTION_SHOW_ENCHANTS, TRANSMOG_ENCHANT_GLOW_GREEN);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Grey Glow", TRANSMOG_ACTION_SHOW_ENCHANTS, TRANSMOG_ENCHANT_GLOW_GREY);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "White Glow", TRANSMOG_ACTION_SHOW_ENCHANTS, TRANSMOG_ENCHANT_GLOW_WHITE);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "No Visual", TRANSMOG_ACTION_SHOW_ENCHANTS, TRANSMOG_ENCHANT_NO_VISUAL);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Back", TRANSMOG_ACTION_SHOW_ENCHANTS, TRANSMOG_ACTION_MAIN_MENU);

    player->SEND_GOSSIP_MENU(1, creature->GetGUID());
    return true;
}

bool Transmogrification::ShowRemoveTransmogItemOptions(Player *player, Creature *creature)
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
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Boots", TRANSMOG_ACTION_SHOW_REMOVE_ITEM_TRANSMOG_OPTIONS, TRANSMOG_ACTION_SELECT_REMOVE_FEET);

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

bool Transmogrification::ShowRemoveTransmogEnchantOptions(Player *player, Creature *creature)
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

bool Transmogrification::SelectIndividualTransmog(Player *player, Creature *creature, uint16 action)
{
    uint8 itemSlot = GetItemSlotByAction(action);
    player->SetSelectedTransmogItemSlot(itemSlot);
    const ItemTemplate *pItemTemplate = player->GetItemByPos(INVENTORY_SLOT_BAG_0, itemSlot)->GetTemplate();
    const VendorItemData *items = creature->GetVendorItems();
    if (!items)
    {
        ChatHandler(player).PSendSysMessage("Unable to find item data");
        player->SetSelectedTransmogItemSlot(0);
        player->CLOSE_GOSSIP_MENU();
        return false;
    }

    player->CLOSE_GOSSIP_MENU();

    uint16 itemCount = items->GetItemCount();
    uint8 count = 0;
    uint8 slot = 0;

    WorldPacket data(SMSG_LIST_INVENTORY, 8 + 1 + itemCount * 8 * 4);
    data << uint64(creature->GetGUID());
    size_t countPos = data.wpos();
    data << uint8(count);

    for (uint16 slot = 0; slot < itemCount; ++slot)
    {
        if (const VendorItem *vItem = items->GetItem(slot))
        {
            if (const ItemTemplate *vItemTemplate = sObjectMgr->GetItemTemplate(vItem->item))
            {
                if (!CheckItem(player, vItemTemplate, pItemTemplate))
                    continue;

                ++count;
                data << uint32(count + 1);                      // Client expects counting to start at 1
                data << uint32(vItem->item);                    // Entry
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
        ChatHandler(player).PSendSysMessage("Unable to find item data");
        player->SetSelectedTransmogItemSlot(0);
        player->CLOSE_GOSSIP_MENU();
        return false;
    }

    data.put<uint8>(countPos, count);
    player->GetSession()->SendPacket(&data);
    return true;
}

bool Transmogrification::CheckItem(Player *player, const ItemTemplate *vItemTemplate, const ItemTemplate *pItemTemplate)
{
    // Faction specific items
    if ((vItemTemplate->Flags2 == ITEM_FLAGS_EXTRA_ALLIANCE_ONLY && player->GetTeam() == HORDE) ||
        (vItemTemplate->Flags2 == ITEM_FLAGS_EXTRA_HORDE_ONLY && player->GetTeam() == ALLIANCE))
        return false;

    // Class specific items
    if (!(vItemTemplate->AllowableClass & player->getClassMask()))
        return false;

    if (IsArmor(vItemTemplate))
        if (vItemTemplate->Class != pItemTemplate->Class || vItemTemplate->SubClass != pItemTemplate->SubClass || vItemTemplate->InventoryType != pItemTemplate->InventoryType)
            return false;

    if (IsWeapon(vItemTemplate))
    {
        if (vItemTemplate->Class != pItemTemplate->Class || vItemTemplate->SubClass != pItemTemplate->SubClass)
            return false;

        // Special case for Fist Weapons because the models for the right hand and left hand are different
        if (vItemTemplate->SubClass == ITEM_SUBCLASS_WEAPON_FIST && vItemTemplate->InventoryType != pItemTemplate->InventoryType)
            return false;
    }

    return true;
}

bool Transmogrification::TransmogrifyIndividual(Player *player, Creature *creature, uint32 item)
{
    const ItemTemplate *vItemTemplate = sObjectMgr->GetItemTemplate(item);
    uint8 itemSlot = player->GetSelectedTransmogItemSlot();
    uint16 transmogSlot = GetTransmogSlotByEquipSlot(itemSlot);
    if (player->GetItemByPos(INVENTORY_SLOT_BAG_0, itemSlot))
    {
        Item* pItem = player->GetItemByPos(INVENTORY_SLOT_BAG_0, itemSlot);
        const ItemTemplate *pItemTemplate = player->GetItemByPos(INVENTORY_SLOT_BAG_0, itemSlot)->GetTemplate();

        if (!CheckItem(player, vItemTemplate, pItemTemplate))
        {
            player->SetSelectedTransmogItemSlot(0);
            player->SEND_GOSSIP_MENU(1, creature->GetGUID());
            player->CLOSE_GOSSIP_MENU();
            return false;
        }

        CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u WHERE guid = %u", vItemTemplate->ItemId, pItem->GetGUIDLow());
        pItem->TransmogEntry = vItemTemplate->ItemId;
        player->SetUInt32Value(transmogSlot, vItemTemplate->ItemId);
        player->SetSelectedTransmogItemSlot(0);
        player->SEND_GOSSIP_MENU(1, creature->GetGUID());
        player->CLOSE_GOSSIP_MENU();
    }

    return true;
}

bool Transmogrification::TransmogrifyEnchant(Player *player, uint16 action)
{
    if (action && player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND) != 0)
    {
        const ItemTemplate *inventoryItem = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND)->GetTemplate();
        if (inventoryItem->Class == ITEM_CLASS_WEAPON)
        {
            CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEnchant = %u WHERE guid = %u",
            action, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND)->GetGUIDLow());

            player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND)->TransmogEnchant = action;
            player->SetUInt16Value(TRANSMOG_SLOT_MAINHAND_ENCHANT, 0, action);
            player->SetUInt16Value(TRANSMOG_SLOT_MAINHAND_ENCHANT, 1, action);
        }
    }

    if (action && player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND) != 0)
    {
        const ItemTemplate *inventoryItem = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND)->GetTemplate();
        if (inventoryItem->Class == ITEM_CLASS_WEAPON)
        {
            CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEnchant = %u WHERE guid = %u",
            action, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND)->GetGUIDLow());

            player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND)->TransmogEnchant = action;
            player->SetUInt16Value(TRANSMOG_SLOT_OFFHAND_ENCHANT, 0, action);
            player->SetUInt16Value(TRANSMOG_SLOT_OFFHAND_ENCHANT, 1, action);
        }
    }

    player->CLOSE_GOSSIP_MENU();
    return true;
}

bool Transmogrification::RemoveItemTransmog(Player *player, uint16 action)
{
    uint8 itemSlot = GetItemSlotByAction(action);
    if (Item *item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, itemSlot))
    {
        CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = 0 WHERE guid = %u", item->GetGUIDLow());
        item->TransmogEntry = 0;
        player->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_ENTRYID + (itemSlot * 2), item->GetEntry());
    }
    player->CLOSE_GOSSIP_MENU();
    return true;
}

bool Transmogrification::RemoveEnchantTransmog(Player *player, uint16 action)
{
    uint8 itemSlot = GetItemSlotByAction(action);
    if (Item *item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, itemSlot))
    {
        CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEnchant = 0 WHERE guid = %u", item->GetGUIDLow());
        item->TransmogEnchant = 0;
        player->SetUInt16Value(PLAYER_VISIBLE_ITEM_1_ENCHANTMENT + (itemSlot * 2), 0, item->GetEnchantmentId(PERM_ENCHANTMENT_SLOT));
        player->SetUInt16Value(PLAYER_VISIBLE_ITEM_1_ENCHANTMENT + (itemSlot * 2), 1, item->GetEnchantmentId(TEMP_ENCHANTMENT_SLOT));
    }
    player->CLOSE_GOSSIP_MENU();
    return true;
}

bool Transmogrification::RemoveAllArmorTransmog(Player *player)
{
    for (uint8 slot = EQUIPMENT_SLOT_START; slot < EQUIPMENT_SLOT_END; slot++)
    {
        if (Item *item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, slot))
        {
            if (slot == EQUIPMENT_SLOT_HEAD ||
                slot == EQUIPMENT_SLOT_SHOULDERS ||
                slot == EQUIPMENT_SLOT_CHEST ||
                slot == EQUIPMENT_SLOT_HANDS ||
                slot == EQUIPMENT_SLOT_LEGS ||
                slot == EQUIPMENT_SLOT_WRISTS ||
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

bool Transmogrification::RemoveAllWeaponTransmog(Player *player)
{
    for (uint8 slot = EQUIPMENT_SLOT_START; slot < EQUIPMENT_SLOT_END; slot++)
    {
        if (Item *item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, slot))
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

bool Transmogrification::RemoveAllEnchantTransmog(Player *player)
{
    for (uint8 slot = EQUIPMENT_SLOT_START; slot < EQUIPMENT_SLOT_END; slot++)
    {
        if (Item *item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, slot))
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

bool Transmogrification::RemoveAllTransmog(Player *player)
{
    for (uint8 slot = EQUIPMENT_SLOT_START; slot < EQUIPMENT_SLOT_END; slot++)
    {
        if (Item *item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, slot))
        {
            if (slot == EQUIPMENT_SLOT_HEAD ||
                slot == EQUIPMENT_SLOT_SHOULDERS ||
                slot == EQUIPMENT_SLOT_CHEST ||
                slot == EQUIPMENT_SLOT_HANDS ||
                slot == EQUIPMENT_SLOT_LEGS ||
                slot == EQUIPMENT_SLOT_WRISTS ||
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

void AddSC_Transmogrification()
{
    new Transmogrification();
}
