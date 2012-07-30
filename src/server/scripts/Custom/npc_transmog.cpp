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

class npc_transmog : public CreatureScript
{
    public:
        npc_transmog() : CreatureScript("npc_transmog") {}

    bool OnGossipHello(Player* player, Creature* creature)
    {
        QueryResult result = WorldDatabase.PQuery("SELECT option_name, id, faction, account_id FROM transmog_armor_sets WHERE class='%d'", player->getClass());

        if (!result)
        {
            creature->MonsterWhisper("Unable to find transmog set data.", player->GetGUID());
            return false;
        }

        do
        {
            Field* fields = result->Fetch();
            if (fields[2].GetUInt32() == player->getFaction() || fields[2].GetUInt32() == 0 || fields[3].GetUInt32() == player->GetSession()->GetAccountId())
                player->ADD_GOSSIP_ITEM(0, fields[0].GetString(), GOSSIP_SENDER_MAIN, fields[1].GetUInt32());
        }
        while (result->NextRow());

        player->ADD_GOSSIP_ITEM(0, "Remove Transmogrifications", GOSSIP_SENDER_MAIN, 100000);
        player->SEND_GOSSIP_MENU(50055, creature->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action)
    {
        if (player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD) == 0
        || player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS) == 0
        || player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST) == 0
        || player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS) == 0
        || player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS) == 0
        || player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST) == 0
        || player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET) == 0)
        {
            creature->MonsterWhisper("You need to have a head, shoulders, chest, gloves, legs, belt and boots equipped to transmogrify.", player->GetGUID());
            player->CLOSE_GOSSIP_MENU();
            return false;
        }

        if (action == 100000)
        {
            for (uint8 Slot = EQUIPMENT_SLOT_START; Slot < EQUIPMENT_SLOT_END; Slot++)
            {
                if (Item* item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, Slot))
                {
                    CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = 0, TransmogOwner = 0 WHERE guid = %u", item->GetGUIDLow());
                    item->TransmogEntry = NULL;
                    item->TransmogOwner = NULL;
                    player->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_ENTRYID + (Slot * 2), item->GetEntry());
                }
            }

            player->CLOSE_GOSSIP_MENU();
            return true;
        }

        TransmogSets const* transmog = sObjectMgr->GetTransmogEntry(action);
        if (!transmog)
        {
            creature->MonsterWhisper("Unable to find transmog set.", player->GetGUID());
            player->CLOSE_GOSSIP_MENU();
            return false;
        }

        if (transmog->head_id != 0)
        {
             CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", transmog->head_id, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD)->GetGUIDLow());
             player->SetUInt32Value(head, transmog->head_id);
        }
        if (transmog->shoulder_id != 0)
        {
            CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", transmog->shoulder_id, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS)->GetGUIDLow());
            player->SetUInt32Value(shoulder, transmog->shoulder_id);
        }
        if (transmog->chest_id != 0)
        {
            CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", transmog->chest_id, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST)->GetGUIDLow());
            player->SetUInt32Value(chest, transmog->chest_id);
        }
        if (transmog->gloves_id != 0)
        {
            CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", transmog->gloves_id, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS)->GetGUIDLow());
            player->SetUInt32Value(gloves, transmog->gloves_id);
        }
        if (transmog->legs_id != 0)
        {
            CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", transmog->legs_id, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS)->GetGUIDLow());
            player->SetUInt32Value(legs, transmog->legs_id);
        }
        if (transmog->belt_id != 0)
        {
            CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", transmog->belt_id, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST)->GetGUIDLow());
            player->SetUInt32Value(belt, transmog->belt_id);
        }
        if (transmog->boots_id != 0)
        {
            CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", transmog->boots_id, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET)->GetGUIDLow());
            player->SetUInt32Value(boots, transmog->boots_id);
        }

        player->CLOSE_GOSSIP_MENU();
        return true;
    }
};

void AddSC_npc_transmog()
{
    new npc_transmog();
}