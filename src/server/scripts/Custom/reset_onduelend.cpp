#include "ScriptPCH.h"
#include "ScriptMgr.h"

class Reset_OnDuelEnd : public PlayerScript
{
    public:
        Reset_OnDuelEnd() : PlayerScript("Reset_OnDuelEnd") {}

        void OnDuelEnd(Player* winner, Player* loser, DuelCompleteType type)
        {
            bool reset = false;
            if (winner->GetAreaId() == 85 || loser->GetAreaId() == 85)
                reset = true;

            winner->SetIsDueling(false);
            loser->SetIsDueling(false);

            if (reset)
            {
                winner->RemoveAllNegativeAuras();
                loser->RemoveAllNegativeAuras();
                winner->SetHealth(winner->GetMaxHealth());
                loser->SetHealth(loser->GetMaxHealth());
                winner->SetPower(POWER_MANA, winner->GetMaxPower(POWER_MANA));
                loser->SetPower(POWER_MANA,  loser->GetMaxPower(POWER_MANA));
                winner->SetPower(POWER_ENERGY, winner->GetMaxPower(POWER_ENERGY));
                loser->SetPower(POWER_ENERGY,  loser->GetMaxPower(POWER_ENERGY));
                winner->SetPower(POWER_RAGE, 0);
                loser->SetPower(POWER_RAGE, 0);
                winner->SetPower(POWER_RUNIC_POWER, 0);
                loser->SetPower(POWER_RUNIC_POWER, 0);
                winner->RemoveAllPlayerSpellCooldowns();
                loser->RemoveAllPlayerSpellCooldowns();
                winner->ClearDiminishings();
                loser->ClearDiminishings();
                winner->ClearComboPoints();
                loser->ClearComboPoints();
                winner->ClearInCombat();
                loser->ClearInCombat();
                winner->getHostileRefManager().deleteReferences();
                loser->getHostileRefManager().deleteReferences();
                winner->RemoveAllTempSummons();
                loser->RemoveAllTempSummons();

                if (Pet* winnerPet = winner->GetPet())
                {
                    winnerPet->SetIsDueling(false);

                    if (reset)
                    {
                        winnerPet->RemoveAllNegativeAuras();
                        winnerPet->SetHealth(winnerPet->GetMaxHealth());
                        winnerPet->SetPower(POWER_MANA, winnerPet->GetMaxPower(POWER_MANA));
                        winnerPet->SetPower(POWER_FOCUS, winnerPet->GetMaxPower(POWER_FOCUS));
                        winnerPet->RemoveAllPetSpellCooldowns(winner);
                        winnerPet->ClearDiminishings();
                        winnerPet->ClearInCombat();
                        winnerPet->getHostileRefManager().deleteReferences();
                    }
                }

                if (Pet* loserPet = loser->GetPet())
                {
                    loserPet->SetIsDueling(false);

                    if (reset)
                    {
                        loserPet->RemoveAllNegativeAuras();
                        loserPet->SetHealth(loserPet->GetMaxHealth());
                        loserPet->SetPower(POWER_MANA, loserPet->GetMaxPower(POWER_MANA));
                        loserPet->SetPower(POWER_FOCUS, loserPet->GetMaxPower(POWER_FOCUS));
                        loserPet->RemoveAllPetSpellCooldowns(loser);
                        loserPet->ClearDiminishings();
                        loserPet->ClearInCombat();
                        loserPet->getHostileRefManager().deleteReferences();
                    }
                }
            }
        }
};

void AddSC_Reset_OnDuelEnd()
{
    new Reset_OnDuelEnd;
}
