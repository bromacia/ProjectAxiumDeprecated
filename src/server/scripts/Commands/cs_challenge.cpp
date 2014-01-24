#include "ChallengeMgr.h"

class challenge_commandscript : public CommandScript
{
    public:
        challenge_commandscript() : CommandScript("challenge_commandscript") { }

        ChatCommand* GetCommands() const
        {
            static ChatCommand commandTable[] =
            {
                { "challenge",          SEC_PLAYER,         false, &HandleChallengeCommand,                 "", NULL },
                { NULL,                 0,                  false, NULL,                                    "", NULL }
            };
            return commandTable;
        }

        static bool HandleChallengeCommand(ChatHandler* handler, const char* args)
        {
            Player* player = handler->GetSession()->GetPlayer();
            if (!player)
                return false;

            if (!*args)
            {
                player->SendSysMessage("Incorrect syntax.");
                player->SendSysMessage("Syntax: .challenge $playerName #arenaMap");
                player->SendSysMessage("Please refer to your Player Handbook for arena map numbers and more information.");
                handler->SetSentErrorMessage(true);
                return false;
            }

            std::string name = strtok((char*)args, " ");
            if (!normalizePlayerName(name))
            {
                player->SendSysMessage("Invalid player name.");
                handler->SetSentErrorMessage(true);
                return false;
            }

            uint64 guid = 0;
            if (Player* player = sObjectAccessor->FindPlayerByName(name.c_str()))
                guid = player->GetGUID();
            else
                guid = sObjectMgr->GetPlayerGUIDByName(name);

            if (!guid)
            {
                player->SendSysMessage("No player found with the name %s.", name.c_str());
                handler->SetSentErrorMessage(true);
                return false;
            }

            uint8 bgTypeId = 0;
            char* bgTypeIdArg = strtok(NULL, " ");

            if (bgTypeIdArg)
                bgTypeId = (uint8)atoi(bgTypeIdArg);

            ChallengeMgr().HandleChallenge(player->GetGUID(), guid, bgTypeId);
            return true;
        }
};

void AddSC_challenge_commandscript()
{
    new challenge_commandscript();
}
