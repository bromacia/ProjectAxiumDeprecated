#ifndef CHALLENGE_MGR_H_
#define CHALLENGE_MGR_H_

class Player;
class Battleground;
class BattlegroundQueue;
struct PvPDifficultyEntry;

class ChallengeMgr
{
    public:
        ChallengeMgr();
        ~ChallengeMgr();

        void HandleChallenge(uint64 challengerGUID, uint64 challengedGUID, uint8 map);

    private:
        void CreateBattleground(uint8 teamSize);
        void AddPlayerToBattleground(Player* player);
        void CleanupChallenge();
        bool IsOnTeamA(uint64 guid);
        bool IsOnTeamB(uint64 guid);

        typedef std::vector<uint64> Players;
        Players teamA;
        Players teamB;
        Battleground* bg;
        const PvPDifficultyEntry* bracketEntry;
        uint8 arenaType;
        uint8 bgTypeId;
        uint8 bgQueueTypeId;
        BattlegroundQueue* bgQueue;
};

#endif /*CHALLENGE_MGR_H_*/
