#include "ScriptPCH.h"
#include "ScriptMgr.h"

class Reset_OnDuelEnd : public PlayerScript
{
    public:
        Reset_OnDuelEnd() : PlayerScript("Reset_OnDuelEnd") {}

        void OnDuelEnd(Player* winner, Player* loser, DuelCompleteType type)
        {
            winner->SetIsDueling(false);
            loser->SetIsDueling(false);
            winner->RemoveAllNegativeAuras();
            loser->RemoveAllNegativeAuras();

            if (Pet* winnerPet = winner->GetPet())
                winnerPet->SetIsDueling(false);

            if (Pet* loserPet = loser->GetPet())
                loserPet->SetIsDueling(false);
        }
};

void AddSC_Reset_OnDuelEnd()
{
    new Reset_OnDuelEnd;
}
