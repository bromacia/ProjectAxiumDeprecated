#ifndef __BATTLEGROUNDBE_H
#define __BATTLEGROUNDBE_H

class Battleground;

enum BattlegroundBEObjectTypes
{
    BG_BE_OBJECT_DOOR_1             = 0,
    BG_BE_OBJECT_DOOR_2             = 1,
    BG_BE_OBJECT_DOOR_3             = 2,
    BG_BE_OBJECT_DOOR_4             = 3,
    BG_BE_OBJECT_BUFF_1             = 4,
    BG_BE_OBJECT_BUFF_2             = 5,
    BG_BE_OBJECT_READY_MARKER_A     = 6,
    BG_BE_OBJECT_READY_MARKER_B     = 7,
    BG_BE_OBJECT_MAX                = 8
};

enum BattlegroundBEObjects
{
    BG_BE_OBJECT_TYPE_DOOR_1            = 183971,
    BG_BE_OBJECT_TYPE_DOOR_2            = 183973,
    BG_BE_OBJECT_TYPE_DOOR_3            = 183970,
    BG_BE_OBJECT_TYPE_DOOR_4            = 183972,
    BG_BE_OBJECT_TYPE_BUFF_1            = 184663,
    BG_BE_OBJECT_TYPE_BUFF_2            = 184664
};

class BattlegroundBEScore : public BattlegroundScore
{
    public:
        BattlegroundBEScore() {};
        virtual ~BattlegroundBEScore() {};
};

class BattlegroundBE : public Battleground
{
    public:
        BattlegroundBE();
        ~BattlegroundBE();

        /* inherited from BattlegroundClass */
        virtual void AddPlayer(Player* player);
        virtual void AddPlayerToScoreboard(Player* player, uint32 team);
        virtual void StartingEventCloseDoors();
        virtual void StartingEventOpenDoors();

        void RemovePlayer(Player* player, uint64 guid, uint32 team);
        void HandleAreaTrigger(Player* Source, uint32 Trigger);
        bool SetupBattleground();
        virtual void Reset();
        virtual void FillInitialWorldStates(WorldPacket &d);
        void HandleKillPlayer(Player* player, Player* killer);
        bool HandlePlayerUnderMap(Player* player);

        /* Scorekeeping */
        void UpdatePlayerScore(Player* Source, uint32 type, uint32 value, bool doAddHonor = true);
};
#endif
