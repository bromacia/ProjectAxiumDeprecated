#include "ScriptPCH.h"
#include "ScriptMgr.h"
#include "Pet.h"
#include "Formulas.h"

class npc_beastmaster : public CreatureScript
{
    public:
        npc_beastmaster() : CreatureScript("npc_beastmaster") {}

        void CreatePet(Player* player, Creature* creature, uint32 creatureEntry)
        {
            if (player->getClass() != CLASS_HUNTER)
            {
                ChatHandler(player).PSendSysMessage("You must be a hunter to have access to pets.");
                return;
            }

            Pet* pet = player->CreateTamedPetFrom(creatureEntry, 0);
            if (!pet)
                return;

            if (Pet* playerPet = player->ToPet())
            {
                player->StopCastingCharm();
                player->RemovePet(playerPet, PET_SAVE_AS_DELETED, false);
            }

            pet->GetMap()->AddToMap(pet->ToCreature());

            player->SetMinion(pet, true);

            pet->InitTalentForLevel();
            player->PetSpellInitialize();
            pet->SetPower(POWER_HAPPINESS, 1000000);
            pet->UpdateAllStats();
            pet->SavePetToDB(PET_SAVE_AS_CURRENT);

            player->CLOSE_GOSSIP_MENU();
            ChatHandler(player).PSendSysMessage("Pet added.");
        }

        bool OnGossipHello(Player* player, Creature* creature)
        {
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TRAINER, "Pets", GOSSIP_SENDER_MAIN, 1000);

            if (player->CanTameExoticPets())
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TRAINER, "Exotic Pets", GOSSIP_SENDER_MAIN, 1100);

            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TRAINER, "Stable", GOSSIP_SENDER_MAIN, 1200);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TRAINER, "Reset Pet Talents", GOSSIP_SENDER_MAIN, 1300);
            player->SEND_GOSSIP_MENU(1, creature->GetGUID());
            return true;
        }

        bool OnGossipSelect(Player* player, Creature* creature, uint32 uiSender, uint32 uiAction)
        {
            player->PlayerTalkClass->ClearMenus();

            switch (uiAction)
            {
                case 100:
                    OnGossipHello(player, creature);
                    break;
                case 1000:
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Bat - [Cunning]", GOSSIP_SENDER_MAIN, 1);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Bear - [Tenacity]", GOSSIP_SENDER_MAIN, 2);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Bird of Prey - [Cunning]", GOSSIP_SENDER_MAIN, 3);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Boar - [Tenacity]", GOSSIP_SENDER_MAIN, 4);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Cat - [Ferocity]", GOSSIP_SENDER_MAIN, 5);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Carrion Bird - [Ferocity]", GOSSIP_SENDER_MAIN, 6);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Crab - [Tenacity]", GOSSIP_SENDER_MAIN, 7);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Crocolisk - [Tenacity]", GOSSIP_SENDER_MAIN, 8);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Dragonhawk - [Cunning]", GOSSIP_SENDER_MAIN, 9);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Gorilla - [Tenacity]", GOSSIP_SENDER_MAIN, 10);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Hyena - [Ferocity]", GOSSIP_SENDER_MAIN, 11);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Moth - [Ferocity]", GOSSIP_SENDER_MAIN, 12);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Nether Ray - [Cunning]", GOSSIP_SENDER_MAIN, 13);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Next Page", GOSSIP_SENDER_MAIN, 1001);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Back", GOSSIP_SENDER_MAIN, 100);
                    player->SEND_GOSSIP_MENU(1, creature->GetGUID());
                    break;
                case 1001:
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Raptor - [Ferocity]", GOSSIP_SENDER_MAIN, 14);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Ravager - [Cunning]", GOSSIP_SENDER_MAIN, 15);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Scorpid - [Tenacity]", GOSSIP_SENDER_MAIN, 16);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Serpent - [Cunning]", GOSSIP_SENDER_MAIN, 17);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Spider - [Cunning]", GOSSIP_SENDER_MAIN, 18);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Spore Bat - [Cunning]", GOSSIP_SENDER_MAIN, 19);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Tallstrider - [Ferocity]", GOSSIP_SENDER_MAIN, 20);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Turtle - [Tenacity]", GOSSIP_SENDER_MAIN, 21);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Warp Stalker - [Tenacity]", GOSSIP_SENDER_MAIN, 22);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Wasp - [Ferocity]", GOSSIP_SENDER_MAIN, 23);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Wind Serpent - [Cunning]", GOSSIP_SENDER_MAIN, 24);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Wolf - [Ferocity]", GOSSIP_SENDER_MAIN, 25);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Previous page", GOSSIP_SENDER_MAIN, 1000);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Back", GOSSIP_SENDER_MAIN, 100);
                    player->SEND_GOSSIP_MENU(1, creature->GetGUID());
                    break;
                case 1100:
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Chimaera - [Cunning]", GOSSIP_SENDER_MAIN, 50);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Core Hound - [Ferocity]", GOSSIP_SENDER_MAIN, 51);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Devilsaur - [Ferocity]", GOSSIP_SENDER_MAIN, 52);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Rhino - [Tenacity]", GOSSIP_SENDER_MAIN, 53);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Silithid - [Cunning]", GOSSIP_SENDER_MAIN, 54);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Worm - [Tenacity]", GOSSIP_SENDER_MAIN, 55);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Loque'nahak - [Ferocity]", GOSSIP_SENDER_MAIN, 56);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Skoll - [Ferocity]", GOSSIP_SENDER_MAIN, 57);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Gondria - [Ferocity]", GOSSIP_SENDER_MAIN, 58);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Arcturis - [Ferocity]", GOSSIP_SENDER_MAIN, 59);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Back", GOSSIP_SENDER_MAIN, 100);
                    player->SEND_GOSSIP_MENU(1, creature->GetGUID());
                    break;
                case 1200:
                    if (player->getClass() != CLASS_HUNTER)
                    {
                        ChatHandler(player).PSendSysMessage("You must be a hunter to access a stable.");
                        player->CLOSE_GOSSIP_MENU();
                        return false;
                    }
                    player->CLOSE_GOSSIP_MENU();
                    player->GetSession()->SendStablePet(creature->GetGUID());
                    break;
                case 1300:
                    if (player->getClass() != CLASS_HUNTER)
                    {
                        ChatHandler(player).PSendSysMessage("You must be a hunter to access a stable.");
                        player->CLOSE_GOSSIP_MENU();
                        return false;
                    }
                    player->CLOSE_GOSSIP_MENU();
                    if (Pet* pet = player->GetPet())
                    {
                        pet->resetTalents();
                        player->SendTalentsInfoData(true);
                    }
                    break;
                case 1: // Bat
                    CreatePet(player, creature, 26622);
                    player->CLOSE_GOSSIP_MENU();
                    break;
                case 2: // Bear
                    CreatePet(player, creature, 24217);
                    player->CLOSE_GOSSIP_MENU();
                    break;
                case 3: // Bird of Prey
                    CreatePet(player, creature, 27244);
                    player->CLOSE_GOSSIP_MENU();
                    break;
                case 4: // Boar
                    CreatePet(player, creature, 4512);
                    player->CLOSE_GOSSIP_MENU();
                    break;
                case 5: // Cat
                    CreatePet(player, creature, 10737);
                    player->CLOSE_GOSSIP_MENU();
                    break;
                case 6: // Carrion Bird
                    CreatePet(player, creature, 21515);
                    player->CLOSE_GOSSIP_MENU();
                    break;
                case 7: // Crab
                    CreatePet(player, creature, 23929);
                    player->CLOSE_GOSSIP_MENU();
                    break;
                case 8: // Crocolisk
                    CreatePet(player, creature, 28002);
                    player->CLOSE_GOSSIP_MENU();
                    break;
                case 9: // Dragonhawk
                    CreatePet(player, creature, 18155);
                    player->CLOSE_GOSSIP_MENU();
                    break;
                case 10: // Gorilla
                    CreatePet(player, creature, 6514);
                    player->CLOSE_GOSSIP_MENU();
                    break;
                case 11: // Hynea
                    CreatePet(player, creature, 4690);
                    player->CLOSE_GOSSIP_MENU();
                    break;
                case 12: // Moth
                    CreatePet(player, creature, 25498);
                    player->CLOSE_GOSSIP_MENU();
                    break;
                case 13: // Nether Ray
                    CreatePet(player, creature, 21901);
                    player->CLOSE_GOSSIP_MENU();
                    break;
                case 14: // Raptor
                    CreatePet(player, creature, 20729);
                    player->CLOSE_GOSSIP_MENU();
                    break;
                case 15: // Ravager
                    CreatePet(player, creature, 16934);
                    player->CLOSE_GOSSIP_MENU();
                    break;
                case 16: // Scorpid
                    CreatePet(player, creature, 5823);
                    player->CLOSE_GOSSIP_MENU();
                    break;
                case 17: // Serpent
                    CreatePet(player, creature, 19784);
                    player->CLOSE_GOSSIP_MENU();
                    break;
                case 18: // Spider
                    CreatePet(player, creature, 17683);
                    player->CLOSE_GOSSIP_MENU();
                    break;
                case 19: // Spore Bat
                    CreatePet(player, creature, 18128);
                    player->CLOSE_GOSSIP_MENU();
                    break;
                case 20: // Tallstrider
                    CreatePet(player, creature, 3068);
                    player->CLOSE_GOSSIP_MENU();
                    break;
                case 21: // Turtle
                    CreatePet(player, creature, 4397);
                    player->CLOSE_GOSSIP_MENU();
                    break;
                case 22: // Warp Stalker
                    CreatePet(player, creature, 23163);
                    player->CLOSE_GOSSIP_MENU();
                    break;
                case 23: // Wasp
                    CreatePet(player, creature, 28086);
                    player->CLOSE_GOSSIP_MENU();
                    break; 
                case 24: // Wind Serpent
                    CreatePet(player, creature, 28477);
                    player->CLOSE_GOSSIP_MENU();
                    break;
                case 25: // Wolf
                    CreatePet(player, creature, 17280);
                    player->CLOSE_GOSSIP_MENU();
                    break;
                case 50: // Chimaera
                    CreatePet(player, creature, 21033);
                    player->CLOSE_GOSSIP_MENU();
                    break;
                case 51: // Core Hound
                    CreatePet(player, creature, 21108);
                    player->CLOSE_GOSSIP_MENU();
                    break;
                case 52: // Devilsaur
                    CreatePet(player, creature, 20931);
                    player->CLOSE_GOSSIP_MENU();
                    break;
                case 53: // Rhino
                    CreatePet(player, creature, 30445);
                    player->CLOSE_GOSSIP_MENU();
                    break;
                case 54: // Silithid
                    CreatePet(player, creature, 14473);
                    player->CLOSE_GOSSIP_MENU();
                    break;
                case 55: // Worm
                    CreatePet(player, creature, 26359);
                    player->CLOSE_GOSSIP_MENU();
                    break;
                case 56: // Loque'nahak
                    CreatePet(player, creature, 32517);
                    player->CLOSE_GOSSIP_MENU();
                    break;
                case 57: // Skoll
                    CreatePet(player, creature, 35189);
                    player->CLOSE_GOSSIP_MENU();
                    break;
                case 58: // Gondria
                    CreatePet(player, creature, 33776);
                    player->CLOSE_GOSSIP_MENU();
                    break;
                case 59: // Arcturis
                    CreatePet(player, creature, 38453);
                    player->CLOSE_GOSSIP_MENU();
                    break;
            }

            return false;
        }
};
 
void AddSC_npc_beastmaster()
{
    new npc_beastmaster();
}