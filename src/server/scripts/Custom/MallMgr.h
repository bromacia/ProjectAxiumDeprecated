#include "ScriptMgr.h"
#include "ScriptPCH.h"

enum MallOptions
{
    MALL_MENU_GENERAL_GOODS = 2,
    MALL_MENU_GEAR,
    MALL_MENU_PROFESSIONS,
    MALL_MENU_ENCHANTS,
    MALL_MENU_GEMS,
    MALL_MENU_APPAREL,
    MALL_MENU_MOUNTS,
    MALL_MENU_GLYPHS,
    MALL_MENU_RESET_TALENTS,
    MALL_MENU_LEARN_DUAL_SPEC,
    MALL_MENU_SETUP_SHADOW_DANCE,
    MALL_MENU_FINISH_SHADOW_DANCE,

    MALL_GEAR_RELENTLESS_GLADIATOR,
    MALL_GEAR_TRIAL_OF_THE_CRUSADER,
    MALL_GEAR_WRATHFUL_GLADIATOR,
    MALL_GEAR_ICECROWN_CITADEL,
    MALL_GEAR_APPAREL,

    GEAR_OPTION_MAINSETS_AND_OFFSETS,
    GEAR_OPTION_ACCESSORIES,
    GEAR_OPTION_WEAPONS,
    GEAR_OPTION_TRINKETS,

    ENCHANT_OPTION_HEAD,
    ENCHANT_OPTION_SHOULDERS,
    ENCHANT_OPTION_CHEST,
    ENCHANT_OPTION_GLOVES,
    ENCHANT_OPTION_LEGS,
    ENCHANT_OPTION_BRACERS,
    ENCHANT_OPTION_BELT,
    ENCHANT_OPTION_BOOTS,
    ENCHANT_OPTION_CLOAK,
    ENCHANT_OPTION_RING1,
    ENCHANT_OPTION_RING2,
    ENCHANT_OPTION_MAIN_HAND,
    ENCHANT_OPTION_OFF_HAND,
    ENCHANT_OPTION_RANGED,
};

enum InventoryListOption
{
    INVENTORY_LIST_GENERAL_GOODS = 1,
    INVENTORY_LIST_GEMS,
    INVENTORY_LIST_MOUNTS,
    INVENTORY_LIST_GLYPHS,
    INVENTORY_LIST_RELENTLESS_GLADIATOR_MAINSETS_AND_OFFSETS,
    INVENTORY_LIST_RELENTLESS_GLADIATOR_ACCESSORIES,
    INVENTORY_LIST_RELENTLESS_GLADIATOR_WEAPONS,
    INVENTORY_LIST_TRIAL_OF_THE_CRUSADER_MAINSETS_AND_OFFSETS,
    INVENTORY_LIST_TRIAL_OF_THE_CRUSADER_ACCESSORIES,
    INVENTORY_LIST_TRIAL_OF_THE_CRUSADER_WEAPONS,
    INVENTORY_LIST_245_TRINKETS,
    INVENTORY_LIST_WRATHFUL_GLADIATOR_MAINSETS_AND_OFFSETS,
    INVENTORY_LIST_WRATHFUL_GLADIATOR_ACCESSORIES,
    INVENTORY_LIST_WRATHFUL_GLADIATOR_WEAPONS,
    INVENTORY_LIST_ICECROWN_CITADEL_MAINSETS_AND_OFFSETS,
    INVENTORY_LIST_ICECROWN_CITADEL_ACCESSORIES,
    INVENTORY_LIST_ICECROWN_CITADEL_WEAPONS,
    INVENTORY_LIST_264_TRINKETS,
    INVENTORY_LIST_APPAREL,
};

enum EnchantId
{
    ENCHANT_HEAD_ARCANUM_OF_TRIUMPH = 3795,
    ENCHANT_HEAD_ARCANUM_OF_DOMINANCE = 3796,
    ENCHANT_HEAD_ARCANUM_OF_TORMENT = 3817,
    ENCHANT_HEAD_ARCANUM_OF_BURNING_MYSTERIES = 3820,
    ENCHANT_HEAD_ARCANUM_OF_BLISSFUL_MENDING = 3819,
    ENCHANT_HEAD_ARCANUM_OF_THE_STALWART_PROTECTOR = 3818,

    ENCHANT_SHOULDER_INSCRIPTION_OF_TRIUMPH = 3793,
    ENCHANT_SHOULDER_INSCRIPTION_OF_DOMINANCE = 3794,
    ENCHANT_SHOULDER_GREATER_INSCRIPTION_OF_THE_AXE = 3808,
    ENCHANT_SHOULDER_GREATER_INSCRIPTION_OF_THE_STORM = 3810,
    ENCHANT_SHOULDER_GREATER_INSCRIPTION_OF_THE_CRAG = 3809,
    ENCHANT_SHOULDER_GREATER_INSCRIPTION_OF_THE_PINNACLE = 3811,

    ENCHANT_CHEST_EXCEPTIONAL_RESILIENCE = 3245,
    ENCHANT_CHEST_POWERFUL_STATS = 3832,
    ENCHANT_CHEST_SUPER_HEALTH = 3297,

    ENCHANT_GLOVES_CRUSHER = 1603,
    ENCHANT_GLOVES_EXCEPTIONAL_SPELLPOWER = 3246,
    ENCHANT_GLOVES_MAJOR_AGILITY = 3222,
    ENCHANT_GLOVES_PERCISION = 3234,

    ENCHANT_LEGS_ICESCALE_LEG_ARMOR = 3823,
    ENCHANT_LEGS_SAPPHIRE_SPELLTHREAD = 3721,
    ENCHANT_LEGS_BRILLIANT_SPELLTHREAD = 3719,
    ENCHANT_LEGS_FROSTHIDE_LEG_ARMOR = 3822,
    ENCHANT_LEGS_EARTHEN_LEG_ARMOR = 3853,

    ENCHANT_BRACERS_GREATER_ASSAULT = 3845,
    ENCHANT_BRACERS_SUPERIOR_SPELLPOWER = 2332,
    ENCHANT_BRACERS_EXCEPTIONAL_INTELLECT = 1119,
    ENCHANT_BRACERS_MAJOR_SPIRIT = 1147,
    ENCHANT_BRACERS_MAJOR_STAMINA = 3850,

    ENCHANT_BELT_ETERNAL_BELT_BUCKLE = 3729,

    ENCHANT_BOOTS_GREATER_ASSULT = 1597,
    ENCHANT_BOOTS_SUPERIOR_AGILITY = 983,
    ENCHANT_BOOTS_ICEWALKER = 3826,
    ENCHANT_BOOTS_TUSKARR_VITALITY = 3232,

    ENCHANT_CLOAK_SPELL_PIERCING = 3243,
    ENCHANT_CLOAK_MAJOR_AGILITY = 1099,
    ENCHANT_CLOAK_GREATER_SPEED = 3831,
    ENCHANT_CLOAK_SHADOW_ARMOR = 3256,

    ENCHANT_2H_WEAPON_MASSACRE = 3827,
    ENCHANT_STAFF_GREATER_SPELLPOWER = 3854,

    ENCHANT_WEAPON_BERSERKING = 3789,
    ENCHANT_WEAPON_BLACK_MAGIC = 3790,
    ENCHANT_WEAPON_BLOOD_DRAINING = 3870,
    ENCHANT_WEAPON_BLADE_WARDING = 3869,
    ENCHANT_WEAPON_TITANIUM_WEAPON_CHAIN = 3731,
    ENCHANT_WEAPON_SUPERIOR_POTENCY = 3833,
    ENCHANT_WEAPON_MIGHTY_SPELLPOWER = 3834,
    ENCHANT_WEAPON_EXCEPTIONAL_AGILITY = 1103,
    ENCHANT_WEAPON_EXCEPTIONAL_SPIRIT = 3844,
    ENCHANT_WEAPON_TITANGUARD = 3851,
    ENCHANT_WEAPON_ACCURACY = 3788,
    ENCHANT_WEAPON_MONGOOSE = 2673,
    ENCHANT_WEAPON_EXECUTIONER = 3225,
    ENCHANT_WEAPON_DEATHFROST = 3273,

    ENCHANT_RANGED_HEARTSEEKER_SCOPE = 3608,
    ENCHANT_RANGED_SUN_SCOPE = 3607,
    ENCHANT_RANGED_DIAMOND_CUT_REFRACTOR_SCOPE = 3843,

    ENCHANT_SHIELD_TITANIUM_PLATING = 3849,
    ENCHANT_SHIELD_GREATER_INTELLECT = 1128,
    ENCHANT_SHIELD_RESILIENCE = 3229,

    // Death Knight Enchants
    ENCHANT_WEAPON_FALLEN_CRUSADER = 3368,
    ENCHANT_WEAPON_CINDERGLACIER = 3369,
    ENCHANT_WEAPON_RAZORICE = 3370,
    ENCHANT_WEAPON_LICHBANE = 3366,
    ENCHANT_WEAPON_SPELLBREAKING = 3595,
    ENCHANT_WEAPON_SPELLSHATTERING = 3367,
    ENCHANT_WEAPON_SWORDBREAKING = 3594,
    ENCHANT_WEAPON_SWORDSHATTERING = 3365,
    ENCHANT_WEAPON_NERUBIAN_CARAPACE = 3883,
    ENCHANT_WEAPON_STONESKIN_GARGOYLE = 3847,

    // Blacksmithing
    ENCHANT_GLOVES_SOCKET = 3723,
    ENCHANT_BRACER_SOCKET = 3717,

    // Enchanting
    ENCHANT_RING_ASSAULT = 3839,
    ENCHANT_RING_GREATER_SPELLPOWER = 3840,
    ENCHANT_RING_STAMINA = 3791,

    // Engineering
    ENCHANT_HEAD_MIND_AMPLIFICATION_DISH = 3878,
    ENCHANT_GLOVES_HAND_MOUNTED_PRYO_ROCKET = 3603,
    ENCHANT_GLOVES_HYPERSPEED_ACCELERATORS = 3604,
    ENCHANT_BELT_FRAG_BELT = 3601,
    ENCHANT_BOOTS_NITRO_BOOSTS = 3606,
    ENCHANT_CLOAK_FLEXWEAVE_UNDERLAY = 3605,
    ENCHANT_CLOAK_SPRINGY_ARACHNOWEAVE = 3859,

    // Inscription
    ENCHANT_SHOULDERS_MASTERS_INSCRIPTION_OF_THE_AXE = 3835,
    ENCHANT_SHOULDERS_MASTERS_INSCRIPTION_OF_THE_STORM = 3838,
    ENCHANT_SHOULDERS_MASTERS_INSCRIPTION_OF_THE_CRAG = 3836,
    ENCHANT_SHOULDERS_MASTERS_INSCRIPTION_OF_THE_PINNACLE = 3837,

    // Leatherworking
    ENCHANT_BRACER_FUR_LINING_ATTACKPOWER = 3756,
    ENCHANT_BRACER_FUR_LINING_SPELLPOWER = 3758,
    ENCHANT_BRACER_FUR_LINING_AGILITY = 4873,
    ENCHANT_BRACER_FUR_LINING_STAMINA = 3757,

    // Tailoring
    ENCHANT_CLOAK_SWORDGUARD_EMBROIDERY = 3730,
    ENCHANT_CLOAK_LIGHTWEAVE_EMBROIDERY = 3722, 
    ENCHANT_CLOAK_DARKGLOW_EMBROIDERY = 3728,
};

class MallMgr : public CreatureScript
{
    public:
        MallMgr() : CreatureScript("MallNPC") {}
        bool OnGossipHello(Player* player, Creature* creature);
        bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action);
        bool HandleGear(Player* player, Creature* creature, uint32 action);
        bool HandleProfessions(Player* player, Creature* creature);
        bool HandleEnchants(Player* player, Creature* creature, uint32 action);
        bool HandleResetTalents(Player* player, Creature* creature);
        bool HandleLearnDualSpecialization(Player* player, Creature* creature);
        bool HandleSetupShadowDanceBar(Player* player, Creature* creature);
        bool HandleFinishShadowDanceBar(Player* player, Creature* creature);
        bool ShowInventory(Player* player, Creature* creature, uint32 action);
        bool EnchantItem(Player* player, Creature* creature, uint16 enchantId, uint8 enchantOption);
        bool LearnSkill(Player* player, Creature* creature, uint16 skill);
    private:
        bool CheckVendorItem(Player* player, const ItemTemplate* vItemTemplate, uint32 action);
        bool CheckSkill(Player* player, uint16 skill);
        bool CheckEnchantItem(Player* player, const ItemTemplate* pItemTemplate, uint16 enchantId, uint8 slot);
        uint8 GetItemSlotByEnchantOption(uint8 invType)
        {
            switch (invType)
            {
                case ENCHANT_OPTION_HEAD:      return EQUIPMENT_SLOT_HEAD;
                case ENCHANT_OPTION_SHOULDERS: return EQUIPMENT_SLOT_SHOULDERS;
                case ENCHANT_OPTION_CHEST:     return EQUIPMENT_SLOT_CHEST;
                case ENCHANT_OPTION_GLOVES:    return EQUIPMENT_SLOT_HANDS;
                case ENCHANT_OPTION_LEGS:      return EQUIPMENT_SLOT_LEGS;
                case ENCHANT_OPTION_BRACERS:   return EQUIPMENT_SLOT_WRISTS;
                case ENCHANT_OPTION_BELT:      return EQUIPMENT_SLOT_WAIST;
                case ENCHANT_OPTION_BOOTS:     return EQUIPMENT_SLOT_FEET;
                case ENCHANT_OPTION_CLOAK:     return EQUIPMENT_SLOT_BACK;
                case ENCHANT_OPTION_RING1:     return EQUIPMENT_SLOT_FINGER1;
                case ENCHANT_OPTION_RING2:     return EQUIPMENT_SLOT_FINGER2;
                case ENCHANT_OPTION_MAIN_HAND: return EQUIPMENT_SLOT_MAINHAND;
                case ENCHANT_OPTION_OFF_HAND:  return EQUIPMENT_SLOT_OFFHAND;
                case ENCHANT_OPTION_RANGED:    return EQUIPMENT_SLOT_RANGED;
                default:                       return EQUIPMENT_SLOT_END;
            }
        }
        uint8 GetUsableArmorProficiencyByClass(uint8 Class)
        {
            switch (Class)
            {
                case CLASS_WARRIOR:      return ITEM_SUBCLASS_ARMOR_PLATE;
                case CLASS_PALADIN:      return ITEM_SUBCLASS_ARMOR_PLATE;
                case CLASS_DEATH_KNIGHT: return ITEM_SUBCLASS_ARMOR_PLATE;
                case CLASS_HUNTER:       return ITEM_SUBCLASS_ARMOR_MAIL;
                case CLASS_SHAMAN:       return ITEM_SUBCLASS_ARMOR_MAIL;
                case CLASS_ROGUE:        return ITEM_SUBCLASS_ARMOR_LEATHER;
                case CLASS_DRUID:        return ITEM_SUBCLASS_ARMOR_LEATHER;
                case CLASS_PRIEST:       return ITEM_SUBCLASS_ARMOR_CLOTH;
                case CLASS_MAGE:         return ITEM_SUBCLASS_ARMOR_CLOTH;
                case CLASS_WARLOCK:      return ITEM_SUBCLASS_ARMOR_CLOTH;
                default:                 return MAX_ITEM_SUBCLASS_ARMOR;
            }
        }
        std::string SlotToSlotString(uint8 slot)
        {
            switch (slot)
            {
                case EQUIPMENT_SLOT_HEAD:      return "head";
                case EQUIPMENT_SLOT_SHOULDERS: return "shoulders";
                case EQUIPMENT_SLOT_CHEST:     return "chest";
                case EQUIPMENT_SLOT_HANDS:     return "hands";
                case EQUIPMENT_SLOT_LEGS:      return "legs";
                case EQUIPMENT_SLOT_WRISTS:    return "wrists";
                case EQUIPMENT_SLOT_WAIST:     return "waist";
                case EQUIPMENT_SLOT_FEET:      return "feet";
                case EQUIPMENT_SLOT_BACK:      return "back";
                case EQUIPMENT_SLOT_FINGER1:   return "finger1";
                case EQUIPMENT_SLOT_FINGER2:   return "finger2";
                case EQUIPMENT_SLOT_MAINHAND:  return "main hand";
                case EQUIPMENT_SLOT_OFFHAND:   return "off hand";
                case EQUIPMENT_SLOT_RANGED:    return "ranged";
                default:                       return "error";
            }
        }
        std::string SkillToSkillString(uint16 skill)
        {
            switch (skill)
            {
                case SKILL_ALCHEMY:        return "Alchemy";
                case SKILL_BLACKSMITHING:  return "Blacksmithing";
                case SKILL_ENCHANTING:     return "Enchanting";
                case SKILL_ENGINEERING:    return "Engineering";
                case SKILL_HERBALISM:      return "Herbalism";
                case SKILL_INSCRIPTION:    return "Inscription";
                case SKILL_JEWELCRAFTING:  return "Jewelcrafting";
                case SKILL_LEATHERWORKING: return "Leatherworking";
                case SKILL_TAILORING:      return "Tailoring";
                default:                   return "Error";
            }
        }
};
