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
        // Warrior
        if (player->getClass() == 1)
        {
            player->ADD_GOSSIP_ITEM(0, "Season 1", GOSSIP_SENDER_MAIN, 10);
            player->ADD_GOSSIP_ITEM(0, "Season 2", GOSSIP_SENDER_MAIN, 11);
            player->ADD_GOSSIP_ITEM(0, "Season 3", GOSSIP_SENDER_MAIN, 12);
            player->ADD_GOSSIP_ITEM(0, "Season 4", GOSSIP_SENDER_MAIN, 13);
            if (player->GetTeam() == ALLIANCE)
            {
                player->ADD_GOSSIP_ITEM(0, "Rank 7", GOSSIP_SENDER_MAIN, 14);
                player->ADD_GOSSIP_ITEM(0, "Rank 14", GOSSIP_SENDER_MAIN, 16);
            }
            if (player->GetTeam() == HORDE)
            {
                player->ADD_GOSSIP_ITEM(0, "Rank 7", GOSSIP_SENDER_MAIN, 15);
                player->ADD_GOSSIP_ITEM(0, "Rank 14", GOSSIP_SENDER_MAIN, 17);
            }
            player->ADD_GOSSIP_ITEM(0, "Tier 2.5", GOSSIP_SENDER_MAIN, 18);
            player->ADD_GOSSIP_ITEM(0, "Tier 3", GOSSIP_SENDER_MAIN, 19);
        }

        // Paladin
        if (player->getClass() == 2)
        {
            player->ADD_GOSSIP_ITEM(0, "Season 1", GOSSIP_SENDER_MAIN, 50);
            player->ADD_GOSSIP_ITEM(0, "Season 2", GOSSIP_SENDER_MAIN, 51);
            player->ADD_GOSSIP_ITEM(0, "Season 3", GOSSIP_SENDER_MAIN, 52);
            player->ADD_GOSSIP_ITEM(0, "Season 4", GOSSIP_SENDER_MAIN, 53);
            if (player->GetTeam() == ALLIANCE)
            {
                player->ADD_GOSSIP_ITEM(0, "Rank 7", GOSSIP_SENDER_MAIN, 54);
                player->ADD_GOSSIP_ITEM(0, "Rank 14", GOSSIP_SENDER_MAIN, 56);
            }
            if (player->GetTeam() == HORDE)
            {
                player->ADD_GOSSIP_ITEM(0, "Rank 7", GOSSIP_SENDER_MAIN, 55);
                player->ADD_GOSSIP_ITEM(0, "Rank 14", GOSSIP_SENDER_MAIN, 57);
            }
            player->ADD_GOSSIP_ITEM(0, "Tier 2.5", GOSSIP_SENDER_MAIN, 58);
            player->ADD_GOSSIP_ITEM(0, "Tier 3", GOSSIP_SENDER_MAIN, 59);
        }

        // Death Knight
        if (player->getClass() == 6)
        {
            player->ADD_GOSSIP_ITEM(0, "Season 1", GOSSIP_SENDER_MAIN, 100);
            player->ADD_GOSSIP_ITEM(0, "Season 2", GOSSIP_SENDER_MAIN, 101);
            player->ADD_GOSSIP_ITEM(0, "Season 3", GOSSIP_SENDER_MAIN, 102);
            player->ADD_GOSSIP_ITEM(0, "Season 4", GOSSIP_SENDER_MAIN, 103);
            player->ADD_GOSSIP_ITEM(0, "Rank 7", GOSSIP_SENDER_MAIN, 104);
            player->ADD_GOSSIP_ITEM(0, "Rank 14", GOSSIP_SENDER_MAIN, 105);
            player->ADD_GOSSIP_ITEM(0, "Tier 2.5", GOSSIP_SENDER_MAIN, 106);
            player->ADD_GOSSIP_ITEM(0, "Tier 3", GOSSIP_SENDER_MAIN, 107);
        }

        // Hunter
        if (player->getClass() == 3)
        {
            player->ADD_GOSSIP_ITEM(0, "Season 1", GOSSIP_SENDER_MAIN, 150);
            player->ADD_GOSSIP_ITEM(0, "Season 2", GOSSIP_SENDER_MAIN, 151);
            player->ADD_GOSSIP_ITEM(0, "Season 3", GOSSIP_SENDER_MAIN, 152);
            player->ADD_GOSSIP_ITEM(0, "Season 4", GOSSIP_SENDER_MAIN, 153);
            if (player->GetTeam() == ALLIANCE)
            {
                player->ADD_GOSSIP_ITEM(0, "Rank 7", GOSSIP_SENDER_MAIN, 154);
                player->ADD_GOSSIP_ITEM(0, "Rank 14", GOSSIP_SENDER_MAIN, 156);
            }
            if (player->GetTeam() == HORDE)
            {
                player->ADD_GOSSIP_ITEM(0, "Rank 7", GOSSIP_SENDER_MAIN, 155);
                player->ADD_GOSSIP_ITEM(0, "Rank 14", GOSSIP_SENDER_MAIN, 157);
            }
            player->ADD_GOSSIP_ITEM(0, "Tier 2.5", GOSSIP_SENDER_MAIN, 158);
            player->ADD_GOSSIP_ITEM(0, "Tier 3", GOSSIP_SENDER_MAIN, 159);
        }

        // Shaman
        if (player->getClass() == 7)
        {
            player->ADD_GOSSIP_ITEM(0, "Season 1", GOSSIP_SENDER_MAIN, 200);
            player->ADD_GOSSIP_ITEM(0, "Season 2", GOSSIP_SENDER_MAIN, 201);
            player->ADD_GOSSIP_ITEM(0, "Season 3", GOSSIP_SENDER_MAIN, 202);
            player->ADD_GOSSIP_ITEM(0, "Season 4", GOSSIP_SENDER_MAIN, 203);
            player->ADD_GOSSIP_ITEM(0, "Rank 7", GOSSIP_SENDER_MAIN, 204);
            player->ADD_GOSSIP_ITEM(0, "Rank 14", GOSSIP_SENDER_MAIN, 205);
            player->ADD_GOSSIP_ITEM(0, "Tier 2.5", GOSSIP_SENDER_MAIN, 206);
            player->ADD_GOSSIP_ITEM(0, "Tier 3", GOSSIP_SENDER_MAIN, 207);
        }

        // Rogue
        if (player->getClass() == 4)
        {
            player->ADD_GOSSIP_ITEM(0, "Season 1", GOSSIP_SENDER_MAIN, 250);
            player->ADD_GOSSIP_ITEM(0, "Season 2", GOSSIP_SENDER_MAIN, 251);
            player->ADD_GOSSIP_ITEM(0, "Season 3", GOSSIP_SENDER_MAIN, 252);
            player->ADD_GOSSIP_ITEM(0, "Season 4", GOSSIP_SENDER_MAIN, 253);
            if (player->GetTeam() == ALLIANCE)
            {
                player->ADD_GOSSIP_ITEM(0, "Rank 7", GOSSIP_SENDER_MAIN, 254);
                player->ADD_GOSSIP_ITEM(0, "Rank 14", GOSSIP_SENDER_MAIN, 256);
            }
            if (player->GetTeam() == HORDE)
            {
                player->ADD_GOSSIP_ITEM(0, "Rank 7", GOSSIP_SENDER_MAIN, 255);
                player->ADD_GOSSIP_ITEM(0, "Rank 14", GOSSIP_SENDER_MAIN, 257);
            }
            player->ADD_GOSSIP_ITEM(0, "Tier 2.5", GOSSIP_SENDER_MAIN, 258);
            player->ADD_GOSSIP_ITEM(0, "Tier 3", GOSSIP_SENDER_MAIN, 259);
            if (player->GetSession()->GetAccountId() == 5)
                player->ADD_GOSSIP_ITEM(0, "Custom", GOSSIP_SENDER_MAIN, 1001);
            if (player->GetSession()->GetAccountId() == 18)
                player->ADD_GOSSIP_ITEM(0, "Custom", GOSSIP_SENDER_MAIN, 1005);
        }

        // Druid
        if (player->getClass() == 11)
        {
            player->ADD_GOSSIP_ITEM(0, "Season 1", GOSSIP_SENDER_MAIN, 300);
            player->ADD_GOSSIP_ITEM(0, "Season 2", GOSSIP_SENDER_MAIN, 301);
            player->ADD_GOSSIP_ITEM(0, "Season 3", GOSSIP_SENDER_MAIN, 302);
            player->ADD_GOSSIP_ITEM(0, "Season 4", GOSSIP_SENDER_MAIN, 303);
            if (player->GetTeam() == ALLIANCE)
            {
                player->ADD_GOSSIP_ITEM(0, "Rank 7", GOSSIP_SENDER_MAIN, 304);
                player->ADD_GOSSIP_ITEM(0, "Rank 14", GOSSIP_SENDER_MAIN, 306);
            }
            if (player->GetTeam() == HORDE)
            {
                player->ADD_GOSSIP_ITEM(0, "Rank 7", GOSSIP_SENDER_MAIN, 305);
                player->ADD_GOSSIP_ITEM(0, "Rank 14", GOSSIP_SENDER_MAIN, 307);
            }
            player->ADD_GOSSIP_ITEM(0, "Tier 2.5", GOSSIP_SENDER_MAIN, 308);
            player->ADD_GOSSIP_ITEM(0, "Tier 3", GOSSIP_SENDER_MAIN, 309);
            if (player->GetSession()->GetAccountId() == 5)
                player->ADD_GOSSIP_ITEM(0, "Custom", GOSSIP_SENDER_MAIN, 1002);
        }

        // Priest
        if (player->getClass() == 5)
        {
            player->ADD_GOSSIP_ITEM(0, "Season 1", GOSSIP_SENDER_MAIN, 350);
            player->ADD_GOSSIP_ITEM(0, "Season 2", GOSSIP_SENDER_MAIN, 351);
            player->ADD_GOSSIP_ITEM(0, "Season 3", GOSSIP_SENDER_MAIN, 352);
            player->ADD_GOSSIP_ITEM(0, "Season 4", GOSSIP_SENDER_MAIN, 353);
            if (player->GetTeam() == ALLIANCE)
            {
                player->ADD_GOSSIP_ITEM(0, "Rank 7", GOSSIP_SENDER_MAIN, 354);
                player->ADD_GOSSIP_ITEM(0, "Rank 14", GOSSIP_SENDER_MAIN, 356);
            }
            if (player->GetTeam() == HORDE)
            {
                player->ADD_GOSSIP_ITEM(0, "Rank 7", GOSSIP_SENDER_MAIN, 355);
                player->ADD_GOSSIP_ITEM(0, "Rank 14", GOSSIP_SENDER_MAIN, 357);
            }
            player->ADD_GOSSIP_ITEM(0, "Tier 2.5", GOSSIP_SENDER_MAIN, 358);
            player->ADD_GOSSIP_ITEM(0, "Tier 3", GOSSIP_SENDER_MAIN, 359);
            if (player->GetSession()->GetAccountId() == 5)
                player->ADD_GOSSIP_ITEM(0, "Custom", GOSSIP_SENDER_MAIN, 1003);
        }

        // Mage
        if (player->getClass() == 8)
        {
            player->ADD_GOSSIP_ITEM(0, "Season 1", GOSSIP_SENDER_MAIN, 400);
            player->ADD_GOSSIP_ITEM(0, "Season 2", GOSSIP_SENDER_MAIN, 401);
            player->ADD_GOSSIP_ITEM(0, "Season 3", GOSSIP_SENDER_MAIN, 402);
            player->ADD_GOSSIP_ITEM(0, "Season 4", GOSSIP_SENDER_MAIN, 403);
            if (player->GetTeam() == ALLIANCE)
            {
                player->ADD_GOSSIP_ITEM(0, "Rank 7", GOSSIP_SENDER_MAIN, 404);
                player->ADD_GOSSIP_ITEM(0, "Rank 14", GOSSIP_SENDER_MAIN, 406);
            }
            if (player->GetTeam() == HORDE)
            {
                player->ADD_GOSSIP_ITEM(0, "Rank 7", GOSSIP_SENDER_MAIN, 405);
                player->ADD_GOSSIP_ITEM(0, "Rank 14", GOSSIP_SENDER_MAIN, 407);
            }
            player->ADD_GOSSIP_ITEM(0, "Tier 2.5", GOSSIP_SENDER_MAIN, 408);
            player->ADD_GOSSIP_ITEM(0, "Tier 3", GOSSIP_SENDER_MAIN, 409);
            if (player->GetSession()->GetAccountId() == 5)
                player->ADD_GOSSIP_ITEM(0, "Custom", GOSSIP_SENDER_MAIN, 1000);
            if (player->GetSession()->GetAccountId() == 51)
                player->ADD_GOSSIP_ITEM(0, "Custom", GOSSIP_SENDER_MAIN, 1004);
        }

        // Warlock
        if (player->getClass() == 9)
        {
            player->ADD_GOSSIP_ITEM(0, "Season 1", GOSSIP_SENDER_MAIN, 450);
            player->ADD_GOSSIP_ITEM(0, "Season 2", GOSSIP_SENDER_MAIN, 451);
            player->ADD_GOSSIP_ITEM(0, "Season 3", GOSSIP_SENDER_MAIN, 452);
            player->ADD_GOSSIP_ITEM(0, "Season 4", GOSSIP_SENDER_MAIN, 453);
            if (player->GetTeam() == ALLIANCE)
            {
                player->ADD_GOSSIP_ITEM(0, "Rank 7", GOSSIP_SENDER_MAIN, 454);
                player->ADD_GOSSIP_ITEM(0, "Rank 14", GOSSIP_SENDER_MAIN, 456);
            }
            if (player->GetTeam() == HORDE)
            {
                player->ADD_GOSSIP_ITEM(0, "Rank 7", GOSSIP_SENDER_MAIN, 455);
                player->ADD_GOSSIP_ITEM(0, "Rank 14", GOSSIP_SENDER_MAIN, 457);
            }
            player->ADD_GOSSIP_ITEM(0, "Tier 2.5", GOSSIP_SENDER_MAIN, 458);
            player->ADD_GOSSIP_ITEM(0, "Tier 3", GOSSIP_SENDER_MAIN, 459);
        }
        player->ADD_GOSSIP_ITEM(0, "Remove Transmogrifications", GOSSIP_SENDER_MAIN, 500);
        player->SEND_GOSSIP_MENU(50055,creature->GetGUID());
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
        switch (action)
        {
//================Warrior=================
            // Season 1
            case 10:
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 24545, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 24546, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 24544, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 24549, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 24547, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 28995, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 28383, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET)->GetGUIDLow());
                player->SetUInt32Value(head, 24545);
                player->SetUInt32Value(shoulder, 24546);
                player->SetUInt32Value(chest, 24544);
                player->SetUInt32Value(gloves, 24549);
                player->SetUInt32Value(legs, 24547);
                player->SetUInt32Value(belt, 28995);
                player->SetUInt32Value(boots, 28383);
                break;
            // Season 2
            case 11:
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 30488, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 30490, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 30486, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 30487, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 30489, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 32805, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 32793, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET)->GetGUIDLow());
                player->SetUInt32Value(head, 30488);
                player->SetUInt32Value(shoulder, 30490);
                player->SetUInt32Value(chest, 30486);
                player->SetUInt32Value(gloves, 30487);
                player->SetUInt32Value(legs, 30489);
                player->SetUInt32Value(belt, 32805);
                player->SetUInt32Value(boots, 32793);
                break;
            // Season 3
            case 12:
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 33730, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 33732, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 33728, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 33729, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 33731, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 33811, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 33812, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET)->GetGUIDLow());
                player->SetUInt32Value(head, 33730);
                player->SetUInt32Value(shoulder, 33732);
                player->SetUInt32Value(chest, 33728);
                player->SetUInt32Value(gloves, 33729);
                player->SetUInt32Value(legs, 33731);
                player->SetUInt32Value(belt, 33811);
                player->SetUInt32Value(boots, 33812);
                break;
            // Season 4
            case 13:
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 35068, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 35070, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 35066, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 35067, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 35069, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 35161, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 35146, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET)->GetGUIDLow());
                player->SetUInt32Value(head, 35068);
                player->SetUInt32Value(shoulder, 35070);
                player->SetUInt32Value(chest, 35066);
                player->SetUInt32Value(gloves, 35067);
                player->SetUInt32Value(legs, 35069);
                player->SetUInt32Value(belt, 35161);
                player->SetUInt32Value(boots, 35146);
                break;
            // Rank 7 Alliance
            case 14:
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 23314, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 23315, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 23300, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 23286, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 23301, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 34651, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 23287, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET)->GetGUIDLow());
                player->SetUInt32Value(head, 23314);
                player->SetUInt32Value(shoulder, 23315);
                player->SetUInt32Value(chest, 23300);
                player->SetUInt32Value(gloves, 23286);
                player->SetUInt32Value(legs, 23301);
                player->SetUInt32Value(belt, 34651);
                player->SetUInt32Value(boots, 23287);
                break;
            // Rank 7 Horde
            case 15:
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 23244, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 23243, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 22872, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 22868, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 22873, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 34651, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 22858, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET)->GetGUIDLow());
                player->SetUInt32Value(head, 23244);
                player->SetUInt32Value(shoulder, 23243);
                player->SetUInt32Value(chest, 22872);
                player->SetUInt32Value(gloves, 22868);
                player->SetUInt32Value(legs, 22873);
                player->SetUInt32Value(belt, 34651);
                player->SetUInt32Value(boots, 22858);
                break;
            // Rank 14 Alliance
            case 16:
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 16478, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 16480, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 16477, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 16484, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 16479, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 34651, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 16483, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET)->GetGUIDLow());
                player->SetUInt32Value(head, 16478);
                player->SetUInt32Value(shoulder, 16480);
                player->SetUInt32Value(chest, 16477);
                player->SetUInt32Value(gloves, 16484);
                player->SetUInt32Value(legs, 16479);
                player->SetUInt32Value(belt, 34651);
                player->SetUInt32Value(boots, 16483);
                break;
            // Rank 14 Horde
            case 17:
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 16542, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 16544, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 16541, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 16548, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 16543, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 34651, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 16545, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET)->GetGUIDLow());
                player->SetUInt32Value(head, 16542);
                player->SetUInt32Value(shoulder, 16544);
                player->SetUInt32Value(chest, 16541);
                player->SetUInt32Value(gloves, 16548);
                player->SetUInt32Value(legs, 16543);
                player->SetUInt32Value(belt, 34651);
                player->SetUInt32Value(boots, 16545);
                    break;
            // Tier 2.5
            case 18:
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 21329, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 21330, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 21331, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 21581, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 21332, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 21598, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 21333, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET)->GetGUIDLow());
                player->SetUInt32Value(head, 21329);
                player->SetUInt32Value(shoulder, 21330);
                player->SetUInt32Value(chest, 21331);
                player->SetUInt32Value(gloves, 21581);
                player->SetUInt32Value(legs, 21332);
                player->SetUInt32Value(belt, 21598);
                player->SetUInt32Value(boots, 21333);
                break;
            // Tier 3
            case 19:
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 22418, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 22419, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 22416, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 22421, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 22417, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 22422, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 22420, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET)->GetGUIDLow());
                player->SetUInt32Value(head, 22418);
                player->SetUInt32Value(shoulder, 22419);
                player->SetUInt32Value(chest, 22416);
                player->SetUInt32Value(gloves, 22421);
                player->SetUInt32Value(legs, 22417);
                player->SetUInt32Value(belt, 22422);
                player->SetUInt32Value(boots, 22420);
                break;
//================Paladin=================
            // Season 1
            case 50:
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 27704, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 27706, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 27702, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 27703, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 27705, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 28641, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 28642, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET)->GetGUIDLow());
                player->SetUInt32Value(head, 27704);
                player->SetUInt32Value(shoulder, 27706);
                player->SetUInt32Value(chest, 27702);
                player->SetUInt32Value(gloves, 27703);
                player->SetUInt32Value(legs, 27705);
                player->SetUInt32Value(belt, 28641);
                player->SetUInt32Value(boots, 28642);
                break;
            // Season 2
            case 51:
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 31997, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 31996, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 31992, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 31993, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 31995, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 32801, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 32789, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET)->GetGUIDLow());
                player->SetUInt32Value(head, 31997);
                player->SetUInt32Value(shoulder, 31996);
                player->SetUInt32Value(chest, 31992);
                player->SetUInt32Value(gloves, 31993);
                player->SetUInt32Value(legs, 31995);
                player->SetUInt32Value(belt, 32801);
                player->SetUInt32Value(boots, 32789);
                break;
            // Season 3
            case 52:
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 33697, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 33699, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 33695, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 33696, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 33698, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 33888, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 33890, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET)->GetGUIDLow());
                player->SetUInt32Value(head, 33697);
                player->SetUInt32Value(shoulder, 33699);
                player->SetUInt32Value(chest, 33695);
                player->SetUInt32Value(gloves, 33696);
                player->SetUInt32Value(legs, 33698);
                player->SetUInt32Value(belt, 33888);
                player->SetUInt32Value(boots, 33890);
                break;
            // Season 4
            case 53:
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 35029, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 35031, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 35027, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 35028, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 35030, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 35155, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 35140, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET)->GetGUIDLow());
                player->SetUInt32Value(head, 35029);
                player->SetUInt32Value(shoulder, 35031);
                player->SetUInt32Value(chest, 35027);
                player->SetUInt32Value(gloves, 35028);
                player->SetUInt32Value(legs, 35030);
                player->SetUInt32Value(belt, 35155);
                player->SetUInt32Value(boots, 35140);
                break;
            // Rank 7 Alliance
            case 54:
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 23314, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 23315, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 23300, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 23286, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 23301, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 34651, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 23287, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET)->GetGUIDLow());
                player->SetUInt32Value(head, 23314);
                player->SetUInt32Value(shoulder, 23315);
                player->SetUInt32Value(chest, 23300);
                player->SetUInt32Value(gloves, 23286);
                player->SetUInt32Value(legs, 23301);
                player->SetUInt32Value(belt, 34651);
                player->SetUInt32Value(boots, 23287);
                break;
            // Rank 7 Horde
            case 55:
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 23244, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 23243, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 22872, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 22868, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 22873, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 34651, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 22858, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET)->GetGUIDLow());
                player->SetUInt32Value(head, 23244);
                player->SetUInt32Value(shoulder, 23243);
                player->SetUInt32Value(chest, 22872);
                player->SetUInt32Value(gloves, 22868);
                player->SetUInt32Value(legs, 22873);
                player->SetUInt32Value(belt, 34651);
                player->SetUInt32Value(boots, 22858);
                break;
            // Rank 14 Alliance
            case 56:
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 16478, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 16480, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 16477, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 16484, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 16479, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 34651, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 16483, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET)->GetGUIDLow());
                player->SetUInt32Value(head, 16478);
                player->SetUInt32Value(shoulder, 16480);
                player->SetUInt32Value(chest, 16477);
                player->SetUInt32Value(gloves, 16484);
                player->SetUInt32Value(legs, 16479);
                player->SetUInt32Value(belt, 34651);
                player->SetUInt32Value(boots, 16483);
                break;
            // Rank 14 Horde
            case 57:
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 16542, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 16544, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 16541, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 16548, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 16543, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 34651, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 16545, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET)->GetGUIDLow());
                player->SetUInt32Value(head, 16542);
                player->SetUInt32Value(shoulder, 16544);
                player->SetUInt32Value(chest, 16541);
                player->SetUInt32Value(gloves, 16548);
                player->SetUInt32Value(legs, 16543);
                player->SetUInt32Value(belt, 34651);
                player->SetUInt32Value(boots, 16545);
                break;
            // Tier 2.5
            case 58:
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 21387, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 21391, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 21389, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 21623, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 21390, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 21606, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 21388, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET)->GetGUIDLow());
                player->SetUInt32Value(head, 21387);
                player->SetUInt32Value(shoulder, 21391);
                player->SetUInt32Value(chest, 21389);
                player->SetUInt32Value(gloves, 21623);
                player->SetUInt32Value(legs, 21390);
                player->SetUInt32Value(belt, 21606);
                player->SetUInt32Value(boots, 21388);
                break;
            // Tier 3
            case 59:
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 22428, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 22429, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 22425, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 22426, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 22427, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 22431, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 22430, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET)->GetGUIDLow());
                player->SetUInt32Value(head, 22428);
                player->SetUInt32Value(shoulder, 22429);
                player->SetUInt32Value(chest, 22425);
                player->SetUInt32Value(gloves, 22426);
                player->SetUInt32Value(legs, 22427);
                player->SetUInt32Value(belt, 22431);
                player->SetUInt32Value(boots, 22430);
                break;
//==============Death Knight==============
            // Season 1
            case 100:
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 40827, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 40868, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 40787, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 40809, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 40848, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 40881, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 40882, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET)->GetGUIDLow());
                player->SetUInt32Value(head, 40827);
                player->SetUInt32Value(shoulder, 40868);
                player->SetUInt32Value(chest, 40787);
                player->SetUInt32Value(gloves, 40809);
                player->SetUInt32Value(legs, 40848);
                player->SetUInt32Value(belt, 40881);
                player->SetUInt32Value(boots, 40882);
                break;
            // Season 2
            case 101:
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 46115, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 46117, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 46111, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 46113, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 46116, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 34651, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 40313, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET)->GetGUIDLow());
                player->SetUInt32Value(head, 46115);
                player->SetUInt32Value(shoulder, 46117);
                player->SetUInt32Value(chest, 46111);
                player->SetUInt32Value(gloves, 46113);
                player->SetUInt32Value(legs, 46116);
                player->SetUInt32Value(belt, 34651);
                player->SetUInt32Value(boots, 40313);
                break;
            // Season 3
            case 102:
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 40554, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 40557, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 40550, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 40552, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 40556, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 45825, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 40742, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET)->GetGUIDLow());
                player->SetUInt32Value(head, 40554);
                player->SetUInt32Value(shoulder, 40557);
                player->SetUInt32Value(chest, 40550);
                player->SetUInt32Value(gloves, 40552);
                player->SetUInt32Value(legs, 40556);
                player->SetUInt32Value(belt, 45825);
                player->SetUInt32Value(boots, 40742);
                break;
            // Season 4
            case 103:
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 45299, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 46037, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 45676, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 45997, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 45982, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 34651, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 45330, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET)->GetGUIDLow());
                player->SetUInt32Value(head, 45299);
                player->SetUInt32Value(shoulder, 46037);
                player->SetUInt32Value(chest, 45676);
                player->SetUInt32Value(gloves, 45997);
                player->SetUInt32Value(legs, 45982);
                player->SetUInt32Value(belt, 34651);
                player->SetUInt32Value(boots, 45330);
                break;
            // Rank 7
            case 104:
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 39395, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 39249, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 39239, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 37363, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 43994, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 37171, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 41392, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET)->GetGUIDLow());
                player->SetUInt32Value(head, 39395);
                player->SetUInt32Value(shoulder, 39249);
                player->SetUInt32Value(chest, 39239);
                player->SetUInt32Value(gloves, 37363);
                player->SetUInt32Value(legs, 43994);
                player->SetUInt32Value(belt, 37171);
                player->SetUInt32Value(boots, 41392);
                break;
            // Rank 14
            case 105:
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 39260, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 40511, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 39188, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 39228, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 37362, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 37670, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 41392, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET)->GetGUIDLow());
                player->SetUInt32Value(head, 39260);
                player->SetUInt32Value(shoulder, 40511);
                player->SetUInt32Value(chest, 39188);
                player->SetUInt32Value(gloves, 39228);
                player->SetUInt32Value(legs, 37362);
                player->SetUInt32Value(belt, 37670);
                player->SetUInt32Value(boots, 41392);
                break;
            // Tier 2.5
            case 106:
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 39760, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 40590, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 40210, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 45268, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 40204, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 43989, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 40592, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET)->GetGUIDLow());
                player->SetUInt32Value(head, 39760);
                player->SetUInt32Value(shoulder, 40590);
                player->SetUInt32Value(chest, 40210);
                player->SetUInt32Value(gloves, 45268);
                player->SetUInt32Value(legs, 40204);
                player->SetUInt32Value(belt, 43989);
                player->SetUInt32Value(boots, 40592);
                break;
            // Tier 3
            case 107:
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 44006, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 39704, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 39767, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 39726, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 40589, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 37241, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 40591, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET)->GetGUIDLow());
                player->SetUInt32Value(head, 44006);
                player->SetUInt32Value(shoulder, 39704);
                player->SetUInt32Value(chest, 39767);
                player->SetUInt32Value(gloves, 39726);
                player->SetUInt32Value(legs, 40589);
                player->SetUInt32Value(belt, 37241);
                player->SetUInt32Value(boots, 40591);
                break;
//=================Hunter=================
            // Season 1
            case 150:
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 28331, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 28333, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 28334, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 28335, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 28332, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 28450, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 28449, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET)->GetGUIDLow());
                player->SetUInt32Value(head, 28331);
                player->SetUInt32Value(shoulder, 28333);
                player->SetUInt32Value(chest, 28334);
                player->SetUInt32Value(gloves, 28335);
                player->SetUInt32Value(legs, 28332);
                player->SetUInt32Value(belt, 28450);
                player->SetUInt32Value(boots, 28449);
                break;
            // Season 2
            case 151:
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 31962, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 31964, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 31960, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 31961, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 31963, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 32797, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 32785, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET)->GetGUIDLow());
                player->SetUInt32Value(head, 31962);
                player->SetUInt32Value(shoulder, 31964);
                player->SetUInt32Value(chest, 31960);
                player->SetUInt32Value(gloves, 31961);
                player->SetUInt32Value(legs, 31963);
                player->SetUInt32Value(belt, 32797);
                player->SetUInt32Value(boots, 32785);
                break;
            // Season 3
            case 152:
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 33666, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 33668, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 33664, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 33665, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 33667, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 33877, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 33878, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET)->GetGUIDLow());
                player->SetUInt32Value(head, 33666);
                player->SetUInt32Value(shoulder, 33668);
                player->SetUInt32Value(chest, 33664);
                player->SetUInt32Value(gloves, 33665);
                player->SetUInt32Value(legs, 33667);
                player->SetUInt32Value(belt, 33877);
                player->SetUInt32Value(boots, 33878);
                break;
            // Season 4
            case 153:
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 34992, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 34994, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 34990, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 34991, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 34993, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 35151, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 35136, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET)->GetGUIDLow());
                player->SetUInt32Value(head, 34992);
                player->SetUInt32Value(shoulder, 34994);
                player->SetUInt32Value(chest, 34990);
                player->SetUInt32Value(gloves, 34991);
                player->SetUInt32Value(legs, 34993);
                player->SetUInt32Value(belt, 35151);
                player->SetUInt32Value(boots, 35136);
                break;
            // Rank 7 Alliance
            case 154:
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 23306, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 23307, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 23292, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 23279, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 23293, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 34651, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 23278, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET)->GetGUIDLow());
                player->SetUInt32Value(head, 23306);
                player->SetUInt32Value(shoulder, 23307);
                player->SetUInt32Value(chest, 23292);
                player->SetUInt32Value(gloves, 23279);
                player->SetUInt32Value(legs, 23293);
                player->SetUInt32Value(belt, 34651);
                player->SetUInt32Value(boots, 23278);
                break;
            // Rank 7 Horde
            case 155:
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 23251, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 23252, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 22874, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 22862, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 22875, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 34651, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 22843, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET)->GetGUIDLow());
                player->SetUInt32Value(head, 23251);
                player->SetUInt32Value(shoulder, 23252);
                player->SetUInt32Value(chest, 22874);
                player->SetUInt32Value(gloves, 22862);
                player->SetUInt32Value(legs, 22875);
                player->SetUInt32Value(belt, 34651);
                player->SetUInt32Value(boots, 22843);
                break;
            // Rank 14 Alliance
            case 156:
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 16465, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 16468, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 16466, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 16463, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 16467, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 34651, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 16462, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET)->GetGUIDLow());
                player->SetUInt32Value(head, 16465);
                player->SetUInt32Value(shoulder, 16468);
                player->SetUInt32Value(chest, 16466);
                player->SetUInt32Value(gloves, 16463);
                player->SetUInt32Value(legs, 16467);
                player->SetUInt32Value(belt, 34651);
                player->SetUInt32Value(boots, 16462);
                break;
            // Rank 14 Horde
            case 157:
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 16566, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 16568, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 16565, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 16571, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 16567, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 34651, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 16569, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET)->GetGUIDLow());
                player->SetUInt32Value(head, 16566);
                player->SetUInt32Value(shoulder, 16568);
                player->SetUInt32Value(chest, 16565);
                player->SetUInt32Value(gloves, 16571);
                player->SetUInt32Value(legs, 16567);
                player->SetUInt32Value(belt, 34651);
                player->SetUInt32Value(boots, 16569);
                break;
            // Tier 2.5
            case 158:
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 21366, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 21367, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 21370, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 21599, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 21368, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 25374, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 21365, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET)->GetGUIDLow());
                player->SetUInt32Value(head, 21366);
                player->SetUInt32Value(shoulder, 21367);
                player->SetUInt32Value(chest, 21370);
                player->SetUInt32Value(gloves, 21599);
                player->SetUInt32Value(legs, 21368);
                player->SetUInt32Value(belt, 25374);
                player->SetUInt32Value(boots, 21365);
                break;
            // Tier 3
            case 159:
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 22438, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 22439, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 22436, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 22441, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 22437, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 22442, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 22440, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET)->GetGUIDLow());
                player->SetUInt32Value(head, 22438);
                player->SetUInt32Value(shoulder, 22439);
                player->SetUInt32Value(chest, 22436);
                player->SetUInt32Value(gloves, 22441);
                player->SetUInt32Value(legs, 22437);
                player->SetUInt32Value(belt, 22442);
                player->SetUInt32Value(boots, 22440);
                break;
//=================Shaman=================
            // Season 1
            case 200:
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 25998, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 25999, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 25997, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 26000, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 26001, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 28639, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 28640, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET)->GetGUIDLow());
                player->SetUInt32Value(head, 25998);
                player->SetUInt32Value(shoulder, 25999);
                player->SetUInt32Value(chest, 25997);
                player->SetUInt32Value(gloves, 26000);
                player->SetUInt32Value(legs, 26001);
                player->SetUInt32Value(belt, 28639);
                player->SetUInt32Value(boots, 28640);
                break;
            // Season 2
            case 201:
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 32006, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 32008, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 32004, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 32005, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 32007, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 32804, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 32792, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET)->GetGUIDLow());
                player->SetUInt32Value(head, 32006);
                player->SetUInt32Value(shoulder, 32008);
                player->SetUInt32Value(chest, 32004);
                player->SetUInt32Value(gloves, 32005);
                player->SetUInt32Value(legs, 32007);
                player->SetUInt32Value(belt, 32804);
                player->SetUInt32Value(boots, 32792);
                break;
            // Season 3
            case 202:
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 33708, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 33710, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 33706, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 33707, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 33709, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 33895, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 33896, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET)->GetGUIDLow());
                player->SetUInt32Value(head, 33708);
                player->SetUInt32Value(shoulder, 33710);
                player->SetUInt32Value(chest, 33706);
                player->SetUInt32Value(gloves, 33707);
                player->SetUInt32Value(legs, 33709);
                player->SetUInt32Value(belt, 33895);
                player->SetUInt32Value(boots, 33896);
                break;
            // Season 4
            case 203:
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 35044, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 35046, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 35042, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 35043, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 35045, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 35157, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 35142, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET)->GetGUIDLow());
                player->SetUInt32Value(head, 35044);
                player->SetUInt32Value(shoulder, 35046);
                player->SetUInt32Value(chest, 35042);
                player->SetUInt32Value(gloves, 35043);
                player->SetUInt32Value(legs, 35045);
                player->SetUInt32Value(belt, 35157);
                player->SetUInt32Value(boots, 35142);
                break;
            // Rank 7
            case 204:
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 16566, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 16568, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 16565, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 16571, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 16567, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 34651, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 16569, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET)->GetGUIDLow());
                player->SetUInt32Value(head, 16566);
                player->SetUInt32Value(shoulder, 16568);
                player->SetUInt32Value(chest, 16565);
                player->SetUInt32Value(gloves, 16571);
                player->SetUInt32Value(legs, 16567);
                player->SetUInt32Value(belt, 34651);
                player->SetUInt32Value(boots, 16569);
                break;
            // Rank 14
            case 205:
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 29610, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 29611, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 29609, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 29607, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 29608, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 34651, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 29606, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET)->GetGUIDLow());
                player->SetUInt32Value(head, 29610);
                player->SetUInt32Value(shoulder, 29611);
                player->SetUInt32Value(chest, 29609);
                player->SetUInt32Value(gloves, 29607);
                player->SetUInt32Value(legs, 29608);
                player->SetUInt32Value(belt, 34651);
                player->SetUInt32Value(boots, 29606);
                break;
            // Tier 2.5
            case 206:
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 21372, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 21376, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 21374, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 21624, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 21375, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 21607, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 21373, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET)->GetGUIDLow());
                player->SetUInt32Value(head, 21372);
                player->SetUInt32Value(shoulder, 21376);
                player->SetUInt32Value(chest, 21374);
                player->SetUInt32Value(gloves, 21624);
                player->SetUInt32Value(legs, 21375);
                player->SetUInt32Value(belt, 21607);
                player->SetUInt32Value(boots, 21373);
                break;
            // Tier 3
            case 207:
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 22466, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 22467, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 22464, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 22469, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 22465, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 22470, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 22468, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET)->GetGUIDLow());
                player->SetUInt32Value(head, 22466);
                player->SetUInt32Value(shoulder, 22467);
                player->SetUInt32Value(chest, 22464);
                player->SetUInt32Value(gloves, 22469);
                player->SetUInt32Value(legs, 22465);
                player->SetUInt32Value(belt, 22470);
                player->SetUInt32Value(boots, 22468);
                break;
//=================Rogue==================
            // Season 1
            case 250:
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 25830, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 25832, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 25831, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 25834, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 25833, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 28423, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 28422, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET)->GetGUIDLow());
                player->SetUInt32Value(head, 25830);
                player->SetUInt32Value(shoulder, 25832);
                player->SetUInt32Value(chest, 25831);
                player->SetUInt32Value(gloves, 25834);
                player->SetUInt32Value(legs, 25833);
                player->SetUInt32Value(belt, 28423);
                player->SetUInt32Value(boots, 28422);
                break;
            // Season 2
            case 251:
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 31999, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 32001, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 32002, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 31998, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 32000, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 32802, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 32790, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET)->GetGUIDLow());
                player->SetUInt32Value(head, 31999);
                player->SetUInt32Value(shoulder, 32001);
                player->SetUInt32Value(chest, 32002);
                player->SetUInt32Value(gloves, 31998);
                player->SetUInt32Value(legs, 32000);
                player->SetUInt32Value(belt, 32802);
                player->SetUInt32Value(boots, 32790);
                break;
            // Season 3
            case 252:
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 33701, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 33703, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 33704, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 33700, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 33702, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 33891, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 33892, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET)->GetGUIDLow());
                player->SetUInt32Value(head, 33701);
                player->SetUInt32Value(shoulder, 33703);
                player->SetUInt32Value(chest, 33704);
                player->SetUInt32Value(gloves, 33700);
                player->SetUInt32Value(legs, 33702);
                player->SetUInt32Value(belt, 33891);
                player->SetUInt32Value(boots, 33892);
                break;
            // Season 4
            case 253:
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 35033, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 35035, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 35036, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 35032, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 35034, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 35156, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 35141, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET)->GetGUIDLow());
                player->SetUInt32Value(head, 35033);
                player->SetUInt32Value(shoulder, 35035);
                player->SetUInt32Value(chest, 35036);
                player->SetUInt32Value(gloves, 35032);
                player->SetUInt32Value(legs, 35034);
                player->SetUInt32Value(belt, 35156);
                player->SetUInt32Value(boots, 35141);
                break;
            // Rank 7 Alliance
            case 254:
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 23308, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 23309, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 23294, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 23280, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 23295, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 34651, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 23281, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET)->GetGUIDLow());
                player->SetUInt32Value(head, 23308);
                player->SetUInt32Value(shoulder, 23309);
                player->SetUInt32Value(chest, 23294);
                player->SetUInt32Value(gloves, 23280);
                player->SetUInt32Value(legs, 23295);
                player->SetUInt32Value(belt, 34651);
                player->SetUInt32Value(boots, 23281);
                break;
            // Rank 7 Horde
            case 255:
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 23257, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 23258, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 22879, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 22864, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 22880, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 34651, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 22856, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET)->GetGUIDLow());
                player->SetUInt32Value(head, 23257);
                player->SetUInt32Value(shoulder, 23258);
                player->SetUInt32Value(chest, 22879);
                player->SetUInt32Value(gloves, 22864);
                player->SetUInt32Value(legs, 22880);
                player->SetUInt32Value(belt, 34651);
                player->SetUInt32Value(boots, 22856);
                break;
            // Rank 14 Alliance
            case 256:
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 16451, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 16449, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 16452, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 16448, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 16450, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 34651, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 16459, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET)->GetGUIDLow());
                player->SetUInt32Value(head, 16451);
                player->SetUInt32Value(shoulder, 16449);
                player->SetUInt32Value(chest, 16452);
                player->SetUInt32Value(gloves, 16448);
                player->SetUInt32Value(legs, 16450);
                player->SetUInt32Value(belt, 34651);
                player->SetUInt32Value(boots, 16459);
                break;
            // Rank 14 Horde
            case 257:
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 16561, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 16562, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 16563, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 16560, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 16564, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 34651, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 16558, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET)->GetGUIDLow());
                player->SetUInt32Value(head, 16561);
                player->SetUInt32Value(shoulder, 16562);
                player->SetUInt32Value(chest, 16563);
                player->SetUInt32Value(gloves, 16560);
                player->SetUInt32Value(legs, 16564);
                player->SetUInt32Value(belt, 34651);
                player->SetUInt32Value(boots, 16558);
                break;
            // Tier 2.5
            case 258:
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 21360, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 21361, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 21364, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 29507, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 21362, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 21586, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 21359, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET)->GetGUIDLow());
                player->SetUInt32Value(head, 21360);
                player->SetUInt32Value(shoulder, 21361);
                player->SetUInt32Value(chest, 21364);
                player->SetUInt32Value(gloves, 29507);
                player->SetUInt32Value(legs, 21362);
                player->SetUInt32Value(belt, 21586);
                player->SetUInt32Value(boots, 21359);
                break;
            // Tier 3
            case 259:
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 22478, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 22479, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 22476, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 22481, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 22477, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 22482, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 22480, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET)->GetGUIDLow());
                player->SetUInt32Value(head, 22478);
                player->SetUInt32Value(shoulder, 22479);
                player->SetUInt32Value(chest, 22476);
                player->SetUInt32Value(gloves, 22481);
                player->SetUInt32Value(legs, 22477);
                player->SetUInt32Value(belt, 22482);
                player->SetUInt32Value(boots, 22480);
                break;
//=================Druid==================
            // Season 1
            case 300:
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 28127, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 28129, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 28130, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 28126, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 28128, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 28443, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 28447, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET)->GetGUIDLow());
                player->SetUInt32Value(head, 28127);
                player->SetUInt32Value(shoulder, 28129);
                player->SetUInt32Value(chest, 28130);
                player->SetUInt32Value(gloves, 28126);
                player->SetUInt32Value(legs, 28128);
                player->SetUInt32Value(belt, 28443);
                player->SetUInt32Value(boots, 28447);
                break;
            // Season 2
            case 301:
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 31968, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 31971, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 31972, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 31967, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 31969, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 32798, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 32786, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET)->GetGUIDLow());
                player->SetUInt32Value(head, 31968);
                player->SetUInt32Value(shoulder, 31971);
                player->SetUInt32Value(chest, 31972);
                player->SetUInt32Value(gloves, 31967);
                player->SetUInt32Value(legs, 31969);
                player->SetUInt32Value(belt, 32798);
                player->SetUInt32Value(boots, 32786);
                break;
            // Season 3
            case 302:
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 33672, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 33674, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 33675, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 33671, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 33673, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 33879, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 33880, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET)->GetGUIDLow());
                player->SetUInt32Value(head, 33672);
                player->SetUInt32Value(shoulder, 33674);
                player->SetUInt32Value(chest, 33675);
                player->SetUInt32Value(gloves, 33671);
                player->SetUInt32Value(legs, 33673);
                player->SetUInt32Value(belt, 33879);
                player->SetUInt32Value(boots, 33880);
                break;
            // Season 4
            case 303:
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 34999, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 35001, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 35002, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 34998, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 35000, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 35152, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 35137, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET)->GetGUIDLow());
                player->SetUInt32Value(head, 34999);
                player->SetUInt32Value(shoulder, 35001);
                player->SetUInt32Value(chest, 35002);
                player->SetUInt32Value(gloves, 34998);
                player->SetUInt32Value(legs, 35000);
                player->SetUInt32Value(belt, 35152);
                player->SetUInt32Value(boots, 35137);
                break;
            // Rank 7 Alliance
            case 304:
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 23308, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 23309, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 23294, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 23280, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 23295, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 34651, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 23281, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET)->GetGUIDLow());
                player->SetUInt32Value(head, 23308);
                player->SetUInt32Value(shoulder, 23309);
                player->SetUInt32Value(chest, 23294);
                player->SetUInt32Value(gloves, 23280);
                player->SetUInt32Value(legs, 23295);
                player->SetUInt32Value(belt, 34651);
                player->SetUInt32Value(boots, 23281);
                break;
            // Rank 7 Horde
            case 305:
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 23253, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 23254, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 22877, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 22863, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 22878, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 34651, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 22852, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET)->GetGUIDLow());
                player->SetUInt32Value(head, 23253);
                player->SetUInt32Value(shoulder, 23254);
                player->SetUInt32Value(chest, 22877);
                player->SetUInt32Value(gloves, 22863);
                player->SetUInt32Value(legs, 22878);
                player->SetUInt32Value(belt, 34651);
                player->SetUInt32Value(boots, 22852);
                break;
            // Rank 14 Alliance
            case 306:
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 16451, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 16449, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 16452, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 16448, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 16450, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 34651, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 16459, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET)->GetGUIDLow());
                player->SetUInt32Value(head, 16451);
                player->SetUInt32Value(shoulder, 16449);
                player->SetUInt32Value(chest, 16452);
                player->SetUInt32Value(gloves, 16448);
                player->SetUInt32Value(legs, 16450);
                player->SetUInt32Value(belt, 34651);
                player->SetUInt32Value(boots, 16459);
                break;
            // Rank 14 Horde
            case 307:
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 16550, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 16551, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 16549, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 16555, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 16552, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 34651, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 16554, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET)->GetGUIDLow());
                player->SetUInt32Value(head, 16550);
                player->SetUInt32Value(shoulder, 16551);
                player->SetUInt32Value(chest, 16549);
                player->SetUInt32Value(gloves, 16555);
                player->SetUInt32Value(legs, 16552);
                player->SetUInt32Value(belt, 34651);
                player->SetUInt32Value(boots, 16554);
                break;
            // Tier 2.5
            case 308:
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 21353, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 21354, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 21357, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 21617, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 21356, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 21609, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 21355, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET)->GetGUIDLow());
                player->SetUInt32Value(head, 21353);
                player->SetUInt32Value(shoulder, 21354);
                player->SetUInt32Value(chest, 21357);
                player->SetUInt32Value(gloves, 21617);
                player->SetUInt32Value(legs, 21356);
                player->SetUInt32Value(belt, 21609);
                player->SetUInt32Value(boots, 21355);
                break;
            // Tier 3
            case 309:
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 22490, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 22491, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 22488, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 22493, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 22489, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 22494, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 22492, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET)->GetGUIDLow());
                player->SetUInt32Value(head, 22490);
                player->SetUInt32Value(shoulder, 22491);
                player->SetUInt32Value(chest, 22488);
                player->SetUInt32Value(gloves, 22493);
                player->SetUInt32Value(legs, 22489);
                player->SetUInt32Value(belt, 22494);
                player->SetUInt32Value(boots, 22492);
                break;
//=================Priest=================
            // Season 1
            case 350:
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 27708, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 27710, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 27711, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 27707, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 27709, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 49796, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 28663, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET)->GetGUIDLow());
                player->SetUInt32Value(head, 27708);
                player->SetUInt32Value(shoulder, 27710);
                player->SetUInt32Value(chest, 27711);
                player->SetUInt32Value(gloves, 27707);
                player->SetUInt32Value(legs, 27709);
                player->SetUInt32Value(belt, 49796);
                player->SetUInt32Value(boots, 28663);
                break;
            // Season 2
            case 351:
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 32016, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 32018, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 32019, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 32015, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 32017, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 32979, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 32981, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET)->GetGUIDLow());
                player->SetUInt32Value(head, 32016);
                player->SetUInt32Value(shoulder, 32018);
                player->SetUInt32Value(chest, 32019);
                player->SetUInt32Value(gloves, 32015);
                player->SetUInt32Value(legs, 32017);
                player->SetUInt32Value(belt, 32979);
                player->SetUInt32Value(boots, 32981);
                break;
            // Season 3
            case 352:
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 33718, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 33720, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 33721, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 33717, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 33719, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 33900, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 33902, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET)->GetGUIDLow());
                player->SetUInt32Value(head, 33718);
                player->SetUInt32Value(shoulder, 33720);
                player->SetUInt32Value(chest, 33721);
                player->SetUInt32Value(gloves, 33717);
                player->SetUInt32Value(legs, 33719);
                player->SetUInt32Value(belt, 33900);
                player->SetUInt32Value(boots, 33902);
                break;
            // Season 4
            case 353:
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 35054, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 35056, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 35057, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 35053, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 35055, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 35159, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 35144, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET)->GetGUIDLow());
                player->SetUInt32Value(head, 35054);
                player->SetUInt32Value(shoulder, 35056);
                player->SetUInt32Value(chest, 35057);
                player->SetUInt32Value(gloves, 35053);
                player->SetUInt32Value(legs, 35055);
                player->SetUInt32Value(belt, 35159);
                player->SetUInt32Value(boots, 35144);
                break;
            // Rank 7 Alliance
            case 354:
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 23316, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 23317, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 23303, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 23288, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 23302, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 34651, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 23289, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET)->GetGUIDLow());
                player->SetUInt32Value(head, 23316);
                player->SetUInt32Value(shoulder, 23317);
                player->SetUInt32Value(chest, 23303);
                player->SetUInt32Value(gloves, 23288);
                player->SetUInt32Value(legs, 23302);
                player->SetUInt32Value(belt, 34651);
                player->SetUInt32Value(boots, 23289);
                break;
            // Rank 7 Horde
            case 355:
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 23261, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 23262, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 22885, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 22869, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 22882, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 34651, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 22859, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET)->GetGUIDLow());
                player->SetUInt32Value(head, 23261);
                player->SetUInt32Value(shoulder, 23262);
                player->SetUInt32Value(chest, 22885);
                player->SetUInt32Value(gloves, 22869);
                player->SetUInt32Value(legs, 22882);
                player->SetUInt32Value(belt, 34651);
                player->SetUInt32Value(boots, 22859);
                break;
            // Rank 14 Alliance
            case 356:
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 17602, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 17604, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 17605, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 17608, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 17603, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 34651, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 17607, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET)->GetGUIDLow());
                player->SetUInt32Value(head, 17602);
                player->SetUInt32Value(shoulder, 17604);
                player->SetUInt32Value(chest, 17605);
                player->SetUInt32Value(gloves, 17608);
                player->SetUInt32Value(legs, 17603);
                player->SetUInt32Value(belt, 34651);
                player->SetUInt32Value(boots, 17607);
                break;
            // Rank 14 Horde
            case 357:
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 17623, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 17622, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 17624, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 17620, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 17625, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 34651, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 17618, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET)->GetGUIDLow());
                player->SetUInt32Value(head, 17623);
                player->SetUInt32Value(shoulder, 17622);
                player->SetUInt32Value(chest, 17624);
                player->SetUInt32Value(gloves, 17620);
                player->SetUInt32Value(legs, 17625);
                player->SetUInt32Value(belt, 34651);
                player->SetUInt32Value(boots, 17618);
                break;
            // Tier 2.5
            case 358:
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 21348, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 21350, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 21351, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 21619, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 21352, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 22730, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 21349, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET)->GetGUIDLow());
                player->SetUInt32Value(head, 21348);
                player->SetUInt32Value(shoulder, 21350);
                player->SetUInt32Value(chest, 21351);
                player->SetUInt32Value(gloves, 21619);
                player->SetUInt32Value(legs, 21352);
                player->SetUInt32Value(belt, 22730);
                player->SetUInt32Value(boots, 21349);
                break;
            // Tier 3
            case 359:
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 22514, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 22515, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 22512, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 22517, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 22513, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 22518, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 22516, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET)->GetGUIDLow());
                player->SetUInt32Value(head, 22514);
                player->SetUInt32Value(shoulder, 22515);
                player->SetUInt32Value(chest, 22512);
                player->SetUInt32Value(gloves, 22517);
                player->SetUInt32Value(legs, 22513);
                player->SetUInt32Value(belt, 22518);
                player->SetUInt32Value(boots, 22516);
                break;
//=================Mage===================
            // Season 1
            case 400:
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 25855, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 25854, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 25856, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 25857, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 25858, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 28409, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 28410, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET)->GetGUIDLow());
                player->SetUInt32Value(head, 25855);
                player->SetUInt32Value(shoulder, 25854);
                player->SetUInt32Value(chest, 25856);
                player->SetUInt32Value(gloves, 25857);
                player->SetUInt32Value(legs, 25858);
                player->SetUInt32Value(belt, 28409);
                player->SetUInt32Value(boots, 28410);
                break;
            // Season 2
            case 401:
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 32048, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 32047, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 32050, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 32049, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 3205, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 32807, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 32795, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET)->GetGUIDLow());
                player->SetUInt32Value(head, 32048);
                player->SetUInt32Value(shoulder, 32047);
                player->SetUInt32Value(chest, 32050);
                player->SetUInt32Value(gloves, 32049);
                player->SetUInt32Value(legs, 32051);
                player->SetUInt32Value(belt, 32807);
                player->SetUInt32Value(boots, 32795);
                break;
            // Season 3
            case 402:
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 33758, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 33757, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 33760, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 33759, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 33761, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 33912, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 33914, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET)->GetGUIDLow());
                player->SetUInt32Value(head, 33758);
                player->SetUInt32Value(shoulder, 33757);
                player->SetUInt32Value(chest, 33760);
                player->SetUInt32Value(gloves, 33759);
                player->SetUInt32Value(legs, 33761);
                player->SetUInt32Value(belt, 33912);
                player->SetUInt32Value(boots, 33914);
                break;
            // Season 4
            case 403:
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 35097, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 35096, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 35099, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 35098, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 35100, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 35164, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 35149, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET)->GetGUIDLow());
                player->SetUInt32Value(head, 35097);
                player->SetUInt32Value(shoulder, 35096);
                player->SetUInt32Value(chest, 35099);
                player->SetUInt32Value(gloves, 35098);
                player->SetUInt32Value(legs, 35100);
                player->SetUInt32Value(belt, 35164);
                player->SetUInt32Value(boots, 35149);
                break;
            // Rank 7 Alliance
            case 404:
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 23318, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 23319, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 23305, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 16391, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 23304, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 34651, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 23291, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET)->GetGUIDLow());
                player->SetUInt32Value(head, 23318);
                player->SetUInt32Value(shoulder, 23319);
                player->SetUInt32Value(chest, 23305);
                player->SetUInt32Value(gloves, 16391);
                player->SetUInt32Value(legs, 23304);
                player->SetUInt32Value(belt, 34651);
                player->SetUInt32Value(boots, 23291);
                break;
            // Rank 7 Horde
            case 405:
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 23263, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 23264, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 22886, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 22870, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 22883, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 34651, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 22860, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET)->GetGUIDLow());
                player->SetUInt32Value(head, 23263);
                player->SetUInt32Value(shoulder, 23264);
                player->SetUInt32Value(chest, 22886);
                player->SetUInt32Value(gloves, 22870);
                player->SetUInt32Value(legs, 22883);
                player->SetUInt32Value(belt, 34651);
                player->SetUInt32Value(boots, 22860);
                break;
            // Rank 14 Alliance
            case 406:
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 16441, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 16444, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 16443, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 16440, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 16442, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 34651, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 16437, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET)->GetGUIDLow());
                player->SetUInt32Value(head, 16441);
                player->SetUInt32Value(shoulder, 16444);
                player->SetUInt32Value(chest, 16443);
                player->SetUInt32Value(gloves, 16440);
                player->SetUInt32Value(legs, 16442);
                player->SetUInt32Value(belt, 34651);
                player->SetUInt32Value(boots, 16437);
                break;
            // Rank 14 Horde
            case 407:
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 16533, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 16536, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 16535, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 16540, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 16534, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 34651, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 16539, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET)->GetGUIDLow());
                player->SetUInt32Value(head, 16533);
                player->SetUInt32Value(shoulder, 16536);
                player->SetUInt32Value(chest, 16535);
                player->SetUInt32Value(gloves, 16540);
                player->SetUInt32Value(legs, 16534);
                player->SetUInt32Value(belt, 34651);
                player->SetUInt32Value(boots, 16539);
                break;
            // Tier 2.5
            case 408:
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 21347, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 21345, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 21343, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 20369, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 21346, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 21582, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 21344, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET)->GetGUIDLow());
                player->SetUInt32Value(head, 21347);
                player->SetUInt32Value(shoulder, 21345);
                player->SetUInt32Value(chest, 21343);
                player->SetUInt32Value(gloves, 20369);
                player->SetUInt32Value(legs, 21346);
                player->SetUInt32Value(belt, 21582);
                player->SetUInt32Value(boots, 21344);
                break;
            // Tier 3
            case 409:
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 22498, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 22499, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 22496, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 22501, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 22497, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 22502, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 22500, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET)->GetGUIDLow());
                player->SetUInt32Value(head, 22498);
                player->SetUInt32Value(shoulder, 22499);
                player->SetUInt32Value(chest, 22496);
                player->SetUInt32Value(gloves, 22501);
                player->SetUInt32Value(legs, 22497);
                player->SetUInt32Value(belt, 22502);
                player->SetUInt32Value(boots, 22500);
                break;
//================Warlock=================
            // Season 1
            case 450:
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 24553, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 24554, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 24552, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 24556, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 24555, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 34651, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 28402, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET)->GetGUIDLow());
                player->SetUInt32Value(head, 24553);
                player->SetUInt32Value(shoulder, 24554);
                player->SetUInt32Value(chest, 24552);
                player->SetUInt32Value(gloves, 24556);
                player->SetUInt32Value(legs, 24555);
                player->SetUInt32Value(belt, 34651);
                player->SetUInt32Value(boots, 28402);
                break;
            // Season 2
            case 451:
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 31974, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 31976, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 31977, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 31973, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 31975, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 32799, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 32787, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET)->GetGUIDLow());
                player->SetUInt32Value(head, 31974);
                player->SetUInt32Value(shoulder, 31976);
                player->SetUInt32Value(chest, 31977);
                player->SetUInt32Value(gloves, 31973);
                player->SetUInt32Value(legs, 31975);
                player->SetUInt32Value(belt, 32799);
                player->SetUInt32Value(boots, 32787);
                break;
            // Season 3
            case 452:
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 33677, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 33679, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 33680, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 33676, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 33678, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 33882, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 33884, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET)->GetGUIDLow());
                player->SetUInt32Value(head, 33677);
                player->SetUInt32Value(shoulder, 33679);
                player->SetUInt32Value(chest, 33680);
                player->SetUInt32Value(gloves, 33676);
                player->SetUInt32Value(legs, 33678);
                player->SetUInt32Value(belt, 33882);
                player->SetUInt32Value(boots, 33884);
                break;
            // Season 4
            case 453:
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 35004, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 35006, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 35007, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 35003, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 35005, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 35153, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 35138, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET)->GetGUIDLow());
                player->SetUInt32Value(head, 35004);
                player->SetUInt32Value(shoulder, 35006);
                player->SetUInt32Value(chest, 35007);
                player->SetUInt32Value(gloves, 35003);
                player->SetUInt32Value(legs, 35005);
                player->SetUInt32Value(belt, 35153);
                player->SetUInt32Value(boots, 35138);
                break;
            // Rank 7 Alliance
            case 454:
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 23310, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 23311, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 23297, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 23282, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 23296, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 34651, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 23283, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET)->GetGUIDLow());
                player->SetUInt32Value(head, 23310);
                player->SetUInt32Value(shoulder, 23311);
                player->SetUInt32Value(chest, 23297);
                player->SetUInt32Value(gloves, 23282);
                player->SetUInt32Value(legs, 23296);
                player->SetUInt32Value(belt, 34651);
                player->SetUInt32Value(boots, 23283);
                break;
            // Rank 7 Horde
            case 455:
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 23255, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 23256, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 22884, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 22865, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 22881, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 34651, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 22855, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET)->GetGUIDLow());
                player->SetUInt32Value(head, 23255);
                player->SetUInt32Value(shoulder, 23256);
                player->SetUInt32Value(chest, 22884);
                player->SetUInt32Value(gloves, 22865);
                player->SetUInt32Value(legs, 22881);
                player->SetUInt32Value(belt, 34651);
                player->SetUInt32Value(boots, 22855);
                break;
            // Rank 14 Alliance
            case 456:
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 17578, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 17580, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 17581, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 17584, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 17579, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 34651, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 17583, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET)->GetGUIDLow());
                player->SetUInt32Value(head, 17578);
                player->SetUInt32Value(shoulder, 17580);
                player->SetUInt32Value(chest, 17581);
                player->SetUInt32Value(gloves, 17584);
                player->SetUInt32Value(legs, 17579);
                player->SetUInt32Value(belt, 34651);
                player->SetUInt32Value(boots, 17583);
                break;
            // Rank 14 Horde
            case 457:
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 17591, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 17590, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 17592, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 17588, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 17593, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 34651, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 17586, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET)->GetGUIDLow());
                player->SetUInt32Value(head, 17591);
                player->SetUInt32Value(shoulder, 17590);
                player->SetUInt32Value(chest, 17592);
                player->SetUInt32Value(gloves, 17588);
                player->SetUInt32Value(legs, 17593);
                player->SetUInt32Value(belt, 34651);
                player->SetUInt32Value(boots, 17586);
                break;
            // Tier 2.5
            case 458:
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 21337, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 21335, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 21334, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 21585, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 21336, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 3380, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 21338, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET)->GetGUIDLow());
                player->SetUInt32Value(head, 21337);
                player->SetUInt32Value(shoulder, 21335);
                player->SetUInt32Value(chest, 21334);
                player->SetUInt32Value(gloves, 21585);
                player->SetUInt32Value(legs, 21336);
                player->SetUInt32Value(belt, 3380);
                player->SetUInt32Value(boots, 21338);
                break;
            // Tier 3
            case 459:
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 22506, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 22507, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 22504, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 22509, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 22505, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 22510, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 22508, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET)->GetGUIDLow());
                player->SetUInt32Value(head, 22506);
                player->SetUInt32Value(shoulder, 22507);
                player->SetUInt32Value(chest, 22504);
                player->SetUInt32Value(gloves, 22509);
                player->SetUInt32Value(legs, 22505);
                player->SetUInt32Value(belt, 22510);
                player->SetUInt32Value(boots, 22508);
                break;
//================Custom==================
            // N3XACTLY - Mage
            case 1000:
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 32235, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 51859, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 51813, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 51921, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 51882, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 51930, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 51899, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET)->GetGUIDLow());
                player->SetUInt32Value(head, 32235);
                player->SetUInt32Value(shoulder, 51859);
                player->SetUInt32Value(chest, 51813);
                player->SetUInt32Value(gloves, 51921);
                player->SetUInt32Value(legs, 51882);
                player->SetUInt32Value(belt, 51930);
                player->SetUInt32Value(boots, 51899);
                break;
            // N3XACTLY - Rogue
            case 1001:
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 32235, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 45245, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 45473, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 45325, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 45536, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 45491, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 45232, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET)->GetGUIDLow());
                player->SetUInt32Value(head, 32235);
                player->SetUInt32Value(shoulder, 45245);
                player->SetUInt32Value(chest, 45473);
                player->SetUInt32Value(gloves, 45325);
                player->SetUInt32Value(legs, 45536);
                player->SetUInt32Value(belt, 45491);
                player->SetUInt32Value(boots, 45232);
                break;
            // N3XACTLY - Druid
            case 1002:
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 32235, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 41276, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 41311, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 41288, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 51422, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 41618, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 51341, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET)->GetGUIDLow());
                player->SetUInt32Value(head, 32235);
                player->SetUInt32Value(shoulder, 41276);
                player->SetUInt32Value(chest, 41311);
                player->SetUInt32Value(gloves, 41288);
                player->SetUInt32Value(legs, 51422);
                player->SetUInt32Value(belt, 41618);
                player->SetUInt32Value(boots, 51341);
                break;
            // N3XACTLY - Priest
            case 1003:
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 31063, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 31069, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 31065, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 31060, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 31067, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 32519, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 30885, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET)->GetGUIDLow());
                player->SetUInt32Value(head, 31063);
                player->SetUInt32Value(shoulder, 31069);
                player->SetUInt32Value(chest, 31065);
                player->SetUInt32Value(gloves, 31060);
                player->SetUInt32Value(legs, 31067);
                player->SetUInt32Value(belt, 32519);
                player->SetUInt32Value(boots, 30885);
                break;
            // WHATHAPPENTOU - Mage
            case 1004:
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 9429, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 22082, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 6609, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 21888, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 7046, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 22743, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 19387, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET)->GetGUIDLow());
                player->SetUInt32Value(head, 9429);
                player->SetUInt32Value(shoulder, 22082);
                player->SetUInt32Value(chest, 6609);
                player->SetUInt32Value(gloves, 21888);
                player->SetUInt32Value(legs, 7046);
                player->SetUInt32Value(belt, 22743);
                player->SetUInt32Value(boots, 19387);
                break;
            // 1337DREW - Rogue
            case 1005:
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 32235, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 29047, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 29045, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 29048, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 29046, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 28750, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST)->GetGUIDLow());
                CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u, TransmogOwner = %u WHERE guid = %u", 28669, player->GetGUIDLow(), player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET)->GetGUIDLow());
                player->SetUInt32Value(head, 32235);
                player->SetUInt32Value(shoulder, 29047);
                player->SetUInt32Value(chest, 29045);
                player->SetUInt32Value(gloves, 29048);
                player->SetUInt32Value(legs, 29046);
                player->SetUInt32Value(belt, 28750);
                player->SetUInt32Value(boots, 28669);
                break;
//============Remove Transmog=============
            case 500:
                for (uint8 Slot = EQUIPMENT_SLOT_START; Slot < EQUIPMENT_SLOT_END; Slot++)
                    if (Item* item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, Slot))
                    {
                        CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = 0, TransmogOwner = 0 WHERE guid = %u", item->GetGUIDLow());
                        item->TransmogEntry = NULL;
                        item->TransmogOwner = NULL;
                        player->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_ENTRYID + (Slot * 2), item->GetEntry());
                    }
                break;
        }
        player->CLOSE_GOSSIP_MENU();
        return true;
    }
};

void AddSC_npc_transmog()
{
    new npc_transmog();
}