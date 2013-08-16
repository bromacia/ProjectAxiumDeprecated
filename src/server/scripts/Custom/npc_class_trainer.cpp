#include "ScriptPCH.h"

enum TrainerOptions
{
    TRAINER_LEARN_ALL_SPELLS = 1,
    TRAINER_LEARN_DUAL_SPEC,
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
            if (player->GetSpecsCount() < 2)
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "|TInterface\\icons\\achievement_general:30|t Learn Dual Specialization", GOSSIP_SENDER_MAIN, TRAINER_LEARN_DUAL_SPEC);
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
                case TRAINER_LEARN_DUAL_SPEC:
                    player->SetSaveTimer(sWorld->getIntConfig(CONFIG_INTERVAL_SAVE));
                    player->learnSpell(63644, false);
                    player->learnSpell(63645, false);
                    player->UpdateSpecCount(2);
                    player->SaveToDB();
                    player->CLOSE_GOSSIP_MENU();
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
                        player->InterruptMovement();
                        player->GetMotionMaster()->MoveFall();
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
            const TrainerSpellData* TrainerSpells = creature->GetTrainerSpells();
            if (!TrainerSpells)
            {
                ChatHandler(player).PSendSysMessage("Unable to find spell data");
                player->CLOSE_GOSSIP_MENU();
                return false;
            }

            // Prevent double save or save during learning spells
            player->SetSaveTimer(sWorld->getIntConfig(CONFIG_INTERVAL_SAVE));

            bool learnedSpells = false;

            for (TrainerSpellMap::const_iterator itr = TrainerSpells->spellList.begin(); itr != TrainerSpells->spellList.end(); ++itr)
            {
                const TrainerSpell* tSpell = &itr->second;
                uint32 spellId = tSpell->spell;

                if (player->HasSpell(spellId))
                    continue;

                if (!(tSpell->reqClass & player->getClassMask()))
                    continue;

                bool disabled = false;

                if (!player->IsSpellFitByClassAndRace(spellId))
                    disabled = true;

                if (uint32 firstSpell = sSpellMgr->GetFirstSpellInChain(spellId))
                    if (sSpellMgr->IsTalentSpell(firstSpell))
                        if (!player->HasSpell(firstSpell))
                            disabled = true;

                // Greater Blessing of Sanctuary
                if (!player->HasSpell(20911))
                    if (spellId == 25899)
                        disabled = true;

                // Mangle (Bear)
                if (!player->HasSpell(33878))
                    if (spellId == 33986 || spellId == 33987 ||
                        spellId == 48563 || spellId == 48564)
                            disabled = true;

                // Mangle (Cat)
                if (!player->HasSpell(33876))
                    if (spellId == 33982 || spellId == 33983 ||
                        spellId == 48565 || spellId == 48566)
                            disabled = true;

                player->addSpell(spellId, true, true, false, false, false, true);

                if (!disabled && player->IsInWorld())
                {
                    WorldPacket data(SMSG_LEARNED_SPELL, 6);
                    data << uint32(spellId);
                    data << uint16(0);
                    player->GetSession()->SendPacket(&data);
                }

                if (disabled)
                    player->removeSpell(spellId, true);

                if (!learnedSpells)
                    learnedSpells = true;
            }

            if (learnedSpells)
                player->SaveToDB();

            player->CLOSE_GOSSIP_MENU();
            return true;
        }

        bool ShowGlyphs(Player* player, Creature* creature)
        {
            const VendorItemData* items = creature->GetVendorItems();
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
                if (const VendorItem* vItem = items->GetItem(slot))
                {
                    if (const ItemTemplate* vItemTemplate = sObjectMgr->GetItemTemplate(vItem->item))
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
            const ItemTemplate* itemTemplate = sObjectMgr->GetItemTemplate(itemId);
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
