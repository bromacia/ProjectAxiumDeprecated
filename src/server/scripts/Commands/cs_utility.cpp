#include "Chat.h"

class utility_commandscript : public CommandScript
{
public:
    utility_commandscript() : CommandScript("utility_commandscript") { }

    ChatCommand* GetCommands() const
    {
        static ChatCommand utilityCommandTable[] =
        {
            { "customize",       SEC_PLAYER,         false, &HandleCustomizeCommand,                 "", NULL },
            { "race",            SEC_PLAYER,         false, &HandleRaceCommand,                      "", NULL },
            { "faction",         SEC_PLAYER,         false, &HandleFactionCommand,                   "", NULL },
            { "prepare",         SEC_GAMEMASTER,     false, &HandlePrepareCommand,                   "", NULL },
            { "barbershop",      SEC_PLAYER,         false, &HandleBarbershopCommand,                "", NULL },
            { "mmr",             SEC_PLAYER,         false, &HandleMMRCommand,                       "", NULL },
            { "sendcooldown",    SEC_GAMEMASTER,     false, &HandleSendCooldownCommand,              "", NULL },
            { NULL,              0,                  false, NULL,                                    "", NULL }
        };
        static ChatCommand commandTable[] =
        {
            { "utility",         SEC_PLAYER,         false, NULL,                     "", utilityCommandTable },
            { NULL,              0,                  false, NULL,                                    "", NULL }
        };
        return commandTable;
    }

    static bool HandleCustomizeCommand(ChatHandler* handler, const char* /*args*/)
    {
        Player* player = handler->GetSession()->GetPlayer();
        
        PreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_UPD_ADD_AT_LOGIN_FLAG);
        stmt->setUInt16(0, uint16(AT_LOGIN_CUSTOMIZE));

        handler->PSendSysMessage("Relog to customize your character");
        player->SetAtLoginFlag(AT_LOGIN_CUSTOMIZE);

        stmt->setUInt32(1, player->GetGUIDLow());

        CharacterDatabase.Execute(stmt);
        return true;
    }

    static bool HandleRaceCommand(ChatHandler* handler, const char* /*args*/)
    {
        Player* player = handler->GetSession()->GetPlayer();
        
        PreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_UPD_ADD_AT_LOGIN_FLAG);
        stmt->setUInt16(0, uint16(AT_LOGIN_CHANGE_RACE));

        handler->PSendSysMessage("Relog to change the race of your character");
        player->SetAtLoginFlag(AT_LOGIN_CHANGE_RACE);

        stmt->setUInt32(1, player->GetGUIDLow());

        CharacterDatabase.Execute(stmt);
        return true;
    }

    static bool HandleFactionCommand(ChatHandler* handler, const char* /*args*/)
    {
        Player* player = handler->GetSession()->GetPlayer();
        
        PreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_UPD_ADD_AT_LOGIN_FLAG);
        stmt->setUInt16(0, uint16(AT_LOGIN_CHANGE_FACTION));

        handler->PSendSysMessage("Relog to change the faction of your character");
        player->SetAtLoginFlag(AT_LOGIN_CHANGE_FACTION);

        stmt->setUInt32(1, player->GetGUIDLow());

        CharacterDatabase.Execute(stmt);
        return true;
    }

    static bool HandlePrepareCommand(ChatHandler* handler, const char* args)
    {
        Player* player = handler->GetSession()->GetPlayer();
        uint64 target_guid = player->GetGUID();

        if (!handler->extractPlayerTarget((char*)args, &player, &target_guid))
            return false;
        
        if (player)
        {
            player->ResurrectPlayer(1.0f);
            player->SpawnCorpseBones();
            player->SaveToDB();
            player->RemoveAllPlayerSpellCooldowns();
            player->RemoveAllNegativeAuras();
            player->ClearDiminishings();
            player->ClearComboPoints();
            player->ClearInCombat();
            player->getHostileRefManager().deleteReferences();
        }
        else
            // will resurrected at login without corpse
            sObjectAccessor->ConvertCorpseForPlayer(target_guid);

        if (Pet* pet = player->GetPet())
            pet->RemoveAllPetSpellCooldowns(player);
        return true;
    }

    static bool HandleBarbershopCommand(ChatHandler* handler, const char* /*args*/)
    {
        Player* player = handler->GetSession()->GetPlayer();

        if (player->InBattleground())
        {
            handler->PSendSysMessage("You cant do that while in a battleground.");
            handler->SetSentErrorMessage(true);
            return false;
        }
        if (player->InArena())
        {
            handler->PSendSysMessage("You cant do that while in arena.");
            handler->SetSentErrorMessage(true);
            return false;
        }
        if (player->IsDueling())
        {
            handler->PSendSysMessage("You cant do that while dueling.");
            handler->SetSentErrorMessage(true);
            return false;
        }
        if (player->isInCombat())
        {
            handler->PSendSysMessage("You cant do that while in combat.");
            handler->SetSentErrorMessage(true);
            return false;
        }
        if (player->IsMounted())
        {
            handler->PSendSysMessage("You cant do that while mounted.");
            handler->SetSentErrorMessage(true);
            return false;
        }
        if (player->IsSitState())
        {
            handler->PSendSysMessage("You cant do that while sitting.");
            handler->SetSentErrorMessage(true);
            return false;
        }
        if (player->isInFlight())
        {
            handler->PSendSysMessage("You cant do that while in flight.");
            handler->SetSentErrorMessage(true);
            return false;
        }
        if (player->IsFlying())
        {
            handler->PSendSysMessage("You cant do that while flying.");
            handler->SetSentErrorMessage(true);
            return false;
        }
        if (player->IsInWater())
        {
            handler->PSendSysMessage("You cant do that while swimming.");
            handler->SetSentErrorMessage(true);
            return false;
        }
        if (player->HasUnitState(UNIT_STATE_CASTING))
        {
            handler->PSendSysMessage("You cant do that while casting.");
            handler->SetSentErrorMessage(true);
            return false;
        }
        if (player->IsCrowdControlled())
        {
            handler->PSendSysMessage("You cant do that while being crowd controlled.");
            handler->SetSentErrorMessage(true);
            return false;
        }
        if (player->HasAuraType(SPELL_AURA_TRANSFORM))
        {
            handler->PSendSysMessage("You cant do that while transformed.");
            handler->SetSentErrorMessage(true);
            return false;
        }
        if ((player->getClass() == CLASS_DRUID && player->HasAuraType(SPELL_AURA_MOD_SHAPESHIFT)))
        {
            handler->PSendSysMessage("You cant do that while shapeshifted.");
            handler->SetSentErrorMessage(true);
            return false;
        }

        WorldPacket data(SMSG_ENABLE_BARBER_SHOP, 0);
        player->GetSession()->SendPacket(&data);
        return true;
    }

    static bool HandleMMRCommand(ChatHandler* handler, const char* args)
    {
        uint32 player_guid = handler->GetSession()->GetPlayer()->GetGUIDLow();
        uint16 mmr = 1500;

        if (!*args)
            return false;

        char* bracket = strtok((char*)args, " ");

        if (!bracket)
            return false;

        if (!stricmp(bracket, "2v2"))
        {
            QueryResult result = CharacterDatabase.PQuery("SELECT matchMakerRating FROM character_arena_stats WHERE guid = %u AND slot = %u", player_guid, 0);

            if (!result)
                handler->PSendSysMessage("2v2 MMR: %u", mmr);
            else
            {
                Field* fields = result->Fetch();
                mmr = fields[0].GetInt16();
                handler->PSendSysMessage("2v2 MMR: %u", mmr);
            }
        }
        else if (!stricmp(bracket, "3v3"))
        {
            QueryResult result = CharacterDatabase.PQuery("SELECT matchMakerRating FROM character_arena_stats WHERE guid = %u AND slot = %u", player_guid, 1);

            if (!result)
                handler->PSendSysMessage("3v3 MMR: %u", mmr);
            else
            {
                Field* fields = result->Fetch();
                mmr = fields[0].GetInt16();
                handler->PSendSysMessage("3v3 MMR: %u", mmr);
            }
        }
        else if (!stricmp(bracket, "5v5"))
        {
            QueryResult result = CharacterDatabase.PQuery("SELECT matchMakerRating FROM character_arena_stats WHERE guid = %u AND slot = %u", player_guid, 2);

            if (!result)
                handler->PSendSysMessage("5v5 MMR: %u", mmr);
            else
            {
                Field* fields = result->Fetch();
                mmr = fields[0].GetInt16();
                handler->PSendSysMessage("5v5 MMR: %u", mmr);
            }
        }
        else
        {
            handler->PSendSysMessage("Invalid bracket.");
            handler->SetSentErrorMessage(true);
            return false;
        }
        return true;
    }

    static bool HandleSendCooldownCommand(ChatHandler* handler, const char* args)
    {
        Player* target = handler->getSelectedPlayer();
        uint64 target_guid = handler->getSelectedPlayer()->GetGUID();

        if (!*args)
            return false;

        uint32 spell = handler->extractSpellIdFromLink((char*)args);

        char* timeArg = strtok(NULL, " ");

        if (!timeArg)
            return false;

        uint32 cooldown = (uint32)atoi(timeArg);

        if (!spell || !sSpellMgr->GetSpellInfo(spell) || !cooldown)
            return false;

        if (!target->HasSpell(spell))
        {
            handler->PSendSysMessage("%s does not know that spell", target->GetName());
            handler->SetSentErrorMessage(true);
            return false;
        }

        target->RemoveSpellCooldown(spell, true);
        target->AddSpellCooldown(spell, 0, time(NULL) + cooldown, true);
        return true;
    }
};

void AddSC_utility_commandscript()
{
    new utility_commandscript();
}