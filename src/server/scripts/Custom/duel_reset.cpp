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
            if (winner->GetZoneId() == 3521 || loser->GetZoneId() == 3521)
                return;
            winner->RemoveAura(41425); // Remove Hypothermia Debuff
            loser->RemoveAura(41425);
            winner->RemoveAura(25771); // Remove Forbearance Debuff
            loser->RemoveAura(25771);
            winner->RemoveAura(57724); // Remove Sated Debuff
            loser->RemoveAura(57724);
            winner->RemoveAura(57723); // Remove Exhaustion Debuff
            loser->RemoveAura(57723);
            winner->RemoveAura(66233); // Remove Ardent Defender Debuff
            loser->RemoveAura(66233);
            winner->RemoveAura(11196); // Remove Recently Bandaged Debuff
            loser->RemoveAura(11196);
            winner->SetHealth(winner->GetMaxHealth());
            loser->SetHealth(loser->GetMaxHealth());
            if (winner->getPowerType() == POWER_MANA) 
                winner->SetPower(POWER_MANA, winner->GetMaxPower(POWER_MANA));
            if (loser->getPowerType() == POWER_MANA) 
                loser->SetPower(POWER_MANA, loser->GetMaxPower(POWER_MANA));
            winner->RemoveArenaSpellCooldowns();
            loser->RemoveArenaSpellCooldowns();
            if (winner->getClass() == CLASS_WARLOCK && !winner->HasItemCount(36892, 1, true))
                winner->AddItem(36892, 1);
            if (loser->getClass() == CLASS_WARLOCK && !loser->HasItemCount(36892, 1, true))
                loser->AddItem(36892, 1);
        }
    }
};

void AddSC_DuelReset()
{
    new Reset_OnDuelEnd;
}
