#include "ScriptPCH.h"
#include "ScriptMgr.h"
#include "Config.h"

class Reset_OnDuelEnd : public PlayerScript
{
    public:
        Reset_OnDuelEnd() : PlayerScript("Reset_OnDuelEnd") {}

    void OnDuelEnd(Player* winner, Player* loser, DuelCompleteType type)
    {
        // reset cooldowns
        if (sWorld->getBoolConfig(CONFIG_DUEL_RESET_COOLDOWN) && type == DUEL_WON)
        {
            if (winner->GetMapId() == 530 || loser->GetMapId() == 530)
                return;
            winner->RemoveAllNegativeAuras();
            loser->RemoveAllNegativeAuras();
            winner->SetHealth(winner->GetMaxHealth());
            loser->SetHealth(loser->GetMaxHealth());
            winner->SetPower(POWER_MANA, winner->GetMaxPower(POWER_MANA));
            loser->SetPower(POWER_MANA,  loser->GetMaxPower(POWER_MANA));
            winner->SetPower(POWER_RAGE, 0);
            loser->SetPower(POWER_RAGE, 0);
            winner->RemoveArenaSpellCooldowns();
            loser->RemoveArenaSpellCooldowns();
            winner->ClearDiminishings();
            loser->ClearDiminishings();
            winner->ClearComboPoints();
            loser->ClearComboPoints();
            winner->ClearInCombat();
            loser->ClearInCombat();
        }
    }
};

void AddSC_DuelReset()
{
    new Reset_OnDuelEnd;
}
