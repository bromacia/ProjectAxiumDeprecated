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
        players[i]->RemoveAllTempSummons();

        if (Pet* pet = players[i]->GetPet())
            pet->SetIsDueling(false);
    }
}

void DuelMgr::HandlePlayerState(Player* player, bool save)
{
    if (!player)
        return;

    player->CombatStop();

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
            for (Unit::AuraApplicationMap::iterator itr = auras.begin(); itr != auras.end();)
            {
                if (!CheckAura(sSpellMgr->GetSpellInfo(itr->first)))
                {
                    ++itr;
                    continue;
                }

                player->playerState.Auras.insert(Unit::AuraApplicationMap::value_type(itr->first, itr->second));
                player->RemoveAura((itr++)->first);
            }
        }

        SpellCooldowns& cooldowns = player->GetSpellCooldownMap();
        if (!cooldowns.empty())
        {
            for (SpellCooldowns::iterator itr = cooldowns.begin(); itr != cooldowns.end();)
            {
                player->playerState.Cooldowns[itr->first] = itr->second;
                player->RemoveSpellCooldown((itr++)->first, true);
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
            for (Unit::AuraApplicationMap::iterator itr = auras.begin(); itr != auras.end();)
            {
                if (!CheckAura(sSpellMgr->GetSpellInfo(itr->first)))
                {
                    ++itr;
                    continue;
                }

                player->RemoveAura((itr++)->first);
            }
        }

        if (!player->playerState.Auras.empty())
        {
            for (Unit::AuraApplicationMap::iterator itr = player->playerState.Auras.begin(); itr != player->playerState.Auras.end();)
            {
                player->AddAura(itr->first, player);
                player->playerState.Auras.erase((itr++));
            }
        }

        player->RemoveAllPlayerSpellCooldowns();

        typedef std::vector<uint32> NonCombatSpells;
        NonCombatSpells ncSpells;

        if (!player->playerState.Cooldowns.empty())
        {
            for (SpellCooldowns::iterator itr = player->playerState.Cooldowns.begin(); itr != player->playerState.Cooldowns.end();)
            {
                if (const SpellInfo* spellInfo = sSpellMgr->GetSpellInfo(itr->first))
                    if (spellInfo->Attributes & SPELL_ATTR0_CANT_USED_IN_COMBAT)
                        ncSpells.push_back(itr->first);

                player->AddSpellCooldown(itr->first, itr->second.itemid, itr->second.end);
                player->playerState.Cooldowns.erase((itr++));
            }

            player->SendInitialSpells();

            // We need to send a generic packet here to update the client.
            // The reason why SMSG_SPELL_COOLDOWN was because of it's
            // small size compared to player object update
            WorldPacket data(SMSG_SPELL_COOLDOWN, 8 + 1 + 4 + 4);
            data << uint64(player->GetGUID());
            data << uint8(0);
            data << uint32(0);
            data << uint32(0);
            player->GetSession()->SendPacket(&data);
        }

        for (NonCombatSpells::iterator itr = ncSpells.begin(); itr != ncSpells.end(); ++itr)
            player->RemoveSpellCooldown(*itr, true);

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

    // Deserter
    if (spellInfo->Id == 26013)
        return false;

    return true;
}
