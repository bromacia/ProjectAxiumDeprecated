#include "Chat.h"

class dbw_commandscript : public CommandScript
{
public:
    dbw_commandscript() : CommandScript("dbw_commandscript") { }

    ChatCommand* GetCommands() const
    {
        static ChatCommand dbwCommandTable[] =
        {
            { "showtransformation",     SEC_PLAYER,     false, &HandleShowTransformationCommand,    "", NULL },
            { "help",                   SEC_PLAYER,     false, &HandleHelpCommand,                  "", NULL },
            { NULL,                     0,              false, NULL,                                "", NULL }
        };
        static ChatCommand commandTable[] =
        {
            { "dbw",                    SEC_PLAYER,     false, NULL,                     "", dbwCommandTable },
            { NULL,                     0,              false, NULL,                                "", NULL }
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
        }
        else if (!stricmp(mode, "off"))
        {
            CharacterDatabase.PExecute("UPDATE characters SET show_dbw_transformation = '0' WHERE guid = '%u'", player->GetGUIDLow());
            player->SetShowDBWTransformation(false);
        }
        return true;
    }

    static bool HandleHelpCommand(ChatHandler* handler, const char* /*args*/)
    {
        Player* player = handler->GetSession()->GetPlayer();

        handler->PSendSysMessage("You can enable/disable Deathbringer's Will transformations via the `.dbw showtransformation on/off` command.");
        handler->PSendSysMessage("Disabling Deathbringer's Will's transformation visual will cause the proc aura to not transform you into a "
                                 "Vrykul/Taunka/Iron Dwarf and instead replace the visual with a purple glow.");
        handler->PSendSysMessage("You still get all the stat bonuses from the proc just not the visual transformation and any changes you make to "
                                 "the visual will only apply to you and not other players.");
        handler->PSendSysMessage("Keep in mind that enabling/disabling the transformation will persist even when you log out and will "
                                 "stay that way until you re enable/disable it. If you have any additional questions feel free to "
                                 "create a ticket and a staff member will assist you.");

        return true;
    }
};

void AddSC_dbw_commandscript()
{
    new dbw_commandscript();
}
