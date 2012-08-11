#include "ScriptPCH.h"

class npc_prof : public CreatureScript
{
    public:
        npc_prof() : CreatureScript("npc_prof") {}

    struct npc_profAI : public ScriptedAI
    {
        npc_profAI(Creature *c) : ScriptedAI(c) { }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_profAI(creature);
    }

    void CreatureWhisperBasedOnBool(const char* text, Creature* creature, Player* player, bool value)
    {
        if (value)
            creature->MonsterWhisper(text, player->GetGUID());
    }

    uint32 PlayerMaxLevel() const
    {
        return sWorld->getIntConfig(CONFIG_MAX_PLAYER_LEVEL);
    }

    void MainMenu(Player* player, Creature* creature)
    {
        player->ADD_GOSSIP_ITEM(9, "[Professions] ->", GOSSIP_SENDER_MAIN, 196);
        player->PlayerTalkClass->SendGossipMenu(907, creature->GetGUID());
    }

    bool PlayerHasItemOrSpell(const Player *plr, uint32 itemId, uint32 spellId) const
    {
        return plr->HasItemCount(itemId, 1, true) || plr->HasSpell(spellId);
    }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        MainMenu(player, creature);
        return true;
    }

    bool PlayerAlreadyHasTwoProfessions(const Player* player) const
    {
        uint32 skillCount = 0;

        if (player->HasSkill(SKILL_MINING))
            skillCount++;
        if (player->HasSkill(SKILL_SKINNING))
            skillCount++;
        if (player->HasSkill(SKILL_HERBALISM))
            skillCount++;

        if (skillCount >= 2)
            return true;

        for (uint32 i = 1; i < sSkillLineStore.GetNumRows(); ++i)
        {
            SkillLineEntry const *SkillInfo = sSkillLineStore.LookupEntry(i);
            if (!SkillInfo)
                continue;

            if (SkillInfo->categoryId == SKILL_CATEGORY_SECONDARY)
                continue;

            if ((SkillInfo->categoryId != SKILL_CATEGORY_PROFESSION) || !SkillInfo->canLink)
                continue;

            const uint32 skillID = SkillInfo->id;
            if (player->HasSkill(skillID))
                skillCount++;

            if (skillCount >= 2)
                return true;
        }
        return false;
    }

    bool LearnAllRecipesInProfession(Player* player, SkillType skill)
    {
        ChatHandler handler(player);
        char* skill_name;

        SkillLineEntry const *SkillInfo = sSkillLineStore.LookupEntry(skill);
        skill_name = SkillInfo->name[handler.GetSessionDbcLocale()];

        if (!SkillInfo)
        {
            sLog->outError("Received non-valid skill ID (LearnAllRecipesInProfession)");
            return false;
        }

        LearnSkillRecipesHelper(player, SkillInfo->id);

        uint16 maxLevel = player->GetPureMaxSkillValue(SkillInfo->id);
        player->SetSkill(SkillInfo->id, player->GetSkillStep(SkillInfo->id), maxLevel, maxLevel);
        handler.PSendSysMessage(LANG_COMMAND_LEARN_ALL_RECIPES, skill_name);

        return true;
    }

    void LearnSkillRecipesHelper(Player *player, uint32 skill_id)
    {
        uint32 classmask = player->getClassMask();

        for (uint32 j = 0; j < sSkillLineAbilityStore.GetNumRows(); ++j)
        {
            SkillLineAbilityEntry const *skillLine = sSkillLineAbilityStore.LookupEntry(j);
            if (!skillLine)
                continue;

            // Wrong Skill
            if (skillLine->skillId != skill_id)
                continue;

            // Not High Enough Rank
            if (skillLine->forward_spellid)
                continue;

            // Skip Racial Skills
            if (skillLine->racemask != 0)
                continue;

            // Skip Wrong Class Skills
            if (skillLine->classmask && (skillLine->classmask & classmask) == 0)
                continue;

            SpellInfo const* spellInfo = sSpellMgr->GetSpellInfo(skillLine->spellId);
            if (!spellInfo || !SpellMgr::IsSpellValid(spellInfo, player, false))
                continue;

            player->learnSpell(skillLine->spellId, false);
        }
    }

    bool IsSecondarySkill(SkillType skill) const
    {
        return skill == SKILL_COOKING || skill == SKILL_FIRST_AID;
    }

    void CompleteLearnProfession(Player* player, Creature* creature, SkillType skill)
    {
        if (PlayerAlreadyHasTwoProfessions(player) && !IsSecondarySkill(skill))
            creature->MonsterWhisper("You already know two professions!", player->GetGUID());
        else
        {
            if (!LearnAllRecipesInProfession(player, skill))
                creature->MonsterWhisper("Internal error occured!", player->GetGUID());
        }
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 uiSender, uint32 uiAction)
    {
        player->PlayerTalkClass->ClearMenus();

        if (uiSender == GOSSIP_SENDER_MAIN)
        {
            switch (uiAction)
            {
                case 196:
                    player->ADD_GOSSIP_ITEM(4, "Alchemy", GOSSIP_SENDER_MAIN, 1);
                    player->ADD_GOSSIP_ITEM(4, "Blacksmithing", GOSSIP_SENDER_MAIN, 2);
                    player->ADD_GOSSIP_ITEM(4, "Cooking", GOSSIP_SENDER_MAIN, 9);
                    player->ADD_GOSSIP_ITEM(4, "Enchanting", GOSSIP_SENDER_MAIN, 6);
                    player->ADD_GOSSIP_ITEM(4, "Engineering", GOSSIP_SENDER_MAIN, 5);
                    player->ADD_GOSSIP_ITEM(4, "First Aid", GOSSIP_SENDER_MAIN, 10);
                    player->ADD_GOSSIP_ITEM(4, "Inscription", GOSSIP_SENDER_MAIN, 8);
                    player->ADD_GOSSIP_ITEM(4, "Jewelcrafting", GOSSIP_SENDER_MAIN, 7);
                    player->ADD_GOSSIP_ITEM(4, "Leatherworking", GOSSIP_SENDER_MAIN, 3);
                    player->ADD_GOSSIP_ITEM(4, "Tailoring", GOSSIP_SENDER_MAIN, 4);
                    player->PlayerTalkClass->SendGossipMenu(907, creature->GetGUID());
                    break;
                case 1:
                    CompleteLearnProfession(player, creature, SKILL_ALCHEMY);
                    player->CLOSE_GOSSIP_MENU();
                    break;
                case 2:
                    CompleteLearnProfession(player, creature, SKILL_BLACKSMITHING);
                    player->CLOSE_GOSSIP_MENU();
                    break;
                case 3:
                    CompleteLearnProfession(player, creature, SKILL_LEATHERWORKING);
                    player->learnSpell(57683, false);
                    player->CLOSE_GOSSIP_MENU();
                    break;
                case 4:
                    CompleteLearnProfession(player, creature, SKILL_TAILORING);
                    player->CLOSE_GOSSIP_MENU();
                    break;
                case 5:
                    CompleteLearnProfession(player, creature, SKILL_ENGINEERING);
                    player->CLOSE_GOSSIP_MENU();
                    break;
                case 6:
                    CompleteLearnProfession(player, creature, SKILL_ENCHANTING);
                    player->CLOSE_GOSSIP_MENU();
                    break;
                case 7:
                    CompleteLearnProfession(player, creature, SKILL_JEWELCRAFTING);
                    player->CLOSE_GOSSIP_MENU();
                    break;
                case 8:
                    CompleteLearnProfession(player, creature, SKILL_INSCRIPTION);
                    player->CLOSE_GOSSIP_MENU();
                    break;
                case 9:
                    CompleteLearnProfession(player, creature, SKILL_COOKING);
                    player->CLOSE_GOSSIP_MENU();
                    break;
                case 10:
                    CompleteLearnProfession(player, creature, SKILL_FIRST_AID);
                    player->CLOSE_GOSSIP_MENU();
                    break;
            }
        }
        return true;
    }
};

void AddSC_npc_prof()
{
    new npc_prof();
}