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
};

void AddSC_utility_commandscript()
{
    new utility_commandscript();
}