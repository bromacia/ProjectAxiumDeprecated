#include "MallMgr.h"

bool MallMgr::OnGossipHello(Player* player, Creature* creature)
{
    player->PlayerTalkClass->ClearMenus();

    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "|TInterface\\icons\\inv_crate_01:30|t General Goods", GOSSIP_SENDER_MAIN, MALL_MENU_GENERAL_GOODS);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "|TInterface\\icons\\inv_chest_cloth_74:30|t Gear", GOSSIP_SENDER_MAIN, MALL_MENU_GEAR);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "|TInterface\\icons\\inv_gizmo_gnomishflameturret:30|t Professions", GOSSIP_SENDER_MAIN, MALL_MENU_PROFESSIONS);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "|TInterface\\icons\\inv_rod_enchantedadamantite:30|t Enchants", GOSSIP_SENDER_MAIN, MALL_MENU_ENCHANTS);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "|TInterface\\icons\\inv_jewelcrafting_pyrestone_02:30|t Gems", GOSSIP_SENDER_MAIN, MALL_MENU_GEMS);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "|TInterface\\icons\\ability_mount_bigblizzardbear:30|t Mounts", GOSSIP_SENDER_MAIN, MALL_MENU_MOUNTS);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "|TInterface\\icons\\inv_inscription_minorglyph00:30|t Glyphs", GOSSIP_SENDER_MAIN, MALL_MENU_GLYPHS);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "|TInterface\\icons\\spell_arcane_mindmastery:30|t Reset Talents", GOSSIP_SENDER_MAIN, MALL_MENU_RESET_TALENTS);

    if (player->GetSpecsCount() < 2)
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "|TInterface\\icons\\achievement_general:30|t Learn Dual Specialization", GOSSIP_SENDER_MAIN, MALL_MENU_LEARN_DUAL_SPEC);

    if (player->getClass() == CLASS_ROGUE && player->HasSpell(51713))
        if (player->HasAura(51713) && player->GetAura(51713, player->GetGUID())->GetDuration() == -1)
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "|TInterface\\icons\\achievement_reputation_01:30|t I'm Finished", GOSSIP_SENDER_MAIN, MALL_MENU_FINISH_SHADOW_DANCE);
        else
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "|TInterface\\icons\\ability_rogue_shadowdance:30|t Setup Shadow Dance Bar", GOSSIP_SENDER_MAIN, MALL_MENU_SETUP_SHADOW_DANCE);

    player->SEND_GOSSIP_MENU(1, creature->GetGUID());
    return true;
}

bool MallMgr::OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action)
{
    player->PlayerTalkClass->ClearMenus();

    switch (sender)
    {
        case GOSSIP_SENDER_MAIN:
        {
            switch (action)
            {
                case GOSSIP_SENDER_MAIN:            OnGossipHello(player, creature);                               break;
                case MALL_MENU_GENERAL_GOODS:       ShowInventory(player, creature, INVENTORY_LIST_GENERAL_GOODS); break;
                case MALL_MENU_GEAR:                HandleGear(player, creature, MALL_MENU_GEAR);                  break;
                case MALL_MENU_PROFESSIONS:         HandleProfessions(player, creature);                           break;
                case MALL_MENU_ENCHANTS:            HandleEnchants(player, creature, MALL_MENU_ENCHANTS);          break;
                case MALL_MENU_GEMS:                HandleGems(player, creature, MALL_MENU_GEMS);                  break;
                case MALL_MENU_MOUNTS:              ShowInventory(player, creature, INVENTORY_LIST_MOUNTS);        break;
                case MALL_MENU_GLYPHS:              ShowInventory(player, creature, INVENTORY_LIST_GLYPHS);        break;
                case MALL_MENU_RESET_TALENTS:       HandleResetTalents(player, creature);                          break;
                case MALL_MENU_LEARN_DUAL_SPEC:     HandleLearnDualSpecialization(player, creature);               break;
                case MALL_MENU_SETUP_SHADOW_DANCE:  HandleSetupShadowDanceBar(player, creature);                   break;
                case MALL_MENU_FINISH_SHADOW_DANCE: HandleFinishShadowDanceBar(player, creature);                  break;
            }
            break;
        }
        case MALL_MENU_GEAR:
        {
            switch (action)
            {
                case MALL_GEAR_RELENTLESS_GLADIATOR:  HandleGear(player, creature, MALL_GEAR_RELENTLESS_GLADIATOR);  break;
                case MALL_GEAR_TRIAL_OF_THE_CRUSADER: HandleGear(player, creature, MALL_GEAR_TRIAL_OF_THE_CRUSADER); break;
                case MALL_GEAR_WRATHFUL_GLADIATOR:    HandleGear(player, creature, MALL_GEAR_WRATHFUL_GLADIATOR);    break;
                case MALL_GEAR_ICECROWN_CITADEL:      HandleGear(player, creature, MALL_GEAR_ICECROWN_CITADEL);      break;
                case MALL_GEAR_APPAREL:               HandleGear(player, creature, MALL_GEAR_APPAREL);               break;
            }
            break;
        }
        case MALL_MENU_PROFESSIONS:
        {
            LearnSkill(player, creature, action);
            break;
        }
        case MALL_MENU_ENCHANTS:
        {
            HandleEnchants(player, creature, action);
            break;
        }
        case MALL_MENU_GEMS:
        {
            HandleGems(player, creature, action);
            break;
        }
        case MALL_GEAR_RELENTLESS_GLADIATOR:
        {
            switch (action)
            {
                case GEAR_OPTION_MAINSETS_AND_OFFSETS: ShowInventory(player, creature, INVENTORY_LIST_RELENTLESS_GLADIATOR_MAINSETS_AND_OFFSETS); break;
                case GEAR_OPTION_ACCESSORIES:          ShowInventory(player, creature, INVENTORY_LIST_RELENTLESS_GLADIATOR_ACCESSORIES);          break;
                case GEAR_OPTION_WEAPONS:              ShowInventory(player, creature, INVENTORY_LIST_RELENTLESS_GLADIATOR_WEAPONS);              break;
                case GEAR_OPTION_TRINKETS:             ShowInventory(player, creature, INVENTORY_LIST_245_TRINKETS);                              break;
            }
            break;
        }
        case MALL_GEAR_TRIAL_OF_THE_CRUSADER:
        {
            switch (action)
            {
                case GEAR_OPTION_MAINSETS_AND_OFFSETS: ShowInventory(player, creature, INVENTORY_LIST_TRIAL_OF_THE_CRUSADER_MAINSETS_AND_OFFSETS); break;
                case GEAR_OPTION_ACCESSORIES:          ShowInventory(player, creature, INVENTORY_LIST_TRIAL_OF_THE_CRUSADER_ACCESSORIES);          break;
                case GEAR_OPTION_WEAPONS:              ShowInventory(player, creature, INVENTORY_LIST_TRIAL_OF_THE_CRUSADER_WEAPONS);              break;
                case GEAR_OPTION_TRINKETS:             ShowInventory(player, creature, INVENTORY_LIST_245_TRINKETS);                               break;
            }
            break;
        }
        case MALL_GEAR_WRATHFUL_GLADIATOR:
        {
            switch (action)
            {
                case GEAR_OPTION_MAINSETS_AND_OFFSETS: ShowInventory(player, creature, INVENTORY_LIST_WRATHFUL_GLADIATOR_MAINSETS_AND_OFFSETS); break;
                case GEAR_OPTION_ACCESSORIES:          ShowInventory(player, creature, INVENTORY_LIST_WRATHFUL_GLADIATOR_ACCESSORIES);          break;
                case GEAR_OPTION_WEAPONS:              ShowInventory(player, creature, INVENTORY_LIST_WRATHFUL_GLADIATOR_WEAPONS);              break;
                case GEAR_OPTION_TRINKETS:             ShowInventory(player, creature, INVENTORY_LIST_264_TRINKETS);                            break;
            }
            break;
        }
        case MALL_GEAR_ICECROWN_CITADEL:
        {
            switch (action)
            {
                case GEAR_OPTION_MAINSETS_AND_OFFSETS: ShowInventory(player, creature, INVENTORY_LIST_ICECROWN_CITADEL_MAINSETS_AND_OFFSETS); break;
                case GEAR_OPTION_ACCESSORIES:          ShowInventory(player, creature, INVENTORY_LIST_ICECROWN_CITADEL_ACCESSORIES);          break;
                case GEAR_OPTION_WEAPONS:              ShowInventory(player, creature, INVENTORY_LIST_ICECROWN_CITADEL_WEAPONS);              break;
                case GEAR_OPTION_TRINKETS:             ShowInventory(player, creature, INVENTORY_LIST_264_TRINKETS);                          break;
            }
            break;
        }
        case ENCHANT_OPTION_HEAD:
        case ENCHANT_OPTION_SHOULDERS:
        case ENCHANT_OPTION_CHEST:
        case ENCHANT_OPTION_GLOVES:
        case ENCHANT_OPTION_LEGS:
        case ENCHANT_OPTION_BRACERS:
        case ENCHANT_OPTION_BELT:
        case ENCHANT_OPTION_BOOTS:
        case ENCHANT_OPTION_CLOAK:
        case ENCHANT_OPTION_RING1:
        case ENCHANT_OPTION_RING2:
        case ENCHANT_OPTION_MAIN_HAND:
        case ENCHANT_OPTION_OFF_HAND:
        case ENCHANT_OPTION_RANGED:
        {
            EnchantItem(player, creature, action, sender);
            break;
        }
    }

    return true;
}

bool MallMgr::HandleGear(Player* player, Creature* creature, uint32 action)
{
    switch (action)
    {
        case MALL_MENU_GEAR:
        {
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Relentless Gladiator", MALL_MENU_GEAR, MALL_GEAR_RELENTLESS_GLADIATOR);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Trial of the Crusader", MALL_MENU_GEAR, MALL_GEAR_TRIAL_OF_THE_CRUSADER);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Wrathful Gladiator", MALL_MENU_GEAR, MALL_GEAR_WRATHFUL_GLADIATOR);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Icecrown Citadel", MALL_MENU_GEAR, MALL_GEAR_ICECROWN_CITADEL);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Apparel", MALL_MENU_GEAR, MALL_GEAR_APPAREL);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Back", GOSSIP_SENDER_MAIN, GOSSIP_SENDER_MAIN);
            player->SEND_GOSSIP_MENU(1, creature->GetGUID());
            break;
        }
        case MALL_GEAR_RELENTLESS_GLADIATOR:
        {
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Mainsets & Offsets", MALL_GEAR_RELENTLESS_GLADIATOR, GEAR_OPTION_MAINSETS_AND_OFFSETS);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Accessories", MALL_GEAR_RELENTLESS_GLADIATOR, GEAR_OPTION_ACCESSORIES);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Weapons", MALL_GEAR_RELENTLESS_GLADIATOR, GEAR_OPTION_WEAPONS);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Trinkets", MALL_GEAR_RELENTLESS_GLADIATOR, GEAR_OPTION_TRINKETS);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Back", GOSSIP_SENDER_MAIN, MALL_MENU_GEAR);
            player->SEND_GOSSIP_MENU(1, creature->GetGUID());
            break;
        }
        case MALL_GEAR_TRIAL_OF_THE_CRUSADER:
        {
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Mainsets & Offsets", MALL_GEAR_TRIAL_OF_THE_CRUSADER, GEAR_OPTION_MAINSETS_AND_OFFSETS);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Accessories", MALL_GEAR_TRIAL_OF_THE_CRUSADER, GEAR_OPTION_ACCESSORIES);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Weapons", MALL_GEAR_TRIAL_OF_THE_CRUSADER, GEAR_OPTION_WEAPONS);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Trinkets", MALL_GEAR_TRIAL_OF_THE_CRUSADER, GEAR_OPTION_TRINKETS);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Back", GOSSIP_SENDER_MAIN, MALL_MENU_GEAR);
            player->SEND_GOSSIP_MENU(1, creature->GetGUID());
            break;
        }
        case MALL_GEAR_WRATHFUL_GLADIATOR:
        {
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Mainsets & Offsets", MALL_GEAR_WRATHFUL_GLADIATOR, GEAR_OPTION_MAINSETS_AND_OFFSETS);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Accessories", MALL_GEAR_WRATHFUL_GLADIATOR, GEAR_OPTION_ACCESSORIES);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Weapons", MALL_GEAR_WRATHFUL_GLADIATOR, GEAR_OPTION_WEAPONS);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Trinkets", MALL_GEAR_WRATHFUL_GLADIATOR, GEAR_OPTION_TRINKETS);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Back", GOSSIP_SENDER_MAIN, MALL_MENU_GEAR);
            player->SEND_GOSSIP_MENU(1, creature->GetGUID());
            break;
        }
        case MALL_GEAR_ICECROWN_CITADEL:
        {
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Mainsets & Offsets", MALL_GEAR_ICECROWN_CITADEL, GEAR_OPTION_MAINSETS_AND_OFFSETS);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Accessories", MALL_GEAR_ICECROWN_CITADEL, GEAR_OPTION_ACCESSORIES);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Weapons", MALL_GEAR_ICECROWN_CITADEL, GEAR_OPTION_WEAPONS);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Trinkets", MALL_GEAR_ICECROWN_CITADEL, GEAR_OPTION_TRINKETS);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Back", GOSSIP_SENDER_MAIN, MALL_MENU_GEAR);
            player->SEND_GOSSIP_MENU(1, creature->GetGUID());
            break;
        }
        case MALL_GEAR_APPAREL:
        {
            ShowInventory(player, creature, INVENTORY_LIST_APPAREL);
            break;
        }
    }

    return true;
}

bool MallMgr::HandleProfessions(Player* player, Creature* creature)
{
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Alchemy", MALL_MENU_PROFESSIONS, SKILL_ALCHEMY);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Blacksmithing", MALL_MENU_PROFESSIONS, SKILL_BLACKSMITHING);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Enchanting", MALL_MENU_PROFESSIONS, SKILL_ENCHANTING);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Engineering", MALL_MENU_PROFESSIONS, SKILL_ENGINEERING);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Herbalism", MALL_MENU_PROFESSIONS, SKILL_HERBALISM);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Inscription", MALL_MENU_PROFESSIONS, SKILL_INSCRIPTION);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Jewelcrafting", MALL_MENU_PROFESSIONS, SKILL_JEWELCRAFTING);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Leatherworking", MALL_MENU_PROFESSIONS, SKILL_LEATHERWORKING);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Tailoring", MALL_MENU_PROFESSIONS, SKILL_TAILORING);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Back", GOSSIP_SENDER_MAIN, GOSSIP_SENDER_MAIN);
    player->SEND_GOSSIP_MENU(1, creature->GetGUID());
    return true;
}

bool MallMgr::HandleEnchants(Player* player, Creature* creature, uint32 action)
{
    ChatHandler* handler = new ChatHandler(player);

    switch (action)
    {
        case MALL_MENU_ENCHANTS:
        {
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Head", MALL_MENU_ENCHANTS, ENCHANT_OPTION_HEAD);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Shoulders", MALL_MENU_ENCHANTS, ENCHANT_OPTION_SHOULDERS);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Chest", MALL_MENU_ENCHANTS, ENCHANT_OPTION_CHEST);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Gloves", MALL_MENU_ENCHANTS, ENCHANT_OPTION_GLOVES);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Legs", MALL_MENU_ENCHANTS, ENCHANT_OPTION_LEGS);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Bracers", MALL_MENU_ENCHANTS, ENCHANT_OPTION_BRACERS);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Belt", MALL_MENU_ENCHANTS, ENCHANT_OPTION_BELT);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Boots", MALL_MENU_ENCHANTS, ENCHANT_OPTION_BOOTS);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Cloak", MALL_MENU_ENCHANTS, ENCHANT_OPTION_CLOAK);

            if (player->GetSkillValue(SKILL_ENCHANTING) == 450)
            {
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Ring 1", MALL_MENU_ENCHANTS, ENCHANT_OPTION_RING1);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Ring 2", MALL_MENU_ENCHANTS, ENCHANT_OPTION_RING2);
            }

            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Main Hand", MALL_MENU_ENCHANTS, ENCHANT_OPTION_MAIN_HAND);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Off Hand", MALL_MENU_ENCHANTS, ENCHANT_OPTION_OFF_HAND);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Ranged", MALL_MENU_ENCHANTS, ENCHANT_OPTION_RANGED);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Back", GOSSIP_SENDER_MAIN, GOSSIP_SENDER_MAIN);
            player->SEND_GOSSIP_MENU(1, creature->GetGUID());
            break;
        }
        case ENCHANT_OPTION_HEAD:
        {
            Item* pItem = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD);
            if (!pItem)
            {
                handler->PSendSysMessage("You have no item equipped in your head slot");
                player->CLOSE_GOSSIP_MENU();
                return false;
            }

            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "+50 Attack Power & +20 Resilience", ENCHANT_OPTION_HEAD, ENCHANT_HEAD_ARCANUM_OF_TRIUMPH);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "+29 Spell Power & +20 Resilience", ENCHANT_OPTION_HEAD, ENCHANT_HEAD_ARCANUM_OF_DOMINANCE);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "+50 Attack Power & +20 Critical Strike", ENCHANT_OPTION_HEAD, ENCHANT_HEAD_ARCANUM_OF_TORMENT);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "30 Spell Power & +20 Critical Strike", ENCHANT_OPTION_HEAD, ENCHANT_HEAD_ARCANUM_OF_BURNING_MYSTERIES);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "30 Spell Power & +10 MP5", ENCHANT_OPTION_HEAD, ENCHANT_HEAD_ARCANUM_OF_BLISSFUL_MENDING);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "+37 Stamina & +20 Resilience", ENCHANT_OPTION_HEAD, ENCHANT_HEAD_ARCANUM_OF_THE_STALWART_PROTECTOR);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Back", GOSSIP_SENDER_MAIN, MALL_MENU_ENCHANTS);
            player->SEND_GOSSIP_MENU(1, creature->GetGUID());
            break;
        }
        case ENCHANT_OPTION_SHOULDERS:
        {
            Item* pItem = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS);
            if (!pItem)
            {
                handler->PSendSysMessage("You have no item equipped in your shoulder slot");
                player->CLOSE_GOSSIP_MENU();
                return false;
            }

            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "+40 Attack Power & +15 Resilience", ENCHANT_OPTION_SHOULDERS, ENCHANT_SHOULDER_INSCRIPTION_OF_TRIUMPH);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "+23 Spell Power & +15 Resilience", ENCHANT_OPTION_SHOULDERS, ENCHANT_SHOULDER_INSCRIPTION_OF_DOMINANCE);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "+40 Attack Power & +15 Critical Strike", ENCHANT_OPTION_SHOULDERS, ENCHANT_SHOULDER_GREATER_INSCRIPTION_OF_THE_AXE);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "+24 Spell Power & +15 Critical Strike", ENCHANT_OPTION_SHOULDERS, ENCHANT_SHOULDER_GREATER_INSCRIPTION_OF_THE_STORM);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "+24 Spell Power & +8 MP5", ENCHANT_OPTION_SHOULDERS, ENCHANT_SHOULDER_GREATER_INSCRIPTION_OF_THE_CRAG);

            if (player->GetSkillValue(SKILL_INSCRIPTION) == 450)
            {
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "+120 Attack Power & +15 Critical Strike", ENCHANT_OPTION_SHOULDERS, ENCHANT_SHOULDERS_MASTERS_INSCRIPTION_OF_THE_AXE);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "+70 Spell Power & +15 Critical Strike", ENCHANT_OPTION_SHOULDERS, ENCHANT_SHOULDERS_MASTERS_INSCRIPTION_OF_THE_STORM);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "+70 Spell Power & +8 MP5", ENCHANT_OPTION_SHOULDERS, ENCHANT_SHOULDERS_MASTERS_INSCRIPTION_OF_THE_CRAG);
            }

            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Back", GOSSIP_SENDER_MAIN, MALL_MENU_ENCHANTS);
            player->SEND_GOSSIP_MENU(1, creature->GetGUID());
            break;
        }
        case ENCHANT_OPTION_CHEST:
        {
            Item* pItem = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST);
            if (!pItem)
            {
                handler->PSendSysMessage("You have no item equipped in your chest slot");
                player->CLOSE_GOSSIP_MENU();
                return false;
            }

            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "+20 Resilience", ENCHANT_OPTION_CHEST, ENCHANT_CHEST_EXCEPTIONAL_RESILIENCE);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "+10 Stats", ENCHANT_OPTION_CHEST, ENCHANT_CHEST_POWERFUL_STATS);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "+275 Health", ENCHANT_OPTION_CHEST, ENCHANT_CHEST_SUPER_HEALTH);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Back", GOSSIP_SENDER_MAIN, MALL_MENU_ENCHANTS);
            player->SEND_GOSSIP_MENU(1, creature->GetGUID());
            break;
        }
        case ENCHANT_OPTION_GLOVES:
        {
            Item* pItem = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS);
            if (!pItem)
            {
                handler->PSendSysMessage("You have no item equipped in your hands slot");
                player->CLOSE_GOSSIP_MENU();
                return false;
            }

            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "+44 Attack Power", ENCHANT_OPTION_GLOVES, ENCHANT_GLOVES_CRUSHER);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "+28 Spell Power", ENCHANT_OPTION_GLOVES, ENCHANT_GLOVES_EXCEPTIONAL_SPELLPOWER);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "+20 Agility", ENCHANT_OPTION_GLOVES, ENCHANT_GLOVES_MAJOR_AGILITY);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "+20 Hit Rating", ENCHANT_OPTION_GLOVES, ENCHANT_GLOVES_PERCISION);

            if (player->GetSkillValue(SKILL_BLACKSMITHING) == 450)
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Socket Gloves", ENCHANT_OPTION_GLOVES, ENCHANT_GLOVES_SOCKET);

            if (player->GetSkillValue(SKILL_ENGINEERING) == 450)
            {
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Hand-Mounted Pyro Rocket", ENCHANT_OPTION_GLOVES, ENCHANT_GLOVES_HAND_MOUNTED_PRYO_ROCKET);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Hyperspeed Accelerators", ENCHANT_OPTION_GLOVES, ENCHANT_GLOVES_HYPERSPEED_ACCELERATORS);
            }

            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Back", GOSSIP_SENDER_MAIN, MALL_MENU_ENCHANTS);
            player->SEND_GOSSIP_MENU(1, creature->GetGUID());
            break;
        }
        case ENCHANT_OPTION_LEGS:
        {
            Item* pItem = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS);
            if (!pItem)
            {
                handler->PSendSysMessage("You have no item equipped in your legs slot");
                player->CLOSE_GOSSIP_MENU();
                return false;
            }

            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "+75 Attack Power & +22 Critical Strike", ENCHANT_OPTION_LEGS, ENCHANT_LEGS_ICESCALE_LEG_ARMOR);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "+50 Spell Power & +30 Stamina", ENCHANT_OPTION_LEGS, ENCHANT_LEGS_SAPPHIRE_SPELLTHREAD);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "+50 Spell Power & +20 Spirit", ENCHANT_OPTION_LEGS, ENCHANT_LEGS_BRILLIANT_SPELLTHREAD);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "+55 Stamina & +22 Agility", ENCHANT_OPTION_LEGS, ENCHANT_LEGS_FROSTHIDE_LEG_ARMOR);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "+40 Resilience & +28 Stamina", ENCHANT_OPTION_LEGS, ENCHANT_LEGS_EARTHEN_LEG_ARMOR);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Back", GOSSIP_SENDER_MAIN, MALL_MENU_ENCHANTS);
            player->SEND_GOSSIP_MENU(1, creature->GetGUID());
            break;
        }
        case ENCHANT_OPTION_BRACERS:
        {
            Item* pItem = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WRISTS);
            if (!pItem)
            {
                handler->PSendSysMessage("You have no item equipped in your wrists slot");
                player->CLOSE_GOSSIP_MENU();
                return false;
            }

            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "+50 Attack Power", ENCHANT_OPTION_BRACERS, ENCHANT_BRACERS_GREATER_ASSAULT);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "+30 Spell Power", ENCHANT_OPTION_BRACERS, ENCHANT_BRACERS_SUPERIOR_SPELLPOWER);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "+16 Intellect", ENCHANT_OPTION_BRACERS, ENCHANT_BRACERS_EXCEPTIONAL_INTELLECT);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "+18 Spirit", ENCHANT_OPTION_BRACERS, ENCHANT_BRACERS_MAJOR_SPIRIT);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "+40 Stamina", ENCHANT_OPTION_BRACERS, ENCHANT_BRACERS_MAJOR_STAMINA);

            if (player->GetSkillValue(SKILL_BLACKSMITHING) == 450)
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Socket Bracer", ENCHANT_OPTION_BRACERS, ENCHANT_BRACER_SOCKET);

            if (player->GetSkillValue(SKILL_LEATHERWORKING) == 450)
            {
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "+130 Attack Power", ENCHANT_OPTION_BRACERS, ENCHANT_BRACER_FUR_LINING_ATTACKPOWER);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "+76 Spell Power", ENCHANT_OPTION_BRACERS, ENCHANT_BRACER_FUR_LINING_SPELLPOWER);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "+57 Agility", ENCHANT_OPTION_BRACERS, ENCHANT_BRACER_FUR_LINING_AGILITY);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "+102 Stamina", ENCHANT_OPTION_BRACERS, ENCHANT_BRACER_FUR_LINING_STAMINA);
            }

            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Back", GOSSIP_SENDER_MAIN, MALL_MENU_ENCHANTS);
            player->SEND_GOSSIP_MENU(1, creature->GetGUID());
            break;
        }
        case ENCHANT_OPTION_BELT:
        {
            Item* pItem = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST);
            if (!pItem)
            {
                handler->PSendSysMessage("You have no item equipped in your waist slot");
                player->CLOSE_GOSSIP_MENU();
                return false;
            }

            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Eternal Belt Buckle", ENCHANT_OPTION_BELT, ENCHANT_BELT_ETERNAL_BELT_BUCKLE);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Back", GOSSIP_SENDER_MAIN, MALL_MENU_ENCHANTS);
            player->SEND_GOSSIP_MENU(1, creature->GetGUID());
            break;
        }
        case ENCHANT_OPTION_BOOTS:
        {
            Item* pItem = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET);
            if (!pItem)
            {
                handler->PSendSysMessage("You have no item equipped in your feet slot");
                player->CLOSE_GOSSIP_MENU();
                return false;
            }

            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "+32 Attack Power", ENCHANT_OPTION_BOOTS, ENCHANT_BOOTS_GREATER_ASSULT);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "+16 Agility", ENCHANT_OPTION_BOOTS, ENCHANT_BOOTS_SUPERIOR_AGILITY);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "+12 Hit Rating & +12 Critical", ENCHANT_OPTION_BOOTS, ENCHANT_BOOTS_ICEWALKER);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "+15 Stamina & +8% Movement Speed", ENCHANT_OPTION_BOOTS, ENCHANT_BOOTS_TUSKARR_VITALITY);

            if (player->GetSkillValue(SKILL_ENGINEERING) == 450)
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Nitro Boosts", ENCHANT_OPTION_BOOTS, ENCHANT_BOOTS_NITRO_BOOSTS);

            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Back", GOSSIP_SENDER_MAIN, MALL_MENU_ENCHANTS);
            player->SEND_GOSSIP_MENU(1, creature->GetGUID());
            break;
        }
        case ENCHANT_OPTION_CLOAK:
        {
            Item* pItem = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_BACK);
            if (!pItem)
            {
                handler->PSendSysMessage("You have no item equipped in your back slot");
                player->CLOSE_GOSSIP_MENU();
                return false;
            }

            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "+35 Spell Penetration", ENCHANT_OPTION_CLOAK, ENCHANT_CLOAK_SPELL_PIERCING);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "+22 Agility", ENCHANT_OPTION_CLOAK, ENCHANT_CLOAK_MAJOR_AGILITY);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "+22 Haste", ENCHANT_OPTION_CLOAK, ENCHANT_CLOAK_GREATER_SPEED);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "+10 Agility & +1 Steath Level", ENCHANT_OPTION_CLOAK, ENCHANT_CLOAK_SHADOW_ARMOR);

            if (player->GetSkillValue(SKILL_ENGINEERING) == 450)
            {
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Flexweave Underlay", ENCHANT_OPTION_CLOAK, ENCHANT_CLOAK_FLEXWEAVE_UNDERLAY);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Springy Arachnoweave", ENCHANT_OPTION_CLOAK, ENCHANT_CLOAK_SPRINGY_ARACHNOWEAVE);
            }

            if (player->GetSkillValue(SKILL_TAILORING) == 450)
            {
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Swordguard Embroidery", ENCHANT_OPTION_CLOAK, ENCHANT_CLOAK_SWORDGUARD_EMBROIDERY);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Lightweave Embroidery", ENCHANT_OPTION_CLOAK, ENCHANT_CLOAK_LIGHTWEAVE_EMBROIDERY);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Darkglow Embroidery", ENCHANT_OPTION_CLOAK, ENCHANT_CLOAK_DARKGLOW_EMBROIDERY);
            }

            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Back", GOSSIP_SENDER_MAIN, MALL_MENU_ENCHANTS);
            player->SEND_GOSSIP_MENU(1, creature->GetGUID());
            break;
        }
        case ENCHANT_OPTION_RING1:
        {
            Item* pItem = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FINGER2);
            if (!pItem)
            {
                handler->PSendSysMessage("You have no item equipped in your finger1 slot");
                player->CLOSE_GOSSIP_MENU();
                return false;
            }

            if (player->GetSkillValue(SKILL_ENCHANTING) == 450)
            {
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "+40 Attack Power", ENCHANT_OPTION_RING1, ENCHANT_RING_ASSAULT);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "+23 Spell Power", ENCHANT_OPTION_RING1, ENCHANT_RING_GREATER_SPELLPOWER);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "+30 Stamina", ENCHANT_OPTION_RING1, ENCHANT_RING_STAMINA);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Back", GOSSIP_SENDER_MAIN, MALL_MENU_ENCHANTS);
                player->SEND_GOSSIP_MENU(1, creature->GetGUID());
            }
            break;
        }
        case ENCHANT_OPTION_RING2:
        {
            Item* pItem = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FINGER2);
            if (!pItem)
            {
                handler->PSendSysMessage("You have no item equipped in your finger2 slot");
                player->CLOSE_GOSSIP_MENU();
                return false;
            }

            if (player->GetSkillValue(SKILL_ENCHANTING) == 450)
            {
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "+40 Attack Power", ENCHANT_OPTION_RING2, ENCHANT_RING_ASSAULT);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "+23 Spell Power", ENCHANT_OPTION_RING2, ENCHANT_RING_GREATER_SPELLPOWER);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "+30 Stamina", ENCHANT_OPTION_RING2, ENCHANT_RING_STAMINA);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Back", GOSSIP_SENDER_MAIN, MALL_MENU_ENCHANTS);
                player->SEND_GOSSIP_MENU(1, creature->GetGUID());
            }
            break;
        }
        case ENCHANT_OPTION_MAIN_HAND:
        {
            Item* pItem = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND);
            if (!pItem)
            {
                handler->PSendSysMessage("You have no item equipped in your main hand slot");
                player->CLOSE_GOSSIP_MENU();
                return false;
            }

            const ItemTemplate* pItemTemplate = pItem->GetTemplate();
            if (!pItemTemplate)
            {
                handler->PSendSysMessage("Unable to get template data for the item in your main hand slot");
                player->CLOSE_GOSSIP_MENU();
                return false;
            }

            if (pItemTemplate->InventoryType == INVTYPE_2HWEAPON)
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "+110 Attack Power", ENCHANT_OPTION_MAIN_HAND, ENCHANT_2H_WEAPON_MASSACRE);

            if (pItemTemplate->SubClass == ITEM_SUBCLASS_WEAPON_STAFF)
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "+81 Spell Power", ENCHANT_OPTION_MAIN_HAND, ENCHANT_STAFF_GREATER_SPELLPOWER);

            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Berserking", ENCHANT_OPTION_MAIN_HAND, ENCHANT_WEAPON_BERSERKING);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Black Magic", ENCHANT_OPTION_MAIN_HAND, ENCHANT_WEAPON_BLACK_MAGIC);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Blood Draining", ENCHANT_OPTION_MAIN_HAND, ENCHANT_WEAPON_BLOOD_DRAINING);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Blade Warding", ENCHANT_OPTION_MAIN_HAND, ENCHANT_WEAPON_BLADE_WARDING);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Titanium Weapon Chain", ENCHANT_OPTION_MAIN_HAND, ENCHANT_WEAPON_TITANIUM_WEAPON_CHAIN);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "+65 Attack Power", ENCHANT_OPTION_MAIN_HAND, ENCHANT_WEAPON_SUPERIOR_POTENCY);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "+63 Spell Power", ENCHANT_OPTION_MAIN_HAND, ENCHANT_WEAPON_MIGHTY_SPELLPOWER);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "+26 Agility", ENCHANT_OPTION_MAIN_HAND, ENCHANT_WEAPON_EXCEPTIONAL_AGILITY);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "+45 Spirit", ENCHANT_OPTION_MAIN_HAND, ENCHANT_WEAPON_EXCEPTIONAL_SPIRIT);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "+50 Stamina", ENCHANT_OPTION_MAIN_HAND, ENCHANT_WEAPON_TITANGUARD);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "+25 Hit Rating & +25 Critical Strike", ENCHANT_OPTION_MAIN_HAND, ENCHANT_WEAPON_ACCURACY);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Mongoose", ENCHANT_OPTION_MAIN_HAND, ENCHANT_WEAPON_MONGOOSE);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Executioner", ENCHANT_OPTION_MAIN_HAND, ENCHANT_WEAPON_EXECUTIONER);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Deathfrost", ENCHANT_OPTION_MAIN_HAND, ENCHANT_WEAPON_DEATHFROST);

            if (player->getClass() == CLASS_DEATH_KNIGHT)
            {
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Fallen Crusader", ENCHANT_OPTION_MAIN_HAND, ENCHANT_WEAPON_FALLEN_CRUSADER);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Cinderglacier", ENCHANT_OPTION_MAIN_HAND, ENCHANT_WEAPON_CINDERGLACIER);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Razorice", ENCHANT_OPTION_MAIN_HAND, ENCHANT_WEAPON_RAZORICE);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Lichbane", ENCHANT_OPTION_MAIN_HAND, ENCHANT_WEAPON_LICHBANE);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Spellbreaking", ENCHANT_OPTION_MAIN_HAND, ENCHANT_WEAPON_SPELLBREAKING);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Spellshattering", ENCHANT_OPTION_MAIN_HAND, ENCHANT_WEAPON_SPELLSHATTERING);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Swordbreaking", ENCHANT_OPTION_MAIN_HAND, ENCHANT_WEAPON_SWORDBREAKING);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Swordshattering", ENCHANT_OPTION_MAIN_HAND, ENCHANT_WEAPON_SWORDSHATTERING);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Nerubian Carapace", ENCHANT_OPTION_MAIN_HAND, ENCHANT_WEAPON_NERUBIAN_CARAPACE);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Stoneskin Gargoyle", ENCHANT_OPTION_MAIN_HAND, ENCHANT_WEAPON_STONESKIN_GARGOYLE);
            }

            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Back", GOSSIP_SENDER_MAIN, MALL_MENU_ENCHANTS);
            player->SEND_GOSSIP_MENU(1, creature->GetGUID());
            break;
        }
        case ENCHANT_OPTION_OFF_HAND:
        {
            Item* pItem = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND);
            if (!pItem)
            {
                handler->PSendSysMessage("You have no item equipped in your off hand slot");
                player->CLOSE_GOSSIP_MENU();
                return false;
            }

            const ItemTemplate* pItemTemplate = pItem->GetTemplate();
            if (!pItemTemplate)
            {
                handler->PSendSysMessage("Unable to get template data for the item in your off hand slot");
                player->CLOSE_GOSSIP_MENU();
                return false;
            }

            if (pItemTemplate->InventoryType == INVTYPE_2HWEAPON)
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "+110 Attack Power", ENCHANT_OPTION_MAIN_HAND, ENCHANT_2H_WEAPON_MASSACRE);

            if (pItemTemplate->SubClass == ITEM_SUBCLASS_WEAPON_STAFF)
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "+81 Spell Power", ENCHANT_OPTION_MAIN_HAND, ENCHANT_STAFF_GREATER_SPELLPOWER);

            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Berserking", ENCHANT_OPTION_OFF_HAND, ENCHANT_WEAPON_BERSERKING);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Black Magic", ENCHANT_OPTION_OFF_HAND, ENCHANT_WEAPON_BLACK_MAGIC);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Blood Draining", ENCHANT_OPTION_OFF_HAND, ENCHANT_WEAPON_BLOOD_DRAINING);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Blade Warding", ENCHANT_OPTION_OFF_HAND, ENCHANT_WEAPON_BLADE_WARDING);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Titanium Weapon Chain", ENCHANT_OPTION_OFF_HAND, ENCHANT_WEAPON_TITANIUM_WEAPON_CHAIN);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "+65 Attack Power", ENCHANT_OPTION_OFF_HAND, ENCHANT_WEAPON_SUPERIOR_POTENCY);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "+63 Spell Power", ENCHANT_OPTION_OFF_HAND, ENCHANT_WEAPON_MIGHTY_SPELLPOWER);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "+26 Agility", ENCHANT_OPTION_OFF_HAND, ENCHANT_WEAPON_EXCEPTIONAL_AGILITY);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "+45 Spirit", ENCHANT_OPTION_OFF_HAND, ENCHANT_WEAPON_EXCEPTIONAL_SPIRIT);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "+50 Stamina", ENCHANT_OPTION_OFF_HAND, ENCHANT_WEAPON_TITANGUARD);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "+25 Hit Rating & +25 Critical Strike", ENCHANT_OPTION_OFF_HAND, ENCHANT_WEAPON_ACCURACY);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Mongoose", ENCHANT_OPTION_OFF_HAND, ENCHANT_WEAPON_MONGOOSE);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Executioner", ENCHANT_OPTION_OFF_HAND, ENCHANT_WEAPON_EXECUTIONER);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Deathfrost", ENCHANT_OPTION_OFF_HAND, ENCHANT_WEAPON_DEATHFROST);

            if (player->getClass() == CLASS_DEATH_KNIGHT)
            {
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Fallen Crusader", ENCHANT_OPTION_OFF_HAND, ENCHANT_WEAPON_FALLEN_CRUSADER);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Cinderglacier", ENCHANT_OPTION_OFF_HAND, ENCHANT_WEAPON_CINDERGLACIER);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Razorice", ENCHANT_OPTION_OFF_HAND, ENCHANT_WEAPON_RAZORICE);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Lichbane", ENCHANT_OPTION_OFF_HAND, ENCHANT_WEAPON_LICHBANE);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Spellbreaking", ENCHANT_OPTION_OFF_HAND, ENCHANT_WEAPON_SPELLBREAKING);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Spellshattering", ENCHANT_OPTION_OFF_HAND, ENCHANT_WEAPON_SPELLSHATTERING);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Swordbreaking", ENCHANT_OPTION_OFF_HAND, ENCHANT_WEAPON_SWORDBREAKING);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Swordshattering", ENCHANT_OPTION_OFF_HAND, ENCHANT_WEAPON_SWORDSHATTERING);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Nerubian Carapace", ENCHANT_OPTION_OFF_HAND, ENCHANT_WEAPON_NERUBIAN_CARAPACE);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Stoneskin Gargoyle", ENCHANT_OPTION_OFF_HAND, ENCHANT_WEAPON_STONESKIN_GARGOYLE);
            }

            if (pItemTemplate->InventoryType == INVTYPE_SHIELD)
            {
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Titanium Plating", ENCHANT_OPTION_OFF_HAND, ENCHANT_SHIELD_TITANIUM_PLATING);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "+25 Intellect", ENCHANT_OPTION_OFF_HAND, ENCHANT_SHIELD_GREATER_INTELLECT);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "+12 Resilience", ENCHANT_OPTION_OFF_HAND, ENCHANT_SHIELD_RESILIENCE);
            }

            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Back", GOSSIP_SENDER_MAIN, MALL_MENU_ENCHANTS);
            player->SEND_GOSSIP_MENU(1, creature->GetGUID());
            break;
        }
        case ENCHANT_OPTION_RANGED:
        {
            Item* pItem = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_RANGED);
            if (!pItem)
            {
                handler->PSendSysMessage("You have no item equipped in your ranged slot");
                player->CLOSE_GOSSIP_MENU();
                return false;
            }

            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "+40 Ranged Critical Strike", ENCHANT_OPTION_RANGED, ENCHANT_RANGED_HEARTSEEKER_SCOPE);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "+40 Ranged Haste", ENCHANT_OPTION_RANGED, ENCHANT_RANGED_SUN_SCOPE);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "+15 Ranged Weapon Damage", ENCHANT_OPTION_RANGED, ENCHANT_RANGED_DIAMOND_CUT_REFRACTOR_SCOPE);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Back", GOSSIP_SENDER_MAIN, MALL_MENU_ENCHANTS);
            player->SEND_GOSSIP_MENU(1, creature->GetGUID());
            break;
        }
    }
    return true;
}

bool MallMgr::HandleGems(Player* player, Creature* creature, uint32 action)
{
    switch (action)
    {
        case MALL_MENU_GEMS:
        {
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Meta Gems", MALL_MENU_GEMS, GEM_OPTION_META);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Colored Gems", MALL_MENU_GEMS, GEM_OPTION_COLORED);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Dragon's Eye Gems", MALL_MENU_GEMS, GEM_OPTION_DRAGONS_EYE);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Back", GOSSIP_SENDER_MAIN, GOSSIP_SENDER_MAIN);
            player->SEND_GOSSIP_MENU(1, creature->GetGUID());
            break;
        }
        case GEM_OPTION_META:
        {
            ShowInventory(player, creature, INVENTORY_LIST_META_GEMS);
            break;
        }
        case GEM_OPTION_COLORED:
        {
            ShowInventory(player, creature, INVENTORY_LIST_COLORED_GEMS);
            break;
        }
        case GEM_OPTION_DRAGONS_EYE:
        {
            ShowInventory(player, creature, INVENTORY_LIST_DRAGONS_EYE_GEMS);
            break;
        }
    }

    return true;
}

bool MallMgr::HandleResetTalents(Player* player, Creature* creature)
{
    player->SendTalentWipeConfirm(creature->GetGUID());
    player->CLOSE_GOSSIP_MENU();
    return true;
}

bool MallMgr::HandleLearnDualSpecialization(Player* player, Creature* creature)
{
    player->SetSaveTimer(sWorld->getIntConfig(CONFIG_INTERVAL_SAVE));
    player->learnSpell(63644, false);
    player->learnSpell(63645, false);
    player->UpdateSpecCount(2);
    player->SaveToDB();
    player->CLOSE_GOSSIP_MENU();
    return true;
}

bool MallMgr::HandleSetupShadowDanceBar(Player* player, Creature* creature)
{
    if (player->HasSpell(51713))
    {
        player->InterruptMovement();
        player->GetMotionMaster()->MoveFall();
        player->SetControlled(true, UNIT_STATE_ROOT);
        player->AddAura(SPELL_SERVERSIDE_SILENCE, player);
        if (!player->HasAura(51713))
            player->AddAura(51713, player);
        if (Aura* ShadowDance = player->GetAura(51713, player->GetGUID()))
            ShadowDance->SetDurationAndMaxDuration(-1);
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "|TInterface\\icons\\achievement_reputation_01:30|t I'm Finished", GOSSIP_SENDER_MAIN, MALL_MENU_FINISH_SHADOW_DANCE);
        player->SEND_GOSSIP_MENU(1, creature->GetGUID());
    }
    else
        player->CLOSE_GOSSIP_MENU();
    return true;
}

bool MallMgr::HandleFinishShadowDanceBar(Player* player, Creature* creature)
{
    player->SetControlled(false, UNIT_STATE_ROOT);
    player->RemoveAura(SPELL_SERVERSIDE_SILENCE);
    player->RemoveAura(51713);
    OnGossipHello(player, creature);
    return true;
}

bool MallMgr::ShowInventory(Player* player, Creature* creature, uint32 action)
{
    ChatHandler* handler = new ChatHandler(player);
    const VendorItemData* items = creature->GetVendorItems();
    if (!items)
    {
        handler->PSendSysMessage("Unable to find item data");
        player->CLOSE_GOSSIP_MENU();
        return false;
    }

    player->CLOSE_GOSSIP_MENU();

    uint16 itemCount = items->GetItemCount();
    uint8 count = 0;

    WorldPacket data(SMSG_LIST_INVENTORY, 8 + 1 + itemCount * 8 * 4);
    data << uint64(creature->GetGUID());
    size_t countPos = data.wpos();
    data << uint8(count);

    for (uint16 slot = 0; slot < itemCount; ++slot)
    {
        if (const VendorItem* vItem = items->GetItem(slot))
        {
            if (const ItemTemplate* vItemTemplate = sObjectMgr->GetItemTemplate(vItem->item))
            {
                if (!CheckVendorItem(player, vItemTemplate, action))
                    continue;

                ++count;
                data << uint32(count + 1);                      // Client expects counting to start at 1
                data << uint32(vItem->item);                    // Entry
                data << uint32(vItemTemplate->DisplayInfoID);   // DisplayId
                data << int32(0xFFFFFFFF);                      // Left in stock
                data << uint32(vItemTemplate->BuyPrice);        // Price
                data << uint32(vItemTemplate->MaxDurability);   // Durability
                data << uint32(vItemTemplate->BuyCount);        // Buy Count
                data << uint32(vItem->ExtendedCost);            // Extended Cost
            }
        }
    }

    if (!count)
    {
        handler->PSendSysMessage("Unable to find item data");
        player->CLOSE_GOSSIP_MENU();
        return false;
    }

    data.put<uint8>(countPos, count);
    player->GetSession()->SendPacket(&data);
    return true;
}

bool MallMgr::EnchantItem(Player* player, Creature* creature, uint16 enchantId, uint8 enchantOption)
{
    ChatHandler* handler = new ChatHandler(player);
    uint8 slot = GetItemSlotByEnchantOption(enchantOption);
    if (slot > EQUIPMENT_SLOT_RANGED)
    {
        handler->PSendSysMessage("Unable to find item slot based on enchant option: %u", enchantOption);
        player->CLOSE_GOSSIP_MENU();
        return false;
    }

    Item* pItem = player->GetItemByPos(INVENTORY_SLOT_BAG_0, slot);
    if (!pItem)
    {
        handler->PSendSysMessage("You have no item equipped in your %s slot", SlotToSlotString(slot));
        player->CLOSE_GOSSIP_MENU();
        return false;
    }

    const ItemTemplate* pItemTemplate = pItem->GetTemplate();
    if (!pItemTemplate)
    {
        handler->PSendSysMessage("Unable to get template data for the item in your %s slot", SlotToSlotString(slot));
        player->CLOSE_GOSSIP_MENU();
        return false;
    }

    const SpellItemEnchantmentEntry* enchantEntry = sSpellItemEnchantmentStore.LookupEntry(enchantId);
    if (!enchantEntry)
    {
        handler->PSendSysMessage("Unable to get data for enchant: %u", enchantId);
        player->CLOSE_GOSSIP_MENU();
        return false;
    }

    if (!CheckEnchantItem(player, pItemTemplate, enchantId, slot))
    {
        player->CLOSE_GOSSIP_MENU();
        return false;
    }

    switch (enchantId)
    {
        case ENCHANT_BELT_ETERNAL_BELT_BUCKLE:
        case ENCHANT_GLOVES_SOCKET:
        case ENCHANT_BRACER_SOCKET:
        {
            bool addSocket = false;

            for (uint8 i = 0; i < MAX_ITEM_ENCHANTMENT_EFFECTS; ++i)
                if (enchantEntry->type[i] == ITEM_ENCHANTMENT_TYPE_PRISMATIC_SOCKET)
                {
                    addSocket = true;
                    break;
                }

            if (!addSocket)
            {
                handler->PSendSysMessage("Unable to add socket to %s because enchant: %u doesn't have enchant entry type: ITEM_ENCHANTMENT_TYPE_PRISMATIC_SOCKET",
                pItemTemplate->Name1.c_str(), enchantId);
                player->CLOSE_GOSSIP_MENU();
                return false;
            }

            player->ApplyEnchantment(pItem, PRISMATIC_ENCHANTMENT_SLOT, false);
            pItem->SetEnchantment(PRISMATIC_ENCHANTMENT_SLOT, enchantId, 0, 0);
            player->ApplyEnchantment(pItem, PRISMATIC_ENCHANTMENT_SLOT, true);
            pItem->ClearSoulboundTradeable(player);
            break;
        }
        default:
        {
            player->ApplyEnchantment(pItem, PERM_ENCHANTMENT_SLOT, false);
            pItem->SetEnchantment(PERM_ENCHANTMENT_SLOT, enchantId, 0, 0);
            player->ApplyEnchantment(pItem, PERM_ENCHANTMENT_SLOT, true);
            pItem->ClearSoulboundTradeable(player);
            break;
        }
    }

    player->CastSpell(player, 61335); // Disenchant Visual
    player->PlayerTalkClass->ClearMenus();
    HandleEnchants(player, creature, MALL_MENU_ENCHANTS);
    return true;
}

bool MallMgr::LearnSkill(Player* player, Creature* creature, uint16 skill)
{
    ChatHandler* handler = new ChatHandler(player);

    if (player->GetSkillValue(skill) == 450)
    {
        handler->PSendSysMessage("You already have that profession");
        player->CLOSE_GOSSIP_MENU();
        return false;
    }

    if (!CheckSkill(player, skill))
    {
        player->CLOSE_GOSSIP_MENU();
        return false;
    }

    const SkillLineEntry* skillLineEntry = sSkillLineStore.LookupEntry(skill);
    if (!skillLineEntry)
    {
        handler->PSendSysMessage("Unable to get skill line entry for profession: %s", SkillToSkillString(skill));
        player->CLOSE_GOSSIP_MENU();
        return false;
    }

    uint32 professionSpellId = 0;
    switch (skill)
    {
        case SKILL_ALCHEMY:        professionSpellId = 65281; break;
        case SKILL_BLACKSMITHING:  professionSpellId = 65282; break;
        case SKILL_ENCHANTING:     professionSpellId = 51312; break;
        case SKILL_ENGINEERING:    professionSpellId = 61464; break;
        case SKILL_HERBALISM:      professionSpellId = 65288; break;
        case SKILL_INSCRIPTION:    professionSpellId = 65287; break;
        case SKILL_JEWELCRAFTING:  professionSpellId = 65286; break;
        case SKILL_LEATHERWORKING: professionSpellId = 65284; break;
        case SKILL_TAILORING:      professionSpellId = 65283; break;
    }

    if (!professionSpellId)
    {
        handler->PSendSysMessage("Unable to get spell for profession: %s", SkillToSkillString(skill));
        player->CLOSE_GOSSIP_MENU();
        return false;
    }

    player->SetSkill(skill, 6, 450, 450);
    player->learnSpell(professionSpellId, false);
    player->CLOSE_GOSSIP_MENU();
    return true;
}

bool MallMgr::CheckVendorItem(Player* player, const ItemTemplate* vItemTemplate, uint32 action)
{
    // Don't allow Nibelung to be purchased until the proc is fixed
    if (IsPhraseInString(vItemTemplate->Name1, "Nibelung"))
        return false;

    // Faction specific items
    if ((vItemTemplate->Flags2 == ITEM_FLAGS_EXTRA_ALLIANCE_ONLY && player->GetTeam() == HORDE) ||
        (vItemTemplate->Flags2 == ITEM_FLAGS_EXTRA_HORDE_ONLY && player->GetTeam() == ALLIANCE))
        return false;

    // Race specific items
    if (!(vItemTemplate->AllowableRace & player->getRaceMask()))
        return false;

    // Class specific items
    if (!(vItemTemplate->AllowableClass & player->getClassMask()))
        return false;

    switch (action)
    {
        case INVENTORY_LIST_GENERAL_GOODS:
        {
            if (vItemTemplate->Class != ITEM_CLASS_CONSUMABLE &&
                vItemTemplate->Class != ITEM_CLASS_CONTAINER &&
                vItemTemplate->Class != ITEM_CLASS_REAGENT &&
                vItemTemplate->Class != ITEM_CLASS_PROJECTILE &&
                vItemTemplate->Class != ITEM_CLASS_TRADE_GOODS &&
                vItemTemplate->Class != ITEM_CLASS_GENERIC &&
                vItemTemplate->Class != ITEM_CLASS_MISC)
                return false;

            if (vItemTemplate->Class == ITEM_CLASS_MISC && vItemTemplate->SubClass == ITEM_SUBCLASS_JUNK_MOUNT)
                return false;

            break;
        }
        case INVENTORY_LIST_META_GEMS:
        {
            if (vItemTemplate->Class != ITEM_CLASS_GEM)
                return false;

            if (vItemTemplate->SubClass != ITEM_SUBCLASS_GEM_META)
                return false;

            break;
        }
        case INVENTORY_LIST_COLORED_GEMS:
        {
            if (vItemTemplate->Class != ITEM_CLASS_GEM)
                return false;

            if (IsPhraseInString(vItemTemplate->Name1, "Dragon's Eye"))
                return false;

            if (vItemTemplate->SubClass != ITEM_SUBCLASS_GEM_RED &&
                vItemTemplate->SubClass != ITEM_SUBCLASS_GEM_YELLOW &&
                vItemTemplate->SubClass != ITEM_SUBCLASS_GEM_BLUE &&
                vItemTemplate->SubClass != ITEM_SUBCLASS_GEM_ORANGE &&
                vItemTemplate->SubClass != ITEM_SUBCLASS_GEM_GREEN &&
                vItemTemplate->SubClass != ITEM_SUBCLASS_GEM_PURPLE &&
                vItemTemplate->SubClass != ITEM_SUBCLASS_GEM_PRISMATIC)
                return false;

            break;
        }
        case INVENTORY_LIST_DRAGONS_EYE_GEMS:
        {
            if (player->GetSkillValue(SKILL_JEWELCRAFTING) < 450)
                return false;

            if (vItemTemplate->Class != ITEM_CLASS_GEM)
                return false;

            if (!IsPhraseInString(vItemTemplate->Name1, "Dragon's Eye"))
                return false;

            break;
        }

        case INVENTORY_LIST_MOUNTS:
        {
            if (vItemTemplate->Class != ITEM_CLASS_MISC)
                return false;

            if (vItemTemplate->SubClass != ITEM_SUBCLASS_JUNK_MOUNT)
                return false;

            break;
        }
        case INVENTORY_LIST_GLYPHS:
        {
            if (vItemTemplate->Class != ITEM_CLASS_GLYPH)
                return false;

            break;
        }
        case INVENTORY_LIST_RELENTLESS_GLADIATOR_MAINSETS_AND_OFFSETS:
        {
            if (!IsPhraseInString(vItemTemplate->Name1, "Relentless") && !IsPhraseInString(vItemTemplate->Name1, "Titan-Forged"))
                return false;

            if (vItemTemplate->Class != ITEM_CLASS_ARMOR)
                return false;

            if (vItemTemplate->SubClass != GetUsableArmorProficiencyByClass(player->getClass()))
                return false;

            if (vItemTemplate->InventoryType != INVTYPE_HEAD &&
                vItemTemplate->InventoryType != INVTYPE_SHOULDERS &&
                vItemTemplate->InventoryType != INVTYPE_CHEST &&
                vItemTemplate->InventoryType != INVTYPE_HANDS &&
                vItemTemplate->InventoryType != INVTYPE_LEGS &&
                vItemTemplate->InventoryType != INVTYPE_WRISTS &&
                vItemTemplate->InventoryType != INVTYPE_WAIST &&
                vItemTemplate->InventoryType != INVTYPE_FEET)
                return false;

            break;
        }
        case INVENTORY_LIST_RELENTLESS_GLADIATOR_ACCESSORIES:
        {
            if (!IsPhraseInString(vItemTemplate->Name1, "Relentless") && !IsPhraseInString(vItemTemplate->Name1, "Titan-Forged"))
                return false;

            if (vItemTemplate->InventoryType != INVTYPE_NECK &&
                vItemTemplate->InventoryType != INVTYPE_CLOAK &&
                vItemTemplate->InventoryType != INVTYPE_FINGER)
                return false;

            break;
        }
        case INVENTORY_LIST_RELENTLESS_GLADIATOR_WEAPONS:
        {
            if (!IsPhraseInString(vItemTemplate->Name1, "Relentless"))
                return false;

            if (vItemTemplate->InventoryType != INVTYPE_WEAPON &&
                vItemTemplate->InventoryType != INVTYPE_SHIELD &&
                vItemTemplate->InventoryType != INVTYPE_RANGED &&
                vItemTemplate->InventoryType != INVTYPE_2HWEAPON &&
                vItemTemplate->InventoryType != INVTYPE_WEAPONMAINHAND &&
                vItemTemplate->InventoryType != INVTYPE_WEAPONOFFHAND &&
                vItemTemplate->InventoryType != INVTYPE_HOLDABLE &&
                vItemTemplate->InventoryType != INVTYPE_THROWN &&
                vItemTemplate->InventoryType != INVTYPE_RANGEDRIGHT &&
                vItemTemplate->InventoryType != INVTYPE_RELIC)
                return false;

            break;
        }
        case INVENTORY_LIST_TRIAL_OF_THE_CRUSADER_MAINSETS_AND_OFFSETS:
        {
            if (IsPhraseInString(vItemTemplate->Name1, "Relentless") || vItemTemplate->ItemLevel != 245)
                return false;

            if (vItemTemplate->Class != ITEM_CLASS_ARMOR)
                return false;

            if (vItemTemplate->SubClass != GetUsableArmorProficiencyByClass(player->getClass()))
                return false;

            if (vItemTemplate->InventoryType != INVTYPE_HEAD &&
                vItemTemplate->InventoryType != INVTYPE_SHOULDERS &&
                vItemTemplate->InventoryType != INVTYPE_CHEST &&
                vItemTemplate->InventoryType != INVTYPE_HANDS &&
                vItemTemplate->InventoryType != INVTYPE_LEGS &&
                vItemTemplate->InventoryType != INVTYPE_WRISTS &&
                vItemTemplate->InventoryType != INVTYPE_WAIST &&
                vItemTemplate->InventoryType != INVTYPE_FEET)
                return false;

            break;
        }
        case INVENTORY_LIST_TRIAL_OF_THE_CRUSADER_ACCESSORIES:
        {
            if (IsPhraseInString(vItemTemplate->Name1, "Relentless") || IsPhraseInString(vItemTemplate->Name1, "Titan-Forged") || vItemTemplate->ItemLevel != 245)
                return false;

            if (vItemTemplate->InventoryType != INVTYPE_NECK &&
                vItemTemplate->InventoryType != INVTYPE_CLOAK &&
                vItemTemplate->InventoryType != INVTYPE_FINGER)
                return false;

            break;
        }
        case INVENTORY_LIST_TRIAL_OF_THE_CRUSADER_WEAPONS:
        {
            if (IsPhraseInString(vItemTemplate->Name1, "Relentless") ||
                (vItemTemplate->ItemLevel != 226 && vItemTemplate->ItemLevel != 232 &&
                vItemTemplate->ItemLevel != 245 && vItemTemplate->ItemLevel != 258))
                return false;

            if (vItemTemplate->InventoryType != INVTYPE_WEAPON &&
                vItemTemplate->InventoryType != INVTYPE_SHIELD &&
                vItemTemplate->InventoryType != INVTYPE_RANGED &&
                vItemTemplate->InventoryType != INVTYPE_2HWEAPON &&
                vItemTemplate->InventoryType != INVTYPE_WEAPONMAINHAND &&
                vItemTemplate->InventoryType != INVTYPE_WEAPONOFFHAND &&
                vItemTemplate->InventoryType != INVTYPE_HOLDABLE &&
                vItemTemplate->InventoryType != INVTYPE_THROWN &&
                vItemTemplate->InventoryType != INVTYPE_RANGEDRIGHT &&
                vItemTemplate->InventoryType != INVTYPE_RELIC)
                return false;

            break;
        }
        case INVENTORY_LIST_245_TRINKETS:
        {
            if (vItemTemplate->InventoryType != INVTYPE_TRINKET || vItemTemplate->ItemLevel != 245)
                return false;

            break;
        }
        case INVENTORY_LIST_WRATHFUL_GLADIATOR_MAINSETS_AND_OFFSETS:
        {
            if (!IsPhraseInString(vItemTemplate->Name1, "Wrathful"))
                return false;

            if (vItemTemplate->Class != ITEM_CLASS_ARMOR)
                return false;

            if (vItemTemplate->SubClass != GetUsableArmorProficiencyByClass(player->getClass()))
                return false;

            if (vItemTemplate->InventoryType != INVTYPE_HEAD &&
                vItemTemplate->InventoryType != INVTYPE_SHOULDERS &&
                vItemTemplate->InventoryType != INVTYPE_CHEST &&
                vItemTemplate->InventoryType != INVTYPE_HANDS &&
                vItemTemplate->InventoryType != INVTYPE_LEGS &&
                vItemTemplate->InventoryType != INVTYPE_WRISTS &&
                vItemTemplate->InventoryType != INVTYPE_WAIST &&
                vItemTemplate->InventoryType != INVTYPE_FEET)
                return false;

            break;
        }
        case INVENTORY_LIST_WRATHFUL_GLADIATOR_ACCESSORIES:
        {
            if (!IsPhraseInString(vItemTemplate->Name1, "Wrathful"))
                return false;

            if (vItemTemplate->InventoryType != INVTYPE_NECK &&
                vItemTemplate->InventoryType != INVTYPE_CLOAK &&
                vItemTemplate->InventoryType != INVTYPE_FINGER)
                return false;

            break;
        }
        case INVENTORY_LIST_WRATHFUL_GLADIATOR_WEAPONS:
        {
            if (!IsPhraseInString(vItemTemplate->Name1, "Wrathful"))
                return false;

            if (vItemTemplate->InventoryType != INVTYPE_WEAPON &&
                vItemTemplate->InventoryType != INVTYPE_SHIELD &&
                vItemTemplate->InventoryType != INVTYPE_RANGED &&
                vItemTemplate->InventoryType != INVTYPE_2HWEAPON &&
                vItemTemplate->InventoryType != INVTYPE_WEAPONMAINHAND &&
                vItemTemplate->InventoryType != INVTYPE_WEAPONOFFHAND &&
                vItemTemplate->InventoryType != INVTYPE_HOLDABLE &&
                vItemTemplate->InventoryType != INVTYPE_THROWN &&
                vItemTemplate->InventoryType != INVTYPE_RANGEDRIGHT &&
                vItemTemplate->InventoryType != INVTYPE_RELIC)
                return false;

            break;
        }
        case INVENTORY_LIST_ICECROWN_CITADEL_MAINSETS_AND_OFFSETS:
        {
            if (IsPhraseInString(vItemTemplate->Name1, "Wrathful") || vItemTemplate->ItemLevel != 264)
                return false;

            if (vItemTemplate->Class != ITEM_CLASS_ARMOR)
                return false;

            if (vItemTemplate->SubClass != GetUsableArmorProficiencyByClass(player->getClass()))
                return false;

            if (vItemTemplate->InventoryType != INVTYPE_HEAD &&
                vItemTemplate->InventoryType != INVTYPE_SHOULDERS &&
                vItemTemplate->InventoryType != INVTYPE_CHEST &&
                vItemTemplate->InventoryType != INVTYPE_HANDS &&
                vItemTemplate->InventoryType != INVTYPE_LEGS &&
                vItemTemplate->InventoryType != INVTYPE_WRISTS &&
                vItemTemplate->InventoryType != INVTYPE_WAIST &&
                vItemTemplate->InventoryType != INVTYPE_FEET)
                return false;

            break;
        }
        case INVENTORY_LIST_ICECROWN_CITADEL_ACCESSORIES:
        {
            if (IsPhraseInString(vItemTemplate->Name1, "Wrathful") || (vItemTemplate->ItemLevel != 264 && vItemTemplate->ItemLevel != 268))
                return false;

            if (vItemTemplate->InventoryType != INVTYPE_NECK &&
                vItemTemplate->InventoryType != INVTYPE_CLOAK &&
                vItemTemplate->InventoryType != INVTYPE_FINGER)
                return false;

            break;
        }
        case INVENTORY_LIST_ICECROWN_CITADEL_WEAPONS:
        {
            if (IsPhraseInString(vItemTemplate->Name1, "Wrathful") || (vItemTemplate->ItemLevel != 264 && vItemTemplate->ItemLevel != 277))
                return false;

            if (vItemTemplate->InventoryType != INVTYPE_WEAPON &&
                vItemTemplate->InventoryType != INVTYPE_SHIELD &&
                vItemTemplate->InventoryType != INVTYPE_RANGED &&
                vItemTemplate->InventoryType != INVTYPE_2HWEAPON &&
                vItemTemplate->InventoryType != INVTYPE_WEAPONMAINHAND &&
                vItemTemplate->InventoryType != INVTYPE_WEAPONOFFHAND &&
                vItemTemplate->InventoryType != INVTYPE_HOLDABLE &&
                vItemTemplate->InventoryType != INVTYPE_THROWN &&
                vItemTemplate->InventoryType != INVTYPE_RANGEDRIGHT &&
                vItemTemplate->InventoryType != INVTYPE_RELIC)
                return false;

            break;
        }
        case INVENTORY_LIST_264_TRINKETS:
        {
            if (vItemTemplate->InventoryType != INVTYPE_TRINKET || vItemTemplate->ItemLevel != 264)
                return false;

            break;
        }
        case INVENTORY_LIST_APPAREL:
        {
            if (vItemTemplate->InventoryType != INVTYPE_SHIRT && vItemTemplate->InventoryType != INVTYPE_TABARD)
                return false;

            break;
        }
    }

    return true;
}

bool MallMgr::CheckSkill(Player* player, uint16 skill)
{
    uint8 skillCount = 0;

    if (player->HasSkill(SKILL_ALCHEMY))
        skillCount++;

    if (player->HasSkill(SKILL_BLACKSMITHING))
        skillCount++;

    if (player->HasSkill(SKILL_ENCHANTING))
        skillCount++;

    if (player->HasSkill(SKILL_ENGINEERING))
        skillCount++;

    if (player->HasSkill(SKILL_HERBALISM))
        skillCount++;

    if (player->HasSkill(SKILL_INSCRIPTION))
        skillCount++;

    if (player->HasSkill(SKILL_JEWELCRAFTING))
        skillCount++;

    if (player->HasSkill(SKILL_LEATHERWORKING))
        skillCount++;

    if (player->HasSkill(SKILL_TAILORING))
        skillCount++;

    if (skillCount > 1)
        return false;

    if (skill != SKILL_ALCHEMY &&
        skill != SKILL_BLACKSMITHING &&
        skill != SKILL_ENCHANTING &&
        skill != SKILL_ENGINEERING &&
        skill != SKILL_HERBALISM &&
        skill != SKILL_INSCRIPTION &&
        skill != SKILL_JEWELCRAFTING &&
        skill != SKILL_LEATHERWORKING &&
        skill != SKILL_TAILORING)
        return false;

    return true;
}

bool MallMgr::CheckEnchantItem(Player* player, const ItemTemplate* pItemTemplate, uint16 enchantId, uint8 slot)
{
    switch (enchantId)
    {
        case ENCHANT_HEAD_ARCANUM_OF_TRIUMPH:
        case ENCHANT_HEAD_ARCANUM_OF_DOMINANCE:
        case ENCHANT_HEAD_ARCANUM_OF_TORMENT:
        case ENCHANT_HEAD_ARCANUM_OF_BURNING_MYSTERIES:
        case ENCHANT_HEAD_ARCANUM_OF_BLISSFUL_MENDING:
        case ENCHANT_HEAD_ARCANUM_OF_THE_STALWART_PROTECTOR:
        case ENCHANT_HEAD_MIND_AMPLIFICATION_DISH:
        {
            if (pItemTemplate->Class != ITEM_CLASS_ARMOR)
                return false;

            if (pItemTemplate->SubClass != ITEM_SUBCLASS_ARMOR_CLOTH &&
                pItemTemplate->SubClass != ITEM_SUBCLASS_ARMOR_LEATHER &&
                pItemTemplate->SubClass != ITEM_SUBCLASS_ARMOR_MAIL &&
                pItemTemplate->SubClass != ITEM_SUBCLASS_ARMOR_PLATE)
                return false;

            if (pItemTemplate->InventoryType != INVTYPE_HEAD)
                return false;

            break;
        }
        case ENCHANT_SHOULDER_INSCRIPTION_OF_TRIUMPH:
        case ENCHANT_SHOULDER_INSCRIPTION_OF_DOMINANCE:
        case ENCHANT_SHOULDER_GREATER_INSCRIPTION_OF_THE_AXE:
        case ENCHANT_SHOULDER_GREATER_INSCRIPTION_OF_THE_STORM:
        case ENCHANT_SHOULDER_GREATER_INSCRIPTION_OF_THE_CRAG:
        case ENCHANT_SHOULDER_GREATER_INSCRIPTION_OF_THE_PINNACLE:
        case ENCHANT_SHOULDERS_MASTERS_INSCRIPTION_OF_THE_AXE:
        case ENCHANT_SHOULDERS_MASTERS_INSCRIPTION_OF_THE_STORM:
        case ENCHANT_SHOULDERS_MASTERS_INSCRIPTION_OF_THE_CRAG:
        case ENCHANT_SHOULDERS_MASTERS_INSCRIPTION_OF_THE_PINNACLE:
        {
            if (pItemTemplate->Class != ITEM_CLASS_ARMOR)
                return false;

            if (pItemTemplate->SubClass != ITEM_SUBCLASS_ARMOR_CLOTH &&
                pItemTemplate->SubClass != ITEM_SUBCLASS_ARMOR_LEATHER &&
                pItemTemplate->SubClass != ITEM_SUBCLASS_ARMOR_MAIL &&
                pItemTemplate->SubClass != ITEM_SUBCLASS_ARMOR_PLATE)
                return false;

            if (pItemTemplate->InventoryType != INVTYPE_SHOULDERS)
                return false;

            break;
        }
        case ENCHANT_CHEST_EXCEPTIONAL_RESILIENCE:
        case ENCHANT_CHEST_POWERFUL_STATS:
        case ENCHANT_CHEST_SUPER_HEALTH:
        {
            if (pItemTemplate->Class != ITEM_CLASS_ARMOR)
                return false;

            if (pItemTemplate->SubClass != ITEM_SUBCLASS_ARMOR_CLOTH &&
                pItemTemplate->SubClass != ITEM_SUBCLASS_ARMOR_LEATHER &&
                pItemTemplate->SubClass != ITEM_SUBCLASS_ARMOR_MAIL &&
                pItemTemplate->SubClass != ITEM_SUBCLASS_ARMOR_PLATE)
                return false;

            if (pItemTemplate->InventoryType != INVTYPE_CHEST)
                return false;

            break;
        }
        case ENCHANT_GLOVES_CRUSHER:
        case ENCHANT_GLOVES_EXCEPTIONAL_SPELLPOWER:
        case ENCHANT_GLOVES_MAJOR_AGILITY:
        case ENCHANT_GLOVES_PERCISION:
        case ENCHANT_GLOVES_SOCKET:
        case ENCHANT_GLOVES_HAND_MOUNTED_PRYO_ROCKET:
        case ENCHANT_GLOVES_HYPERSPEED_ACCELERATORS:
        {
            if (pItemTemplate->Class != ITEM_CLASS_ARMOR)
                return false;

            if (pItemTemplate->SubClass != ITEM_SUBCLASS_ARMOR_CLOTH &&
                pItemTemplate->SubClass != ITEM_SUBCLASS_ARMOR_LEATHER &&
                pItemTemplate->SubClass != ITEM_SUBCLASS_ARMOR_MAIL &&
                pItemTemplate->SubClass != ITEM_SUBCLASS_ARMOR_PLATE)
                return false;

            if (pItemTemplate->InventoryType != INVTYPE_HANDS)
                return false;

            break;
        }
        case ENCHANT_LEGS_ICESCALE_LEG_ARMOR:
        case ENCHANT_LEGS_SAPPHIRE_SPELLTHREAD:
        case ENCHANT_LEGS_BRILLIANT_SPELLTHREAD:
        case ENCHANT_LEGS_FROSTHIDE_LEG_ARMOR:
        case ENCHANT_LEGS_EARTHEN_LEG_ARMOR:
        {
            if (pItemTemplate->Class != ITEM_CLASS_ARMOR)
                return false;

            if (pItemTemplate->SubClass != ITEM_SUBCLASS_ARMOR_CLOTH &&
                pItemTemplate->SubClass != ITEM_SUBCLASS_ARMOR_LEATHER &&
                pItemTemplate->SubClass != ITEM_SUBCLASS_ARMOR_MAIL &&
                pItemTemplate->SubClass != ITEM_SUBCLASS_ARMOR_PLATE)
                return false;

            if (pItemTemplate->InventoryType != INVTYPE_LEGS)
                return false;

            break;
        }
        case ENCHANT_BRACERS_GREATER_ASSAULT:
        case ENCHANT_BRACERS_SUPERIOR_SPELLPOWER:
        case ENCHANT_BRACERS_EXCEPTIONAL_INTELLECT:
        case ENCHANT_BRACERS_MAJOR_SPIRIT:
        case ENCHANT_BRACERS_MAJOR_STAMINA:
        case ENCHANT_BRACER_SOCKET:
        case ENCHANT_BRACER_FUR_LINING_ATTACKPOWER:
        case ENCHANT_BRACER_FUR_LINING_SPELLPOWER:
        case ENCHANT_BRACER_FUR_LINING_AGILITY:
        case ENCHANT_BRACER_FUR_LINING_STAMINA:
        {
            if (pItemTemplate->Class != ITEM_CLASS_ARMOR)
                return false;

            if (pItemTemplate->SubClass != ITEM_SUBCLASS_ARMOR_CLOTH &&
                pItemTemplate->SubClass != ITEM_SUBCLASS_ARMOR_LEATHER &&
                pItemTemplate->SubClass != ITEM_SUBCLASS_ARMOR_MAIL &&
                pItemTemplate->SubClass != ITEM_SUBCLASS_ARMOR_PLATE)
                return false;

            if (pItemTemplate->InventoryType != INVTYPE_WRISTS)
                return false;

            break;
        }
        case ENCHANT_BELT_ETERNAL_BELT_BUCKLE:
        case ENCHANT_BELT_FRAG_BELT:
        {
            if (pItemTemplate->Class != ITEM_CLASS_ARMOR)
                return false;

            if (pItemTemplate->SubClass != ITEM_SUBCLASS_ARMOR_CLOTH &&
                pItemTemplate->SubClass != ITEM_SUBCLASS_ARMOR_LEATHER &&
                pItemTemplate->SubClass != ITEM_SUBCLASS_ARMOR_MAIL &&
                pItemTemplate->SubClass != ITEM_SUBCLASS_ARMOR_PLATE)
                return false;

            if (pItemTemplate->InventoryType != INVTYPE_WAIST)
                return false;

            break;
        }
        case ENCHANT_BOOTS_GREATER_ASSULT:
        case ENCHANT_BOOTS_SUPERIOR_AGILITY:
        case ENCHANT_BOOTS_ICEWALKER:
        case ENCHANT_BOOTS_TUSKARR_VITALITY:
        case ENCHANT_BOOTS_NITRO_BOOSTS:
        {
            if (pItemTemplate->Class != ITEM_CLASS_ARMOR)
                return false;

            if (pItemTemplate->SubClass != ITEM_SUBCLASS_ARMOR_CLOTH &&
                pItemTemplate->SubClass != ITEM_SUBCLASS_ARMOR_LEATHER &&
                pItemTemplate->SubClass != ITEM_SUBCLASS_ARMOR_MAIL &&
                pItemTemplate->SubClass != ITEM_SUBCLASS_ARMOR_PLATE)
                return false;

            if (pItemTemplate->InventoryType != INVTYPE_FEET)
                return false;

            break;
        }
        case ENCHANT_CLOAK_SPELL_PIERCING:
        case ENCHANT_CLOAK_MAJOR_AGILITY:
        case ENCHANT_CLOAK_GREATER_SPEED:
        case ENCHANT_CLOAK_SHADOW_ARMOR:
        case ENCHANT_CLOAK_FLEXWEAVE_UNDERLAY:
        case ENCHANT_CLOAK_SPRINGY_ARACHNOWEAVE:
        case ENCHANT_CLOAK_SWORDGUARD_EMBROIDERY:
        case ENCHANT_CLOAK_LIGHTWEAVE_EMBROIDERY:
        case ENCHANT_CLOAK_DARKGLOW_EMBROIDERY:
        {
            if (pItemTemplate->Class != ITEM_CLASS_ARMOR)
                return false;

            if (pItemTemplate->SubClass != ITEM_SUBCLASS_ARMOR_CLOTH)
                return false;

            if (pItemTemplate->InventoryType != INVTYPE_CLOAK)
                return false;

            break;
        }
        case ENCHANT_2H_WEAPON_MASSACRE:
        {
            if (pItemTemplate->Class != ITEM_CLASS_WEAPON)
                return false;

            if (pItemTemplate->SubClass != ITEM_SUBCLASS_WEAPON_AXE2 &&
                pItemTemplate->SubClass != ITEM_SUBCLASS_WEAPON_MACE2 &&
                pItemTemplate->SubClass != ITEM_SUBCLASS_WEAPON_SWORD2 &&
                pItemTemplate->SubClass != ITEM_SUBCLASS_WEAPON_POLEARM &&
                pItemTemplate->SubClass != ITEM_SUBCLASS_WEAPON_STAFF &&
                pItemTemplate->SubClass != ITEM_SUBCLASS_WEAPON_AXE2 &&
                pItemTemplate->SubClass != ITEM_SUBCLASS_WEAPON_AXE2 &&
                pItemTemplate->SubClass != ITEM_SUBCLASS_WEAPON_AXE2 &&
                pItemTemplate->SubClass != ITEM_SUBCLASS_WEAPON_AXE2)
                return false;

            if (pItemTemplate->InventoryType != INVTYPE_2HWEAPON)
                return false;

            break;
        }
        case ENCHANT_STAFF_GREATER_SPELLPOWER:
        {
            if (pItemTemplate->Class != ITEM_CLASS_WEAPON)
                return false;

            if (pItemTemplate->SubClass != ITEM_SUBCLASS_WEAPON_STAFF)
                return false;

            if (pItemTemplate->InventoryType != INVTYPE_2HWEAPON)
                return false;

            break;
        }
        case ENCHANT_WEAPON_BERSERKING:
        case ENCHANT_WEAPON_BLACK_MAGIC:
        case ENCHANT_WEAPON_BLOOD_DRAINING:
        case ENCHANT_WEAPON_BLADE_WARDING:
        case ENCHANT_WEAPON_TITANIUM_WEAPON_CHAIN:
        case ENCHANT_WEAPON_SUPERIOR_POTENCY:
        case ENCHANT_WEAPON_MIGHTY_SPELLPOWER:
        case ENCHANT_WEAPON_EXCEPTIONAL_AGILITY:
        case ENCHANT_WEAPON_EXCEPTIONAL_SPIRIT:
        case ENCHANT_WEAPON_TITANGUARD:
        case ENCHANT_WEAPON_ACCURACY:
        case ENCHANT_WEAPON_MONGOOSE:
        case ENCHANT_WEAPON_EXECUTIONER:
        case ENCHANT_WEAPON_DEATHFROST:
        case ENCHANT_WEAPON_FALLEN_CRUSADER:
        case ENCHANT_WEAPON_CINDERGLACIER:
        case ENCHANT_WEAPON_RAZORICE:
        case ENCHANT_WEAPON_LICHBANE:
        case ENCHANT_WEAPON_SPELLBREAKING:
        case ENCHANT_WEAPON_SPELLSHATTERING:
        case ENCHANT_WEAPON_SWORDBREAKING:
        case ENCHANT_WEAPON_SWORDSHATTERING:
        case ENCHANT_WEAPON_NERUBIAN_CARAPACE:
        case ENCHANT_WEAPON_STONESKIN_GARGOYLE:
        {
            if (pItemTemplate->Class != ITEM_CLASS_WEAPON)
                return false;

            if (pItemTemplate->SubClass != ITEM_SUBCLASS_WEAPON_AXE &&
                pItemTemplate->SubClass != ITEM_SUBCLASS_WEAPON_AXE2 &&
                pItemTemplate->SubClass != ITEM_SUBCLASS_WEAPON_MACE &&
                pItemTemplate->SubClass != ITEM_SUBCLASS_WEAPON_MACE2 &&
                pItemTemplate->SubClass != ITEM_SUBCLASS_WEAPON_POLEARM &&
                pItemTemplate->SubClass != ITEM_SUBCLASS_WEAPON_SWORD &&
                pItemTemplate->SubClass != ITEM_SUBCLASS_WEAPON_SWORD2 &&
                pItemTemplate->SubClass != ITEM_SUBCLASS_WEAPON_STAFF &&
                pItemTemplate->SubClass != ITEM_SUBCLASS_WEAPON_FIST &&
                pItemTemplate->SubClass != ITEM_SUBCLASS_WEAPON_DAGGER)
                return false;

            if (pItemTemplate->InventoryType != INVTYPE_2HWEAPON &&
                pItemTemplate->InventoryType != INVTYPE_WEAPON &&
                pItemTemplate->InventoryType != INVTYPE_WEAPONMAINHAND &&
                pItemTemplate->InventoryType != INVTYPE_WEAPONOFFHAND)
                return false;

            break;
        }
        case ENCHANT_RANGED_HEARTSEEKER_SCOPE:
        case ENCHANT_RANGED_SUN_SCOPE:
        case ENCHANT_RANGED_DIAMOND_CUT_REFRACTOR_SCOPE:
        {
            if (pItemTemplate->Class != ITEM_CLASS_WEAPON)
                return false;

            if (pItemTemplate->SubClass != ITEM_SUBCLASS_WEAPON_BOW &&
                pItemTemplate->SubClass != ITEM_SUBCLASS_WEAPON_GUN &&
                pItemTemplate->SubClass != ITEM_SUBCLASS_WEAPON_CROSSBOW)
                return false;

            if (pItemTemplate->InventoryType != INVTYPE_RANGED &&
                pItemTemplate->InventoryType != INVTYPE_RANGEDRIGHT)
                return false;

            break;
        }
        case ENCHANT_SHIELD_TITANIUM_PLATING:
        case ENCHANT_SHIELD_GREATER_INTELLECT:
        case ENCHANT_SHIELD_RESILIENCE:
        {
            if (pItemTemplate->Class != ITEM_CLASS_ARMOR)
                return false;

            if (pItemTemplate->SubClass != ITEM_SUBCLASS_ARMOR_SHIELD)
                return false;

            if (pItemTemplate->InventoryType != INVTYPE_SHIELD)
                return false;

            break;
        }
        case ENCHANT_RING_ASSAULT:
        case ENCHANT_RING_GREATER_SPELLPOWER:
        case ENCHANT_RING_STAMINA:
        {
            if (pItemTemplate->Class != ITEM_CLASS_ARMOR)
                return false;

            if (pItemTemplate->SubClass != ITEM_SUBCLASS_ARMOR_MISC)
                return false;

            if (pItemTemplate->InventoryType != INVTYPE_FINGER)
                return false;

            break;
        }
    }

    switch (slot)
    {
        case EQUIPMENT_SLOT_HEAD:
        case EQUIPMENT_SLOT_SHOULDERS:
        case EQUIPMENT_SLOT_CHEST:
        case EQUIPMENT_SLOT_HANDS:
        case EQUIPMENT_SLOT_LEGS:
        case EQUIPMENT_SLOT_WRISTS:
        case EQUIPMENT_SLOT_WAIST:
        case EQUIPMENT_SLOT_FEET:
        {
            if (pItemTemplate->Class != ITEM_CLASS_ARMOR)
                return false;

            if (pItemTemplate->Class == ITEM_CLASS_ARMOR)
                if (pItemTemplate->SubClass != ITEM_SUBCLASS_ARMOR_CLOTH &&
                    pItemTemplate->SubClass != ITEM_SUBCLASS_ARMOR_LEATHER &&
                    pItemTemplate->SubClass != ITEM_SUBCLASS_ARMOR_MAIL &&
                    pItemTemplate->SubClass != ITEM_SUBCLASS_ARMOR_PLATE)
                    return false;

            if (pItemTemplate->InventoryType != INVTYPE_HEAD &&
                pItemTemplate->InventoryType != INVTYPE_SHOULDERS &&
                pItemTemplate->InventoryType != INVTYPE_CHEST &&
                pItemTemplate->InventoryType != INVTYPE_HANDS &&
                pItemTemplate->InventoryType != INVTYPE_LEGS &&
                pItemTemplate->InventoryType != INVTYPE_WRISTS &&
                pItemTemplate->InventoryType != INVTYPE_WAIST &&
                pItemTemplate->InventoryType != INVTYPE_FEET)
                return false;

            break;
        }
        case EQUIPMENT_SLOT_BACK:
        {
            if (pItemTemplate->Class != ITEM_CLASS_ARMOR)
                return false;

            if (pItemTemplate->Class == ITEM_CLASS_ARMOR)
                if (pItemTemplate->SubClass != ITEM_SUBCLASS_ARMOR_CLOTH)
                    return false;

            if (pItemTemplate->InventoryType != INVTYPE_CLOAK)
                return false;

            break;
        }
        case EQUIPMENT_SLOT_FINGER1:
        case EQUIPMENT_SLOT_FINGER2:
        {
            if (pItemTemplate->Class != ITEM_CLASS_ARMOR)
                return false;

            if (pItemTemplate->Class == ITEM_CLASS_ARMOR)
                if (pItemTemplate->SubClass != ITEM_SUBCLASS_ARMOR_MISC)
                    return false;

            if (pItemTemplate->InventoryType != INVTYPE_FINGER)
                return false;

            break;
        }
        case EQUIPMENT_SLOT_MAINHAND:
        {
            if (pItemTemplate->Class != ITEM_CLASS_WEAPON)
                return false;

            if (pItemTemplate->Class == ITEM_CLASS_WEAPON)
                if (pItemTemplate->SubClass != ITEM_SUBCLASS_WEAPON_AXE &&
                    pItemTemplate->SubClass != ITEM_SUBCLASS_WEAPON_AXE2 &&
                    pItemTemplate->SubClass != ITEM_SUBCLASS_WEAPON_MACE &&
                    pItemTemplate->SubClass != ITEM_SUBCLASS_WEAPON_MACE2 &&
                    pItemTemplate->SubClass != ITEM_SUBCLASS_WEAPON_SWORD &&
                    pItemTemplate->SubClass != ITEM_SUBCLASS_WEAPON_SWORD2 &&
                    pItemTemplate->SubClass != ITEM_SUBCLASS_WEAPON_POLEARM &&
                    pItemTemplate->SubClass != ITEM_SUBCLASS_WEAPON_STAFF &&
                    pItemTemplate->SubClass != ITEM_SUBCLASS_WEAPON_FIST &&
                    pItemTemplate->SubClass != ITEM_SUBCLASS_WEAPON_DAGGER)
                    return false;

            if (pItemTemplate->InventoryType != INVTYPE_WEAPON &&
                pItemTemplate->InventoryType != INVTYPE_WEAPONMAINHAND &&
                pItemTemplate->InventoryType != INVTYPE_WEAPONOFFHAND &&
                pItemTemplate->InventoryType != INVTYPE_2HWEAPON)
                return false;

            break;
        }
        case EQUIPMENT_SLOT_OFFHAND:
        {
            if (pItemTemplate->Class != ITEM_CLASS_WEAPON && pItemTemplate->Class != ITEM_CLASS_ARMOR)
                return false;

            if (pItemTemplate->Class == ITEM_CLASS_WEAPON)
                if (pItemTemplate->SubClass != ITEM_SUBCLASS_WEAPON_AXE &&
                    pItemTemplate->SubClass != ITEM_SUBCLASS_WEAPON_AXE2 &&
                    pItemTemplate->SubClass != ITEM_SUBCLASS_WEAPON_MACE &&
                    pItemTemplate->SubClass != ITEM_SUBCLASS_WEAPON_MACE2 &&
                    pItemTemplate->SubClass != ITEM_SUBCLASS_WEAPON_SWORD &&
                    pItemTemplate->SubClass != ITEM_SUBCLASS_WEAPON_SWORD2 &&
                    pItemTemplate->SubClass != ITEM_SUBCLASS_WEAPON_POLEARM &&
                    pItemTemplate->SubClass != ITEM_SUBCLASS_WEAPON_STAFF &&
                    pItemTemplate->SubClass != ITEM_SUBCLASS_WEAPON_FIST &&
                    pItemTemplate->SubClass != ITEM_SUBCLASS_WEAPON_DAGGER)
                    return false;

            if (pItemTemplate->Class == ITEM_CLASS_ARMOR)
                if (pItemTemplate->SubClass != ITEM_SUBCLASS_ARMOR_SHIELD)
                    return false;

            if (pItemTemplate->InventoryType != INVTYPE_WEAPON &&
                pItemTemplate->InventoryType != INVTYPE_WEAPONMAINHAND &&
                pItemTemplate->InventoryType != INVTYPE_WEAPONOFFHAND &&
                pItemTemplate->InventoryType != INVTYPE_2HWEAPON &&
                pItemTemplate->InventoryType != INVTYPE_SHIELD)
                return false;

            break;
        }
        case EQUIPMENT_SLOT_RANGED:
        {
            if (pItemTemplate->Class != ITEM_CLASS_WEAPON)
                return false;

            if (pItemTemplate->Class == ITEM_CLASS_WEAPON)
                if (pItemTemplate->SubClass != ITEM_SUBCLASS_WEAPON_BOW &&
                    pItemTemplate->SubClass != ITEM_SUBCLASS_WEAPON_GUN &&
                    pItemTemplate->SubClass != ITEM_SUBCLASS_WEAPON_CROSSBOW)
                    return false;

            if (pItemTemplate->InventoryType != INVTYPE_RANGED &&
                pItemTemplate->InventoryType != INVTYPE_RANGEDRIGHT)
                return false;

            break;
        }
    }

    switch (enchantId)
    {
        case ENCHANT_2H_WEAPON_MASSACRE:
        {
            if (pItemTemplate->Class == ITEM_CLASS_WEAPON && pItemTemplate->InventoryType != INVTYPE_2HWEAPON)
                return false;

            break;
        }
        case ENCHANT_STAFF_GREATER_SPELLPOWER:
        {
            if (pItemTemplate->Class == ITEM_CLASS_WEAPON && pItemTemplate->SubClass != ITEM_SUBCLASS_WEAPON_STAFF)
                return false;

            break;
        }
        case ENCHANT_RANGED_HEARTSEEKER_SCOPE:
        case ENCHANT_RANGED_SUN_SCOPE:
        case ENCHANT_RANGED_DIAMOND_CUT_REFRACTOR_SCOPE:
        {
            if (pItemTemplate->Class == ITEM_CLASS_WEAPON && (pItemTemplate->SubClass != ITEM_SUBCLASS_WEAPON_BOW &&
                pItemTemplate->SubClass != ITEM_SUBCLASS_WEAPON_GUN && pItemTemplate->SubClass != ITEM_SUBCLASS_WEAPON_CROSSBOW))
                return false;

            break;
        }
        case ENCHANT_SHIELD_TITANIUM_PLATING:
        case ENCHANT_SHIELD_GREATER_INTELLECT:
        case ENCHANT_SHIELD_RESILIENCE:
        {
            if (pItemTemplate->InventoryType != INVTYPE_SHIELD)
                return false;

            break;
        }
        case ENCHANT_WEAPON_FALLEN_CRUSADER:
        case ENCHANT_WEAPON_CINDERGLACIER:
        case ENCHANT_WEAPON_RAZORICE:
        case ENCHANT_WEAPON_LICHBANE:
        case ENCHANT_WEAPON_SPELLBREAKING:
        case ENCHANT_WEAPON_SPELLSHATTERING:
        case ENCHANT_WEAPON_SWORDBREAKING:
        case ENCHANT_WEAPON_SWORDSHATTERING:
        case ENCHANT_WEAPON_NERUBIAN_CARAPACE:
        case ENCHANT_WEAPON_STONESKIN_GARGOYLE:
        {
            if (pItemTemplate->Class == ITEM_CLASS_WEAPON && player->getClass() != CLASS_DEATH_KNIGHT)
                return false;

            break;
        }
        case ENCHANT_GLOVES_SOCKET:
        case ENCHANT_BRACER_SOCKET:
        {
            if (player->GetSkillValue(SKILL_BLACKSMITHING) < 450)
                return false;

            break;
        }
        case ENCHANT_RING_ASSAULT:
        case ENCHANT_RING_GREATER_SPELLPOWER:
        case ENCHANT_RING_STAMINA:
        {
            if (player->GetSkillValue(SKILL_ENCHANTING) < 450)
                return false;

            break;
        }
        case ENCHANT_HEAD_MIND_AMPLIFICATION_DISH:
        case ENCHANT_GLOVES_HAND_MOUNTED_PRYO_ROCKET:
        case ENCHANT_GLOVES_HYPERSPEED_ACCELERATORS:
        case ENCHANT_BELT_FRAG_BELT:
        case ENCHANT_BOOTS_NITRO_BOOSTS:
        case ENCHANT_CLOAK_FLEXWEAVE_UNDERLAY:
        case ENCHANT_CLOAK_SPRINGY_ARACHNOWEAVE:
        {
            if (player->GetSkillValue(SKILL_ENGINEERING) < 450)
                return false;

            for (uint8 i = 0; i < MAX_ITEM_SPELLS; ++i)
                if (pItemTemplate->Spells[i].SpellId && !pItemTemplate->Spells[i].SpellTrigger)
                    return false;

            break;
        }
        case ENCHANT_SHOULDERS_MASTERS_INSCRIPTION_OF_THE_AXE:
        case ENCHANT_SHOULDERS_MASTERS_INSCRIPTION_OF_THE_STORM:
        case ENCHANT_SHOULDERS_MASTERS_INSCRIPTION_OF_THE_CRAG:
        case ENCHANT_SHOULDERS_MASTERS_INSCRIPTION_OF_THE_PINNACLE:
        {
            if (player->GetSkillValue(SKILL_INSCRIPTION) < 450)
                return false;

            break;
        }
        case ENCHANT_BRACER_FUR_LINING_ATTACKPOWER:
        case ENCHANT_BRACER_FUR_LINING_SPELLPOWER:
        case ENCHANT_BRACER_FUR_LINING_AGILITY:
        case ENCHANT_BRACER_FUR_LINING_STAMINA:
        {
            if (player->GetSkillValue(SKILL_LEATHERWORKING) < 450)
                return false;

            break;
        }
        case ENCHANT_CLOAK_SWORDGUARD_EMBROIDERY:
        case ENCHANT_CLOAK_LIGHTWEAVE_EMBROIDERY: 
        case ENCHANT_CLOAK_DARKGLOW_EMBROIDERY:
        {
            if (player->GetSkillValue(SKILL_TAILORING) < 450)
                return false;

            break;
        }
    }

    return true;
}

void AddSC_MallMgr()
{
    new MallMgr();
}
