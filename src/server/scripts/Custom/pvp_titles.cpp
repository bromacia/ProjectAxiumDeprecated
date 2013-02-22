#include "ScriptPCH.h"

const uint8 AllianceTitles[14] =
{
    1,  // 1  Private
    2,  // 2  Corporal
    3,  // 3  Sergeant
    4,  // 4  Master Sergeant
    5,  // 5  Sergeant Major
    6,  // 6  Knight
    7,  // 7  Knight-Lieutenant
    8,  // 8  Knight-Captain
    9,  // 9  Knight-Champion
    10, // 10 Lieutenant Commander
    11, // 11 Commander
    12, // 12 Marshal
    13, // 13 Field Marshal
    14  // 14 Grand Marshal
};

const uint8 HordeTitles[14] =
{
    15, // 1  Scout
    16, // 2  Grunt
    17, // 3  Sergeant
    18, // 4  Senior Sergeant
    19, // 5  First Sergeant
    20, // 6  Stone Guard
    21, // 7  Blood Guard
    22, // 8  Legionnaire
    23, // 9  Centurion
    24, // 10 Champion
    25, // 11 Lieutenant General
    26, // 12 General
    27, // 13 Warlord
    28  // 14 High Warlord
};

const uint16 RequiredHKs[14] =
{
    500,  // Rank 1
    1000, // Rank 2
    1500, // Rank 3
    2000, // Rank 4
    2500, // Rank 5
    3000, // Rank 6
    3500, // Rank 7
    4000, // Rank 8
    5000, // Rank 9
    6000, // Rank 10
    7000, // Rank 11
    8000, // Rank 12
    9000, // Rank 13
    10000 // Rank 14
};

class pvp_titles : public PlayerScript
{
    public:
        pvp_titles() : PlayerScript("pvp_titles") {}

        void OnPVPKill(Player* killer, Player* killed)
        {
            if (!killer)
                return;

            uint32 HKs = killer->GetUInt32Value(PLAYER_FIELD_LIFETIME_HONORABLE_KILLS);
            for (uint8 rank = 0; rank < 14; rank++)
            {
                if (HKs >= RequiredHKs[rank])
                    killer->SetTitle(sCharTitlesStore.LookupEntry((killer->GetTeam() == ALLIANCE ? AllianceTitles : HordeTitles)[rank]));
            }
        }
};

void AddSC_pvp_titles()
{
    new pvp_titles();
}
