#include "ScriptPCH.h"
#include "ScriptMgr.h"
#include "Pet.h"
#include "Formulas.h"

void CreatePet(Player* player, Creature* m_creature, uint32 entry)
{
    if(player->getClass() != CLASS_HUNTER)
    {
        m_creature->MonsterWhisper("You are not hunter.", player->GetGUID());
        player->CLOSE_GOSSIP_MENU();
        return;
    }

    if(player->GetPet())
    {
        m_creature->MonsterWhisper("First you must dismiss your pet.", player->GetGUID());
        player->CLOSE_GOSSIP_MENU();
        return;
    }

    Creature *creatureTarget = m_creature->SummonCreature(entry, player->GetPositionX(), player->GetPositionY()+2, player->GetPositionZ(), player->GetOrientation(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 500);
    if(!creatureTarget) return;

    Pet* pet = player->CreateTamedPetFrom(creatureTarget, 0);
    if(!pet) return;

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

    if(!pet->InitStatsForLevel(player->getLevel()))
    sLog->outError("Pet Create fail: no init stats for entry %u", entry);
    pet->UpdateAllStats();

    player->SetMinion(pet, true);

    pet->SavePetToDB(PET_SAVE_AS_CURRENT);
    pet->InitTalentForLevel();
    player->PetSpellInitialize();

    player->CLOSE_GOSSIP_MENU();
    m_creature->MonsterWhisper("Pet added.", player->GetGUID());
}

class npc_beastmaster : public CreatureScript
{
    public: npc_beastmaster() : CreatureScript("npc_beastmaster") { }

    bool OnGossipHello(Player* pPlayer, Creature* pCreature)
    {
        if(pPlayer->getClass() != CLASS_HUNTER)
        {
            pCreature->MonsterWhisper("You are not hunter.", pPlayer->GetGUID());
            return true;
        }

        pPlayer->ADD_GOSSIP_ITEM(4, "Pets", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 30);

        if (pPlayer->CanTameExoticPets())
        {
            pPlayer->ADD_GOSSIP_ITEM(4, "Exotic Pets", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 50);
        }

        pPlayer->ADD_GOSSIP_ITEM(2, "Stable", GOSSIP_SENDER_MAIN, GOSSIP_OPTION_STABLEPET);
        pPlayer->SEND_GOSSIP_MENU(1,pCreature->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player* pPlayer, Creature* pCreature, uint32 /*uiSender*/, uint32 uiAction)
    {
        ShowMenuItems(pPlayer, pCreature, uiAction);
        return true;
    }

    void ShowMenuItems(Player* pPlayer, Creature* pCreature, uint32 uiAction)
    {
        switch (uiAction)
        {
            case GOSSIP_ACTION_INFO_DEF + 100:
                pPlayer->PlayerTalkClass->ClearMenus();
                pPlayer->ADD_GOSSIP_ITEM(4, "Pets", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 30);

                if (pPlayer->CanTameExoticPets())
                {
                    pPlayer->ADD_GOSSIP_ITEM(4, "Exotic Pets", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 50);
                }

                pPlayer->ADD_GOSSIP_ITEM(2, "Stable", GOSSIP_SENDER_MAIN, GOSSIP_OPTION_STABLEPET);
                pPlayer->SEND_GOSSIP_MENU(1,pCreature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 30:
                pPlayer->PlayerTalkClass->ClearMenus();
                pPlayer->ADD_GOSSIP_ITEM(2, "<< Back to main menu", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 100);
                pPlayer->ADD_GOSSIP_ITEM(4, "Next page >>", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 31);
                pPlayer->ADD_GOSSIP_ITEM(6, "Bat - [Cunning]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
                pPlayer->ADD_GOSSIP_ITEM(6, "Bear - [Tenacity]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
                pPlayer->ADD_GOSSIP_ITEM(6, "Boar - [Tenacity]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
                pPlayer->ADD_GOSSIP_ITEM(6, "Cat - [Ferocity]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);
                pPlayer->ADD_GOSSIP_ITEM(6, "Carrion Bird - [Ferocity]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 5);
                pPlayer->ADD_GOSSIP_ITEM(6, "Crab - [Tenacity]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 6);
                pPlayer->ADD_GOSSIP_ITEM(6, "Crocolisk - [Tenacity]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 7);
                pPlayer->ADD_GOSSIP_ITEM(6, "Dragonhawk - [Cunning]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 8);
                pPlayer->ADD_GOSSIP_ITEM(6, "Gorilla - [Tenacity]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 9);
                pPlayer->ADD_GOSSIP_ITEM(6, "Hyena - [Ferocity]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 10);
                pPlayer->ADD_GOSSIP_ITEM(6, "Moth - [Ferocity]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 11);
                pPlayer->ADD_GOSSIP_ITEM(6, "Nether Ray - [Cunning]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 12);
                pPlayer->ADD_GOSSIP_ITEM(6, "Owl - [Cunning]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 13);
                pPlayer->SEND_GOSSIP_MENU(1,pCreature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 31:
                pPlayer->PlayerTalkClass->ClearMenus();
                pPlayer->ADD_GOSSIP_ITEM(2, "<< Back to main menu", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 100);
                pPlayer->ADD_GOSSIP_ITEM(4, "<< Previous page", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 30);
                pPlayer->ADD_GOSSIP_ITEM(6, "Raptor - [Ferocity]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 14);
                pPlayer->ADD_GOSSIP_ITEM(6, "Ravager - [Cunning]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 15);
                pPlayer->ADD_GOSSIP_ITEM(6, "Scorpid - [Tenacity]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 16);
                pPlayer->ADD_GOSSIP_ITEM(6, "Serpent - [Cunning]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 17);
                pPlayer->ADD_GOSSIP_ITEM(6, "Spider - [Cunning]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 18);
                pPlayer->ADD_GOSSIP_ITEM(6, "Spore Bat - [Cunning]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 19);
                pPlayer->ADD_GOSSIP_ITEM(6, "Tallstrider - [Ferocity]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 20);
                pPlayer->ADD_GOSSIP_ITEM(6, "Turtle - [Tenacity]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 21);
                pPlayer->ADD_GOSSIP_ITEM(6, "Warp Stalker - [Tenacity]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 22);
                pPlayer->ADD_GOSSIP_ITEM(6, "Wasp - [Ferocity]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 23);
                pPlayer->ADD_GOSSIP_ITEM(6, "Wind Serpent - [Cunning]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 24);
                pPlayer->ADD_GOSSIP_ITEM(6, "Wolf - [Ferocity]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 25);
                pPlayer->SEND_GOSSIP_MENU(1,pCreature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 50:
                pPlayer->PlayerTalkClass->ClearMenus();
                pPlayer->ADD_GOSSIP_ITEM(2, "<< Back to main menu", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 100);
                pPlayer->ADD_GOSSIP_ITEM(6, "Chimaera - [Cunning]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 51);
                pPlayer->ADD_GOSSIP_ITEM(6, "Core Hound - [Ferocity]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 52);
                pPlayer->ADD_GOSSIP_ITEM(6, "Devilsaur - [Ferocity]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 53);
                pPlayer->ADD_GOSSIP_ITEM(6, "Rhino - [Tenacity]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 54);
                pPlayer->ADD_GOSSIP_ITEM(6, "Silithid - [Cunning]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 55);
                pPlayer->ADD_GOSSIP_ITEM(6, "Worm - [Tenacity]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 56);
                pPlayer->ADD_GOSSIP_ITEM(6, "Loque'nahak - [Ferocity]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 57);
                pPlayer->ADD_GOSSIP_ITEM(6, "Skoll - [Ferocity]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 58);
                pPlayer->ADD_GOSSIP_ITEM(6, "Gondria - [Ferocity]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 59);
                pPlayer->SEND_GOSSIP_MENU(1,pCreature->GetGUID());
                break;
            case GOSSIP_OPTION_STABLEPET:
                pPlayer->CLOSE_GOSSIP_MENU();
                pPlayer->GetSession()->SendStablePet(pCreature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 1: // Bat
                CreatePet(pPlayer, pCreature, 26622);
                pPlayer->CLOSE_GOSSIP_MENU();
                break;
            case GOSSIP_ACTION_INFO_DEF + 2: // Bear
                CreatePet(pPlayer, pCreature, 24217);
                pPlayer->CLOSE_GOSSIP_MENU();
                break;
            case GOSSIP_ACTION_INFO_DEF + 3: // Boar
                CreatePet(pPlayer, pCreature, 4512);
                pPlayer->CLOSE_GOSSIP_MENU();
                break;
            case GOSSIP_ACTION_INFO_DEF + 4: // Cat
                CreatePet(pPlayer, pCreature, 10737);
                pPlayer->CLOSE_GOSSIP_MENU();
                break;
            case GOSSIP_ACTION_INFO_DEF + 5: // Carrion Bird
                CreatePet(pPlayer, pCreature, 21515);
                pPlayer->CLOSE_GOSSIP_MENU();
                break;
            case GOSSIP_ACTION_INFO_DEF + 6: // Crab
                CreatePet(pPlayer, pCreature, 2544);
                pPlayer->CLOSE_GOSSIP_MENU();
                break;
            case GOSSIP_ACTION_INFO_DEF + 7: // Crocolisk
                CreatePet(pPlayer, pCreature, 28002);
                pPlayer->CLOSE_GOSSIP_MENU();
                break;
            case GOSSIP_ACTION_INFO_DEF + 8: // Dragonhawk
                CreatePet(pPlayer, pCreature, 18155);
                pPlayer->CLOSE_GOSSIP_MENU();
                break;
            case GOSSIP_ACTION_INFO_DEF + 9: // Gorilla
                CreatePet(pPlayer, pCreature, 6585);
                pPlayer->CLOSE_GOSSIP_MENU();
                break;
            case GOSSIP_ACTION_INFO_DEF + 10: // Hynea
                CreatePet(pPlayer, pCreature, 8300);
                pPlayer->CLOSE_GOSSIP_MENU();
                break;
            case GOSSIP_ACTION_INFO_DEF + 11: // Moth
                CreatePet(pPlayer, pCreature, 20611);
                pPlayer->CLOSE_GOSSIP_MENU();
                break;
            case GOSSIP_ACTION_INFO_DEF + 12: // Nether Ray
                CreatePet(pPlayer, pCreature, 21901);
                pPlayer->CLOSE_GOSSIP_MENU();
                break;
            case GOSSIP_ACTION_INFO_DEF + 13: // Owl
                CreatePet(pPlayer, pCreature, 7456);
                pPlayer->CLOSE_GOSSIP_MENU();
                break;
            case GOSSIP_ACTION_INFO_DEF + 14: // Raptor
                CreatePet(pPlayer, pCreature, 21124);
                pPlayer->CLOSE_GOSSIP_MENU();
                break;
            case GOSSIP_ACTION_INFO_DEF + 15: // Ravager
                CreatePet(pPlayer, pCreature, 16934);
                pPlayer->CLOSE_GOSSIP_MENU();
                break;
            case GOSSIP_ACTION_INFO_DEF + 16: // Scorpid
                CreatePet(pPlayer, pCreature, 11735);
                pPlayer->CLOSE_GOSSIP_MENU();
                break;
            case GOSSIP_ACTION_INFO_DEF + 17: // Serpent
                CreatePet(pPlayer, pCreature, 19784);
                pPlayer->CLOSE_GOSSIP_MENU();
                break;
            case GOSSIP_ACTION_INFO_DEF + 18: // Spider
                CreatePet(pPlayer, pCreature, 17683);
                pPlayer->CLOSE_GOSSIP_MENU();
                break;
            case GOSSIP_ACTION_INFO_DEF + 19: // Spore Bat
                CreatePet(pPlayer, pCreature, 18128);
                pPlayer->CLOSE_GOSSIP_MENU();
                break;
            case GOSSIP_ACTION_INFO_DEF + 20: // Tallstrider
                CreatePet(pPlayer, pCreature, 3068);
                pPlayer->CLOSE_GOSSIP_MENU();
                break;
            case GOSSIP_ACTION_INFO_DEF + 21: // Turtle
                CreatePet(pPlayer, pCreature, 4397);
                pPlayer->CLOSE_GOSSIP_MENU();
                break;
            case GOSSIP_ACTION_INFO_DEF + 22: // Warp Stalker
                CreatePet(pPlayer, pCreature, 23163);
                pPlayer->CLOSE_GOSSIP_MENU();
                break;
            case GOSSIP_ACTION_INFO_DEF + 23: // Wasp
                CreatePet(pPlayer, pCreature, 20198);
                pPlayer->CLOSE_GOSSIP_MENU();
                break; 
            case GOSSIP_ACTION_INFO_DEF + 24: // Wind Serpent
                CreatePet(pPlayer, pCreature, 28477);
                pPlayer->CLOSE_GOSSIP_MENU();
                break;
            case GOSSIP_ACTION_INFO_DEF + 25: // Wolf
                CreatePet(pPlayer, pCreature, 17280);
                pPlayer->CLOSE_GOSSIP_MENU();
                break;
            case GOSSIP_ACTION_INFO_DEF + 51: // Chimaera
                CreatePet(pPlayer, pCreature, 20932);
                pPlayer->CLOSE_GOSSIP_MENU();
                break;
            case GOSSIP_ACTION_INFO_DEF + 52: // Core Hound
                CreatePet(pPlayer, pCreature, 21108);
                pPlayer->CLOSE_GOSSIP_MENU();
                break;
            case GOSSIP_ACTION_INFO_DEF + 53: // Devilsaur
                CreatePet(pPlayer, pCreature, 20931);
                pPlayer->CLOSE_GOSSIP_MENU();
                break;
            case GOSSIP_ACTION_INFO_DEF + 54: // Rhino
                CreatePet(pPlayer, pCreature, 30445);
                pPlayer->CLOSE_GOSSIP_MENU();
                break;
            case GOSSIP_ACTION_INFO_DEF + 55: // Silithid
                CreatePet(pPlayer, pCreature, 14473);
                pPlayer->CLOSE_GOSSIP_MENU();
                break;
            case GOSSIP_ACTION_INFO_DEF + 56: // Worm
                CreatePet(pPlayer, pCreature, 26359);
                pPlayer->CLOSE_GOSSIP_MENU();
                break;
            case GOSSIP_ACTION_INFO_DEF + 57: // Loque'nahak
                CreatePet(pPlayer, pCreature, 32517);
                pPlayer->CLOSE_GOSSIP_MENU();
                break;
            case GOSSIP_ACTION_INFO_DEF + 58: // Skoll
                CreatePet(pPlayer, pCreature, 35189);
                pPlayer->CLOSE_GOSSIP_MENU();
                break;
            case GOSSIP_ACTION_INFO_DEF + 59: // Gondria
                CreatePet(pPlayer, pCreature, 33776);
                pPlayer->CLOSE_GOSSIP_MENU();
                break;
        }
    }
};
 
void AddSC_npc_beastmaster()
{
    new npc_beastmaster();
}