#include "Chat.h"
#include "Player.h"
#include "PvPMgr.h"

class pvp_commandscript : public CommandScript
{
public:
    pvp_commandscript() : CommandScript("pvp_commandscript") { }

    ChatCommand* GetCommands() const
    {
        static ChatCommand pvpCommandTable[] =
        {
            { "notifications",    SEC_PLAYER,         false, &HandleNotificationsCommand,             "", NULL },
            { "rating",           SEC_PLAYER,         false, &HandleRatingCommand,                    "", NULL },
            { "mmr",              SEC_PLAYER,         false, &HandleMMRCommand,                       "", NULL },
            { NULL,               0,                  false, NULL,                                    "", NULL }
        };
        static ChatCommand commandTable[] =
        {
            { "pvp",              SEC_PLAYER,         false, NULL,                         "", pvpCommandTable },
            { NULL,               0,                  false, NULL,                                    "", NULL }
        };
        return commandTable;
    }

    static bool HandleNotificationsCommand(ChatHandler* handler, const char* /*args*/)
    {
        Player* player = handler->GetSession()->GetPlayer();

        if (player->HasPvPNotificationsEnabled())
        {
            player->SetPvPNotificationsEnabled(false);
            handler->PSendSysMessage("Notifications from actions in PvP are now disabled.");
            return true;
        }
        else
        {
            player->SetPvPNotificationsEnabled(true);
            handler->PSendSysMessage("Notifications from actions in PvP are now enabled.");
            return true;
        }

        return true;
    }

    static bool HandleRatingCommand(ChatHandler* handler, const char* args)
    {
        uint64 targetGUID;
        std::string targetName;

        uint32 parseGUID = MAKE_NEW_GUID(atol((char*)args), 0, HIGHGUID_PLAYER);

        if (sObjectMgr->GetPlayerNameByGUID(parseGUID, targetName))
            targetGUID = parseGUID;
        else if (!handler->extractPlayerTarget((char*)args, 0, &targetGUID, &targetName))
            return false;

        handler->PSendSysMessage("Player: %s", targetName.c_str());
        handler->PSendSysMessage("Current PvP Rating: %u", sPvPMgr->GetPvPRatingByGUIDLow(GUID_LOPART(targetGUID)));
        handler->PSendSysMessage("Highest PvP Rating: %u", sPvPMgr->GetLifetimePvPRatingByGUIDLow(GUID_LOPART(targetGUID)));
        return true;
    }

    static bool HandleMMRCommand(ChatHandler* handler, const char* args)
    {
        uint64 targetGUID;
        std::string targetName;

        uint32 parseGUID = MAKE_NEW_GUID(atol((char*)args), 0, HIGHGUID_PLAYER);

        if (sObjectMgr->GetPlayerNameByGUID(parseGUID, targetName))
            targetGUID = parseGUID;
        else if (!handler->extractPlayerTarget((char*)args, 0, &targetGUID, &targetName))
            return false;

        handler->PSendSysMessage("Player: %s", targetName.c_str());
        handler->PSendSysMessage("2v2 MMR: %u", sPvPMgr->Get2v2MMRByGUIDLow(GUID_LOPART(targetGUID)));
        handler->PSendSysMessage("3v3 MMR: %u", sPvPMgr->Get3v3MMRByGUIDLow(GUID_LOPART(targetGUID)));
        handler->PSendSysMessage("5v5 MMR: %u", sPvPMgr->Get5v5MMRByGUIDLow(GUID_LOPART(targetGUID)));
        return true;
    }
};

void AddSC_pvp_commandscript()
{
    new pvp_commandscript();
}
