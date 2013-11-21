#include "ScriptedGossip.h"
#include "Creature.h"
#include "Player.h"
#include "Chat.h"
#include "Item.h"
#include "ItemPrototype.h"
#include "ObjectMgr.h"
#include "WorldPacket.h"
#include "WorldSession.h"

#define CONVERSION_RATE_ARENA_POINTS 5
#define CONVERSION_RATE_HONOR_POINTS 250

enum GossipOptions
{
    OPTION_SHOW_GADGETS = 2,
    OPTION_SHOW_271_GEAR,
    OPTION_CONVERT_TOKENS,
    OPTION_RANDOM_TELEPORT,
};

class npc_world_pvp : public CreatureScript
{
    public:
        npc_world_pvp() : CreatureScript("WorldPvPNPC") {}

        bool OnGossipHello(Player* player, Creature* creature)
        {
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Gadgets", GOSSIP_SENDER_MAIN, OPTION_SHOW_GADGETS);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TABARD, "271 Gear", GOSSIP_SENDER_MAIN, OPTION_SHOW_271_GEAR);
            player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_VENDOR, "Convert Tokens", GOSSIP_SENDER_MAIN, OPTION_CONVERT_TOKENS, "", 0, true);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "Teleport to a Random Location", GOSSIP_SENDER_MAIN, OPTION_RANDOM_TELEPORT);
            player->SEND_GOSSIP_MENU(1, creature->GetGUID());
            return true;
        }

        bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action)
        {
            player->PlayerTalkClass->ClearMenus();

            switch (sender)
            {
                case GOSSIP_SENDER_MAIN:
                {
                    switch (action)
                    {
                        case OPTION_SHOW_GADGETS:    ShowInventory(player, creature, OPTION_SHOW_GADGETS);         break;
                        case OPTION_SHOW_271_GEAR:   ShowInventory(player, creature, OPTION_SHOW_271_GEAR);        break;
                        case OPTION_RANDOM_TELEPORT: HandleRandomTeleport(player);                                 break;
                    }

                    break;
                }
            }

            return true;
        }

        bool OnGossipSelectCode(Player* player, Creature* creature, uint32 sender, uint32 action, const char* code)
        {
            player->PlayerTalkClass->ClearMenus();

            switch (action)
            {
                case OPTION_CONVERT_TOKENS:
                {
                    ChatHandler* handler = new ChatHandler(player);

                    player->CLOSE_GOSSIP_MENU();

                    if (!isNumeric(code))
                    {
                        handler->PSendSysMessage("Invalid Number; Please try again.");
                        return false;
                    }

                    uint32 amount = atoi(code);

                    if (!amount || amount > 2000000)
                    {
                        handler->PSendSysMessage("The amount of tokens to convert must be a number between 0 and 2,000,000.");
                        return false;
                    }

                    uint32 amountInBags = player->GetItemCount(43589);
                    uint32 arenaPoints = 0;
                    uint32 honorPoints = 0;

                    if (amount > amountInBags)
                    {
                        player->DestroyItemCount(43589, amountInBags, true);
                        arenaPoints = CONVERSION_RATE_ARENA_POINTS * amountInBags;
                        player->ModifyArenaPoints(arenaPoints);
                        honorPoints = CONVERSION_RATE_HONOR_POINTS * amountInBags;
                        player->ModifyHonorPoints(honorPoints);
                        handler->PSendSysMessage("Converted %u tokens into %u Arena Points and %u Honor Points.", amountInBags, arenaPoints, honorPoints);
                    }
                    else
                    {
                        player->DestroyItemCount(43589, amount, true);
                        arenaPoints = CONVERSION_RATE_ARENA_POINTS * amount;
                        player->ModifyArenaPoints(arenaPoints);
                        honorPoints = CONVERSION_RATE_HONOR_POINTS * amount;
                        player->ModifyHonorPoints(honorPoints);
                        handler->PSendSysMessage("Converted %u tokens into %u Arena Points and %u Honor Points.", amount, arenaPoints, honorPoints);
                    }
                    break;
                }
            }

            return true;
        }

        void ShowInventory(Player* player, Creature* creature, uint32 option)
        {
            ChatHandler* handler = new ChatHandler(player);

            player->CLOSE_GOSSIP_MENU();

            const VendorItemData* items = creature->GetVendorItems();
            if (!items)
            {
                handler->PSendSysMessage("This npc doesn't have any items.");
                return;
            }

            uint16 itemCount = items->GetItemCount();
            uint8 count = 0;
            uint8 slot = 0;

            WorldPacket data(SMSG_LIST_INVENTORY, 8 + 1 + itemCount * 8 * 4);
            data << uint64(creature->GetGUID());
            size_t countPos = data.wpos();
            data << uint8(count);

            for (uint16 slot = 0; slot < itemCount; ++slot)
            {
                if (const VendorItem* vItem = items->GetItemByVendorSlot(slot))
                {
                    if (const ItemTemplate* vItemTemplate = sObjectMgr->GetItemTemplate(vItem->item))
                    {
                        if (!CheckItemType(vItemTemplate, option))
                            continue;

                        int32 leftInStock = 0xFFFFFFFF; // The item will appear normally

                        if (!CheckItemCost(vItemTemplate))
                            leftInStock = 0x0; // The item will appear greyed out

                        ++count;
                        data << uint32(slot + 1);                       // Client expects counting to start at 1
                        data << uint32(vItem->item);                    // Entry
                        data << uint32(vItemTemplate->DisplayInfoID);   // DisplayId
                        data << int32(leftInStock);                     // Left in stock
                        data << uint32(0);                              // Price
                        data << uint32(vItemTemplate->MaxDurability);   // Durability
                        data << uint32(vItemTemplate->BuyCount);        // Buy Count
                        data << uint32(0);                              // Extended Cost

                    }
                }
            }

            if (!count)
            {
                handler->PSendSysMessage("No items found for that option.");
                return;
            }

            data.put<uint8>(countPos, count);
            player->GetSession()->SendPacket(&data);
        }

        bool CheckItemType(const ItemTemplate* itemTemplate, uint32 option)
        {
            switch (option)
            {
                case OPTION_SHOW_GADGETS:
                {
                    if (itemTemplate->Class != ITEM_CLASS_CONSUMABLE)
                        return false;

                    break;
                }
                case OPTION_SHOW_271_GEAR:
                {
                    if (itemTemplate->Class != ITEM_CLASS_ARMOR)
                        return false;

                    break;
                }
            }

            return true;
        }

        bool CheckItemCost(const ItemTemplate* itemTemplate)
        {
            return true;
        }

        void HandleRandomTeleport(Player* player)
        {
            LoadTeleportLocations();
            player->TeleportTo(*locations[urand(0, locations.size())]);
        }

        void LoadItemCosts()
        {
        }

        void LoadTeleportLocations()
        {
            locations.push_back(new WorldLocation(530, 821.72f, 5227.23f, 23.49f, 2.65f));
            locations.push_back(new WorldLocation(530, 822.51f, 5488.22f, 11.37f, 3.81f));
            locations.push_back(new WorldLocation(530, 423.51f, 5376.16f, 19.86f, 6.28f));
            locations.push_back(new WorldLocation(530, 85.48f, 5232.76f, 22.44f, 2.32f));
            locations.push_back(new WorldLocation(530, 204.46f, 5526.36f, 20.40f, 3.42f));
            locations.push_back(new WorldLocation(530, -254.36f, 5502.50f, 66.60f, 0.52f));
            locations.push_back(new WorldLocation(530, -858.74f, 5557.39f, 23.20f, 4.08f));
            locations.push_back(new WorldLocation(530, -825.02f, 5785.34f, 22.95f, 1.20f));
            locations.push_back(new WorldLocation(530, -576.04f, 6118.05f, 34.17f, 6.03f));
            locations.push_back(new WorldLocation(530, -339.08f, 5904.12f, 22.72f, 1.46f));
            locations.push_back(new WorldLocation(530, -273.66f, 6389.34f, 23.82f, 0.83f));
            locations.push_back(new WorldLocation(530, 56.54f, 6073.44f, 23.48f, 0.58f));
            locations.push_back(new WorldLocation(530, 571.48f, 6030.98f, 23.35f, 2.40f));
            locations.push_back(new WorldLocation(530, 499.47f, 6618.85f, 24.49f, 2.20f));
            locations.push_back(new WorldLocation(530, 285.49f, 6443.62f, 24.19f, 2.34f));
            locations.push_back(new WorldLocation(530, 251.83f, 5807.13f, 20.01f, 1.45f));
            locations.push_back(new WorldLocation(530, -76.46f, 5739.16f, 19.81f, 2.52f));
            locations.push_back(new WorldLocation(530, 590.99f, 5726.24f, 23.12f, 2.93f));
            locations.push_back(new WorldLocation(530, -515.72f, 5513.48f, 24.14f, 1.50f));
            locations.push_back(new WorldLocation(530, -1102.86f, 5198.18f, 57.20f, 0.69f));
            locations.push_back(new WorldLocation(530, -98.06f, 6215.40f, 23.86f, 1.23f));
            locations.push_back(new WorldLocation(530, 757.10f, 6328.82f, 22.36f, 2.85f));
            locations.push_back(new WorldLocation(530, 96.50f, 6610.24f, 21.56f, 0.71f));
            locations.push_back(new WorldLocation(530, -92.06f, 6481.50f, 20.64f, 1.33f));
            locations.push_back(new WorldLocation(530, -252.01f, 6669.28f, 21.80f, 0.62f));
            locations.push_back(new WorldLocation(530, -170.92f, 6851.39f, 22.25f, 0.37f));
            locations.push_back(new WorldLocation(530, 137.40f, 6834.44f, 23.67f, 2.82f));
            locations.push_back(new WorldLocation(530, 800.97f, 6803.94f, 21.53f, 3.12f));
            locations.push_back(new WorldLocation(530, 492.71f, 6952.27f, 22.74f, 6.28f));
            locations.push_back(new WorldLocation(530, 763.14f, 7175.59f, 22.44f, 3.08f));
            locations.push_back(new WorldLocation(530, 955.07f, 7373.71f, 27.92f, 2.94f));
            locations.push_back(new WorldLocation(530, 517.46f, 7395.41f, 26.10f, 3.58f));
            locations.push_back(new WorldLocation(530, 727.40f, 7422.81f, 23.44f, 3.85f));
            locations.push_back(new WorldLocation(530, 252.58f, 7483.30f, 24.09f, 5.26f));
            locations.push_back(new WorldLocation(530, 89.32f, 7173.18f, 23.19f, 2.93f));
            locations.push_back(new WorldLocation(530, -62.61f, 6985.07f, 19.07f, 3.20f));
            locations.push_back(new WorldLocation(530, -292.33f, 6918.30f, 22.68f, 0.36f));
            locations.push_back(new WorldLocation(530, -39.57f, 7315.69f, 23.10f, 6.25f));
            locations.push_back(new WorldLocation(530, -170.70f, 7587.23f, 24.65f, 1.00f));
            locations.push_back(new WorldLocation(530, -11.47f, 7659.88f, 21.84f, 0.17f));
            locations.push_back(new WorldLocation(530, 319.33f, 7749.21f, 22.43f, 6.28f));
            locations.push_back(new WorldLocation(530, 535.06f, 7685.40f, 17.38f, .018f));
            locations.push_back(new WorldLocation(530, 874.73f, 7705.78f, 22.78f, 3.58f));
            locations.push_back(new WorldLocation(530, 743.84f, 7688.42f, 26.62f, 2.97f));
            locations.push_back(new WorldLocation(530, 1208.41f, 7776.21f, 30.56f, 3.17f));
            locations.push_back(new WorldLocation(530, 1001.15f, 7957.99f, 28.09f, 2.67f));
            locations.push_back(new WorldLocation(530, 675.12f, 8090.81f, 26.76f, 3.60f));
            locations.push_back(new WorldLocation(530, 389.66f, 8002.01f, 23.10f, 3.55f));
            locations.push_back(new WorldLocation(530, -171.56f, 7991.64f, 41.55f, 2.00f));
            locations.push_back(new WorldLocation(530, -195.92f, 8196.46f, 20.20f, 6.18f));
            locations.push_back(new WorldLocation(530, -221.30f, 8600.51f, 21.07f, 0.14f));
            locations.push_back(new WorldLocation(530, -25.45f, 8492.29f, 23.12f, 2.02f));
            locations.push_back(new WorldLocation(530, 189.34f, 8772.22f, 22.46f, 3.55f));
            locations.push_back(new WorldLocation(530, 350.17f, 8511.57f, 21.46f, 5.08f));
            locations.push_back(new WorldLocation(530, 791.44f, 8440.83f, 20.08f, 4.30f));
            locations.push_back(new WorldLocation(530, -68.62f, 8994.41f, 22.42f, 4.78f));
            locations.push_back(new WorldLocation(530, 1789.79f, 8499.70f, -14.99f, 3.60f));
            locations.push_back(new WorldLocation(530, 1171.95f, 8428.23f, 60.46f, 3.51f));
            locations.push_back(new WorldLocation(530, 159.31f, 8164.48f, 23.34f, 3.86f));
            locations.push_back(new WorldLocation(530, 510.47f, 6994.56f, 79.42f, 3.08f));
        }

    private:
        std::vector<WorldLocation*> locations;
};

void AddSC_npc_world_pvp()
{
    new npc_world_pvp;
}
