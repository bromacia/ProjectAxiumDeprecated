#include "ScriptPCH.h"

enum TrainerOptions
{
    TRAINER_LEARN_ALL_SPELLS = 1,
    TRAINER_RESET_TALENTS,
    TRAINER_RESET_HUNTER_PET_TALENTS,
    TRAINER_BUY_GLYPHS,
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
                if (player->HasAura(51713) && player->GetAura(51713, player->GetGUID())->GetDuration() == -1)
                {
                        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "|TInterface\\icons\\achievement_reputation_01:30|t Im Finished", GOSSIP_SENDER_MAIN, TRAINER_FINISH_SHADOW_DANCE);
                        player->SEND_GOSSIP_MENU(1, creature->GetGUID());
                        return true;
                }
                else
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "|TInterface\\icons\\ability_rogue_shadowdance:30|t Setup Shadow Dance Bar", GOSSIP_SENDER_MAIN, TRAINER_SETUP_SHADOW_DANCE);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "|TInterface\\icons\\spell_arcane_mindmastery:30|t Learn All Spells", GOSSIP_SENDER_MAIN, TRAINER_LEARN_ALL_SPELLS);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "|TInterface\\icons\\spell_arcane_focusedpower:30|t Reset Talents", GOSSIP_SENDER_MAIN, TRAINER_RESET_TALENTS);
            if (player->getClass() == CLASS_HUNTER)
                if (Pet* pet = player->GetPet())
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "|TInterface\\icons\\ability_hunter_aspectmastery:30|t Reset Talents", GOSSIP_SENDER_MAIN, TRAINER_RESET_HUNTER_PET_TALENTS);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "|TInterface\\icons\\inv_inscription_minorglyph00:30|t Buy Glyphs", GOSSIP_SENDER_MAIN, TRAINER_BUY_GLYPHS);

            player->SEND_GOSSIP_MENU(1, creature->GetGUID());
            return true;
        }

        bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action)
        {
            player->PlayerTalkClass->ClearMenus();

            switch (action)
            {
                case TRAINER_LEARN_ALL_SPELLS:
                    LearnAllSpells(player, creature, sender, action);
                    break;
                case TRAINER_RESET_TALENTS:
                    player->resetTalents(true);
                    player->SendTalentsInfoData(false);
                    break;
                case TRAINER_RESET_HUNTER_PET_TALENTS:
                    if (Pet* pet = player->GetPet())
                    {
                        Pet::resetTalentsForAllPetsOf(player, pet);
                        player->SendTalentsInfoData(true);
                    }
                    break;
                case TRAINER_BUY_GLYPHS:
                    ShowGlyphs(player, creature, sender, action);
                    break;
                case TRAINER_SETUP_SHADOW_DANCE:
                    if (player->HasSpell(51713))
                    {
                        player->SetControlled(true, UNIT_STATE_ROOT);
                        player->AddAura(2, player);
                        if (!player->HasAura(51713))
                            player->AddAura(51713, player);
                        if (Aura* shadowdance = player->GetAura(51713, player->GetGUID()))
                            shadowdance->SetDurationAndMaxDuration(-1);
                        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "|TInterface\\icons\\achievement_reputation_01:30|t Im Finished", GOSSIP_SENDER_MAIN, TRAINER_FINISH_SHADOW_DANCE);
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

        bool LearnAllSpells(Player* player, Creature* creature, uint32 sender, uint32 action)
        {
            return true;
        }

        bool ShowGlyphs(Player* player, Creature* creature, uint32 sender, uint32 action)
        {
            return true;
        }

        bool BuyGlyphs(Player* player, Creature* creature, uint32 sender, uint32 action)
        {
            return true;
        }
};

void AddSC_npc_class_trainer()
{
    new npc_class_trainer();
}
