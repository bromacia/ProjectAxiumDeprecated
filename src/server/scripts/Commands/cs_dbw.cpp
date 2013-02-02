#include "Chat.h"

class dbw_commandscript : public CommandScript
{
public:
    dbw_commandscript() : CommandScript("dbw_commandscript") { }

    ChatCommand* GetCommands() const
    {
        static ChatCommand dbwCommandTable[] =
        {
            { "showtransformation", SEC_PLAYER,         false, &HandleShowTransformationCommand,        "", NULL },
            { NULL,                 0,                  false, NULL,                                    "", NULL }
        };
        static ChatCommand commandTable[] =
        {
            { "dbw",                SEC_PLAYER,         false, NULL,                         "", dbwCommandTable },
            { NULL,                 0,                  false, NULL,                                    "", NULL }
        };
        return commandTable;
    }

    static bool HandleShowTransformationCommand(ChatHandler* handler, const char* args)
    {
        Player* player = handler->GetSession()->GetPlayer();

        if (!*args)
            return false;

        char* mode = strtok((char*)args, " ");

        if (!mode)
            return false;

        if (!stricmp(mode, "on"))
        {
            CharacterDatabase.PExecute("UPDATE characters SET show_dbw_transformation = '1' WHERE guid = '%u'", player->GetGUIDLow());
            player->SetShowDBWTransformation(true);
            handler->PSendSysMessage("Transformations from DBW will now show. Type in '.dbw showtransformation off' to disable transformations.");
        }
        else if (!stricmp(mode, "off"))
        {
            CharacterDatabase.PExecute("UPDATE characters SET show_dbw_transformation = '0' WHERE guid = '%u'", player->GetGUIDLow());
            player->SetShowDBWTransformation(false);
            handler->PSendSysMessage("Transformations from DBW will no longer show. Type in '.dbw showtransformation on' to enable transformations.");
        }
        return true;
    }
};

void AddSC_dbw_commandscript()
{
    new dbw_commandscript();
}
