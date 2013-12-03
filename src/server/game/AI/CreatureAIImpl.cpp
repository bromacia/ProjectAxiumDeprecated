/*
 * Copyright (C) 2008-2012 TrinityCore <http://www.trinitycore.org/>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "CreatureAIImpl.h"

// Sets event phase, must be in range 1 - 8
void EventMap::SetPhase(uint32 phase)
{
    if (phase && phase < 8)
        _phase = (1 << (phase + 24));
}

// Creates new event entry in map with given id, time, group if given (1 - 8) and phase if given (1 - 8)
// 0 for group/phase means it belongs to no group or runs in all phases
void EventMap::ScheduleEvent(uint32 eventId, uint32 time, uint32 groupId, uint32 phase)
{
    time += _time;
    if (groupId && groupId < 9)
        eventId |= (1 << (groupId + 16));
    if (phase && phase < 8)
        eventId |= (1 << (phase + 24));
    const_iterator itr = find(time);
    while (itr != end())
    {
        ++time;
        itr = find(time);
    }

    insert(std::make_pair(time, eventId));
}

// Removes event with specified id and creates new entry for it
void EventMap::RescheduleEvent(uint32 eventId, uint32 time, uint32 groupId, uint32 phase)
{
    CancelEvent(eventId);
    ScheduleEvent(eventId, time, groupId, phase);
}

// Reschedules closest event
void EventMap::RepeatEvent(uint32 time)
{
    if (empty())
        return;

    uint32 eventId = begin()->second;
    erase(begin());
    time += _time;
    const_iterator itr = find(time);
    while (itr != end())
    {
        ++time;
        itr = find(time);
    }

    insert(std::make_pair(time, eventId));
}

// Gets next event id to execute and removes it from map
uint32 EventMap::ExecuteEvent()
{
    while (!empty())
    {
        if (begin()->first > _time)
            return 0;
        else if (_phase && (begin()->second & 0xFF000000) && !(begin()->second & _phase))
            erase(begin());
        else
        {
            uint32 eventId = (begin()->second & 0x0000FFFF);
            erase(begin());
            return eventId;
        }
    }
    return 0;
}

// Gets next event id to execute
uint32 EventMap::GetEvent()
{
    while (!empty())
    {
        if (begin()->first > _time)
            return 0;
        else if (_phase && (begin()->second & 0xFF000000) && !(begin()->second & _phase))
            erase(begin());
        else
            return (begin()->second & 0x0000FFFF);
    }

    return 0;
}

// Delay all events
void EventMap::DelayEvents(uint32 delay)
{
    if (delay < _time)
        _time -= delay;
    else
        _time = 0;
}

// Delay all events having the specified Group
void EventMap::DelayEvents(uint32 delay, uint32 groupId)
{
    uint32 nextTime = _time + delay;
    uint32 groupMask = (1 << (groupId + 16));
    for (iterator itr = begin(); itr != end() && itr->first < nextTime;)
    {
        if (itr->second & groupMask)
        {
            ScheduleEvent(itr->second, itr->first - _time + delay);
            erase(itr);
            itr = begin();
        }
        else
            ++itr;
    }
}

// Cancel events with specified id
void EventMap::CancelEvent(uint32 eventId)
{
    for (iterator itr = begin(); itr != end();)
    {
        if (eventId == (itr->second & 0x0000FFFF))
        {
            erase(itr);
            itr = begin();
        }
        else
            ++itr;
    }
}

// Cancel events belonging to specified group
void EventMap::CancelEventGroup(uint32 groupId)
{
    uint32 groupMask = (1 << (groupId + 16));

    for (iterator itr = begin(); itr != end();)
    {
        if (itr->second & groupMask)
        {
            erase(itr);
            itr = begin();
        }
        else
            ++itr;
    }
}

// Returns time of next event to execute
// To get how much time remains substract _time
uint32 EventMap::GetNextEventTime(uint32 eventId) const
{
    for (const_iterator itr = begin(); itr != end(); ++itr)
        if (eventId == (itr->second & 0x0000FFFF))
            return itr->first;

    return 0;
}

void CreatureAI::SetGazeOn(Unit* target)
{
    if (me->IsValidAttackTarget(target))
    {
        AttackStart(target);
        me->SetReactState(REACT_PASSIVE);
    }
}

bool CreatureAI::UpdateVictimWithGaze()
{
    if (!me->isInCombat())
        return false;

    if (me->HasReactState(REACT_PASSIVE))
    {
        if (me->getVictim())
            return true;
        else
            me->SetReactState(REACT_AGGRESSIVE);
    }

    if (Unit* victim = me->SelectVictim())
        AttackStart(victim);
    return me->getVictim();
}

bool CreatureAI::UpdateVictim()
{
    if (!me->isInCombat() && me->GetScriptName() != "npc_shadowfiend") // Shadowfiend must start attacking immediately (victim pre-set in SummonGuardian)
        return false;

    if (!me->HasReactState(REACT_PASSIVE) || me->GetScriptName() == "npc_shadowfiend")
    {
        if (Unit* victim = me->SelectVictim())
        {
            if (me->GetScriptName() == "npc_mirror_image")
                AttackStartCaster(victim, 30.0f);
            else
                AttackStart(victim);
        }
        return me->getVictim();
    }
    else if (me->getThreatManager().isThreatListEmpty())
    {
        EnterEvadeMode();
        return false;
    }

    return true;
}

bool CreatureAI::_EnterEvadeMode()
{
    if (!me->isAlive())
        return false;

    // dont remove vehicle auras, passengers arent supposed to drop off the vehicle
    me->RemoveAllAurasExceptType(SPELL_AURA_CONTROL_VEHICLE);

    // sometimes bosses stuck in combat?
    me->DeleteThreatList();
    me->CombatStop(true);
    me->LoadCreaturesAddon();
    me->SetLootRecipient(NULL);
    me->ResetPlayerDamageReq();

    if (me->IsInEvadeMode())
        return false;

    return true;
}

void UnitAI::DoCast(Unit* victim, uint32 spellId, bool triggered)
{
    if (!victim || (me->HasUnitState(UNIT_STATE_CASTING) && !triggered))
        return;

    me->CastSpell(victim, spellId, triggered);
}

void UnitAI::DoCastVictim(uint32 spellId, bool triggered)
{
    me->CastSpell(me->getVictim(), spellId, triggered);
}

void UnitAI::DoCastAOE(uint32 spellId, bool triggered)
{
    if (!triggered && me->HasUnitState(UNIT_STATE_CASTING))
        return;

    me->CastSpell((Unit*)NULL, spellId, triggered);
}

Creature* CreatureAI::DoSummon(uint32 entry, const Position& pos, uint32 despawnTime, TempSummonType summonType)
{
    return me->SummonCreature(entry, pos, summonType, despawnTime);
}

Creature* CreatureAI::DoSummon(uint32 entry, WorldObject* obj, float radius, uint32 despawnTime, TempSummonType summonType)
{
    Position pos;
    obj->GetRandomNearPosition(pos, radius);
    return me->SummonCreature(entry, pos, summonType, despawnTime);
}

Creature* CreatureAI::DoSummonFlyer(uint32 entry, WorldObject* obj, float flightZ, float radius, uint32 despawnTime, TempSummonType summonType)
{
    Position pos;
    obj->GetRandomNearPosition(pos, radius);
    pos.m_positionZ += flightZ;
    return me->SummonCreature(entry, pos, summonType, despawnTime);
}