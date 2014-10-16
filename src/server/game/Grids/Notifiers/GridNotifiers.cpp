#include "GridNotifiers.h"
#include "GridNotifiersImpl.h"
#include "WorldPacket.h"
#include "WorldSession.h"
#include "UpdateData.h"
#include "Item.h"
#include "Map.h"
#include "Transport.h"
#include "ObjectAccessor.h"
#include "CellImpl.h"
#include "SpellInfo.h"

using namespace Axium;

void VisibleNotifier::SendToSelf()
{
    // at this moment i_clientGUIDs have guids that not iterate at grid level checks
    // but exist one case when this possible and object not out of range: transports
    if (Transport* transport = i_player.GetTransport())
        for (Transport::PlayerSet::const_iterator itr = transport->GetPassengers().begin();itr != transport->GetPassengers().end();++itr)
        {
            if (vis_guids.find((*itr)->GetGUID()) != vis_guids.end())
            {
                vis_guids.erase((*itr)->GetGUID());

                i_player.UpdateVisibilityOf((*itr), i_data, i_visibleNow);

                if (!(*itr)->isNeedNotify(NOTIFY_VISIBILITY_CHANGED))
                    (*itr)->UpdateVisibilityOf(&i_player);
            }
        }

    for (Player::ClientGUIDs::const_iterator it = vis_guids.begin();it != vis_guids.end(); ++it)
    {
        i_player.m_clientGUIDs.erase(*it);
        i_data.AddOutOfRangeGUID(*it);

        if (IS_PLAYER_GUID(*it))
        {
            Player* player = ObjectAccessor::FindPlayer(*it);
            if (player && player->IsInWorld() && !player->isNeedNotify(NOTIFY_VISIBILITY_CHANGED))
                player->UpdateVisibilityOf(&i_player);
        }
    }

    if (!i_data.HasData())
        return;

    WorldPacket packet;
    i_data.BuildPacket(&packet);
    i_player.GetSession()->SendPacket(&packet);

    for (std::set<Unit*>::const_iterator it = i_visibleNow.begin(); it != i_visibleNow.end(); ++it)
        i_player.SendInitialVisiblePackets(*it);
}

void VisibleChangesNotifier::Visit(PlayerMapType &m)
{
    for (PlayerMapType::iterator iter = m.begin(); iter != m.end(); ++iter)
    {
        if (iter->getSource() == &i_object)
            continue;

        iter->getSource()->UpdateVisibilityOf(&i_object);

        if (!iter->getSource()->GetSharedVisionList().empty())
            for (SharedVisionList::const_iterator i = iter->getSource()->GetSharedVisionList().begin(); i != iter->getSource()->GetSharedVisionList().end(); ++i)
                if ((*i)->m_seer == iter->getSource())
                    (*i)->UpdateVisibilityOf(&i_object);
    }
}

void VisibleChangesNotifier::Visit(CreatureMapType &m)
{
    for (CreatureMapType::iterator iter = m.begin(); iter != m.end(); ++iter)
        if (!iter->getSource()->GetSharedVisionList().empty())
            for (SharedVisionList::const_iterator i = iter->getSource()->GetSharedVisionList().begin(); i != iter->getSource()->GetSharedVisionList().end(); ++i)
                if ((*i)->m_seer == iter->getSource())
                    (*i)->UpdateVisibilityOf(&i_object);
}

void VisibleChangesNotifier::Visit(DynamicObjectMapType &m)
{
    for (DynamicObjectMapType::iterator iter = m.begin(); iter != m.end(); ++iter)
        if (IS_PLAYER_GUID(iter->getSource()->GetCasterGUID()))
            if (Player* caster = (Player*)iter->getSource()->GetCaster())
                if (caster->m_seer == iter->getSource())
                    caster->UpdateVisibilityOf(&i_object);
}

inline void CreatureUnitRelocationWorker(Creature* c, Unit* u)
{
    if (!c || !u)
        return;

    if (!u->isAlive() || !c->isAlive() || c == u || u->isInFlight())
        return;

    if (c->HasReactState(REACT_AGGRESSIVE) && !c->HasUnitState(UNIT_STATE_SIGHTLESS))
        if (c->IsAIEnabled && c->canSeeOrDetect(u, false, true))
            c->AI()->MoveInLineOfSight_Safe(u);
}

void PlayerRelocationNotifier::Visit(PlayerMapType &m)
{
    for (PlayerMapType::iterator iter = m.begin(); iter != m.end(); ++iter)
    {
        Player* player = iter->getSource();
        if (!player)
            continue;

        vis_guids.erase(player->GetGUID());

        i_player.UpdateVisibilityOf(player, i_data, i_visibleNow);

        if (player->m_seer->isNeedNotify(NOTIFY_VISIBILITY_CHANGED))
            continue;

        player->UpdateVisibilityOf(&i_player);
    }
}

void PlayerRelocationNotifier::Visit(CreatureMapType &m)
{
    bool relocated_for_ai = (&i_player == i_player.m_seer);

    for (CreatureMapType::iterator iter = m.begin(); iter != m.end(); ++iter)
    {
        Creature* creature = iter->getSource();
        if (!creature)
            continue;

        vis_guids.erase(creature->GetGUID());

        i_player.UpdateVisibilityOf(creature, i_data, i_visibleNow);

        if (relocated_for_ai && !creature->isNeedNotify(NOTIFY_VISIBILITY_CHANGED))
            CreatureUnitRelocationWorker(creature, &i_player);
    }
}

void CreatureRelocationNotifier::Visit(PlayerMapType &m)
{
    for (PlayerMapType::iterator iter = m.begin(); iter != m.end(); ++iter)
    {
        Player* player = iter->getSource();
        if (!player)
            continue;

        if (!player->m_seer->isNeedNotify(NOTIFY_VISIBILITY_CHANGED))
            player->UpdateVisibilityOf(&i_creature);

        CreatureUnitRelocationWorker(&i_creature, player);
    }
}

void CreatureRelocationNotifier::Visit(CreatureMapType &m)
{
    if (!i_creature.isAlive())
        return;

    for (CreatureMapType::iterator iter = m.begin(); iter != m.end(); ++iter)
    {
        Creature* creature = iter->getSource();
        if (!creature)
            continue;

        CreatureUnitRelocationWorker(&i_creature, creature);

        if (!creature->isNeedNotify(NOTIFY_VISIBILITY_CHANGED))
            CreatureUnitRelocationWorker(creature, &i_creature);
    }
}

void DelayedUnitRelocation::Visit(CreatureMapType &m)
{
    for (CreatureMapType::iterator iter = m.begin(); iter != m.end(); ++iter)
    {
        Creature* creature = iter->getSource();
        if (!creature)
            continue;

        if (!creature->isNeedNotify(NOTIFY_VISIBILITY_CHANGED))
            continue;

        CreatureRelocationNotifier relocate(*creature);

        TypeContainerVisitor<CreatureRelocationNotifier, WorldTypeMapContainer> c2world_relocation(relocate);
        TypeContainerVisitor<CreatureRelocationNotifier, GridTypeMapContainer>  c2grid_relocation(relocate);

        cell.Visit(p, c2world_relocation, i_map, *creature, i_radius);
        cell.Visit(p, c2grid_relocation, i_map, *creature, i_radius);
    }
}

void DelayedUnitRelocation::Visit(PlayerMapType &m)
{
    for (PlayerMapType::iterator iter = m.begin(); iter != m.end(); ++iter)
    {
        Player* player = iter->getSource();
        if (!player)
            continue;

        if (!player->m_seer->isNeedNotify(NOTIFY_VISIBILITY_CHANGED))
            continue;

        if (player != player->m_seer && !player->m_seer->IsPositionValid())
            continue;

        CellCoord pair2(Axium::ComputeCellCoord(player->m_seer->GetPositionX(), player->m_seer->GetPositionY()));
        Cell cell2(pair2);
        //cell.SetNoCreate(); need load cells around viewPoint or player, that's why its commented

        PlayerRelocationNotifier relocate(*player);
        TypeContainerVisitor<PlayerRelocationNotifier, WorldTypeMapContainer> c2world_relocation(relocate);
        TypeContainerVisitor<PlayerRelocationNotifier, GridTypeMapContainer>  c2grid_relocation(relocate);

        cell2.Visit(pair2, c2world_relocation, i_map, *player->m_seer, i_radius);
        cell2.Visit(pair2, c2grid_relocation, i_map, *player->m_seer, i_radius);

        relocate.SendToSelf();
    }
}

void AIRelocationNotifier::Visit(CreatureMapType &m)
{
    for (CreatureMapType::iterator iter = m.begin(); iter != m.end(); ++iter)
    {
        Creature* creature = iter->getSource();
        if (!creature)
            continue;

        CreatureUnitRelocationWorker(creature, &i_unit);
        if (isCreature)
            CreatureUnitRelocationWorker((Creature*)&i_unit, creature);
    }
}

void MessageDistDeliverer::Visit(PlayerMapType &m)
{
    for (PlayerMapType::iterator iter = m.begin(); iter != m.end(); ++iter)
    {
        Player* target = iter->getSource();
        if (!target)
            continue;

        if (!target->InSamePhase(i_phaseMask))
            continue;

        if (target->GetExactDist2dSq(i_source) > i_distSq)
            continue;

        // Send packet to all who are sharing the player's vision
        if (!target->GetSharedVisionList().empty())
        {
            SharedVisionList::const_iterator i = target->GetSharedVisionList().begin();
            for (; i != target->GetSharedVisionList().end(); ++i)
                if ((*i)->m_seer == target)
                    SendPacket(*i);
        }

        if (target->m_seer == target || target->GetVehicle())
            SendPacket(target);
    }
}

void MessageDistDeliverer::Visit(CreatureMapType &m)
{
    for (CreatureMapType::iterator iter = m.begin(); iter != m.end(); ++iter)
    {
        Creature* target = iter->getSource();
        if (!target)
            continue;

        if (!target->InSamePhase(i_phaseMask))
            continue;

        if (target->GetExactDist2dSq(i_source) > i_distSq)
            continue;

        // Send packet to all who are sharing the creature's vision
        if (!target->GetSharedVisionList().empty())
        {
            SharedVisionList::const_iterator i = target->GetSharedVisionList().begin();
            for (; i != target->GetSharedVisionList().end(); ++i)
                if ((*i)->m_seer == target)
                    SendPacket(*i);
        }
    }
}

void MessageDistDeliverer::Visit(DynamicObjectMapType &m)
{
    for (DynamicObjectMapType::iterator iter = m.begin(); iter != m.end(); ++iter)
    {
        DynamicObject* target = iter->getSource();
        if (!target)
            continue;

        if (!target->InSamePhase(i_phaseMask))
            continue;

        if (target->GetExactDist2dSq(i_source) > i_distSq)
            continue;

        if (IS_PLAYER_GUID(target->GetCasterGUID()))
        {
            // Send packet back to the caster if the caster has vision of dynamic object
            Player* caster = (Player*)target->GetCaster();
            if (caster && caster->m_seer == target)
                SendPacket(caster);
        }
    }
}

/*
void
MessageDistDeliverer::VisitObject(Player* player)
{
    if (!i_ownTeamOnly || (i_source.GetTypeId() == TYPEID_PLAYER && player->GetTeam() == ((Player&)i_source).GetTeam()))
    {
        SendPacket(player);
    }
}
*/

template<class T>
void ObjectUpdater::Visit(GridRefManager<T> &m)
{
    for (typename GridRefManager<T>::iterator iter = m.begin(); iter != m.end(); ++iter)
    {
        if (iter->getSource()->IsInWorld())
            iter->getSource()->Update(i_timeDiff);
    }
}

bool AnyDeadUnitObjectInRangeCheck::operator()(Player* u)
{
    return !u->isAlive() && !u->HasAuraType(SPELL_AURA_GHOST) && i_searchObj->IsWithinDistInMap(u, i_range);
}

bool AnyDeadUnitObjectInRangeCheck::operator()(Corpse* u)
{
    return u->GetType() != CORPSE_BONES && i_searchObj->IsWithinDistInMap(u, i_range);
}

bool AnyDeadUnitObjectInRangeCheck::operator()(Creature* u)
{
    return !u->isAlive() && i_searchObj->IsWithinDistInMap(u, i_range);
}

bool AnyDeadUnitSpellTargetInRangeCheck::operator()(Player* u)
{
    return AnyDeadUnitObjectInRangeCheck::operator()(u)
        && (i_spellInfo->CheckTarget(i_searchObj, u, true) == SPELL_CAST_OK)
        && i_searchObj->IsTargetMatchingCheck(u, i_check);
}

bool AnyDeadUnitSpellTargetInRangeCheck::operator()(Corpse* u)
{
    Player* owner = ObjectAccessor::FindPlayer(u->GetOwnerGUID());
    return owner && AnyDeadUnitObjectInRangeCheck::operator()(u)
        && (i_spellInfo->CheckTarget(i_searchObj, owner, true) == SPELL_CAST_OK)
        && i_searchObj->IsTargetMatchingCheck(owner, i_check);
}

bool AnyDeadUnitSpellTargetInRangeCheck::operator()(Creature* u)
{
    return AnyDeadUnitObjectInRangeCheck::operator()(u)
        && (i_spellInfo->CheckTarget(i_searchObj, u, true) == SPELL_CAST_OK)
        && i_searchObj->IsTargetMatchingCheck(u, i_check);
}

template void ObjectUpdater::Visit<GameObject>(GameObjectMapType &);
template void ObjectUpdater::Visit<DynamicObject>(DynamicObjectMapType &);
