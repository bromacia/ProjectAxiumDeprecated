#include "ScriptPCH.h"

enum TrainerOptions
{
    TRAINER_LEARN_ALL_SPELLS = 1,
    TRAINER_RESET_TALENTS,
    TRAINER_RESET_HUNTER_PET_TALENTS,
    TRAINER_SHOW_GLYPHS,
    TRAINER_SETUP_SHADOW_DANCE,
    TRAINER_FINISH_SHADOW_DANCE,
};

class npc_class_trainer : public CreatureScript
{
    public:
        npc_class_trainer() : CreatureScript("npc_class_trainer") {}

        bool OnGossipHello(Player* player, Creature* creature)
        {
            player->PlayerTalkClass->ClearMenus();

            if (player->getClass() == CLASS_ROGUE && player->HasSpell(51713))
            {
                if (player->HasAura(51713) && player->GetAura(51713, player->GetGUID())->GetDuration() == -1)
                {
                        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "|TInterface\\icons\\achievement_reputation_01:30|t I'm Finished", GOSSIP_SENDER_MAIN, TRAINER_FINISH_SHADOW_DANCE);
                        player->SEND_GOSSIP_MENU(1, creature->GetGUID());
                        return true;
                }
                else
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "|TInterface\\icons\\ability_rogue_shadowdance:30|t Setup Shadow Dance Bar", GOSSIP_SENDER_MAIN, TRAINER_SETUP_SHADOW_DANCE);
            }
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "|TInterface\\icons\\spell_arcane_mindmastery:30|t Learn All Spells", GOSSIP_SENDER_MAIN, TRAINER_LEARN_ALL_SPELLS);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "|TInterface\\icons\\spell_arcane_focusedpower:30|t Reset Talents", GOSSIP_SENDER_MAIN, TRAINER_RESET_TALENTS);
            if (player->getClass() == CLASS_HUNTER)
                if (Pet* pet = player->GetPet())
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "|TInterface\\icons\\ability_hunter_aspectmastery:30|t Reset Talents", GOSSIP_SENDER_MAIN, TRAINER_RESET_HUNTER_PET_TALENTS);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "|TInterface\\icons\\inv_inscription_minorglyph00:30|t Buy Glyphs", GOSSIP_SENDER_MAIN, TRAINER_SHOW_GLYPHS);

            player->SEND_GOSSIP_MENU(1, creature->GetGUID());
            return true;
        }

        bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action)
        {
            player->PlayerTalkClass->ClearMenus();

            switch (action)
            {
                case TRAINER_LEARN_ALL_SPELLS:
                    LearnAllSpells(player, creature);
                    break;
                case TRAINER_RESET_TALENTS:
                    player->SendTalentWipeConfirm(creature->GetGUID());
                    player->CLOSE_GOSSIP_MENU();
                    break;
                case TRAINER_RESET_HUNTER_PET_TALENTS:
                    if (Pet* pet = player->GetPet())
                    {
                        Pet::resetTalentsForAllPetsOf(player, pet);
                        player->SendTalentsInfoData(true);
                    }
                    break;
                case TRAINER_SHOW_GLYPHS:
                    ShowGlyphs(player, creature);
                    break;
                case TRAINER_SETUP_SHADOW_DANCE:
                    if (player->HasSpell(51713))
                    {
                        player->SetControlled(true, UNIT_STATE_ROOT);
                        player->AddAura(2, player);
                        if (!player->HasAura(51713))
                            player->AddAura(51713, player);
                        if (Aura* ShadowDance = player->GetAura(51713, player->GetGUID()))
                            ShadowDance->SetDurationAndMaxDuration(-1);
                        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "|TInterface\\icons\\achievement_reputation_01:30|t I'm Finished", GOSSIP_SENDER_MAIN, TRAINER_FINISH_SHADOW_DANCE);
                        player->SEND_GOSSIP_MENU(1, creature->GetGUID());
                    }
                    break;
                case TRAINER_FINISH_SHADOW_DANCE:
                    player->SetControlled(false, UNIT_STATE_ROOT);
                    player->RemoveAura(2);
                    player->RemoveAura(51713);
                    OnGossipHello(player, creature);
                    break;
            }
            return false;
        }

        bool LearnAllSpells(Player* player, Creature* creature)
        {
            TrainerSpellData const* TrainerSpells = creature->GetTrainerSpells();
            if (!TrainerSpells)
            {
                ChatHandler(player).PSendSysMessage("Unable to find spell data");
                player->CLOSE_GOSSIP_MENU();
                return false;
            }

            for (TrainerSpellMap::const_iterator itr = TrainerSpells->spellList.begin(); itr != TrainerSpells->spellList.end(); ++itr)
            {
                TrainerSpell const* tSpell = &itr->second;

                if (player->getClass() != tSpell->reqClass)
                    continue;

                if (player->HasSpell(tSpell->spell))
                    continue;

                SpellInfo const* spellInfo = sSpellMgr->GetSpellInfo(tSpell->spell);
                if (!spellInfo || !SpellMgr::IsSpellValid(spellInfo, player))
                    continue;

                if (tSpell->IsCastable())
                    player->CastSpell(player, tSpell->spell, true);
                else
                    player->learnSpell(tSpell->spell, false);
            }

            player->CLOSE_GOSSIP_MENU();
            return true;
        }

        bool ShowGlyphs(Player* player, Creature* creature)
        {
            VendorItemData const* items = creature->GetVendorItems();
            if (!items)
            {
                ChatHandler(player).PSendSysMessage("Unable to find item data");
                player->SetSelectedTransmogItemSlot(NULL);
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
                if (VendorItem const* vItem = items->GetItem(slot))
                {
                    if (ItemTemplate const* vItemTemplate = sObjectMgr->GetItemTemplate(vItem->item))
                    {
                        if (!(vItemTemplate->AllowableClass & player->getClassMask()))
                            continue;

                        ++count;
                        data << uint32(count + 1);                      // Client expects counting to start at 1
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
                ChatHandler(player).PSendSysMessage("Unable to find item data");
                player->SetSelectedTransmogItemSlot(NULL);
                player->CLOSE_GOSSIP_MENU();
                return false;
            }

            data.put<uint8>(countPos, count);
            player->GetSession()->SendPacket(&data);
            return true;
        }

        static bool BuyGlyph(Player* player, Creature* creature, uint32 itemId)
        {
            ItemTemplate const* itemTemplate = sObjectMgr->GetItemTemplate(itemId);
            if (!itemTemplate)
                return false;

            uint8 count = 1;
            uint32 noSpaceForCount = 0;

            ItemPosCountVec dest;
            InventoryResult msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, itemId, count, &noSpaceForCount);
            if (msg != EQUIP_ERR_OK)
                count -= noSpaceForCount;

            if (count == 0 || dest.empty())
                return false;

            Item* item = player->StoreNewItem(dest, itemId, true, Item::GenerateItemRandomPropertyId(itemId));

            if (count > 0 && item)
                player->SendNewItem(item, count, false, true);
            return true;
        }
};

void AddSC_npc_class_trainer()
{
    new npc_class_trainer();
}
