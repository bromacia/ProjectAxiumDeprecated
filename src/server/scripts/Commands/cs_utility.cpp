#include "Chat.h"
#include "MapManager.h"

class utility_commandscript : public CommandScript
{
public:
    utility_commandscript() : CommandScript("utility_commandscript") { }

    ChatCommand* GetCommands() const
    {
        static ChatCommand utilityCommandTable[] =
        {
            { "customize",       SEC_PLAYER,         false, &HandleCustomizeCommand,                 "", NULL },
            { "race",            SEC_PLAYER,         false, &HandleRaceCommand,                      "", NULL },
            { "faction",         SEC_PLAYER,         false, &HandleFactionCommand,                   "", NULL },
            { "prepare",         SEC_GAMEMASTER,     false, &HandlePrepareCommand,                   "", NULL },
            { "barbershop",      SEC_PLAYER,         false, &HandleBarbershopCommand,                "", NULL },
            { "mmr",             SEC_PLAYER,         false, &HandleMMRCommand,                       "", NULL },
            { "sendcooldown",    SEC_GAMEMASTER,     false, &HandleSendCooldownCommand,              "", NULL },
            { "transmogcopy",    SEC_GAMEMASTER,     false, &HandleTransmogCopyCommand,              "", NULL },
            { "transmogsend",    SEC_GAMEMASTER,     false, &HandleTransmogSendCommand,              "", NULL },
            { "warp",            SEC_GAMEMASTER,     false, &HandleWarpCommand,                      "", NULL },
            { "hijackcharacter", SEC_ADMINISTRATOR,  false, &HandleHijackCharacterCommand,           "", NULL },
            { "returncharacter", SEC_ADMINISTRATOR,  false, &HandleReturnCharacterCommand,           "", NULL },
            { "getspeedrate",    SEC_GAMEMASTER,     false, &HandleGetSpeedRateCommand,              "", NULL },
            { NULL,              0,                  false, NULL,                                    "", NULL }
        };
        static ChatCommand commandTable[] =
        {
            { "utility",         SEC_PLAYER,         false, NULL,                     "", utilityCommandTable },
            { NULL,              0,                  false, NULL,                                    "", NULL }
        };
        return commandTable;
    }

    static bool HandleCustomizeCommand(ChatHandler* handler, const char* /*args*/)
    {
        Player* player = handler->GetSession()->GetPlayer();
        
        PreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_UPD_ADD_AT_LOGIN_FLAG);
        stmt->setUInt16(0, uint16(AT_LOGIN_CUSTOMIZE));

        handler->PSendSysMessage("Relog to customize your character");
        player->SetAtLoginFlag(AT_LOGIN_CUSTOMIZE);

        stmt->setUInt32(1, player->GetGUIDLow());

        CharacterDatabase.Execute(stmt);
        return true;
    }

    static bool HandleRaceCommand(ChatHandler* handler, const char* /*args*/)
    {
        Player* player = handler->GetSession()->GetPlayer();
        
        PreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_UPD_ADD_AT_LOGIN_FLAG);
        stmt->setUInt16(0, uint16(AT_LOGIN_CHANGE_RACE));

        handler->PSendSysMessage("Relog to change the race of your character");
        player->SetAtLoginFlag(AT_LOGIN_CHANGE_RACE);

        stmt->setUInt32(1, player->GetGUIDLow());

        CharacterDatabase.Execute(stmt);
        return true;
    }

    static bool HandleFactionCommand(ChatHandler* handler, const char* /*args*/)
    {
        Player* player = handler->GetSession()->GetPlayer();
        
        PreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_UPD_ADD_AT_LOGIN_FLAG);
        stmt->setUInt16(0, uint16(AT_LOGIN_CHANGE_FACTION));

        handler->PSendSysMessage("Relog to change the faction of your character");
        player->SetAtLoginFlag(AT_LOGIN_CHANGE_FACTION);

        stmt->setUInt32(1, player->GetGUIDLow());

        CharacterDatabase.Execute(stmt);
        return true;
    }

    static bool HandlePrepareCommand(ChatHandler* handler, const char* args)
    {
        Player* player = handler->GetSession()->GetPlayer();
        uint64 target_guid = player->GetGUID();

        if (!handler->extractPlayerTarget((char*)args, &player, &target_guid))
            return false;
        
        if (player)
        {
            player->ResurrectPlayer(1.0f);
            player->SpawnCorpseBones();
            player->SaveToDB();
            player->RemoveAllPlayerSpellCooldowns();
            player->RemoveAllNegativeAuras();
            player->ClearDiminishings();
            player->ClearComboPoints();
            player->ClearInCombat();
            player->getHostileRefManager().deleteReferences();
        }
        else
            // will resurrected at login without corpse
            sObjectAccessor->ConvertCorpseForPlayer(target_guid);

        if (Pet* pet = player->GetPet())
            pet->RemoveAllPetSpellCooldowns(player);
        return true;
    }

    static bool HandleBarbershopCommand(ChatHandler* handler, const char* /*args*/)
    {
        Player* player = handler->GetSession()->GetPlayer();

        if (player->IsMorphed())
        {
            handler->PSendSysMessage("You can't do that while morphed");
            handler->SetSentErrorMessage(true);
            return false;
        }

        if (player->IsSitState())
        {
            handler->PSendSysMessage("You cant do that while sitting");
            handler->SetSentErrorMessage(true);
            return false;
        }

        if (player->HasAuraType(SPELL_AURA_TRANSFORM))
        {
            handler->PSendSysMessage("You cant do that while transformed");
            handler->SetSentErrorMessage(true);
            return false;
        }

        if (player->getClass() == CLASS_DRUID && player->HasAuraType(SPELL_AURA_MOD_SHAPESHIFT))
        {
            handler->PSendSysMessage("You cant do that while shapeshifted");
            handler->SetSentErrorMessage(true);
            return false;
        }

        WorldPacket data(SMSG_ENABLE_BARBER_SHOP, 0);
        player->GetSession()->SendPacket(&data);
        return true;
    }

    static bool HandleMMRCommand(ChatHandler* handler, const char* args)
    {
        uint32 player_guid = handler->GetSession()->GetPlayer()->GetGUIDLow();
        uint16 mmr = 1500;

        if (!*args)
            return false;

        char* bracket = strtok((char*)args, " ");

        if (!bracket)
            return false;

        if (!stricmp(bracket, "2v2"))
        {
            QueryResult result = CharacterDatabase.PQuery("SELECT matchMakerRating FROM character_arena_stats WHERE guid = %u AND slot = %u", player_guid, 0);

            if (!result)
                handler->PSendSysMessage("2v2 MMR: %u", mmr);
            else
            {
                Field* fields = result->Fetch();
                mmr = fields[0].GetInt16();
                handler->PSendSysMessage("2v2 MMR: %u", mmr);
            }
        }
        else if (!stricmp(bracket, "3v3"))
        {
            QueryResult result = CharacterDatabase.PQuery("SELECT matchMakerRating FROM character_arena_stats WHERE guid = %u AND slot = %u", player_guid, 1);

            if (!result)
                handler->PSendSysMessage("3v3 MMR: %u", mmr);
            else
            {
                Field* fields = result->Fetch();
                mmr = fields[0].GetInt16();
                handler->PSendSysMessage("3v3 MMR: %u", mmr);
            }
        }
        else if (!stricmp(bracket, "5v5"))
        {
            QueryResult result = CharacterDatabase.PQuery("SELECT matchMakerRating FROM character_arena_stats WHERE guid = %u AND slot = %u", player_guid, 2);

            if (!result)
                handler->PSendSysMessage("5v5 MMR: %u", mmr);
            else
            {
                Field* fields = result->Fetch();
                mmr = fields[0].GetInt16();
                handler->PSendSysMessage("5v5 MMR: %u", mmr);
            }
        }
        else
        {
            handler->PSendSysMessage("Invalid bracket.");
            handler->SetSentErrorMessage(true);
            return false;
        }
        return true;
    }

    static bool HandleSendCooldownCommand(ChatHandler* handler, const char* args)
    {
        Player* target = handler->getSelectedPlayer();
        uint64 target_guid = handler->getSelectedPlayer()->GetGUID();

        if (!*args)
            return false;

        uint32 spell = handler->extractSpellIdFromLink((char*)args);

        char* timeArg = strtok(NULL, " ");

        if (!timeArg)
            return false;

        uint32 cooldown = (uint32)atoi(timeArg);

        if (!spell || !sSpellMgr->GetSpellInfo(spell) || !cooldown)
            return false;

        if (!target->HasSpell(spell))
        {
            handler->PSendSysMessage("%s does not know that spell", target->GetName());
            handler->SetSentErrorMessage(true);
            return false;
        }

        target->RemoveSpellCooldown(spell, true);
        target->AddSpellCooldown(spell, 0, time(NULL) + cooldown, true);
        return true;
    }

    static bool HandleTransmogCopyCommand(ChatHandler* handler, const char* /*args*/)
    {
        Player* player = handler->GetSession()->GetPlayer();
        Unit* unitTarget = handler->getSelectedUnit();

        if (handler->getSelectedUnit()->GetTypeId() != TYPEID_PLAYER)
        {
            handler->PSendSysMessage("Target is not a player.");
            handler->SetSentErrorMessage(true);
            return false;
        }

        Player* target = unitTarget->ToPlayer();

        for (uint8 slot = EQUIPMENT_SLOT_START; slot < EQUIPMENT_SLOT_END; slot++)
        {
            if (Item* playerItem = player->GetItemByPos(INVENTORY_SLOT_BAG_0, slot))
                if (Item* targetItem = target->GetItemByPos(INVENTORY_SLOT_BAG_0, slot))
                {
                    if (slot == EQUIPMENT_SLOT_HEAD ||
                        slot == EQUIPMENT_SLOT_SHOULDERS ||
                        slot == EQUIPMENT_SLOT_CHEST ||
                        slot == EQUIPMENT_SLOT_HANDS ||
                        slot == EQUIPMENT_SLOT_LEGS ||
                        slot == EQUIPMENT_SLOT_WAIST ||
                        slot == EQUIPMENT_SLOT_FEET ||
                        slot == EQUIPMENT_SLOT_MAINHAND ||
                        slot == EQUIPMENT_SLOT_OFFHAND ||
                        slot == EQUIPMENT_SLOT_RANGED)
                    {
                        if (targetItem->TransmogEntry)
                        {
                            CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u WHERE guid = %u", targetItem->TransmogEntry, playerItem->GetGUIDLow());
                            playerItem->TransmogEntry = targetItem->TransmogEntry;
                            player->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_ENTRYID + (slot * 2), targetItem->TransmogEntry);
                        }
                        else
                        {
                            CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u WHERE guid = %u", targetItem->GetEntry(), playerItem->GetGUIDLow());
                            playerItem->TransmogEntry = targetItem->GetEntry();
                            player->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_ENTRYID + (slot * 2), targetItem->GetEntry());
                        }

                        if (targetItem->TransmogEnchant)
                        {
                            CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEnchant = %u WHERE guid = %u", targetItem->TransmogEnchant, playerItem->GetGUIDLow());
                            playerItem->TransmogEnchant = targetItem->TransmogEnchant;
                            player->SetUInt16Value(PLAYER_VISIBLE_ITEM_1_ENCHANTMENT + (slot * 2), 0, targetItem->TransmogEnchant);
                            player->SetUInt16Value(PLAYER_VISIBLE_ITEM_1_ENCHANTMENT + (slot * 2), 1, targetItem->TransmogEnchant);
                        }
                    }
                }
        }
        return true;
    }

    static bool HandleTransmogSendCommand(ChatHandler* handler, const char* /*args*/)
    {
        Player* player = handler->GetSession()->GetPlayer();
        Unit* unitTarget = handler->getSelectedUnit();

        if (handler->getSelectedUnit()->GetTypeId() != TYPEID_PLAYER)
        {
            handler->PSendSysMessage("Target is not a player.");
            handler->SetSentErrorMessage(true);
            return false;
        }

        Player* target = unitTarget->ToPlayer();

        for (uint8 slot = EQUIPMENT_SLOT_START; slot < EQUIPMENT_SLOT_END; slot++)
        {
            if (Item* playerItem = player->GetItemByPos(INVENTORY_SLOT_BAG_0, slot))
                if (Item* targetItem = target->GetItemByPos(INVENTORY_SLOT_BAG_0, slot))
                {
                    if (slot == EQUIPMENT_SLOT_HEAD ||
                        slot == EQUIPMENT_SLOT_SHOULDERS ||
                        slot == EQUIPMENT_SLOT_CHEST ||
                        slot == EQUIPMENT_SLOT_HANDS ||
                        slot == EQUIPMENT_SLOT_LEGS ||
                        slot == EQUIPMENT_SLOT_WAIST ||
                        slot == EQUIPMENT_SLOT_FEET ||
                        slot == EQUIPMENT_SLOT_MAINHAND ||
                        slot == EQUIPMENT_SLOT_OFFHAND ||
                        slot == EQUIPMENT_SLOT_RANGED)
                    {
                        if (playerItem->TransmogEntry)
                        {
                            CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u WHERE guid = %u", playerItem->TransmogEntry, targetItem->GetGUIDLow());
                            targetItem->TransmogEntry = playerItem->TransmogEntry;
                            target->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_ENTRYID + (slot * 2), playerItem->TransmogEntry);
                        }
                        else
                        {
                            CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEntry = %u WHERE guid = %u", playerItem->GetEntry(), targetItem->GetGUIDLow());
                            targetItem->TransmogEntry = playerItem->GetEntry();
                            target->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_ENTRYID + (slot * 2), playerItem->GetEntry());
                        }

                        if (playerItem->TransmogEnchant)
                        {
                            CharacterDatabase.PExecute("UPDATE item_instance SET TransmogEnchant = %u WHERE guid = %u", playerItem->TransmogEnchant, playerItem->GetGUIDLow());
                            targetItem->TransmogEnchant = playerItem->TransmogEnchant;
                            target->SetUInt16Value(PLAYER_VISIBLE_ITEM_1_ENCHANTMENT + (slot * 2), 0, playerItem->TransmogEnchant);
                            target->SetUInt16Value(PLAYER_VISIBLE_ITEM_1_ENCHANTMENT + (slot * 2), 1, playerItem->TransmogEnchant);
                        }
                    }
                }
        }
        return true;
    }

    static bool HandleWarpCommand(ChatHandler* handler, const char* args)
    {
        if (!*args)
            return false;

        Player* player = handler->GetSession()->GetPlayer();

        char* arg1 = strtok((char*)args, " ");
        char* arg2 = strtok(NULL, " ");

        if (!arg1)
            return false;

        if (!arg2)
            return false;

        char dir = arg1[0];
        uint32 value = (int)atoi(arg2);
        float x = player->GetPositionX();
        float y = player->GetPositionY();
        float z = player->GetPositionZ();
        float o = player->GetOrientation();
        uint32 mapid = player->GetMapId();

        if (!MapManager::IsValidMapCoord(mapid, x, y, z))
        {
            handler->PSendSysMessage(LANG_INVALID_TARGET_COORD, x, y, mapid);
            handler->SetSentErrorMessage(true);
            return false;
        }

        if (player->isInFlight())
        {
            player->GetMotionMaster()->MovementExpired();
            player->CleanupAfterTaxiFlight();
        }
        else
            player->SaveRecallPosition();

        switch (dir)
        {
            case 'u':
                player->TeleportTo(mapid, x, y, z + value, o);
                break;
            case 'd':
                player->TeleportTo(mapid, x, y, z - value, o);
                break;
            case 'f':
            {
                float fx = x + cosf(o) * value;
                float fy = y + sinf(o) * value; 
                player->TeleportTo(mapid, fx, fy, z, o);
                break;
            }
            case 'b':
            {
                float bx = x - cosf(o) * value;
                float by = y - sinf(o) * value;
                player->TeleportTo(mapid, bx, by, z, o);
                break;
            }
            default:
                break;
        }

        return true;
    }

    static bool HandleHijackCharacterCommand(ChatHandler* handler, const char* /*args*/)
    {
        Player* player = handler->GetSession()->GetPlayer();
        Unit* unitTarget = handler->getSelectedUnit();
        uint32 playerAccountId = player->GetSession()->GetAccountId();
        Player* target = unitTarget->ToPlayer();
        uint32 targetAccountId = target->GetSession()->GetAccountId();
        uint32 targetGUID = target->GetGUIDLow();

        if (handler->getSelectedUnit()->GetTypeId() != TYPEID_PLAYER)
        {
            handler->PSendSysMessage("Target is not a player.");
            handler->SetSentErrorMessage(true);
            return false;
        }

        if (target->GetHijackedCharacterAccountId())
        {
            handler->PSendSysMessage("You cant hijack a character that has already been hijacked");
            handler->SetSentErrorMessage(true);
            return false;
        }

        QueryResult result = CharacterDatabase.PQuery("SELECT COUNT(*) FROM characters WHERE account = %u", playerAccountId);

        if (!result)
            return false;

        Field* fields = result->Fetch();

        if (fields[0].GetUInt32() > 9)
        {
            handler->PSendSysMessage("You already have 10 characters on your account");
            handler->SetSentErrorMessage(true);
            return false;
        }

        CharacterDatabase.PExecute("UPDATE characters SET account = %u, hijackedAccountId = %u WHERE guid = %u", playerAccountId, targetAccountId, targetGUID);
        target->GetSession()->KickPlayer();

        return true;
    }

    static bool HandleReturnCharacterCommand(ChatHandler* handler, const char* /*args*/)
    {
        Player* hijackedCharacter = handler->GetSession()->GetPlayer();
        uint32 hijackedCharacterGUID = hijackedCharacter->GetGUIDLow();
        uint32 hijackedCharacterAccountId = 0;

        if (hijackedCharacter->GetHijackedCharacterAccountId())
            hijackedCharacterAccountId = hijackedCharacter->GetHijackedCharacterAccountId();
        else
        {
            handler->PSendSysMessage("This character is not hijacked");
            handler->SetSentErrorMessage(true);
            return false;
        }

            CharacterDatabase.PExecute("UPDATE characters SET account = %u, hijackedAccountId = 0 WHERE guid = %u", hijackedCharacterAccountId, hijackedCharacterGUID);
            hijackedCharacter->GetSession()->KickPlayer();

        return true;
    }

    static bool HandleGetSpeedRateCommand(ChatHandler* handler, const char* args)
    {
        if (!*args)
            return false;

        char* typeArg = strtok((char*)args, " ");

        if (!typeArg)
            return false;

        uint8 moveType = (uint8)atoi(typeArg);

        if (moveType > MAX_MOVE_TYPE)
            return false;

        Unit* target = handler->getSelectedUnit();
        if (!target)
            target = handler->GetSession()->GetPlayer();
        float speed = 0.0f;
        float speedRate = 0.0f;
        std::string moveTypeString = "Unknown";

        switch (moveType)
        {
            case MOVE_WALK:        speed = target->GetSpeed(MOVE_WALK);        speedRate = target->GetSpeedRate(MOVE_WALK);        moveTypeString = "MOVE_WALK";        break;
            case MOVE_RUN:         speed = target->GetSpeed(MOVE_RUN);         speedRate = target->GetSpeedRate(MOVE_RUN);         moveTypeString = "MOVE_RUN";         break;
            case MOVE_RUN_BACK:    speed = target->GetSpeed(MOVE_RUN_BACK);    speedRate = target->GetSpeedRate(MOVE_RUN_BACK);    moveTypeString = "MOVE_RUN_BACK";    break;
            case MOVE_SWIM:        speed = target->GetSpeed(MOVE_SWIM);        speedRate = target->GetSpeedRate(MOVE_SWIM);        moveTypeString = "MOVE_SWIM";        break;
            case MOVE_SWIM_BACK:   speed = target->GetSpeed(MOVE_SWIM_BACK);   speedRate = target->GetSpeedRate(MOVE_SWIM_BACK);   moveTypeString = "MOVE_SWIM_BACK";   break;
            case MOVE_TURN_RATE:   speed = target->GetSpeed(MOVE_TURN_RATE);   speedRate = target->GetSpeedRate(MOVE_TURN_RATE);   moveTypeString = "MOVE_TURN_RATE";   break;
            case MOVE_FLIGHT:      speed = target->GetSpeed(MOVE_FLIGHT);      speedRate = target->GetSpeedRate(MOVE_FLIGHT);      moveTypeString = "MOVE_FLIGHT";      break;
            case MOVE_FLIGHT_BACK: speed = target->GetSpeed(MOVE_FLIGHT_BACK); speedRate = target->GetSpeedRate(MOVE_FLIGHT_BACK); moveTypeString = "MOVE_FLIGHT_BACK"; break;
            case MOVE_PITCH_RATE:  speed = target->GetSpeed(MOVE_PITCH_RATE);  speedRate = target->GetSpeedRate(MOVE_PITCH_RATE);  moveTypeString = "MOVE_PITCH_RATE";  break;
            default: break;
        }

        handler->PSendSysMessage("Target: %s, Move Type: %s", target->GetName(), moveTypeString.c_str());
        handler->PSendSysMessage("Speed: %f", speed);
        handler->PSendSysMessage("Speed Rate: %f", speedRate);
        return true;
    }
};

void AddSC_utility_commandscript()
{
    new utility_commandscript();
}