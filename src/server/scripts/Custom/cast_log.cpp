#include "ScriptPCH.h"
#include "Spell.h"
#include "Log.h"
#include "Config.h"
#include <sstream>

class cast_log : public PlayerScript
{
public:
    cast_log() : PlayerScript("cast_log") {}

    void OnCastSpellOpcode(Player* player, Spell* spell)
    {
        if (!sWorld->getBoolConfig(CONFIG_CASTLOG_ENABLED))
            return;

        Player* target = NULL;
        if (spell->m_targets.GetUnitTarget())
            target = spell->m_targets.GetUnitTarget()->ToPlayer();

        if (!target)
            return;

        bool found = false;
        uint32 accountId;
        std::istringstream ss(ConfigMgr::GetStringDefault("CastLogs.Accounts", ""));

        while (ss >> accountId)
        {
            if (accountId == player->GetSession()->GetAccountId())
            {
                found = true;
                break;
            }
        }

        if (!found)
            return;

        SpellCastResult result = spell->CheckCast(true);
        if (result != SPELL_CAST_OK)
            return;

        if (target == player)
            sLog->outCast("CastSpellOpcode: Player %s (%u) casts %u on self",
                player->GetName(), player->GetGUIDLow(), spell->GetSpellInfo()->Id);
        else
            sLog->outCast("CastSpellOpcode: Player %s (%u) casts %u - Target: %s (%u)",
                player->GetName(), player->GetGUIDLow(), spell->GetSpellInfo()->Id, target->GetName(), target->GetGUIDLow());
    }
};

void AddSC_cast_log()
{
    new cast_log();
}