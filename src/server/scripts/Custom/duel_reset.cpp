#include "ScriptPCH.h"
#include "ScriptMgr.h"
#include "Config.h"

class Reset_OnDuelEnd : public PlayerScript
{
    public:
        Reset_OnDuelEnd() : PlayerScript("Reset_OnDuelEnd") {}

    void OnDuelEnd(Player *winner, Player *looser, DuelCompleteType type)
    {
        // reset cooldowns
        if (sWorld->getBoolConfig(CONFIG_DUEL_RESET_COOLDOWN) && type == DUEL_WON)
        {
            winner->RemoveAura(41425); // Remove Hypothermia Debuff
            looser->RemoveAura(41425);
            winner->RemoveAura(25771); // Remove Forbearance Debuff
            looser->RemoveAura(25771);
            winner->RemoveAura(57724); // Remove Sated Debuff
            looser->RemoveAura(57724);
            winner->RemoveAura(57723); // Remove Exhaustion Debuff
            looser->RemoveAura(57723);
            winner->RemoveAura(66233); // Remove Ardent Defender Debuff
            looser->RemoveAura(66233);
            winner->RemoveAura(11196); // Remove Recently Bandaged Debuff
            looser->RemoveAura(11196);
            winner->SetHealth(winner->GetMaxHealth());
            looser->SetHealth(looser->GetMaxHealth());
            if (winner->getPowerType() == POWER_MANA) 
                winner->SetPower(POWER_MANA, winner->GetMaxPower(POWER_MANA));
            if (looser->getPowerType() == POWER_MANA) 
                looser->SetPower(POWER_MANA, looser->GetMaxPower(POWER_MANA));
            winner->RemoveArenaSpellCooldowns();
            looser->RemoveArenaSpellCooldowns();

        }
    }
};

void AddSC_DuelReset()
{
    new Reset_OnDuelEnd;
}