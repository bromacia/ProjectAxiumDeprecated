#include "ScriptPCH.h"
#include "ScriptMgr.h"
#include "Pet.h"
#include "Formulas.h"

void CreatePet(Player* player, Creature* creature, uint32 entry)
{
    if (player->getClass() != CLASS_HUNTER)
    {
        creature->MonsterWhisper("You are not hunter.", player->GetGUID());
        player->CLOSE_GOSSIP_MENU();
        return;
    }

    if (player->GetPet())
    {
        creature->MonsterWhisper("First you must dismiss your pet.", player->GetGUID());
        player->CLOSE_GOSSIP_MENU();
        return;
    }

    Creature* creatureTarget = creature->SummonCreature(entry, player->GetPositionX(), player->GetPositionY()+2, player->GetPositionZ(), player->GetOrientation(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 500);
    if (!creatureTarget)
        return;

    Pet* pet = player->CreateTamedPetFrom(creatureTarget, 0);
    if (!pet)
        return;

    // Kill original creature
    creatureTarget->setDeathState(JUST_DIED);
    creatureTarget->RemoveCorpse();
    creatureTarget->SetHealth(0);

    pet->SetPower(POWER_HAPPINESS, 1048000);

    // Prepare visual effect for Level Up
    pet->SetUInt32Value(UNIT_FIELD_LEVEL, player->getLevel() - 1);
    pet->GetMap()->AddToMap((Creature*)pet);
    // Visual effect for Level Up
    pet->SetUInt32Value(UNIT_FIELD_LEVEL, player->getLevel());

    if (!pet->InitStatsForLevel(player->getLevel()))
        sLog->outError("Pet Create fail: no init stats for entry %u", entry);

    pet->UpdateAllStats();

    player->SetMinion(pet, true);

    pet->SavePetToDB(PET_SAVE_AS_CURRENT);
    pet->InitTalentForLevel();
    player->PetSpellInitialize();

    player->CLOSE_GOSSIP_MENU();
    creature->MonsterWhisper("Pet added.", player->GetGUID());
}

class npc_beastmaster : public CreatureScript
{
    public: npc_beastmaster() : CreatureScript("npc_beastmaster") { }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (player->getClass() != CLASS_HUNTER)
        {
            creature->MonsterWhisper("You are not hunter.", player->GetGUID());
            return true;
        }

        player->ADD_GOSSIP_ITEM(4, "Pets", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 30);

        if (player->CanTameExoticPets())
        {
            player->ADD_GOSSIP_ITEM(4, "Exotic Pets", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 50);
        }

        player->ADD_GOSSIP_ITEM(2, "Stable", GOSSIP_SENDER_MAIN, GOSSIP_OPTION_STABLEPET);
        player->SEND_GOSSIP_MENU(1,creature->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 /*uiSender*/, uint32 uiAction)
    {
        ShowMenuItems(player, creature, uiAction);
        return true;
    }

    void ShowMenuItems(Player* player, Creature* creature, uint32 uiAction)
    {
        switch (uiAction)
        {
            case GOSSIP_ACTION_INFO_DEF + 100:
                player->PlayerTalkClass->ClearMenus();
                player->ADD_GOSSIP_ITEM(4, "Pets", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 30);

                if (player->CanTameExoticPets())
                {
                    player->ADD_GOSSIP_ITEM(4, "Exotic Pets", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 50);
                }

                player->ADD_GOSSIP_ITEM(2, "Stable", GOSSIP_SENDER_MAIN, GOSSIP_OPTION_STABLEPET);
                player->SEND_GOSSIP_MENU(1,creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 30:
                player->PlayerTalkClass->ClearMenus();
                player->ADD_GOSSIP_ITEM(2, "<< Back to main menu", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 100);
                player->ADD_GOSSIP_ITEM(4, "Next page >>", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 31);
                player->ADD_GOSSIP_ITEM(6, "Bat - [Cunning]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
                player->ADD_GOSSIP_ITEM(6, "Bear - [Tenacity]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
                player->ADD_GOSSIP_ITEM(6, "Boar - [Tenacity]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
                player->ADD_GOSSIP_ITEM(6, "Cat - [Ferocity]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);
                player->ADD_GOSSIP_ITEM(6, "Carrion Bird - [Ferocity]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 5);
                player->ADD_GOSSIP_ITEM(6, "Crab - [Tenacity]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 6);
                player->ADD_GOSSIP_ITEM(6, "Crocolisk - [Tenacity]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 7);
                player->ADD_GOSSIP_ITEM(6, "Dragonhawk - [Cunning]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 8);
                player->ADD_GOSSIP_ITEM(6, "Gorilla - [Tenacity]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 9);
                player->ADD_GOSSIP_ITEM(6, "Hyena - [Ferocity]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 10);
                player->ADD_GOSSIP_ITEM(6, "Moth - [Ferocity]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 11);
                player->ADD_GOSSIP_ITEM(6, "Nether Ray - [Cunning]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 12);
                player->ADD_GOSSIP_ITEM(6, "Owl - [Cunning]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 13);
                player->SEND_GOSSIP_MENU(1,creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 31:
                player->PlayerTalkClass->ClearMenus();
                player->ADD_GOSSIP_ITEM(2, "<< Back to main menu", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 100);
                player->ADD_GOSSIP_ITEM(4, "<< Previous page", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 30);
                player->ADD_GOSSIP_ITEM(6, "Raptor - [Ferocity]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 14);
                player->ADD_GOSSIP_ITEM(6, "Ravager - [Cunning]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 15);
                player->ADD_GOSSIP_ITEM(6, "Scorpid - [Tenacity]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 16);
                player->ADD_GOSSIP_ITEM(6, "Serpent - [Cunning]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 17);
                player->ADD_GOSSIP_ITEM(6, "Spider - [Cunning]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 18);
                player->ADD_GOSSIP_ITEM(6, "Spore Bat - [Cunning]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 19);
                player->ADD_GOSSIP_ITEM(6, "Tallstrider - [Ferocity]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 20);
                player->ADD_GOSSIP_ITEM(6, "Turtle - [Tenacity]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 21);
                player->ADD_GOSSIP_ITEM(6, "Warp Stalker - [Tenacity]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 22);
                player->ADD_GOSSIP_ITEM(6, "Wasp - [Ferocity]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 23);
                player->ADD_GOSSIP_ITEM(6, "Wind Serpent - [Cunning]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 24);
                player->ADD_GOSSIP_ITEM(6, "Wolf - [Ferocity]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 25);
                player->SEND_GOSSIP_MENU(1,creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 50:
                player->PlayerTalkClass->ClearMenus();
                player->ADD_GOSSIP_ITEM(2, "<< Back to main menu", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 100);
                player->ADD_GOSSIP_ITEM(6, "Chimaera - [Cunning]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 51);
                player->ADD_GOSSIP_ITEM(6, "Core Hound - [Ferocity]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 52);
                player->ADD_GOSSIP_ITEM(6, "Devilsaur - [Ferocity]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 53);
                player->ADD_GOSSIP_ITEM(6, "Rhino - [Tenacity]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 54);
                player->ADD_GOSSIP_ITEM(6, "Silithid - [Cunning]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 55);
                player->ADD_GOSSIP_ITEM(6, "Worm - [Tenacity]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 56);
                player->ADD_GOSSIP_ITEM(6, "Loque'nahak - [Ferocity]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 57);
                player->ADD_GOSSIP_ITEM(6, "Skoll - [Ferocity]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 58);
                player->ADD_GOSSIP_ITEM(6, "Gondria - [Ferocity]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 59);
                player->SEND_GOSSIP_MENU(1,creature->GetGUID());
                break;
            case GOSSIP_OPTION_STABLEPET:
                player->CLOSE_GOSSIP_MENU();
                player->GetSession()->SendStablePet(creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 1: // Bat
                CreatePet(player, creature, 26622);
                player->CLOSE_GOSSIP_MENU();
                break;
            case GOSSIP_ACTION_INFO_DEF + 2: // Bear
                CreatePet(player, creature, 24217);
                player->CLOSE_GOSSIP_MENU();
                break;
            case GOSSIP_ACTION_INFO_DEF + 3: // Boar
                CreatePet(player, creature, 4512);
                player->CLOSE_GOSSIP_MENU();
                break;
            case GOSSIP_ACTION_INFO_DEF + 4: // Cat
                CreatePet(player, creature, 10737);
                player->CLOSE_GOSSIP_MENU();
                break;
            case GOSSIP_ACTION_INFO_DEF + 5: // Carrion Bird
                CreatePet(player, creature, 21515);
                player->CLOSE_GOSSIP_MENU();
                break;
            case GOSSIP_ACTION_INFO_DEF + 6: // Crab
                CreatePet(player, creature, 2544);
                player->CLOSE_GOSSIP_MENU();
                break;
            case GOSSIP_ACTION_INFO_DEF + 7: // Crocolisk
                CreatePet(player, creature, 28002);
                player->CLOSE_GOSSIP_MENU();
                break;
            case GOSSIP_ACTION_INFO_DEF + 8: // Dragonhawk
                CreatePet(player, creature, 18155);
                player->CLOSE_GOSSIP_MENU();
                break;
            case GOSSIP_ACTION_INFO_DEF + 9: // Gorilla
                CreatePet(player, creature, 6585);
                player->CLOSE_GOSSIP_MENU();
                break;
            case GOSSIP_ACTION_INFO_DEF + 10: // Hynea
                CreatePet(player, creature, 8300);
                player->CLOSE_GOSSIP_MENU();
                break;
            case GOSSIP_ACTION_INFO_DEF + 11: // Moth
                CreatePet(player, creature, 20611);
                player->CLOSE_GOSSIP_MENU();
                break;
            case GOSSIP_ACTION_INFO_DEF + 12: // Nether Ray
                CreatePet(player, creature, 21901);
                player->CLOSE_GOSSIP_MENU();
                break;
            case GOSSIP_ACTION_INFO_DEF + 13: // Owl
                CreatePet(player, creature, 7456);
                player->CLOSE_GOSSIP_MENU();
                break;
            case GOSSIP_ACTION_INFO_DEF + 14: // Raptor
                CreatePet(player, creature, 21124);
                player->CLOSE_GOSSIP_MENU();
                break;
            case GOSSIP_ACTION_INFO_DEF + 15: // Ravager
                CreatePet(player, creature, 16934);
                player->CLOSE_GOSSIP_MENU();
                break;
            case GOSSIP_ACTION_INFO_DEF + 16: // Scorpid
                CreatePet(player, creature, 11735);
                player->CLOSE_GOSSIP_MENU();
                break;
            case GOSSIP_ACTION_INFO_DEF + 17: // Serpent
                CreatePet(player, creature, 19784);
                player->CLOSE_GOSSIP_MENU();
                break;
            case GOSSIP_ACTION_INFO_DEF + 18: // Spider
                CreatePet(player, creature, 17683);
                player->CLOSE_GOSSIP_MENU();
                break;
            case GOSSIP_ACTION_INFO_DEF + 19: // Spore Bat
                CreatePet(player, creature, 18128);
                player->CLOSE_GOSSIP_MENU();
                break;
            case GOSSIP_ACTION_INFO_DEF + 20: // Tallstrider
                CreatePet(player, creature, 3068);
                player->CLOSE_GOSSIP_MENU();
                break;
            case GOSSIP_ACTION_INFO_DEF + 21: // Turtle
                CreatePet(player, creature, 4397);
                player->CLOSE_GOSSIP_MENU();
                break;
            case GOSSIP_ACTION_INFO_DEF + 22: // Warp Stalker
                CreatePet(player, creature, 23163);
                player->CLOSE_GOSSIP_MENU();
                break;
            case GOSSIP_ACTION_INFO_DEF + 23: // Wasp
                CreatePet(player, creature, 20198);
                player->CLOSE_GOSSIP_MENU();
                break; 
            case GOSSIP_ACTION_INFO_DEF + 24: // Wind Serpent
                CreatePet(player, creature, 28477);
                player->CLOSE_GOSSIP_MENU();
                break;
            case GOSSIP_ACTION_INFO_DEF + 25: // Wolf
                CreatePet(player, creature, 17280);
                player->CLOSE_GOSSIP_MENU();
                break;
            case GOSSIP_ACTION_INFO_DEF + 51: // Chimaera
                CreatePet(player, creature, 20932);
                player->CLOSE_GOSSIP_MENU();
                break;
            case GOSSIP_ACTION_INFO_DEF + 52: // Core Hound
                CreatePet(player, creature, 21108);
                player->CLOSE_GOSSIP_MENU();
                break;
            case GOSSIP_ACTION_INFO_DEF + 53: // Devilsaur
                CreatePet(player, creature, 20931);
                player->CLOSE_GOSSIP_MENU();
                break;
            case GOSSIP_ACTION_INFO_DEF + 54: // Rhino
                CreatePet(player, creature, 30445);
                player->CLOSE_GOSSIP_MENU();
                break;
            case GOSSIP_ACTION_INFO_DEF + 55: // Silithid
                CreatePet(player, creature, 14473);
                player->CLOSE_GOSSIP_MENU();
                break;
            case GOSSIP_ACTION_INFO_DEF + 56: // Worm
                CreatePet(player, creature, 26359);
                player->CLOSE_GOSSIP_MENU();
                break;
            case GOSSIP_ACTION_INFO_DEF + 57: // Loque'nahak
                CreatePet(player, creature, 32517);
                player->CLOSE_GOSSIP_MENU();
                break;
            case GOSSIP_ACTION_INFO_DEF + 58: // Skoll
                CreatePet(player, creature, 35189);
                player->CLOSE_GOSSIP_MENU();
                break;
            case GOSSIP_ACTION_INFO_DEF + 59: // Gondria
                CreatePet(player, creature, 33776);
                player->CLOSE_GOSSIP_MENU();
                break;
        }
    }
};
 
void AddSC_npc_beastmaster()
{
    new npc_beastmaster();
}