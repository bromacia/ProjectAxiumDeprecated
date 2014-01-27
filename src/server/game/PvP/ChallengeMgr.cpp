#include "ChallengeMgr.h"
#include "Chat.h"
#include "Battleground.h"
#include "BattlegroundMgr.h"
#include "BattlegroundQueue.h"
#include "Player.h"
#include "SocialMgr.h"
#include "Group.h"
#include "SharedDefines.h"

void ChallengeMgr::HandleChallenge(uint64 challengerGUID, uint64 challengedGUID, uint8 map)
{
    Player* challengerPlayer = ObjectAccessor::FindPlayer(challengerGUID);
    if (!challengerPlayer)
        return;

    Player* challengedPlayer = ObjectAccessor::FindPlayer(challengedGUID);
    if (!challengedPlayer)
        return;

    if (challengerPlayer == challengedPlayer)
    {
        challengerPlayer->SendSysMessage("You can't challenge yourself.");
        return;
    }

    if (challengedPlayer->HasGameMasterTagOn())
    {
        challengerPlayer->SendSysMessage("You can't challenge Game Masters.");
        return;
    }

    if (challengedPlayer->isDND())
    {
        challengerPlayer->SendSysMessage("You can't challenge players with Do Not Disturbed enabled.");
        return;
    }

    if (challengedPlayer->GetSocial()->HasIgnore(GUID_LOPART(challengerGUID)))
    {
        challengerPlayer->SendSysMessage("You can't challenge players who have ignored you.");
        return;
    }

    if (challengerPlayer->InBattleground())
    {
        challengerPlayer->SendSysMessage("You can't challenge another player while in a battleground.");
        return;
    }

    if (challengedPlayer->InBattleground())
    {
        challengerPlayer->SendSysMessage("The player you're trying to challenge is in a battleground.");
        return;
    }

    if (challengerPlayer->InBattlegroundQueue())
    {
        challengerPlayer->SendSysMessage("You can't challenge another player while in a battleground or arena queue.");
        return;
    }

    if (challengedPlayer->InBattlegroundQueue())
    {
        challengerPlayer->SendSysMessage("The player you're trying to challenge is in a battleground or arena queue.");
        return;
    }

    Group* groupA = challengerPlayer->GetGroup();
    Group* groupB = challengedPlayer->GetGroup();

    if (groupA && groupB && groupA != groupB)
    {
        if (groupA->GetMembersCount() != groupB->GetMembersCount())
        {
            challengerPlayer->SendSysMessage("Your group size doesn't match %s's group size.", challengedPlayer->GetName());
            return;
        }

        switch (groupA->GetMembersCount())
        {
            case 2: arenaType = ARENA_TYPE_2v2; break;
            case 3: arenaType = ARENA_TYPE_3v3; break;
            case 5: arenaType = ARENA_TYPE_5v5; break;
        }

        if (!arenaType)
        {
            challengerPlayer->SendSysMessage("Your group size doens't fit into any arena bracket.");
            return;
        }

        Group::MemberSlotList membersA = groupA->GetMembers();
        Group::MemberSlotList membersB = groupB->GetMembers();

        for (Group::member_citerator citr = membersA.begin(); citr != membersA.end(); ++citr)
        {
            Player* member = ObjectAccessor::FindPlayer(citr->guid);

            if (member->InBattlegroundQueue())
            {
                challengerPlayer->SendSysMessage("A player from your group is in a battleground or arena queue.");
                return;
            }

            if (member->InBattleground())
            {
                challengerPlayer->SendSysMessage("A player from your group is in a battleground.");
                return;
            }

            teamA.push_back(citr->guid);
        }

        for (Group::member_citerator citr = membersB.begin(); citr != membersB.end(); ++citr)
        {
            Player* member = ObjectAccessor::FindPlayer(citr->guid);

            if (member->InBattlegroundQueue())
            {
                challengerPlayer->SendSysMessage("A player in the group of the player you're challenging is in a battleground or arena queue.");
                return;
            }

            if (member->InBattleground())
            {
                challengerPlayer->SendSysMessage("A player in the group of the player you're challenging is in a battleground.");
                return;
            }

            teamB.push_back(citr->guid);
        }

        if (teamA.size() != teamB.size())
            return;
    }
    else
    {
        arenaType = ARENA_TYPE_2v2;

        teamA.push_back(challengerGUID);
        teamB.push_back(challengedGUID);
    }

    switch (map)
    {
        case 1:  bgTypeId = BATTLEGROUND_NA; break;
        case 2:  bgTypeId = BATTLEGROUND_BE; break;
        case 3:  bgTypeId = BATTLEGROUND_RL; break;
        case 4:  bgTypeId = BATTLEGROUND_DS; break;
        default: bgTypeId = BATTLEGROUND_AA; break;
    }

    Battleground* battlegroundTemplate = sBattlegroundMgr->GetBattlegroundTemplate((BattlegroundTypeId)bgTypeId);
    if (!battlegroundTemplate)
    {
        challengerPlayer->SendSysMessage("Unable to find battleground template for type Id %u.", bgTypeId);
        return;
    }

    const PvPDifficultyEntry* bracketEntry = GetBattlegroundBracketByLevel(battlegroundTemplate->GetMapId(), challengedPlayer->getLevel());
    if (!bracketEntry)
    {
        challengerPlayer->SendSysMessage("Unable to find bracket entry for map %u.", battlegroundTemplate->GetMapId());
        return;
    }

    CreateBattleground(bracketEntry, teamA.size());

    BattlegroundBracketId bracketId = bracketEntry->GetBracketId();
    bgQueueTypeId = BattlegroundMgr::BGQueueTypeId((BattlegroundTypeId)bgTypeId, arenaType);
    bgQueue = &sBattlegroundMgr->m_BattlegroundQueues[bgQueueTypeId];

    for (Players::iterator itr = teamA.begin(); itr != teamA.end(); ++itr)
    {
        if (Player* player = ObjectAccessor::FindPlayer(*itr))
        {
            AddPlayerToBattleground(player, bracketId);
            player->SendSysMessage("You have challenged %s.", challengedPlayer->GetName());
        }
    }

    for (Players::iterator itr = teamB.begin(); itr != teamB.end(); ++itr)
    {
        if (Player* player = ObjectAccessor::FindPlayer(*itr))
        {
            AddPlayerToBattleground(player, bracketId);
            player->SendSysMessage("You have been challenged by %s.", challengerPlayer->GetName());
        }
    }

    CleanupChallenge();
}

void ChallengeMgr::CleanupChallenge()
{
    teamA.clear();
    teamB.clear();
    arenaType = 0;
    bgTypeId = 0;
    bgQueueTypeId = 0;
    bg = NULL;
    bgQueue = NULL;
}

void ChallengeMgr::CreateBattleground(const PvPDifficultyEntry* bracketEntry, uint8 teamSize)
{
    bg = sBattlegroundMgr->CreateNewBattleground((BattlegroundTypeId)bgTypeId, bracketEntry, arenaType, false, bgTypeId == BATTLEGROUND_AA ? true : false);
    bg->SetRated(false);
    bg->SetChallenge(true);
    bg->SetChallengeTeamSize(teamSize);
    bg->StartBattleground();
}

void ChallengeMgr::AddPlayerToBattleground(Player* player, BattlegroundBracketId bracketId)
{
    uint64 guid = player->GetGUID();
    uint32 msTime = getMSTime();
    uint32 queueSlot = player->AddBattlegroundQueueId((BattlegroundQueueTypeId)bgQueueTypeId);

    WorldPacket data;
    sBattlegroundMgr->BuildBattlegroundStatusPacket(&data, bg, queueSlot, STATUS_WAIT_QUEUE, 0, 0, arenaType);
    player->GetSession()->SendPacket(&data);

    sBattlegroundMgr->ScheduleQueueUpdate(0, arenaType, (BattlegroundQueueTypeId)bgQueueTypeId, (BattlegroundTypeId)bgTypeId, bracketId);

    uint32 team = 0;
    if (IsOnTeamA(guid))
        team = ALLIANCE;
    else if (IsOnTeamB(guid))
        team = HORDE;

    if (!team)
        return;

    GroupQueueInfo* ginfo               = new GroupQueueInfo;
    ginfo->BgTypeId                     = (BattlegroundTypeId)bgTypeId;
    ginfo->ArenaType                    = arenaType;
    ginfo->IsRated                      = false;
    ginfo->IsInvitedToBGInstanceGUID    = 0;
    ginfo->JoinTime                     = msTime;
    ginfo->RemoveInviteTime             = 0;
    ginfo->Team                         = team;
    ginfo->ArenaTeamId                  = 0;
    ginfo->ArenaTeamRating              = 0;
    ginfo->ArenaMatchmakerRating        = 0;
    ginfo->OTeam                        = team == HORDE ? ALLIANCE : HORDE;
    ginfo->OpponentsTeamRating          = 0;
    ginfo->OpponentsMatchmakerRating    = 0;
    ginfo->Players.clear();

    PlayerQueueInfo* info   = new PlayerQueueInfo;
    info->GroupInfo         = ginfo;
    info->LastOnlineTime    = msTime;

    ginfo->Players[guid] = info;

    player->challengeInfo.ginfo = ginfo;

    bgQueue->m_QueuedPlayers[guid] = *info;
    bgQueue->m_QueuedGroups[bracketId][team == HORDE ? BG_QUEUE_PREMADE_HORDE : BG_QUEUE_PREMADE_ALLIANCE].push_back(ginfo);
    bgQueue->InviteGroupToBG(ginfo, bg);
}

bool ChallengeMgr::IsOnTeamA(uint64 guid)
{
    for (Players::iterator itr = teamA.begin(); itr != teamA.end(); ++itr)
        if (*itr == guid)
            return true;

    return false;
}

bool ChallengeMgr::IsOnTeamB(uint64 guid)
{
    for (Players::iterator itr = teamB.begin(); itr != teamB.end(); ++itr)
        if (*itr == guid)
            return true;

    return false;
}

ChatCommand* challenge_commandscript::GetCommands() const
{
    static ChatCommand commandTable[] =
    {
        { "challenge",          SEC_PLAYER,         false, &HandleChallengeCommand,                 "", NULL },
        { NULL,                 0,                  false, NULL,                                    "", NULL }
    };
    return commandTable;
}

bool challenge_commandscript::HandleChallengeCommand(ChatHandler* handler, const char* args)
{
    Player* player = handler->GetSession()->GetPlayer();
    if (!player)
        return false;

    if (!*args)
    {
        player->SendSysMessage("Incorrect syntax.");
        player->SendSysMessage("Syntax: .challenge $playerName #arenaMap");
        player->SendSysMessage("Please refer to your Player Handbook for arena map numbers and more information.");
        handler->SetSentErrorMessage(true);
        return false;
    }

    std::string name = strtok((char*)args, " ");
    if (!normalizePlayerName(name))
    {
        player->SendSysMessage("Invalid player name.");
        handler->SetSentErrorMessage(true);
        return false;
    }

    uint64 guid = 0;
    if (Player* player = sObjectAccessor->FindPlayerByName(name.c_str()))
        guid = player->GetGUID();
    else
        guid = sObjectMgr->GetPlayerGUIDByName(name);

    if (!guid)
    {
        player->SendSysMessage("No player found with the name %s.", name.c_str());
        handler->SetSentErrorMessage(true);
        return false;
    }

    uint8 bgTypeId = 0;
    char* bgTypeIdArg = strtok(NULL, " ");

    if (bgTypeIdArg)
        bgTypeId = (uint8)atoi(bgTypeIdArg);

    sChallengeMgr->HandleChallenge(player->GetGUID(), guid, bgTypeId);
    return true;
}

void AddSC_challenge_commandscript()
{
    new challenge_commandscript();
}
