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

/* ScriptData
Name: modify_commandscript
%Complete: 100
Comment: All modify related commands
Category: commandscripts
EndScriptData */

#include "ScriptMgr.h"
#include "ObjectMgr.h"
#include "Chat.h"
#include "PvPMgr.h"

class modify_commandscript : public CommandScript
{
public:
    modify_commandscript() : CommandScript("modify_commandscript") { }

    ChatCommand* GetCommands() const
    {
        static ChatCommand modifyCommandTable[] =
        {
            { "hp",                 SEC_GAMEMASTER,     false, &HandleModifyHPCommand,                  "", NULL },
            { "mana",               SEC_GAMEMASTER,     false, &HandleModifyManaCommand,                "", NULL },
            { "rage",               SEC_GAMEMASTER,     false, &HandleModifyRageCommand,                "", NULL },
            { "runicpower",         SEC_GAMEMASTER,     false, &HandleModifyRunicPowerCommand,          "", NULL },
            { "energy",             SEC_GAMEMASTER,     false, &HandleModifyEnergyCommand,              "", NULL },
            { "money",              SEC_GAMEMASTER,     false, &HandleModifyMoneyCommand,               "", NULL },
            { "speed",              SEC_GAMEMASTER,     false, &HandleModifySpeedCommand,               "", NULL },
            { "swim",               SEC_GAMEMASTER,     false, &HandleModifySwimCommand,                "", NULL },
            { "scale",              SEC_GAMEMASTER,     false, &HandleModifyScaleCommand,               "", NULL },
            { "bit",                SEC_GAMEMASTER,     false, &HandleModifyBitCommand,                 "", NULL },
            { "bwalk",              SEC_GAMEMASTER,     false, &HandleModifyBWalkCommand,               "", NULL },
            { "fly",                SEC_GAMEMASTER,     false, &HandleModifyFlyCommand,                 "", NULL },
            { "aspeed",             SEC_GAMEMASTER,     false, &HandleModifyASpeedCommand,              "", NULL },
            { "faction",            SEC_GAMEMASTER,     false, &HandleModifyFactionCommand,             "", NULL },
            { "spell",              SEC_GAMEMASTER,     false, &HandleModifySpellCommand,               "", NULL },
            { "tp",                 SEC_GAMEMASTER,     false, &HandleModifyTalentCommand,              "", NULL },
            { "honor",              SEC_GAMEMASTER,     false, &HandleModifyHonorCommand,               "", NULL },
            { "rep",                SEC_GAMEMASTER,     false, &HandleModifyRepCommand,                 "", NULL },
            { "arena",              SEC_GAMEMASTER,     false, &HandleModifyArenaCommand,               "", NULL },
            { "drunk",              SEC_GAMEMASTER,     false, &HandleModifyDrunkCommand,               "", NULL },
            { "standstate",         SEC_GAMEMASTER,     false, &HandleModifyStandStateCommand,          "", NULL },
            { "displayid",          SEC_GAMEMASTER,     false, &HandleModifyDisplayIdCommand,           "", NULL },
            { "mountid",            SEC_GAMEMASTER,     false, &HandleModifyMountIdCommand,             "", NULL },
            { "phase",              SEC_GAMEMASTER,     false, &HandleModifyPhaseCommand,               "", NULL },
            { "gender",             SEC_GAMEMASTER,     false, &HandleModifyGenderCommand,              "", NULL },
            { NULL,                 0,                  false, NULL,                                    "", NULL }
        };
        static ChatCommand commandTable[] =
        {
            { "modify",             SEC_GAMEMASTER,     false, NULL,                      "", modifyCommandTable },
            { NULL,                 0,                  false, NULL,                                    "", NULL }
        };
        return commandTable;
    }

    //Edit Player HP
    static bool HandleModifyHPCommand(ChatHandler* handler, const char* args)
    {
        if (!*args)
            return false;

        int32 hp = atoi((char*)args);
        int32 hpm = atoi((char*)args);

        if (hp < 1 || hpm < 1 || hpm < hp)
        {
            handler->SendSysMessage(LANG_BAD_VALUE);
            handler->SetSentErrorMessage(true);
            return false;
        }

        Player* target = handler->getSelectedPlayer();
        if (!target)
        {
            handler->SendSysMessage(LANG_NO_CHAR_SELECTED);
            handler->SetSentErrorMessage(true);
            return false;
        }

        if (handler->HasLowerSecurity(target, 0))
            return false;

        handler->PSendSysMessage(LANG_YOU_CHANGE_HP, handler->GetNameLink(target).c_str(), hp, hpm);
        if (handler->needReportToTarget(target))
            target->SendSysMessage(LANG_YOURS_HP_CHANGED, handler->GetNameLink().c_str(), hp, hpm);

        target->SetMaxHealth(hpm);
        target->SetHealth(hp);

        return true;
    }

    //Edit Player Mana
    static bool HandleModifyManaCommand(ChatHandler* handler, const char* args)
    {
        if (!*args)
            return false;

        int32 mana = atoi((char*)args);
        int32 manam = atoi((char*)args);

        if (mana <= 0 || manam <= 0 || manam < mana)
        {
            handler->SendSysMessage(LANG_BAD_VALUE);
            handler->SetSentErrorMessage(true);
            return false;
        }

        Player* target = handler->getSelectedPlayer();
        if (!target)
        {
            handler->SendSysMessage(LANG_NO_CHAR_SELECTED);
            handler->SetSentErrorMessage(true);
            return false;
        }

        // check online security
        if (handler->HasLowerSecurity(target, 0))
            return false;

        handler->PSendSysMessage(LANG_YOU_CHANGE_MANA, handler->GetNameLink(target).c_str(), mana, manam);
        if (handler->needReportToTarget(target))
            target->SendSysMessage(LANG_YOURS_MANA_CHANGED, handler->GetNameLink().c_str(), mana, manam);

        target->SetMaxPower(POWER_MANA, manam);
        target->SetPower(POWER_MANA, mana);

        return true;
    }

    //Edit Player Energy
    static bool HandleModifyEnergyCommand(ChatHandler* handler, const char* args)
    {
        if (!*args)
            return false;

        // char* pmana = strtok((char*)args, " ");
        // if (!pmana)
        //     return false;

        // char* pmanaMax = strtok(NULL, " ");
        // if (!pmanaMax)
        //     return false;

        // int32 manam = atoi(pmanaMax);
        // int32 mana = atoi(pmana);

        int32 energy = atoi((char*)args)*10;
        int32 energym = atoi((char*)args)*10;

        if (energy <= 0 || energym <= 0 || energym < energy)
        {
            handler->SendSysMessage(LANG_BAD_VALUE);
            handler->SetSentErrorMessage(true);
            return false;
        }

        Player* target = handler->getSelectedPlayer();
        if (!target)
        {
            handler->SendSysMessage(LANG_NO_CHAR_SELECTED);
            handler->SetSentErrorMessage(true);
            return false;
        }

        // check online security
        if (handler->HasLowerSecurity(target, 0))
            return false;

        handler->PSendSysMessage(LANG_YOU_CHANGE_ENERGY, handler->GetNameLink(target).c_str(), energy/10, energym/10);
        if (handler->needReportToTarget(target))
            target->SendSysMessage(LANG_YOURS_ENERGY_CHANGED, handler->GetNameLink().c_str(), energy/10, energym/10);

        target->SetMaxPower(POWER_ENERGY, energym);
        target->SetPower(POWER_ENERGY, energy);

        sLog->outDetail(handler->GetTrinityString(LANG_CURRENT_ENERGY), target->GetMaxPower(POWER_ENERGY));

        return true;
    }

    //Edit Player Rage
    static bool HandleModifyRageCommand(ChatHandler* handler, const char* args)
    {
        if (!*args)
            return false;

        // char* pmana = strtok((char*)args, " ");
        // if (!pmana)
        //     return false;

        // char* pmanaMax = strtok(NULL, " ");
        // if (!pmanaMax)
        //     return false;

        // int32 manam = atoi(pmanaMax);
        // int32 mana = atoi(pmana);

        int32 rage = atoi((char*)args)*10;
        int32 ragem = atoi((char*)args)*10;

        if (rage <= 0 || ragem <= 0 || ragem < rage)
        {
            handler->SendSysMessage(LANG_BAD_VALUE);
            handler->SetSentErrorMessage(true);
            return false;
        }

        Player* target = handler->getSelectedPlayer();
        if (!target)
        {
            handler->SendSysMessage(LANG_NO_CHAR_SELECTED);
            handler->SetSentErrorMessage(true);
            return false;
        }

        // check online security
        if (handler->HasLowerSecurity(target, 0))
            return false;

        handler->PSendSysMessage(LANG_YOU_CHANGE_RAGE, handler->GetNameLink(target).c_str(), rage/10, ragem/10);
        if (handler->needReportToTarget(target))
            target->SendSysMessage(LANG_YOURS_RAGE_CHANGED, handler->GetNameLink().c_str(), rage/10, ragem/10);

        target->SetMaxPower(POWER_RAGE, ragem);
        target->SetPower(POWER_RAGE, rage);

        return true;
    }

    // Edit Player Runic Power
    static bool HandleModifyRunicPowerCommand(ChatHandler* handler, const char* args)
    {
        if (!*args)
            return false;

        int32 rune = atoi((char*)args)*10;
        int32 runem = atoi((char*)args)*10;

        if (rune <= 0 || runem <= 0 || runem < rune)
        {
            handler->SendSysMessage(LANG_BAD_VALUE);
            handler->SetSentErrorMessage(true);
            return false;
        }

        Player* target = handler->getSelectedPlayer();
        if (!target)
        {
            handler->SendSysMessage(LANG_NO_CHAR_SELECTED);
            handler->SetSentErrorMessage(true);
            return false;
        }

        handler->PSendSysMessage(LANG_YOU_CHANGE_RUNIC_POWER, handler->GetNameLink(target).c_str(), rune/10, runem/10);
        if (handler->needReportToTarget(target))
            target->SendSysMessage(LANG_YOURS_RUNIC_POWER_CHANGED, handler->GetNameLink().c_str(), rune/10, runem/10);

        target->SetMaxPower(POWER_RUNIC_POWER, runem);
        target->SetPower(POWER_RUNIC_POWER, rune);

        return true;
    }

    //Edit Player Faction
    static bool HandleModifyFactionCommand(ChatHandler* handler, const char* args)
    {
        if (!*args)
            return false;

        char* pfactionid = handler->extractKeyFromLink((char*)args, "Hfaction");

        Creature* target = handler->getSelectedCreature();
        if (!target)
        {
            handler->SendSysMessage(LANG_SELECT_CREATURE);
            handler->SetSentErrorMessage(true);
            return false;
        }

        if (!pfactionid)
        {
            if (target)
            {
                uint32 factionid = target->getFaction();
                uint32 flag      = target->GetUInt32Value(UNIT_FIELD_FLAGS);
                uint32 npcflag   = target->GetUInt32Value(UNIT_NPC_FLAGS);
                uint32 dyflag    = target->GetUInt32Value(UNIT_DYNAMIC_FLAGS);
                handler->PSendSysMessage(LANG_CURRENT_FACTION, target->GetGUIDLow(), factionid, flag, npcflag, dyflag);
            }
            return true;
        }

        if (!target)
        {
            handler->SendSysMessage(LANG_NO_CHAR_SELECTED);
            handler->SetSentErrorMessage(true);
            return false;
        }

        uint32 factionid = atoi(pfactionid);
        uint32 flag;

        char *pflag = strtok(NULL, " ");
        if (!pflag)
            flag = target->GetUInt32Value(UNIT_FIELD_FLAGS);
        else
            flag = atoi(pflag);

        char* pnpcflag = strtok(NULL, " ");

        uint32 npcflag;
        if (!pnpcflag)
            npcflag   = target->GetUInt32Value(UNIT_NPC_FLAGS);
        else
            npcflag = atoi(pnpcflag);

        char* pdyflag = strtok(NULL, " ");

        uint32  dyflag;
        if (!pdyflag)
            dyflag   = target->GetUInt32Value(UNIT_DYNAMIC_FLAGS);
        else
            dyflag = atoi(pdyflag);

        if (!sFactionTemplateStore.LookupEntry(factionid))
        {
            handler->PSendSysMessage(LANG_WRONG_FACTION, factionid);
            handler->SetSentErrorMessage(true);
            return false;
        }

        handler->PSendSysMessage(LANG_YOU_CHANGE_FACTION, target->GetGUIDLow(), factionid, flag, npcflag, dyflag);

        target->setFaction(factionid);
        target->SetUInt32Value(UNIT_FIELD_FLAGS, flag);
        target->SetUInt32Value(UNIT_NPC_FLAGS, npcflag);
        target->SetUInt32Value(UNIT_DYNAMIC_FLAGS, dyflag);

        return true;
    }

    //Edit Player Spell
    static bool HandleModifySpellCommand(ChatHandler* handler, const char* args)
    {
        if (!*args) return false;
        char* pspellflatid = strtok((char*)args, " ");
        if (!pspellflatid)
            return false;

        char* pop = strtok(NULL, " ");
        if (!pop)
            return false;

        char* pval = strtok(NULL, " ");
        if (!pval)
            return false;

        uint16 mark;

        char* pmark = strtok(NULL, " ");

        uint8 spellflatid = atoi(pspellflatid);
        uint8 op   = atoi(pop);
        uint16 val = atoi(pval);
        if (!pmark)
            mark = 65535;
        else
            mark = atoi(pmark);

        Player* target = handler->getSelectedPlayer();
        if (target == NULL)
        {
            handler->SendSysMessage(LANG_NO_CHAR_SELECTED);
            handler->SetSentErrorMessage(true);
            return false;
        }

        // check online security
        if (handler->HasLowerSecurity(target, 0))
            return false;

        handler->PSendSysMessage(LANG_YOU_CHANGE_SPELLFLATID, spellflatid, val, mark, handler->GetNameLink(target).c_str());
        if (handler->needReportToTarget(target))
            target->SendSysMessage(LANG_YOURS_SPELLFLATID_CHANGED, handler->GetNameLink().c_str(), spellflatid, val, mark);

        WorldPacket data(SMSG_SET_FLAT_SPELL_MODIFIER, (1+1+2+2));
        data << uint8(spellflatid);
        data << uint8(op);
        data << uint16(val);
        data << uint16(mark);
        target->GetSession()->SendPacket(&data);

        return true;
    }

    //Edit Player TP
    static bool HandleModifyTalentCommand (ChatHandler* handler, const char* args)
    {
        if (!*args)
            return false;

        int tp = atoi((char*)args);
        if (tp < 0)
            return false;

        Unit* target = handler->getSelectedUnit();
        if (!target)
        {
            handler->SendSysMessage(LANG_NO_CHAR_SELECTED);
            handler->SetSentErrorMessage(true);
            return false;
        }

        if (target->GetTypeId() == TYPEID_PLAYER)
        {
            // check online security
            if (handler->HasLowerSecurity(target->ToPlayer(), 0))
                return false;
            target->ToPlayer()->SetFreeTalentPoints(tp);
            target->ToPlayer()->SendTalentsInfoData(false);
            return true;
        }
        else if (target->ToCreature()->isPet())
        {
            Unit* owner = target->GetOwner();
            if (owner && owner->GetTypeId() == TYPEID_PLAYER && ((Pet*)target)->IsPermanentPetFor(owner->ToPlayer()))
            {
                // check online security
                if (handler->HasLowerSecurity(owner->ToPlayer(), 0))
                    return false;
                ((Pet*)target)->SetFreeTalentPoints(tp);
                owner->ToPlayer()->SendTalentsInfoData(true);
                return true;
            }
        }

        handler->SendSysMessage(LANG_NO_CHAR_SELECTED);
        handler->SetSentErrorMessage(true);
        return false;
    }

    //Edit Player Aspeed
    static bool HandleModifyASpeedCommand(ChatHandler* handler, const char* args)
    {
        if (!*args)
            return false;

        float ASpeed = (float)atof((char*)args);
        Player* target = handler->getSelectedPlayer();
        if (!target)
        {
            handler->SendSysMessage(LANG_NO_CHAR_SELECTED);
            handler->SetSentErrorMessage(true);
            return false;
        }

        // check online security
        if (handler->HasLowerSecurity(target, 0))
            return false;

        std::string targetNameLink = handler->GetNameLink(target);

        if (target->isInFlight())
        {
            handler->PSendSysMessage(LANG_CHAR_IN_FLIGHT, targetNameLink.c_str());
            handler->SetSentErrorMessage(true);
            return false;
        }

        handler->PSendSysMessage(LANG_YOU_CHANGE_ASPEED, ASpeed, targetNameLink.c_str());
        if (handler->needReportToTarget(target))
            target->SendSysMessage(LANG_YOURS_ASPEED_CHANGED, handler->GetNameLink().c_str(), ASpeed);

        target->SetSpeed(MOVE_WALK,    ASpeed, true);
        target->SetSpeed(MOVE_RUN,     ASpeed, true);
        target->SetSpeed(MOVE_SWIM,    ASpeed, true);
        //target->SetSpeed(MOVE_TURN,    ASpeed, true);
        target->SetSpeed(MOVE_FLIGHT,     ASpeed, true);
        return true;
    }

    //Edit Player Speed
    static bool HandleModifySpeedCommand(ChatHandler* handler, const char* args)
    {
        if (!*args)
            return false;

        float Speed = (float)atof((char*)args);
        Player* target = handler->getSelectedPlayer();
        if (!target)
        {
            handler->SendSysMessage(LANG_NO_CHAR_SELECTED);
            handler->SetSentErrorMessage(true);
            return false;
        }

        // check online security
        if (handler->HasLowerSecurity(target, 0))
            return false;

        std::string targetNameLink = handler->GetNameLink(target);

        if (target->isInFlight())
        {
            handler->PSendSysMessage(LANG_CHAR_IN_FLIGHT, targetNameLink.c_str());
            handler->SetSentErrorMessage(true);
            return false;
        }

        handler->PSendSysMessage(LANG_YOU_CHANGE_SPEED, Speed, targetNameLink.c_str());
        if (handler->needReportToTarget(target))
            target->SendSysMessage(LANG_YOURS_SPEED_CHANGED, handler->GetNameLink().c_str(), Speed);

        target->SetSpeed(MOVE_RUN, Speed, true);

        return true;
    }

    //Edit Player Swim Speed
    static bool HandleModifySwimCommand(ChatHandler* handler, const char* args)
    {
        if (!*args)
            return false;

        float Swim = (float)atof((char*)args);

        if (Swim > 50.0f || Swim < 0.1f)
        {
            handler->SendSysMessage(LANG_BAD_VALUE);
            handler->SetSentErrorMessage(true);
            return false;
        }

        Player* target = handler->getSelectedPlayer();
        if (!target)
        {
            handler->SendSysMessage(LANG_NO_CHAR_SELECTED);
            handler->SetSentErrorMessage(true);
            return false;
        }

        // check online security
        if (handler->HasLowerSecurity(target, 0))
            return false;

        std::string targetNameLink = handler->GetNameLink(target);

        if (target->isInFlight())
        {
            handler->PSendSysMessage(LANG_CHAR_IN_FLIGHT, targetNameLink.c_str());
            handler->SetSentErrorMessage(true);
            return false;
        }

        handler->PSendSysMessage(LANG_YOU_CHANGE_SWIM_SPEED, Swim, targetNameLink.c_str());
        if (handler->needReportToTarget(target))
            target->SendSysMessage(LANG_YOURS_SWIM_SPEED_CHANGED, handler->GetNameLink().c_str(), Swim);

        target->SetSpeed(MOVE_SWIM, Swim, true);

        return true;
    }

    //Edit Player Walk Speed
    static bool HandleModifyBWalkCommand(ChatHandler* handler, const char* args)
    {
        if (!*args)
            return false;

        float BSpeed = (float)atof((char*)args);

        if (BSpeed > 50.0f || BSpeed < 0.1f)
        {
            handler->SendSysMessage(LANG_BAD_VALUE);
            handler->SetSentErrorMessage(true);
            return false;
        }

        Player* target = handler->getSelectedPlayer();
        if (!target)
        {
            handler->SendSysMessage(LANG_NO_CHAR_SELECTED);
            handler->SetSentErrorMessage(true);
            return false;
        }

        // check online security
        if (handler->HasLowerSecurity(target, 0))
            return false;

        std::string targetNameLink = handler->GetNameLink(target);

        if (target->isInFlight())
        {
            handler->PSendSysMessage(LANG_CHAR_IN_FLIGHT, targetNameLink.c_str());
            handler->SetSentErrorMessage(true);
            return false;
        }

        handler->PSendSysMessage(LANG_YOU_CHANGE_BACK_SPEED, BSpeed, targetNameLink.c_str());
        if (handler->needReportToTarget(target))
            target->SendSysMessage(LANG_YOURS_BACK_SPEED_CHANGED, handler->GetNameLink().c_str(), BSpeed);

        target->SetSpeed(MOVE_RUN_BACK, BSpeed, true);

        return true;
    }

    //Edit Player Fly
    static bool HandleModifyFlyCommand(ChatHandler* handler, const char* args)
    {
        if (!*args)
            return false;

        float FSpeed = (float)atof((char*)args);

        if (FSpeed > 50.0f || FSpeed < 0.1f)
        {
            handler->SendSysMessage(LANG_BAD_VALUE);
            handler->SetSentErrorMessage(true);
            return false;
        }

        Player* target = handler->getSelectedPlayer();
        if (!target)
        {
            handler->SendSysMessage(LANG_NO_CHAR_SELECTED);
            handler->SetSentErrorMessage(true);
            return false;
        }

        // check online security
        if (handler->HasLowerSecurity(target, 0))
            return false;

        handler->PSendSysMessage(LANG_YOU_CHANGE_FLY_SPEED, FSpeed, handler->GetNameLink(target).c_str());
        if (handler->needReportToTarget(target))
            target->SendSysMessage(LANG_YOURS_FLY_SPEED_CHANGED, handler->GetNameLink().c_str(), FSpeed);

        target->SetSpeed(MOVE_FLIGHT, FSpeed, true);

        return true;
    }

    //Edit Player or Creature Scale
    static bool HandleModifyScaleCommand(ChatHandler* handler, const char* args)
    {
        if (!*args)
            return false;

        float Scale = (float)atof((char*)args);

        Unit* target = handler->getSelectedUnit();
        if (!target)
        {
            handler->SendSysMessage(LANG_SELECT_CHAR_OR_CREATURE);
            handler->SetSentErrorMessage(true);
            return false;
        }

        if (Player* player = target->ToPlayer())
        {
            // check online security
            if (handler->HasLowerSecurity(player, 0))
                return false;

            handler->PSendSysMessage(LANG_YOU_CHANGE_SIZE, Scale, handler->GetNameLink(player).c_str());
            if (handler->needReportToTarget(player))
                player->SendSysMessage(LANG_YOURS_SIZE_CHANGED, handler->GetNameLink().c_str(), Scale);
        }

        target->SetFloatValue(OBJECT_FIELD_SCALE_X, Scale);

        return true;
    }

    //Edit Player money
    static bool HandleModifyMoneyCommand(ChatHandler* handler, const char* args)
    {
        if (!*args)
            return false;

        Player* target = handler->getSelectedPlayer();
        if (!target)
        {
            handler->SendSysMessage(LANG_NO_CHAR_SELECTED);
            handler->SetSentErrorMessage(true);
            return false;
        }

        // check online security
        if (handler->HasLowerSecurity(target, 0))
            return false;

        int32 addmoney = atoi((char*)args);

        uint32 moneyuser = target->GetMoney();

        if (addmoney < 0)
        {
            int32 newmoney = int32(moneyuser) + addmoney;

            sLog->outDetail(handler->GetTrinityString(LANG_CURRENT_MONEY), moneyuser, addmoney, newmoney);
            if (newmoney <= 0)
            {
                handler->PSendSysMessage(LANG_YOU_TAKE_ALL_MONEY, handler->GetNameLink(target).c_str());
                if (handler->needReportToTarget(target))
                    target->SendSysMessage(LANG_YOURS_ALL_MONEY_GONE, handler->GetNameLink().c_str());

                target->SetMoney(0);
            }
            else
            {
                if (newmoney > MAX_MONEY_AMOUNT)
                    newmoney = MAX_MONEY_AMOUNT;

                handler->PSendSysMessage(LANG_YOU_TAKE_MONEY, abs(addmoney), handler->GetNameLink(target).c_str());
                if (handler->needReportToTarget(target))
                    target->SendSysMessage(LANG_YOURS_MONEY_TAKEN, handler->GetNameLink().c_str(), abs(addmoney));
                target->SetMoney(newmoney);
            }
        }
        else
        {
            handler->PSendSysMessage(LANG_YOU_GIVE_MONEY, addmoney, handler->GetNameLink(target).c_str());
            if (handler->needReportToTarget(target))
                target->SendSysMessage(LANG_YOURS_MONEY_GIVEN, handler->GetNameLink().c_str(), addmoney);

            if (addmoney >=MAX_MONEY_AMOUNT)
                target->SetMoney(MAX_MONEY_AMOUNT);
            else
                target->ModifyMoney(addmoney);
        }

        sLog->outDetail(handler->GetTrinityString(LANG_NEW_MONEY), moneyuser, addmoney, target->GetMoney());

        return true;
    }

    //Edit Unit field
    static bool HandleModifyBitCommand(ChatHandler* handler, const char* args)
    {
        if (!*args)
            return false;

        Unit* target = handler->getSelectedUnit();
        if (!target)
        {
            handler->SendSysMessage(LANG_NO_CHAR_SELECTED);
            handler->SetSentErrorMessage(true);
            return false;
        }

        // check online security
        if (target->GetTypeId() == TYPEID_PLAYER && handler->HasLowerSecurity(target->ToPlayer(), 0))
            return false;

        char* pField = strtok((char*)args, " ");
        if (!pField)
            return false;

        char* pBit = strtok(NULL, " ");
        if (!pBit)
            return false;

        uint16 field = atoi(pField);
        uint32 bit   = atoi(pBit);

        if (field < OBJECT_END || field >= target->GetValuesCount())
        {
            handler->SendSysMessage(LANG_BAD_VALUE);
            handler->SetSentErrorMessage(true);
            return false;
        }
        if (bit < 1 || bit > 32)
        {
            handler->SendSysMessage(LANG_BAD_VALUE);
            handler->SetSentErrorMessage(true);
            return false;
        }

        if (target->HasFlag(field, (1<<(bit-1))))
        {
            target->RemoveFlag(field, (1<<(bit-1)));
            handler->PSendSysMessage(LANG_REMOVE_BIT, bit, field);
        }
        else
        {
            target->SetFlag(field, (1<<(bit-1)));
            handler->PSendSysMessage(LANG_SET_BIT, bit, field);
        }
        return true;
    }

    static bool HandleModifyHonorCommand (ChatHandler* handler, const char* args)
    {
        if (!*args)
            return false;

        Player* target = handler->getSelectedPlayer();
        if (!target)
        {
            handler->SendSysMessage(LANG_PLAYER_NOT_FOUND);
            handler->SetSentErrorMessage(true);
            return false;
        }

        // check online security
        if (handler->HasLowerSecurity(target, 0))
            return false;

        int32 amount = (uint32)atoi(args);

        target->ModifyHonorPoints(amount);

        handler->PSendSysMessage(LANG_COMMAND_MODIFY_HONOR, handler->GetNameLink(target).c_str(), target->GetHonorPoints());

        return true;
    }

    static bool HandleModifyDrunkCommand(ChatHandler* handler, const char* args)
    {
        if (!*args)    return false;

        uint32 drunklevel = (uint32)atoi(args);
        if (drunklevel > 100)
            drunklevel = 100;

        uint16 drunkMod = drunklevel * 0xFFFF / 100;

        Player* target = handler->getSelectedPlayer();
        if (!target)
            target = handler->GetSession()->GetPlayer();

        if (target)
            target->SetDrunkValue(drunkMod);

        return true;
    }

    static bool HandleModifyRepCommand(ChatHandler* handler, const char* args)
    {
        if (!*args) return false;

        Player* target = handler->getSelectedPlayer();

        if (!target)
        {
            handler->SendSysMessage(LANG_PLAYER_NOT_FOUND);
            handler->SetSentErrorMessage(true);
            return false;
        }

        // check online security
        if (handler->HasLowerSecurity(target, 0))
            return false;

        char* factionTxt = handler->extractKeyFromLink((char*)args, "Hfaction");
        if (!factionTxt)
            return false;

        uint32 factionId = atoi(factionTxt);

        int32 amount = 0;
        char *rankTxt = strtok(NULL, " ");
        if (!factionTxt || !rankTxt)
            return false;

        amount = atoi(rankTxt);
        if ((amount == 0) && (rankTxt[0] != '-') && !isdigit(rankTxt[0]))
        {
            std::string rankStr = rankTxt;
            std::wstring wrankStr;
            if (!Utf8toWStr(rankStr, wrankStr))
                return false;
            wstrToLower(wrankStr);

            int r = 0;
            amount = -42000;
            for (; r < MAX_REPUTATION_RANK; ++r)
            {
                std::string rank = handler->GetTrinityString(ReputationRankStrIndex[r]);
                if (rank.empty())
                    continue;

                std::wstring wrank;
                if (!Utf8toWStr(rank, wrank))
                    continue;

                wstrToLower(wrank);

                if (wrank.substr(0, wrankStr.size()) == wrankStr)
                {
                    char *deltaTxt = strtok(NULL, " ");
                    if (deltaTxt)
                    {
                        int32 delta = atoi(deltaTxt);
                        if ((delta < 0) || (delta > ReputationMgr::PointsInRank[r] -1))
                        {
                            handler->PSendSysMessage(LANG_COMMAND_FACTION_DELTA, (ReputationMgr::PointsInRank[r]-1));
                            handler->SetSentErrorMessage(true);
                            return false;
                        }
                        amount += delta;
                    }
                    break;
                }
                amount += ReputationMgr::PointsInRank[r];
            }
            if (r >= MAX_REPUTATION_RANK)
            {
                handler->PSendSysMessage(LANG_COMMAND_FACTION_INVPARAM, rankTxt);
                handler->SetSentErrorMessage(true);
                return false;
            }
        }

        FactionEntry const* factionEntry = sFactionStore.LookupEntry(factionId);

        if (!factionEntry)
        {
            handler->PSendSysMessage(LANG_COMMAND_FACTION_UNKNOWN, factionId);
            handler->SetSentErrorMessage(true);
            return false;
        }

        if (factionEntry->reputationListID < 0)
        {
            handler->PSendSysMessage(LANG_COMMAND_FACTION_NOREP_ERROR, factionEntry->name[handler->GetSessionDbcLocale()], factionId);
            handler->SetSentErrorMessage(true);
            return false;
        }

        target->GetReputationMgr().SetReputation(factionEntry, amount);
        handler->PSendSysMessage(LANG_COMMAND_MODIFY_REP, factionEntry->name[handler->GetSessionDbcLocale()], factionId,
            handler->GetNameLink(target).c_str(), target->GetReputationMgr().GetReputation(factionEntry));
        return true;
    }

    static bool HandleModifyDisplayIdCommand(ChatHandler* handler, const char* args)
    {
        if (!*args)
            return false;

        uint16 display_id = (uint16)atoi((char*)args);

        Unit* target = handler->getSelectedUnit();
        if (!target)
            target = handler->GetSession()->GetPlayer();
        else if (target->GetTypeId() == TYPEID_PLAYER && handler->HasLowerSecurity(target->ToPlayer(), 0))
            return false;

        target->SetDisplayId(display_id);
        return true;
    }

    static bool HandleModifyMountIdCommand(ChatHandler* handler, const char* args)
    {
        if (!*args)
            return false;

        uint16 mount_id = (uint16)atoi((char*)args);

        Unit* target = handler->getSelectedUnit();
        if (!target)
            target = handler->GetSession()->GetPlayer();
        else if (target->GetTypeId() == TYPEID_PLAYER && handler->HasLowerSecurity(target->ToPlayer(), 0))
            return false;

        target->SetUInt32Value(UNIT_FIELD_MOUNTDISPLAYID, mount_id);
        return true;
    }

    //set temporary phase mask for player
    static bool HandleModifyPhaseCommand(ChatHandler* handler, const char* args)
    {
        if (!*args)
            return false;

        uint32 phasemask = (uint32)atoi((char*)args);

        Unit* target = handler->getSelectedUnit();
        if (!target)
            target = handler->GetSession()->GetPlayer();

        // check online security
        else if (target->GetTypeId() == TYPEID_PLAYER && handler->HasLowerSecurity(target->ToPlayer(), 0))
            return false;

        target->SetPhaseMask(phasemask, true);

        return true;
    }

    //change standstate
    static bool HandleModifyStandStateCommand(ChatHandler* handler, const char* args)
    {
        if (!*args)
            return false;

        uint8 anim_id = (uint8)atoi((char*)args);
        handler->GetSession()->GetPlayer()->SetStandState(anim_id);

        return true;
    }

    static bool HandleModifyArenaCommand(ChatHandler* handler, const char* args)
    {
        if (!*args)
            return false;

        Player* target = handler->getSelectedPlayer();
        if (!target)
        {
            handler->SendSysMessage(LANG_PLAYER_NOT_FOUND);
            handler->SetSentErrorMessage(true);
            return false;
        }

        int32 amount = (uint32)atoi(args);

        target->ModifyArenaPoints(amount);

        handler->PSendSysMessage(LANG_COMMAND_MODIFY_ARENA, handler->GetNameLink(target).c_str(), target->GetArenaPoints());

        return true;
    }

    static bool HandleModifyGenderCommand(ChatHandler* handler, const char* args)
    {
        if (!*args)
            return false;

        Player* target = handler->getSelectedPlayer();

        if (!target)
        {
            handler->PSendSysMessage(LANG_PLAYER_NOT_FOUND);
            handler->SetSentErrorMessage(true);
            return false;
        }

        PlayerInfo const* info = sObjectMgr->GetPlayerInfo(target->getRace(), target->getClass());
        if (!info)
            return false;

        char const* gender_str = (char*)args;
        int gender_len = strlen(gender_str);

        Gender gender;

        if (!strncmp(gender_str, "male", gender_len))            // MALE
        {
            if (target->getGender() == GENDER_MALE)
                return true;

            gender = GENDER_MALE;
        }
        else if (!strncmp(gender_str, "female", gender_len))    // FEMALE
        {
            if (target->getGender() == GENDER_FEMALE)
                return true;

            gender = GENDER_FEMALE;
        }
        else
        {
            handler->SendSysMessage(LANG_MUST_MALE_OR_FEMALE);
            handler->SetSentErrorMessage(true);
            return false;
        }

        // Set gender
        target->SetByteValue(UNIT_FIELD_BYTES_0, 2, gender);
        target->SetByteValue(PLAYER_BYTES_3, 0, gender);

        // Change display ID
        target->InitDisplayIds();

        char const* gender_full = gender ? "female" : "male";

        handler->PSendSysMessage(LANG_YOU_CHANGE_GENDER, handler->GetNameLink(target).c_str(), gender_full);

        if (handler->needReportToTarget(target))
            target->SendSysMessage(LANG_YOUR_GENDER_CHANGED, gender_full, handler->GetNameLink().c_str());

        return true;
    }
};

void AddSC_modify_commandscript()
{
    new modify_commandscript();
}
