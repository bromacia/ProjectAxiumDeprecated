#include "ScriptMgr.h"
#include "ScriptPCH.h"

enum TransmogSlots
{
    TRANSMOG_SLOT_HEAD             = PLAYER_VISIBLE_ITEM_1_ENTRYID,
    TRANSMOG_SLOT_SHOULDERS        = PLAYER_VISIBLE_ITEM_3_ENTRYID,
    TRANSMOG_SLOT_CHEST            = PLAYER_VISIBLE_ITEM_5_ENTRYID,
    TRANSMOG_SLOT_HANDS            = PLAYER_VISIBLE_ITEM_10_ENTRYID,
    TRANSMOG_SLOT_LEGS             = PLAYER_VISIBLE_ITEM_7_ENTRYID,
    TRANSMOG_SLOT_WRISTS           = PLAYER_VISIBLE_ITEM_9_ENTRYID,
    TRANSMOG_SLOT_WAIST            = PLAYER_VISIBLE_ITEM_6_ENTRYID,
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
    TRANSMOG_ACTION_SHOW_INDIVIDUAL,
    TRANSMOG_ACTION_SHOW_ENCHANTS,
    TRANSMOG_ACTION_SHOW_INDIVIDUAL_HEAD,
    TRANSMOG_ACTION_SHOW_INDIVIDUAL_SHOULDERS,
    TRANSMOG_ACTION_SHOW_INDIVIDUAL_CHEST,
    TRANSMOG_ACTION_SHOW_INDIVIDUAL_HANDS,
    TRANSMOG_ACTION_SHOW_INDIVIDUAL_LEGS,
    TRANSMOG_ACTION_SHOW_INDIVIDUAL_WRISTS,
    TRANSMOG_ACTION_SHOW_INDIVIDUAL_WAIST,
    TRANSMOG_ACTION_SHOW_INDIVIDUAL_BOOTS,
    TRANSMOG_ACTION_SHOW_INDIVIDUAL_MAINHAND,
    TRANSMOG_ACTION_SHOW_INDIVIDUAL_OFFHAND,
    TRANSMOG_ACTION_SHOW_INDIVIDUAL_RANGED,
    TRANSMOG_ACTION_SHOW_REMOVE_ITEM_TRANSMOG_OPTIONS,
    TRANSMOG_ACTION_SHOW_REMOVE_ENCHANT_TRANSMOG_OPTIONS,
    TRANSMOG_ACTION_SELECT_INDIVIDUAL,
    TRANSMOG_ACTION_SELECT_REMOVE_HEAD,
    TRANSMOG_ACTION_SELECT_REMOVE_SHOULDERS,
    TRANSMOG_ACTION_SELECT_REMOVE_CHEST,
    TRANSMOG_ACTION_SELECT_REMOVE_HANDS,
    TRANSMOG_ACTION_SELECT_REMOVE_LEGS,
    TRANSMOG_ACTION_SELECT_REMOVE_WRISTS,
    TRANSMOG_ACTION_SELECT_REMOVE_WAIST,
    TRANSMOG_ACTION_SELECT_REMOVE_BOOTS,
    TRANSMOG_ACTION_SELECT_REMOVE_MAINHAND,
    TRANSMOG_ACTION_SELECT_REMOVE_OFFHAND,
    TRANSMOG_ACTION_SELECT_REMOVE_RANGED,
    TRANSMOG_ACTION_SELECT_REMOVE_MAINHAND_ENCHANT,
    TRANSMOG_ACTION_SELECT_REMOVE_OFFHAND_ENCHANT,
    TRANSMOG_ACTION_SELECT_REMOVE_ALL_ARMOR,
    TRANSMOG_ACTION_SELECT_REMOVE_ALL_WEAPON,
    TRANSMOG_ACTION_SELECT_REMOVE_ALL_ENCHANT,
    TRANSMOG_ACTION_SELECT_REMOVE_EVERYTHING,
    TRANSMOG_ACTION_MAIN_MENU,
};

class Transmogrification : public CreatureScript
{
    public:
        Transmogrification() : CreatureScript("Transmogrifier") {}
        bool OnGossipHello(Player* player, Creature* creature);
        bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action);
        static bool ShowTransmogArmorSets(Player* player, Creature* creature);
        static bool ShowIndividualTransmogOptions(Player* player, Creature* creature);
        static bool ShowTransmogEnchants(Player* player, Creature* creature);
        static bool ShowRemoveTransmogItemOptions(Player* player, Creature* creature);
        static bool ShowRemoveTransmogEnchantOptions(Player* player, Creature* creature);
        static bool SelectIndividualTransmog(Player* player, Creature* creature, uint16 action);
        static bool TransmogrifyArmor(Player* player, uint16 action);
        static bool TransmogrifyIndividual(Player* player, Creature* creature, uint32 item);
        static bool TransmogrifyEnchant(Player* player, uint16 action);
        static bool RemoveItemTransmog(Player* player, uint16 action);
        static bool RemoveEnchantTransmog(Player* player, uint16 action);
        static bool RemoveAllArmorTransmog(Player* player);
        static bool RemoveAllWeaponTransmog(Player* player);
        static bool RemoveAllEnchantTransmog(Player* player);
        static bool RemoveAllTransmog(Player* player);
    private:
        static bool IsArmor(ItemTemplate const* itemTemplate) { return itemTemplate->Class == ITEM_CLASS_ARMOR; }
        static bool IsWeapon(ItemTemplate const* itemTemplate) { return itemTemplate->Class == ITEM_CLASS_WEAPON; }
        static uint16 GetTeamById(uint8 Id)
        {
            switch (Id)
            {
                case 1:  return ALLIANCE;
                case 2:  return HORDE;
                default: return NULL;
            }
        }
        static uint8 GetItemSlotByAction(uint8 action)
        {
            switch (action)
            {
                case TRANSMOG_ACTION_SHOW_INDIVIDUAL_HEAD:
                case TRANSMOG_ACTION_SELECT_REMOVE_HEAD:
                    return EQUIPMENT_SLOT_HEAD;
                case TRANSMOG_ACTION_SHOW_INDIVIDUAL_SHOULDERS:
                case TRANSMOG_ACTION_SELECT_REMOVE_SHOULDERS:
                    return EQUIPMENT_SLOT_SHOULDERS;
                case TRANSMOG_ACTION_SHOW_INDIVIDUAL_CHEST:
                case TRANSMOG_ACTION_SELECT_REMOVE_CHEST:
                    return EQUIPMENT_SLOT_CHEST;
                case TRANSMOG_ACTION_SHOW_INDIVIDUAL_HANDS:
                case TRANSMOG_ACTION_SELECT_REMOVE_HANDS:
                    return EQUIPMENT_SLOT_HANDS;
                case TRANSMOG_ACTION_SHOW_INDIVIDUAL_LEGS:
                case TRANSMOG_ACTION_SELECT_REMOVE_LEGS:
                    return EQUIPMENT_SLOT_LEGS;
                case TRANSMOG_ACTION_SHOW_INDIVIDUAL_WRISTS:
                case TRANSMOG_ACTION_SELECT_REMOVE_WRISTS:
                    return EQUIPMENT_SLOT_WRISTS;
                case TRANSMOG_ACTION_SHOW_INDIVIDUAL_WAIST:
                case TRANSMOG_ACTION_SELECT_REMOVE_WAIST:
                    return EQUIPMENT_SLOT_WAIST;
                case TRANSMOG_ACTION_SHOW_INDIVIDUAL_BOOTS:
                case TRANSMOG_ACTION_SELECT_REMOVE_BOOTS:
                    return EQUIPMENT_SLOT_FEET;
                case TRANSMOG_ACTION_SHOW_INDIVIDUAL_MAINHAND:
                case TRANSMOG_ACTION_SELECT_REMOVE_MAINHAND:
                case TRANSMOG_ACTION_SELECT_REMOVE_MAINHAND_ENCHANT:
                    return EQUIPMENT_SLOT_MAINHAND;
                case TRANSMOG_ACTION_SHOW_INDIVIDUAL_OFFHAND:
                case TRANSMOG_ACTION_SELECT_REMOVE_OFFHAND:
                case TRANSMOG_ACTION_SELECT_REMOVE_OFFHAND_ENCHANT:
                    return EQUIPMENT_SLOT_OFFHAND;
                case TRANSMOG_ACTION_SHOW_INDIVIDUAL_RANGED:
                case TRANSMOG_ACTION_SELECT_REMOVE_RANGED:
                    return EQUIPMENT_SLOT_RANGED;
                default:
                    return NULL;
            }
        }
        static uint16 GetTransmogSlotByEquipSlot(uint8 slot)
        {
            switch (slot)
            {
                case EQUIPMENT_SLOT_HEAD:      return PLAYER_VISIBLE_ITEM_1_ENTRYID;
                case EQUIPMENT_SLOT_SHOULDERS: return PLAYER_VISIBLE_ITEM_3_ENTRYID;
                case EQUIPMENT_SLOT_CHEST:     return PLAYER_VISIBLE_ITEM_5_ENTRYID;
                case EQUIPMENT_SLOT_HANDS:     return PLAYER_VISIBLE_ITEM_10_ENTRYID;
                case EQUIPMENT_SLOT_LEGS:      return PLAYER_VISIBLE_ITEM_7_ENTRYID;
                case EQUIPMENT_SLOT_WRISTS:    return PLAYER_VISIBLE_ITEM_9_ENTRYID;
                case EQUIPMENT_SLOT_WAIST:     return PLAYER_VISIBLE_ITEM_6_ENTRYID;
                case EQUIPMENT_SLOT_FEET:      return PLAYER_VISIBLE_ITEM_8_ENTRYID;
                case EQUIPMENT_SLOT_MAINHAND:  return PLAYER_VISIBLE_ITEM_16_ENTRYID;
                case EQUIPMENT_SLOT_OFFHAND:   return PLAYER_VISIBLE_ITEM_17_ENTRYID;
                case EQUIPMENT_SLOT_RANGED:    return PLAYER_VISIBLE_ITEM_18_ENTRYID;
                default: return NULL;
            }
        }
};
