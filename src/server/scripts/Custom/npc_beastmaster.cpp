#include "ScriptPCH.h"
#include "ScriptMgr.h"
#include "Pet.h"
#include "Formulas.h"
 
#define GOSSIP_ITEM_STABLE        "Stable"
#define GOSSIP_ITEM_NEWPET        "New Pet"
#define GOSSIP_ITEM_BOAR        "Boar"
#define GOSSIP_ITEM_SERPENT        "Serpent"
#define GOSSIP_ITEM_SCRAB        "Scrab"
#define GOSSIP_ITEM_LION        "Lion"
#define GOSSIP_ITEM_WOLF        "Wolf"
#define GOSSIP_ITEM_RAVAGER        "Ravenger"
#define GOSSIP_ITEM_UNTRAINEPET "Restart Pet"
 
void CreatePet(Player* player, Creature* m_creature, uint32 entry)
{
    if(player->getClass() != CLASS_HUNTER)
    {
        m_creature->MonsterWhisper("You are not hunter! Your order have been rejected.", player->GetGUID());
        player->CLOSE_GOSSIP_MENU();
        return;
    }
 
    if(player->GetPet())
    {
        m_creature->MonsterWhisper("First you must drop your pet!", player->GetGUID());
        player->CLOSE_GOSSIP_MENU();
        return;
    }
 
    Creature *creatureTarget = m_creature->SummonCreature(entry, player->GetPositionX(), player->GetPositionY()+2, player->GetPositionZ(), player->GetOrientation(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 500);
    if(!creatureTarget) return;
    
    Pet* pet = player->CreateTamedPetFrom(creatureTarget, 0);
    if(!pet) return;
 
    // kill original creature
    creatureTarget->setDeathState(JUST_DIED);
    creatureTarget->RemoveCorpse();
    creatureTarget->SetHealth(0);                       // just for nice GM-mode view
 
    pet->SetPower(POWER_HAPPINESS, 1048000);
 
    //pet->SetUInt32Value(UNIT_FIELD_PETEXPERIENCE,0);
    //pet->SetUInt32Value(UNIT_FIELD_PETNEXTLEVELEXP, uint32((Trinity::XP::xp_to_level(70))/4));
 
    // prepare visual effect for levelup
    pet->SetUInt32Value(UNIT_FIELD_LEVEL, player->getLevel() - 1);
    pet->GetMap()->AddToMap((Creature*)pet);
    // visual effect for levelup
    pet->SetUInt32Value(UNIT_FIELD_LEVEL, player->getLevel());
 
    if(!pet->InitStatsForLevel(player->getLevel()))
    sLog->outError("Pet Create fail: no init stats for entry %u", entry);
    pet->UpdateAllStats();
    
    // caster have pet now
    player->SetMinion(pet, true);
 
    pet->SavePetToDB(PET_SAVE_AS_CURRENT);
    pet->InitTalentForLevel();
    player->PetSpellInitialize();
    
    //end
    player->CLOSE_GOSSIP_MENU();
    m_creature->MonsterWhisper("Pet added. You might want to feed it and name it somehow.", player->GetGUID());
}
 
class npc_beastmaster : public CreatureScript
{
    public: npc_beastmaster() : CreatureScript("npc_beastmaster")
    {
    }
 
    bool OnGossipHello(Player* pPlayer, Creature* pCreature)
        { //Show Main Menu
            if(pPlayer->getClass() != CLASS_HUNTER)
            {
                pCreature->MonsterWhisper("You are not hunter!", pPlayer->GetGUID());
                return true;
            }
        
            pPlayer->ADD_GOSSIP_ITEM(4, "Get new pet", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 30);
 
            if (pPlayer->CanTameExoticPets())
            {
                pPlayer->ADD_GOSSIP_ITEM(4, "Get new exotic pet", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 50);
            }
        
            pPlayer->ADD_GOSSIP_ITEM(2, "Take me to stable", GOSSIP_SENDER_MAIN, GOSSIP_OPTION_STABLEPET);
            pPlayer->ADD_GOSSIP_ITEM(6, "Sell me some food", GOSSIP_SENDER_MAIN, GOSSIP_OPTION_VENDOR);
            pPlayer->SEND_GOSSIP_MENU(1,pCreature->GetGUID());
            return true;
        }
 
    bool OnGossipSelect(Player* pPlayer, Creature* pCreature, uint32 /*uiSender*/, uint32 uiAction)
        {
            ShowMenuItems(pPlayer, pCreature, uiAction);
            return true;
        }
    
    void ShowMenuItems(Player* pPlayer, Creature* pCreature, uint32 uiAction)
    { //BACK BUTTON FOO
        switch (uiAction)
        {
            case GOSSIP_ACTION_INFO_DEF + 100:
                pPlayer->PlayerTalkClass->ClearMenus();
                pPlayer->ADD_GOSSIP_ITEM(4, "Get new pet", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 30);
                
                if (pPlayer->CanTameExoticPets())
                {
                    pPlayer->ADD_GOSSIP_ITEM(4, "Get new exotic pet", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 50);
                }
 
                pPlayer->ADD_GOSSIP_ITEM(2, "Take me to stable", GOSSIP_SENDER_MAIN, GOSSIP_OPTION_STABLEPET);
                pPlayer->ADD_GOSSIP_ITEM(6, "Sell me some food", GOSSIP_SENDER_MAIN, GOSSIP_OPTION_VENDOR);
                pPlayer->SEND_GOSSIP_MENU(1,pCreature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 30:
                pPlayer->PlayerTalkClass->ClearMenus();
                pPlayer->ADD_GOSSIP_ITEM(2, "<< Back to main menu", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 100);
                pPlayer->ADD_GOSSIP_ITEM(4, "Next page >>", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 31);
                pPlayer->ADD_GOSSIP_ITEM(6, "Bat", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 18);
                pPlayer->ADD_GOSSIP_ITEM(6, "Bear", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
                pPlayer->ADD_GOSSIP_ITEM(6, "Boar", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
                pPlayer->ADD_GOSSIP_ITEM(6, "Cat", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);
                pPlayer->ADD_GOSSIP_ITEM(6, "Carrion Bird", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 5);
                pPlayer->ADD_GOSSIP_ITEM(6, "Crab", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 6);
                pPlayer->ADD_GOSSIP_ITEM(6, "Crocolisk", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 7);
                pPlayer->ADD_GOSSIP_ITEM(6, "Dragonhawk", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 17);
                pPlayer->ADD_GOSSIP_ITEM(6, "Gorilla", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 8);
                pPlayer->ADD_GOSSIP_ITEM(6, "Hound", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 9);
                pPlayer->ADD_GOSSIP_ITEM(6, "Hyena", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 10);
                pPlayer->ADD_GOSSIP_ITEM(6, "Moth", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 11);
                pPlayer->ADD_GOSSIP_ITEM(6, "Owl", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 12);
                pPlayer->SEND_GOSSIP_MENU(1,pCreature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 31:
                pPlayer->PlayerTalkClass->ClearMenus();
                pPlayer->ADD_GOSSIP_ITEM(2, "<< Back to main menu", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 100);
                pPlayer->ADD_GOSSIP_ITEM(4, "<< Previous page", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 30);
                pPlayer->ADD_GOSSIP_ITEM(6, "Raptor", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 20);
                pPlayer->ADD_GOSSIP_ITEM(6, "Ravager", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 19);
                pPlayer->ADD_GOSSIP_ITEM(6, "Strider", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 13);
                pPlayer->ADD_GOSSIP_ITEM(6, "Scorpid", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 14);
                pPlayer->ADD_GOSSIP_ITEM(6, "Spider", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 16);
                pPlayer->ADD_GOSSIP_ITEM(6, "Serpent", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 21);  
                pPlayer->ADD_GOSSIP_ITEM(6, "Turtle", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 15);
                pPlayer->ADD_GOSSIP_ITEM(6, "Wasp", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
                pPlayer->SEND_GOSSIP_MENU(1,pCreature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 50:
                pPlayer->PlayerTalkClass->ClearMenus();
                pPlayer->ADD_GOSSIP_ITEM(2, "<< Back to main menu", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 100);
                pPlayer->ADD_GOSSIP_ITEM(6, "Chimaera", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 51);
                pPlayer->ADD_GOSSIP_ITEM(6, "Core Hound", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 52);
                pPlayer->ADD_GOSSIP_ITEM(6, "Devilsaur", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 53);
                pPlayer->ADD_GOSSIP_ITEM(6, "Rhino", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 54);
                pPlayer->ADD_GOSSIP_ITEM(6, "Silithid", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 55);
                pPlayer->ADD_GOSSIP_ITEM(6, "Worm", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 56);  
                pPlayer->ADD_GOSSIP_ITEM(6, "Loque'nahak", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 57);
                pPlayer->ADD_GOSSIP_ITEM(6, "Skoll", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 58);
                pPlayer->ADD_GOSSIP_ITEM(6, "Gondria", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 59);
                pPlayer->SEND_GOSSIP_MENU(1,pCreature->GetGUID());
                break;
            case GOSSIP_OPTION_STABLEPET:
                pPlayer->CLOSE_GOSSIP_MENU();
                pPlayer->GetSession()->SendStablePet(pCreature->GetGUID());
                break;
            case GOSSIP_OPTION_VENDOR:
                /*pPlayer->SEND_VENDORLIST( pCreature->GetGUID());*/
                pPlayer->CLOSE_GOSSIP_MENU();
                pPlayer->GetSession()->SendListInventory( pCreature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 51: //chimera
                CreatePet(pPlayer, pCreature, 21879);
                pPlayer->CLOSE_GOSSIP_MENU();
                break;
            case GOSSIP_ACTION_INFO_DEF + 52: //core hound
                CreatePet(pPlayer, pCreature, 21108);
                pPlayer->CLOSE_GOSSIP_MENU();
                break;
            case GOSSIP_ACTION_INFO_DEF + 53: //Devilsaur
                CreatePet(pPlayer, pCreature, 20931);
                pPlayer->CLOSE_GOSSIP_MENU();
                break;
            case GOSSIP_ACTION_INFO_DEF + 54: //rhino
                CreatePet(pPlayer, pCreature, 30445);
                pPlayer->CLOSE_GOSSIP_MENU();
                break;
            case GOSSIP_ACTION_INFO_DEF + 55: //silithid
                CreatePet(pPlayer, pCreature, 5460);
                pPlayer->CLOSE_GOSSIP_MENU();
                break;
            case GOSSIP_ACTION_INFO_DEF + 56: //Worm
                CreatePet(pPlayer, pCreature, 30148);
                pPlayer->CLOSE_GOSSIP_MENU();
                break;
            case GOSSIP_ACTION_INFO_DEF + 57: //Loque'nahak
                CreatePet(pPlayer, pCreature, 32517);
                pPlayer->CLOSE_GOSSIP_MENU();
                break;
            case GOSSIP_ACTION_INFO_DEF + 58: //Skoll
                CreatePet(pPlayer, pCreature, 35189);
                pPlayer->CLOSE_GOSSIP_MENU();
                break;
            case GOSSIP_ACTION_INFO_DEF + 59: //Gondria
                CreatePet(pPlayer, pCreature, 33776);
                pPlayer->CLOSE_GOSSIP_MENU();
                break;
            case GOSSIP_ACTION_INFO_DEF + 16: //Spider
                CreatePet(pPlayer, pCreature, 2349);
                pPlayer->CLOSE_GOSSIP_MENU();
                break;
            case GOSSIP_ACTION_INFO_DEF + 17: //Dragonhawk
                CreatePet(pPlayer, pCreature, 27946);
                pPlayer->CLOSE_GOSSIP_MENU();
                break;
            case GOSSIP_ACTION_INFO_DEF + 18: //Bat
                CreatePet(pPlayer, pCreature, 28233);
                pPlayer->CLOSE_GOSSIP_MENU();
                break;
            case GOSSIP_ACTION_INFO_DEF + 19: //Ravager
                CreatePet(pPlayer, pCreature, 17199);
                pPlayer->CLOSE_GOSSIP_MENU();
                break;
            case GOSSIP_ACTION_INFO_DEF + 20: //Raptor
                CreatePet(pPlayer, pCreature, 14821);
                pPlayer->CLOSE_GOSSIP_MENU();
                break;
            case GOSSIP_ACTION_INFO_DEF + 21: //Serpent
                CreatePet(pPlayer, pCreature, 28358);
                pPlayer->CLOSE_GOSSIP_MENU();
                break;
            case GOSSIP_ACTION_INFO_DEF + 1: //bear
                CreatePet(pPlayer, pCreature, 29319);
                pPlayer->CLOSE_GOSSIP_MENU();
                break;
            case GOSSIP_ACTION_INFO_DEF + 2: //Boar
                CreatePet(pPlayer, pCreature, 29996);
                pPlayer->CLOSE_GOSSIP_MENU();
                break;
            case GOSSIP_ACTION_INFO_DEF + 3: //Bug
                CreatePet(pPlayer, pCreature, 28085);
                pPlayer->CLOSE_GOSSIP_MENU();
                break;
            case GOSSIP_ACTION_INFO_DEF + 4: //cat
                CreatePet(pPlayer, pCreature, 28097);
                pPlayer->CLOSE_GOSSIP_MENU();
                break;
            case GOSSIP_ACTION_INFO_DEF + 5: //carrion
                CreatePet(pPlayer, pCreature, 26838);
                pPlayer->CLOSE_GOSSIP_MENU();
                break;
            case GOSSIP_ACTION_INFO_DEF + 6: //crab
                CreatePet(pPlayer, pCreature, 24478);
                pPlayer->CLOSE_GOSSIP_MENU();
                break;
            case GOSSIP_ACTION_INFO_DEF + 7: //crocolisk
                CreatePet(pPlayer, pCreature, 1417);
                pPlayer->CLOSE_GOSSIP_MENU();
                break;  
            case GOSSIP_ACTION_INFO_DEF + 8: //gorila
                CreatePet(pPlayer, pCreature, 28213);
                pPlayer->CLOSE_GOSSIP_MENU();
                break;
            case GOSSIP_ACTION_INFO_DEF + 9: //hound
                CreatePet(pPlayer, pCreature, 29452);
                pPlayer->CLOSE_GOSSIP_MENU();
                break;
            case GOSSIP_ACTION_INFO_DEF + 10: //hynea
                CreatePet(pPlayer, pCreature, 13036);
                pPlayer->CLOSE_GOSSIP_MENU();
                break;
            case GOSSIP_ACTION_INFO_DEF + 11: //Moth
                CreatePet(pPlayer, pCreature, 27421);
                pPlayer->CLOSE_GOSSIP_MENU();
                break;
            case GOSSIP_ACTION_INFO_DEF + 12: //owl
                CreatePet(pPlayer, pCreature, 23136);
                pPlayer->CLOSE_GOSSIP_MENU();
                break;
            case GOSSIP_ACTION_INFO_DEF + 13: //strider
                CreatePet(pPlayer, pCreature, 22807);
                pPlayer->CLOSE_GOSSIP_MENU();
                break;
            case GOSSIP_ACTION_INFO_DEF + 14: //scorpid
                CreatePet(pPlayer, pCreature, 9698);
                pPlayer->CLOSE_GOSSIP_MENU();
                break;
            case GOSSIP_ACTION_INFO_DEF + 15: //turtle
                CreatePet(pPlayer, pCreature, 25482);
                pPlayer->CLOSE_GOSSIP_MENU();
                break;
        }
    
        /*return true;*/
    }
};
 
void AddSC_npc_beastmaster()
{
    new npc_beastmaster();
}