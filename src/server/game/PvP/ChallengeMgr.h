#ifndef CHALLENGE_MGR_H_
#define CHALLENGE_MGR_H_

#include <ace/Singleton.h>
#include "ScriptMgr.h"

class Player;
class Battleground;
class BattlegroundQueue;
struct PvPDifficultyEntry;
class ChatHandler;

class ChallengeMgr
{
    friend class ACE_Singleton<ChallengeMgr, ACE_Null_Mutex>;

    private:
        ChallengeMgr() {}
        ~ChallengeMgr() {}

    public:
        void HandleChallenge(uint64 challengerGUID, uint64 challengedGUID, uint8 map);

    private:
        void CleanupChallenge();
        void CreateBattleground(const PvPDifficultyEntry* bracketEntry, uint8 teamSize);
        void AddPlayerToBattleground(Player* player, BattlegroundBracketId bracketId);
        bool IsOnTeamA(uint64 guid);
        bool IsOnTeamB(uint64 guid);

        typedef std::vector<uint64> Players;
        Players teamA;
        Players teamB;
        uint8 arenaType;
        uint8 bgTypeId;
        Battleground* bg;
        uint8 bgQueueTypeId;
        BattlegroundQueue* bgQueue;
};

#define sChallengeMgr ACE_Singleton<ChallengeMgr, ACE_Null_Mutex>::instance()

class challenge_commandscript : public CommandScript
{
    public:
        challenge_commandscript() : CommandScript("challenge_commandscript") { }

        ChatCommand* GetCommands() const;
        static bool HandleChallengeCommand(ChatHandler* handler, const char* args);
};

#endif /*CHALLENGE_MGR_H_*/
