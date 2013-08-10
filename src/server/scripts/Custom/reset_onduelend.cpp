#include "ScriptPCH.h"
#include "ScriptMgr.h"

class Reset_OnDuelEnd : public PlayerScript
{
    public:
        Reset_OnDuelEnd() : PlayerScript("Reset_OnDuelEnd") {}

        void OnDuelEnd(Player* winner, Player* loser, DuelCompleteType type)
        {
            Player* players[2] = { winner, loser };

            for (uint8 i = 0; i < 2; ++i)
            {
                players[i]->SetIsDueling(false);
                players[i]->RemoveAllNegativeAuras();

                if (Pet* winnerPet = players[i]->GetPet())
                    winnerPet->SetIsDueling(false);
            }
        }
};

void AddSC_Reset_OnDuelEnd()
{
    new Reset_OnDuelEnd;
}
