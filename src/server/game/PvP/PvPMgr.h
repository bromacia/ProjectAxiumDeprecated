#ifndef PVP_MGR_H_
#define PVP_MGR_H_

#include <ace/Singleton.h>

class Player;
class Battleground;
class ChatHandler;

#define DAMAGE_RESET_TIME_MS 30000

enum PvPTitle
{
    TITLE_A_PRIVATE              = 1,
    TITLE_A_CORPORAL             = 2,
    TITLE_A_SERGEANT             = 3,
    TITLE_A_MASTER_SERGEANT      = 4,
    TITLE_A_SERGEANT_MAJOR       = 5,
    TITLE_A_KNIGHT               = 6,
    TITLE_A_KNIGHT_LIEUTENANT    = 7,
    TITLE_A_KNIGHT_CAPTAIN       = 8,
    TITLE_A_KNIGHT_CHAMPION      = 9,
    TITLE_A_LIEUTENANT_COMMANDER = 10,
    TITLE_A_COMMANDER            = 11,
    TITLE_A_MARSHAL              = 12,
    TITLE_A_FIELD_MARSHAL        = 13,
    TITLE_A_GRAND_MARSHAL        = 14,
    TITLE_H_SCOUT                = 15,
    TITLE_H_GRUNT                = 16,
    TITLE_H_SERGEANT             = 17,
    TITLE_H_SENIOR_SERGEANT      = 18,
    TITLE_H_FIRST_SERGEANT       = 19,
    TITLE_H_STONE_GUARD          = 20,
    TITLE_H_BLOOD_GUARD          = 21,
    TITLE_H_LEGIONAIRE           = 22,
    TITLE_H_CENTURION            = 23,
    TITLE_H_CHAMPION             = 24,
    TITLE_H_LIEUTENANT_GENERAL   = 25,
    TITLE_H_GENERAL              = 26,
    TITLE_H_WARLORD              = 27,
    TITLE_H_HIGH_WARLORD         = 28,
};

class PvPMgr
{
    friend class ACE_Singleton<PvPMgr, ACE_Null_Mutex>;

    private:
        PvPMgr();
        ~PvPMgr();

    public:
        void HandleDealDamage(Player* attacker, Player* victim, uint32 damage);
        void HandlePvPKill(Player* victim, Player* pwner = NULL);
        void HandleBattlegroundEnd(Battleground* bg);
        void HandleTwinSpireCapture(Team faction);

        uint16 Get2v2MMRByGUIDLow(uint32 GUIDLow) const;
        void Set2v2MMRByGUIDLow(uint32 GUIDLow, uint16 mmr);
        uint16 Get3v3MMRByGUIDLow(uint32 GUIDLow) const;
        void Set3v3MMRByGUIDLow(uint32 GUIDLow, uint16 mmr);
        uint16 Get5v5MMRByGUIDLow(uint32 GUIDLow) const;
        void Set5v5MMRByGUIDLow(uint32 GUIDLow, uint16 mmr);

        uint16 GetPvPRatingByGUIDLow(uint32 GUIDLow) const;
        void SetPvPRatingByGUIDLow(uint32 GUIDLow, uint16 rating);
        uint16 GetLifetimePvPRatingByGUIDLow(uint32 GUIDLow) const;
        void SetLifetimePvPRatingByGUIDLow(uint32 GUIDLow, uint16 rating);

        uint16 GetLifetime2v2RatingByGUIDLow(uint32 GUIDLow) const;
        void SetLifetime2v2RatingByGUIDLow(uint32 GUIDLow, uint16 rating);
        uint16 GetLifetime2v2MMRByGUIDLow(uint32 GUIDLow) const;
        void SetLifetime2v2MMRByGUIDLow(uint32 GUIDLow, uint16 mmr);
        uint16 GetLifetime2v2WinsByGUIDLow(uint32 GUIDLow) const;
        void SetLifetime2v2WinsByGUIDLow(uint32 GUIDLow, uint16 wins);
        uint16 GetLifetime2v2GamesByGUIDLow(uint32 GUIDLow) const;
        void SetLifetime2v2GamesByGUIDLow(uint32 GUIDLow, uint16 games);

        uint16 GetLifetime3v3RatingByGUIDLow(uint32 GUIDLow) const;
        void SetLifetime3v3RatingByGUIDLow(uint32 GUIDLow, uint16 rating);
        uint16 GetLifetime3v3MMRByGUIDLow(uint32 GUIDLow) const;
        void SetLifetime3v3MMRByGUIDLow(uint32 GUIDLow, uint16 mmr);
        uint16 GetLifetime3v3WinsByGUIDLow(uint32 GUIDLow) const;
        void SetLifetime3v3WinsByGUIDLow(uint32 GUIDLow, uint16 wins);
        uint16 GetLifetime3v3GamesByGUIDLow(uint32 GUIDLow) const;
        void SetLifetime3v3GamesByGUIDLow(uint32 GUIDLow, uint16 games);

        uint16 GetLifetime5v5RatingByGUIDLow(uint32 GUIDLow) const;
        void SetLifetime5v5RatingByGUIDLow(uint32 GUIDLow, uint16 rating);
        uint16 GetLifetime5v5MMRByGUIDLow(uint32 GUIDLow) const;
        void SetLifetime5v5MMRByGUIDLow(uint32 GUIDLow, uint16 mmr);
        uint16 GetLifetime5v5WinsByGUIDLow(uint32 GUIDLow) const;
        void SetLifetime5v5WinsByGUIDLow(uint32 GUIDLow, uint16 wins);
        uint16 GetLifetime5v5GamesByGUIDLow(uint32 GUIDLow) const;
        void SetLifetime5v5GamesByGUIDLow(uint32 GUIDLow, uint16 games);

    private:
        ChatHandler* handler;
};

#define sPvPMgr ACE_Singleton<PvPMgr, ACE_Null_Mutex>::instance()

#endif /*PVP_MGR_H_*/
