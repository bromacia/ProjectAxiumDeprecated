/*
* Copyright (C) 1337 - 2012 Niggers <http://www.axium-wow.com>
*/

#include "ScriptPCH.h"

class npc_enchant : public CreatureScript
{
    public: npc_enchant() : CreatureScript("npc_enchant")    {}

    uint8 slotid;
    uint32 Enchantid;
    uint32 reqil;
    uint32 twoha;

bool OnGossipHello(Player* player, Creature* creature)
{
    MainMenu(player, creature);
    return true;
}

void MainMenu(Player* player, Creature* creature)
{
        slotid = 0; Enchantid = 0; reqil = 0; twoha = 0;

        Item* item;

        player->ADD_GOSSIP_ITEM(0, "Back", GOSSIP_SENDER_MAIN, 14);
        player->ADD_GOSSIP_ITEM(0, "Chest", GOSSIP_SENDER_MAIN, 4);
        player->ADD_GOSSIP_ITEM(0, "Writs", GOSSIP_SENDER_MAIN, 8);
        player->ADD_GOSSIP_ITEM(0, "Hands", GOSSIP_SENDER_MAIN, 9);

        item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, 6);

        if(item)

        player->ADD_GOSSIP_ITEM(0, "Legs", GOSSIP_SENDER_MAIN, 6);
        player->ADD_GOSSIP_ITEM(0, "Boots", GOSSIP_SENDER_MAIN, 7);
        player->ADD_GOSSIP_ITEM(0, "Main hand", GOSSIP_SENDER_MAIN, 15);

        item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, 16);

        if(item)
        {
            if(item->GetTemplate()->SubClass == 6)
            {
                player->ADD_GOSSIP_ITEM(0, "Shield", GOSSIP_SENDER_MAIN, 18);
            }
        else
            {
                player->ADD_GOSSIP_ITEM(0, "Off hand", GOSSIP_SENDER_MAIN, 16);
            }
        }

        player->SEND_GOSSIP_MENU(1, creature->GetGUID());

        item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, 17);

        if(item)
        {
            if((item->GetTemplate()->SubClass == 2) || (item->GetTemplate()->SubClass == 3) || (item->GetTemplate()->SubClass == 18))
                {
                    player->ADD_GOSSIP_ITEM(0, "Ranged : mortal glasses", GOSSIP_SENDER_MAIN, 17);
                }
        }

    player->SEND_GOSSIP_MENU(20003, creature->GetGUID());
}

void Enchant(Player* player, Creature* creature, Item* item)
{
    item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, slotid );

    if(!item)
    {
        creature->MonsterWhisper("You must equip the item.", player->GetGUID());
        MainMenu(player, creature);
        return;
    }
    /*if ((reqil == 1) && (item->GetTemplate()->ItemLevel < 35))
    {
        creature->MonsterWhisper("L'objet n'est pas d'un niveau suffisant.", player->GetGUID());
        MainMenu(player, creature);
        return;
    }*/
    if ((twoha == 1) && (item->GetTemplate()->InventoryType == 17))
    {
        creature->MonsterWhisper("This enchant need a 2H.", player->GetGUID());
        MainMenu(player, creature);
        return;
    }

    SpellItemEnchantmentEntry const* Enchant_id = sSpellItemEnchantmentStore.LookupEntry(Enchantid);
    if (!Enchant_id)
    {
        creature->MonsterWhisper("Error, contact the administrator if you got this message", player->GetGUID());
        player->CLOSE_GOSSIP_MENU();
        return;
    }
    player->ApplyEnchantment(item, PERM_ENCHANTMENT_SLOT, false);
    item->SetEnchantment(PERM_ENCHANTMENT_SLOT, Enchantid, 0, 0);
    player->ApplyEnchantment(item, PERM_ENCHANTMENT_SLOT, true);
    MainMenu(player, creature);
}

bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action)
 {
    player->PlayerTalkClass->ClearMenus();
    Item* item;

    switch (action)
    {
        case 100:
        MainMenu(player, creature);
        break;
        // Cloak
        case 14:
            slotid = 14;
            player->ADD_GOSSIP_ITEM(3, "70 armor", GOSSIP_SENDER_MAIN, 1412);
            player->ADD_GOSSIP_ITEM(3, "120 armor", GOSSIP_SENDER_MAIN, 1407);
            player->ADD_GOSSIP_ITEM(3, "5 resistance", GOSSIP_SENDER_MAIN, 1413);
            player->ADD_GOSSIP_ITEM(3, "7 resistance", GOSSIP_SENDER_MAIN, 1408);
            player->ADD_GOSSIP_ITEM(3, "12 agility", GOSSIP_SENDER_MAIN, 1401);
            player->ADD_GOSSIP_ITEM(3, "12 dodge", GOSSIP_SENDER_MAIN, 1406);
            player->ADD_GOSSIP_ITEM(3, "12 defense", GOSSIP_SENDER_MAIN, 1411);
            player->ADD_GOSSIP_ITEM(3, "20 spell pene armor", GOSSIP_SENDER_MAIN, 1409);
            player->ADD_GOSSIP_ITEM(3, "10 shadow resistance", GOSSIP_SENDER_MAIN, 1404);
            player->ADD_GOSSIP_ITEM(3, "15 shadow resistance", GOSSIP_SENDER_MAIN, 1403);
            player->ADD_GOSSIP_ITEM(3, "15 fire resistance", GOSSIP_SENDER_MAIN, 1405);
            player->ADD_GOSSIP_ITEM(3, "15 arcane resistance", GOSSIP_SENDER_MAIN, 1410);
            player->ADD_GOSSIP_ITEM(3, "15 nature resistance", GOSSIP_SENDER_MAIN, 1400);
            player->ADD_GOSSIP_ITEM(3, "increased stealth", GOSSIP_SENDER_MAIN, 1402);
            player->ADD_GOSSIP_ITEM(0, "=> Back", GOSSIP_SENDER_MAIN, 100);
            player->SEND_GOSSIP_MENU(20004, creature->GetGUID());
        break;

        case 1400:
        Enchantid = 1395;
        Enchant(player, creature, item);
        break;

        case 1401:
        Enchantid = 368;
        Enchant(player, creature, item);
        break;

        case 1402:
        Enchantid = 910;
        Enchant(player, creature, item);
        break;

        case 1403:
        Enchantid = 1441;
        reqil = 1;
        Enchant(player, creature, item);
        break;

        case 1404:
        Enchantid = 804;
        Enchant(player, creature, item);
        break;

        case 1405:
        Enchantid = 1349;
        Enchant(player, creature, item);
        break;

        case 1406:
        Enchantid = 2078;
        Enchant(player, creature, item);
        break;

        case 1407:
        Enchantid = 2662;
        reqil = 1;
        Enchant(player, creature, item);
        break;
        
        case 1408:
        Enchantid = 2663;
        reqil = 1;   
        Enchant(player, creature, item);
        break;

        case 1409:
        Enchantid = 2780;
        reqil = 1;   
        Enchant(player, creature, item);
        break;

        case 1410:
        Enchantid = 1257;
        reqil = 1;
        Enchant(player, creature, item);
        break;

        case 1411:
        Enchantid = 1943;
        reqil = 1;
        Enchant(player, creature, item);
        break;

        case 1412:
        Enchantid = 1889;
        Enchant(player, creature, item);
        break;

        case 1413:
        Enchantid = 1888;
        Enchant(player, creature, item);
        break;

        // Chest
        case 4:
            slotid = 4;
            player->ADD_GOSSIP_ITEM(3, "100 health", GOSSIP_SENDER_MAIN, 402);
            player->ADD_GOSSIP_ITEM(3, "100 mana", GOSSIP_SENDER_MAIN, 403);
            player->ADD_GOSSIP_ITEM(3, "150 health", GOSSIP_SENDER_MAIN, 401);
            player->ADD_GOSSIP_ITEM(3, "4 all stats", GOSSIP_SENDER_MAIN, 404);
            player->ADD_GOSSIP_ITEM(3, "6 all stats", GOSSIP_SENDER_MAIN, 400);
            player->ADD_GOSSIP_ITEM(3, "7 mana per 5", GOSSIP_SENDER_MAIN, 405);
            player->ADD_GOSSIP_ITEM(3, "15 resilience", GOSSIP_SENDER_MAIN, 406);
            player->ADD_GOSSIP_ITEM(3, "15 spirit", GOSSIP_SENDER_MAIN, 407);
            player->ADD_GOSSIP_ITEM(0, "=> Back", GOSSIP_SENDER_MAIN, 100);
            player->SEND_GOSSIP_MENU(20005, creature->GetGUID());
        break;

        case 400:
        Enchantid = 1503;
        reqil = 1;
        Enchant(player, creature, item);
        break;

        case 401:
        Enchantid = 2659;
        reqil = 1;
        Enchant(player, creature, item);
        break;

        case 402:
        Enchantid = 1503;
        Enchant(player, creature, item);
        break;

        case 403:
        Enchantid = 1893;
        Enchant(player, creature, item);
        break;

        case 404:
        Enchantid = 1891;
        Enchant(player, creature, item);
        break;

        case 405:
        Enchantid = 2852;
        reqil = 1;
        Enchant(player, creature, item);
        break;

        case 406:
        Enchantid = 2789;
        reqil = 1;
        Enchant(player, creature, item);
        break;

        case 407:
        Enchantid = 1144;
        reqil = 1;
        Enchant(player, creature, item);
        break;

        //wrist
        case 8:
            slotid = 8;
            player->ADD_GOSSIP_ITEM(3, "12 stamina", GOSSIP_SENDER_MAIN, 805);
            player->ADD_GOSSIP_ITEM(3, "12 intel", GOSSIP_SENDER_MAIN, 806);
            player->ADD_GOSSIP_ITEM(3, "12 strength", GOSSIP_SENDER_MAIN, 801);
            player->ADD_GOSSIP_ITEM(3, "24 attack power", GOSSIP_SENDER_MAIN, 807);
            player->ADD_GOSSIP_ITEM(3, "15 spell power", GOSSIP_SENDER_MAIN, 800);
            player->ADD_GOSSIP_ITEM(3, "4 all stats", GOSSIP_SENDER_MAIN, 802);
            player->ADD_GOSSIP_ITEM(3, "9 spirit", GOSSIP_SENDER_MAIN, 808);
            player->ADD_GOSSIP_ITEM(3, "12 defense", GOSSIP_SENDER_MAIN, 803);
            player->ADD_GOSSIP_ITEM(3, "8 mana per 5", GOSSIP_SENDER_MAIN, 804);
            player->ADD_GOSSIP_ITEM(0, "=> Back", GOSSIP_SENDER_MAIN, 100);
            player->SEND_GOSSIP_MENU(20006, creature->GetGUID());
        break;

        case 800:
        Enchantid = 2319;
        Enchant(player, creature, item);
        break;

        case 801:
        Enchantid = 372;
        reqil = 1;
        Enchant(player, creature, item);
        break;

        case 802:
        Enchantid = 1891;
        reqil = 1;
        Enchant(player, creature, item);
        break;

        case 803:
        Enchantid = 1943;
        reqil = 1;
        Enchant(player, creature, item);
        break;

        case 804:
        Enchantid = 2382;
        reqil = 1;
        Enchant(player, creature, item);
        break;

        case 805:
        Enchantid = 371;
        reqil = 1;
        Enchant(player, creature, item);
        break;

        case 806:
        Enchantid = 369;
        reqil = 1;
        Enchant(player, creature, item);
        break;

        case 807:
        Enchantid = 1593;
        reqil = 1;
        Enchant(player, creature, item);
        break;

        case 808:
        Enchantid = 355;
        Enchant(player, creature, item);
        break;

        // gloves
        case 9:
            slotid = 9;
            player->ADD_GOSSIP_ITEM(3, "15 strength", GOSSIP_SENDER_MAIN, 904);
            player->ADD_GOSSIP_ITEM(3, "15 agility", GOSSIP_SENDER_MAIN, 901);
            player->ADD_GOSSIP_ITEM(3, "15 hit rating", GOSSIP_SENDER_MAIN, 903);
            player->ADD_GOSSIP_ITEM(3, "10 critical", GOSSIP_SENDER_MAIN, 902);
            player->ADD_GOSSIP_ITEM(3, "26 attack power", GOSSIP_SENDER_MAIN, 905);
            player->ADD_GOSSIP_ITEM(3, "20 attack power", GOSSIP_SENDER_MAIN, 906);
            player->ADD_GOSSIP_ITEM(3, "10 haste", GOSSIP_SENDER_MAIN, 907);
            player->ADD_GOSSIP_ITEM(3, "2% mount speed", GOSSIP_SENDER_MAIN, 908);
            player->ADD_GOSSIP_ITEM(3, "5 phising", GOSSIP_SENDER_MAIN, 900);
            player->ADD_GOSSIP_ITEM(0, "=> Back", GOSSIP_SENDER_MAIN, 100);
            player->SEND_GOSSIP_MENU(20007, creature->GetGUID());
        break;

        case 900:
        Enchantid = 2603;
        Enchant(player, creature, item);
        break;

        case 901:
        Enchantid = 883;
        Enchant(player, creature, item);
        break;

        case 902:
        Enchantid = 2913;
        reqil = 1;
        Enchant(player, creature, item);
        break;

        case 903:
        Enchantid = 2935;
        reqil = 1;
        Enchant(player, creature, item);
        break;

        case 904:
        Enchantid = 684;
        reqil = 1;
        Enchant(player, creature, item);
        break;

        case 905:
        Enchantid = 1594;
        reqil = 1;
        Enchant(player, creature, item);
        break;

        case 906:
        Enchantid = 2323;
        reqil = 1;
        Enchant(player, creature, item);
        break;

        case 907:
        Enchantid = 931;
        Enchant(player, creature, item);
        break;

        case 908:
        Enchantid = 930;
        Enchant(player, creature, item);
        break;

        // legs
        case 6:
        slotid = 6;
        Enchantid = 18;
        Enchant(player, creature, item);
        break;

        //boots
        case 7:
            slotid = 7;
            player->ADD_GOSSIP_ITEM(3, "12 stamina", GOSSIP_SENDER_MAIN, 701);
            player->ADD_GOSSIP_ITEM(3, "12 agility", GOSSIP_SENDER_MAIN, 704);
            player->ADD_GOSSIP_ITEM(3, "9 stamina + minor speed", GOSSIP_SENDER_MAIN, 703);
            player->ADD_GOSSIP_ITEM(3, "6 agility + minor speed", GOSSIP_SENDER_MAIN, 705);
            player->ADD_GOSSIP_ITEM(3, "5 health and mana per 5", GOSSIP_SENDER_MAIN, 700);
            player->ADD_GOSSIP_ITEM(3, "10 hit & critical rating", GOSSIP_SENDER_MAIN, 702);
            player->ADD_GOSSIP_ITEM(3, "5 critical", GOSSIP_SENDER_MAIN, 706);
            player->ADD_GOSSIP_ITEM(0, "=> Back", GOSSIP_SENDER_MAIN, 100);
            player->SEND_GOSSIP_MENU(20008, creature->GetGUID());
        break;

        case 700:
        Enchantid = 2656;
        reqil = 1;
        Enchant(player, creature, item);
        break;

        case 701:
        Enchantid = 371;
        reqil = 1;
        Enchant(player, creature, item);
        break;

        case 702:
        Enchantid = 2658;
        reqil = 1;
        Enchant(player, creature, item);
        break;

        case 703:
        Enchantid = 2940;
        reqil = 1;
        Enchant(player, creature, item);
        break;

        case 704:
        Enchantid = 368;
        reqil = 1;
        Enchant(player, creature, item);
        break;

        case 705:
        Enchantid = 2939;
        reqil = 1;
        Enchant(player, creature, item);
        break;

        case 706:
        Enchantid = 3858;
        Enchant(player, creature, item);
        break;

       //weapon
        case 15:
        slotid = 15;
        goto l153;
        break;

        case 16:
        slotid = 16;
        l153:
        case 153:
            player->ADD_GOSSIP_ITEM(3, "=> Page 2", GOSSIP_SENDER_MAIN, 154);
            player->ADD_GOSSIP_ITEM(3, "15 strength", GOSSIP_SENDER_MAIN, 1502);
            player->ADD_GOSSIP_ITEM(3, "20 strength", GOSSIP_SENDER_MAIN, 1508);
            player->ADD_GOSSIP_ITEM(3, "15 agility", GOSSIP_SENDER_MAIN, 1503);
            player->ADD_GOSSIP_ITEM(3, "20 agility", GOSSIP_SENDER_MAIN, 1517);
            player->ADD_GOSSIP_ITEM(3, "20 spirit", GOSSIP_SENDER_MAIN, 1504);
            player->ADD_GOSSIP_ITEM(3, "22 intel", GOSSIP_SENDER_MAIN, 1505);
            player->ADD_GOSSIP_ITEM(3, "30 intel", GOSSIP_SENDER_MAIN, 1507);
            player->ADD_GOSSIP_ITEM(3, "29 spell power", GOSSIP_SENDER_MAIN, 1516);
            player->ADD_GOSSIP_ITEM(3, "30 spell power", GOSSIP_SENDER_MAIN, 1501);
            player->ADD_GOSSIP_ITEM(3, "5 weapon damage", GOSSIP_SENDER_MAIN, 1521);
            player->ADD_GOSSIP_ITEM(3, "7 weapon damage", GOSSIP_SENDER_MAIN, 1506);
            player->ADD_GOSSIP_ITEM(3, "40 spell power (white)", GOSSIP_SENDER_MAIN, 1515);
            player->ADD_GOSSIP_ITEM(3, "40 spell power (yellow)", GOSSIP_SENDER_MAIN, 1509);
            player->ADD_GOSSIP_ITEM(3, "50 fire & arcane", GOSSIP_SENDER_MAIN, 1510);
            player->ADD_GOSSIP_ITEM(3, "54 givre & shadow", GOSSIP_SENDER_MAIN, 1511);
            player->ADD_GOSSIP_ITEM(3, "5 weapon damage", GOSSIP_SENDER_MAIN, 1521);
            player->ADD_GOSSIP_ITEM(3, "7 weapon damage", GOSSIP_SENDER_MAIN, 1506);
            player->ADD_GOSSIP_ITEM(0, "=> Back", GOSSIP_SENDER_MAIN, 100);
            player->SEND_GOSSIP_MENU(20009, creature->GetGUID());
            break;

        case 154:
            player->ADD_GOSSIP_ITEM(3, "Page 1 <=", GOSSIP_SENDER_MAIN, 153);
            player->ADD_GOSSIP_ITEM(3, "Crusader", GOSSIP_SENDER_MAIN, 1500);
            player->ADD_GOSSIP_ITEM(3, "lifestealing", GOSSIP_SENDER_MAIN, 1518);
            player->ADD_GOSSIP_ITEM(3, "Impie", GOSSIP_SENDER_MAIN, 1519);
            player->ADD_GOSSIP_ITEM(3, "Fiery weapon", GOSSIP_SENDER_MAIN, 1520);
            player->ADD_GOSSIP_ITEM(3, "Frisson glacial", GOSSIP_SENDER_MAIN, 1522);
            player->ADD_GOSSIP_ITEM(3, "Tueur de demon", GOSSIP_SENDER_MAIN, 1522);
            player->ADD_GOSSIP_ITEM(3, "Mangooste", GOSSIP_SENDER_MAIN, 1512);
            player->ADD_GOSSIP_ITEM(3, "Eruption de sort", GOSSIP_SENDER_MAIN, 1513);
            player->ADD_GOSSIP_ITEM(3, "Master of war", GOSSIP_SENDER_MAIN, 1514);
            player->ADD_GOSSIP_ITEM(3, "2M - 25 agility", GOSSIP_SENDER_MAIN, 1524);
            player->ADD_GOSSIP_ITEM(3, "2M - 70 attack power", GOSSIP_SENDER_MAIN, 1525);
            player->ADD_GOSSIP_ITEM(3, "2M - 35 agility", GOSSIP_SENDER_MAIN, 1526);
            player->ADD_GOSSIP_ITEM(3, "2M - 9 weapon damage", GOSSIP_SENDER_MAIN, 1527);
            player->ADD_GOSSIP_ITEM(0, "=> Back", GOSSIP_SENDER_MAIN, 100);
            player->SEND_GOSSIP_MENU(20009, creature->GetGUID());
        break;
        // 1H

        case 1500:
        Enchantid = 2656;
        Enchant(player, creature, item);
        break;

        case 1501:
        Enchantid = 2504;
        Enchant(player, creature, item);
        break;

        case 1502:
        Enchantid = 2563;
        Enchant(player, creature, item);
        break;

        case 1503:
        Enchantid = 2564;
        Enchant(player, creature, item);
        break;

        case 1504:
        Enchantid = 2567;
        Enchant(player, creature, item);
        break;

        case 1505:
        Enchantid = 2568;
        Enchant(player, creature, item);
        break;

        case 1506:
        Enchantid = 120;
        reqil = 1;
        Enchant(player, creature, item);
        break;

        case 1507:
        Enchantid = 2666;
        reqil = 1;
        Enchant(player, creature, item);
        break;

        case 1508:
        Enchantid = 2668;
        reqil = 1;
        Enchant(player, creature, item);
        break;

        case 1509:
        Enchantid = 2669;
        reqil = 1;
        Enchant(player, creature, item);
        break;

        case 1510:
        Enchantid = 2671;
        reqil = 1;
        Enchant(player, creature, item);
        break;

        case 1511:
        Enchantid = 2672;
        reqil = 1;
        Enchant(player, creature, item);
        break;

        case 1512:
        Enchantid = 2673;
        reqil = 1;
        Enchant(player, creature, item);
        break;

        case 1513:
        Enchantid = 2674;
        reqil = 1;
        Enchant(player, creature, item);
        break;

        case 1514:
        Enchantid = 2675;
        reqil = 1;
        Enchant(player, creature, item);
        break;

        case 1515:
        Enchantid = 3846;
        reqil = 1;
        Enchant(player, creature, item);
        break;

        case 1516:
        Enchantid = 2505;
        Enchant(player, creature, item);
        break;

        case 1517:
        Enchantid = 3222;
        reqil = 1;
        Enchant(player, creature, item);
        break;

        case 1518:
        Enchantid = 1989;
        Enchant(player, creature, item);
        break;

        case 1519:
        Enchantid = 1899;
        Enchant(player, creature, item);
        break;

        case 1520:
        Enchantid = 803;
        Enchant(player, creature, item);
        break;

        case 1521:
        Enchantid = 118;
        Enchant(player, creature, item);
        break;

        case 1522:
        Enchantid = 1894;
        Enchant(player, creature, item);
        break;

        case 1523:
        Enchantid = 912;
        Enchant(player, creature, item);
        break;
        // 2H
        case 1524:
        Enchantid = 2646;
        twoha = 1;
        Enchant(player, creature, item);
        break;

        case 1525:
        Enchantid = 2667;
        twoha = 1;
        reqil = 1;
        Enchant(player, creature, item);
        break;

        case 1526:
        Enchantid = 2670;
        twoha = 1;
        reqil = 1;
        Enchant(player, creature, item);
        break;

        case 1527:
        Enchantid = 1895;
        twoha = 1;
        Enchant(player, creature, item);
        break;

        // shield
        case 18:
            slotid = 16;
            player->ADD_GOSSIP_ITEM(3, "18 stamania", GOSSIP_SENDER_MAIN, 1803);
            player->ADD_GOSSIP_ITEM(3, "12 intel", GOSSIP_SENDER_MAIN, 1804);
            player->ADD_GOSSIP_ITEM(3, "12 resilience", GOSSIP_SENDER_MAIN, 1800);
            player->ADD_GOSSIP_ITEM(3, "36 block rating", GOSSIP_SENDER_MAIN, 1801);
            player->ADD_GOSSIP_ITEM(3, "15 score de blocage", GOSSIP_SENDER_MAIN, 1802);
            player->ADD_GOSSIP_ITEM(3, "5 all stats", GOSSIP_SENDER_MAIN, 1805);
            player->ADD_GOSSIP_ITEM(0, "=> Back", GOSSIP_SENDER_MAIN, 100);
            player->SEND_GOSSIP_MENU(20010, creature->GetGUID());
        break;

        case 1800:
        Enchantid = 3215;
        reqil = 1;
        Enchant(player, creature, item);
        break;

        case 1801:
        Enchantid = 2653;
        reqil = 1;
        Enchant(player, creature, item);
        break;

        case 1802:
        Enchantid = 1985;
        reqil = 1;
        Enchant(player, creature, item);
        break;

        case 1803:
        Enchantid = 1071;
        reqil = 1;
        Enchant(player, creature, item);
        break;

        case 1804:
        Enchantid = 2654;
        reqil = 1;
        Enchant(player, creature, item);
        break;

        case 1805:
        Enchantid = 3242;
        reqil = 1;
        Enchant(player, creature, item);
        break;

        // Ranged
        case 17:
        slotid = 17;
        Enchantid = 663;
        Enchant(player, creature, item);
        break;


        }
    return true;
    }
};

void AddSC_npc_enchant()
{
    new npc_enchant();
}