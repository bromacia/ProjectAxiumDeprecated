#include "DuelMgr.h"
#include "Player.h"
#include "Unit.h"
#include "SpellInfo.h"
#include "SpellMgr.h"
#include "SpellAuras.h"

DuelMgr::DuelMgr()
{
}

DuelMgr::~DuelMgr()
{
}

void DuelMgr::HandleDuelStart(Player* initiator, Player* opponent)
{
    if (!initiator || !opponent)
        return;

    Player* players[2] = { initiator, opponent };

    for (uint8 i = 0; i < 2; ++i)
    {
        HandlePlayerState(players[i], true);
        players[i]->SetIsDueling(true);
        players[i]->ClearDiminishings();
        players[i]->ClearComboPoints();
        players[i]->ClearInCombat();
        players[i]->getHostileRefManager().deleteReferences();
        players[i]->RemoveAllTempSummons();

        if (Pet* pet = players[i]->GetPet())
        {
            pet->SetIsDueling(true);
            pet->RemoveAllNegativeAuras();
            pet->SetHealth(pet->GetMaxHealth());
            pet->SetPower(POWER_MANA, pet->GetMaxPower(POWER_MANA));
            pet->SetPower(POWER_FOCUS, pet->GetMaxPower(POWER_FOCUS));
            pet->RemoveAllPetSpellCooldowns(players[i]);
            pet->ClearDiminishings();
            pet->ClearInCombat();
            pet->getHostileRefManager().deleteReferences();
        }
    }
}

void DuelMgr::HandleDuelEnd(Player* winner, Player* loser, DuelCompleteType type)
{
    if (!winner || !loser)
        return;

    Player* players[2] = { winner, loser };

    for (uint8 i = 0; i < 2; ++i)
    {
        players[i]->SetIsDueling(false);
        HandlePlayerState(players[i], false);

        if (Pet* pet = players[i]->GetPet())
            pet->SetIsDueling(false);
    }
}

void DuelMgr::HandlePlayerState(Player* player, bool save)
{
    if (!player)
        return;

    if (save)
    {
        player->playerState.Health = 0;
        player->playerState.Mana = 0;
        player->playerState.Auras.clear();
        player->playerState.Cooldowns.clear();

        player->playerState.Health = player->GetHealth();
        player->playerState.Mana = player->GetPower(POWER_MANA);

        player->SetHealth(player->GetMaxHealth());
        player->SetPower(POWER_MANA, player->GetMaxPower(POWER_MANA));
        player->SetPower(POWER_ENERGY, player->GetMaxPower(POWER_ENERGY));
        player->SetPower(POWER_RAGE, 0);
        player->SetPower(POWER_RUNIC_POWER, 0);

        Unit::AuraApplicationMap& auras = player->GetAppliedAuras();
        if (!auras.empty())
        {
            for (Unit::AuraApplicationMap::iterator itr = auras.begin(); itr != auras.end(); ++itr)
            {
                if (!CheckAura(sSpellMgr->GetSpellInfo(itr->first)))
                    continue;

                player->playerState.Auras.insert(Unit::AuraApplicationMap::value_type(itr->first, itr->second));
                player->RemoveAura(itr->first);
            }
        }

        SpellCooldowns& cooldowns = player->GetSpellCooldownMap();
        if (!cooldowns.empty())
        {
            for (SpellCooldowns::const_iterator itr = cooldowns.begin(); itr != cooldowns.end(); ++itr)
            {
                player->playerState.Cooldowns[itr->first] = itr->second;
                player->RemoveSpellCooldown(itr->first, true);
            }
        }
    }
    else
    {
        if (player->playerState.Health)
            player->SetHealth(player->playerState.Health);

        if (player->playerState.Mana)
            player->SetPower(POWER_MANA, player->playerState.Mana);

        Unit::AuraApplicationMap& auras = player->GetAppliedAuras();
        if (!auras.empty())
        {
            for (Unit::AuraApplicationMap::iterator itr = auras.begin(); itr != auras.end(); ++itr)
            {
                if (!CheckAura(sSpellMgr->GetSpellInfo(itr->first)))
                    continue;

                player->RemoveAura(itr->first);
            }
        }

        if (!player->playerState.Auras.empty())
        {
            for (Unit::AuraApplicationMap::iterator itr = player->playerState.Auras.begin(); itr != player->playerState.Auras.end(); ++itr)
            {
                player->AddAura(itr->first, player);
                player->playerState.Auras.erase(itr);
            }
        }

        if (!player->playerState.Cooldowns.empty())
        {
            for (SpellCooldowns::const_iterator itr = player->playerState.Cooldowns.begin(); itr != player->playerState.Cooldowns.end(); ++itr)
            {
                player->AddSpellCooldown(itr->first, itr->second.itemid, itr->second.end);
                player->playerState.Cooldowns.erase(itr);
            }

            player->SendInitialSpells();
            player->SendUpdateToPlayer(player);
        }

        player->playerState.Health = 0;
        player->playerState.Mana = 0;
        player->playerState.Auras.clear();
        player->playerState.Cooldowns.clear();
    }
}

bool DuelMgr::CheckAura(const SpellInfo* spellInfo)
{
    if (!spellInfo)
        return false;

    if (spellInfo->IsPositive() || spellInfo->GetDuration() == -1 || spellInfo->IsPassive())
        return false;

    return true;
}
