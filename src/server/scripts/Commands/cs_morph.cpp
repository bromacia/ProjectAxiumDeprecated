#include "Chat.h"

class morph_commandscript : public CommandScript
{
public:
    morph_commandscript() : CommandScript("morph_commandscript") { }

    ChatCommand* GetCommands() const
    {
        static ChatCommand morphCommandTable[] =
        {
            { "hum",             SEC_MODERATOR,      false, &HandleMorphHumanMaleCommand,            "", NULL },
            { "huf",             SEC_MODERATOR,      false, &HandleMorphHumanFemaleCommand,          "", NULL },
            { "dwm",             SEC_MODERATOR,      false, &HandleMorphDwarfMaleCommand,            "", NULL },
            { "nem",             SEC_MODERATOR,      false, &HandleMorphNightElfMaleCommand,         "", NULL },
            { "gnm",             SEC_MODERATOR,      false, &HandleMorphGnomeMaleCommand,            "", NULL },
            { "gnf",             SEC_MODERATOR,      false, &HandleMorphGnomeFemaleCommand,          "", NULL },
            { "drf",             SEC_MODERATOR,      false, &HandleMorphDraeneiFemaleCommand,        "", NULL },
            { "orcm",            SEC_MODERATOR,      false, &HandleMorphFelOrcMaleCommand,           "", NULL },
            { "orcf",            SEC_MODERATOR,      false, &HandleMorphOrcFemaleCommand,            "", NULL },
            { "tam",             SEC_MODERATOR,      false, &HandleMorphTaurenMaleCommand,           "", NULL },
            { "taf",             SEC_MODERATOR,      false, &HandleMorphTaurenFemaleCommand,         "", NULL },
            { "trm",             SEC_MODERATOR,      false, &HandleMorphTrollMaleCommand,            "", NULL },
            { "bem",             SEC_MODERATOR,      false, &HandleMorphBloodElfMaleCommand,         "", NULL },
            { "bef",             SEC_MODERATOR,      false, &HandleMorphBloodElfFemaleCommand,       "", NULL },
            { "gobm",            SEC_MODERATOR,      false, &HandleMorphGoblinMaleCommand,           "", NULL },
            { "gobf",            SEC_MODERATOR,      false, &HandleMorphGoblinFemaleCommand,         "", NULL },
            { "none",            SEC_MODERATOR,      false, &HandleMorphNoneCommand,                 "", NULL },
            { NULL,              0,                  false, NULL,                                    "", NULL }
        };
        static ChatCommand commandTable[] =
        {
            { "morph",           SEC_MODERATOR,      false, NULL,                       "", morphCommandTable },
            { NULL,              0,                  false, NULL,                                    "", NULL }
        };
        return commandTable;
    }
    
    enum
    {
        HUM      = 19723,
        HUF      = 19724,
        DWM      = 20317,
        NEM      = 20318,
        GNM      = 20580,
        GNF      = 20581,
        DRF      = 20323,
        ORCM     = 21267,
        ORCF     = 20316,
        TAM      = 20585,
        TAF      = 20584,
        TRM      = 20321,
        BEM      = 20578,
        BEF      = 20579,
        GOBM     = 20582,
        GOBF     = 20583
    };

    static bool HandleMorphHumanMaleCommand(ChatHandler* handler, const char* /*args*/)
    {
        Player* player = handler->GetSession()->GetPlayer();
        if (player->HasAuraType(SPELL_AURA_TRANSFORM))
        {
            handler->PSendSysMessage("You cannot morph when you are transformed.");
            return false;
        }
        else if (player->getClass() == CLASS_DRUID && player->HasAuraType(SPELL_AURA_MOD_SHAPESHIFT))
        {
            handler->PSendSysMessage("You cannot morph when you are shapeshifted.");
            return false;
        }
        else if (player->InArena())
        {
            handler->PSendSysMessage("You cannot morph when you are in arena.");
            return false;
        }
        else
            player->SetNativeDisplayId(HUM);
            player->SetDisplayId(HUM);
        return true;
    }

    static bool HandleMorphHumanFemaleCommand(ChatHandler* handler, const char* /*args*/)
    {
        Player* player = handler->GetSession()->GetPlayer();
        if (player->HasAuraType(SPELL_AURA_TRANSFORM))
        {
            handler->PSendSysMessage("You cannot morph when you are transformed.");
            return false;
        }
        else if (player->getClass() == CLASS_DRUID && player->HasAuraType(SPELL_AURA_MOD_SHAPESHIFT))
        {
            handler->PSendSysMessage("You cannot morph when you are shapeshifted.");
            return false;
        }
        else if (player->InArena())
        {
            handler->PSendSysMessage("You cannot morph when you are in arena.");
            return false;
        }
        else
            player->SetNativeDisplayId(HUF);
            player->SetDisplayId(HUF);
        return true;
    }

    static bool HandleMorphDwarfMaleCommand(ChatHandler* handler, const char* /*args*/)
    {
        Player* player = handler->GetSession()->GetPlayer();
        if (player->HasAuraType(SPELL_AURA_TRANSFORM))
        {
            handler->PSendSysMessage("You cannot morph when you are transformed.");
            return false;
        }
        else if (player->getClass() == CLASS_DRUID && player->HasAuraType(SPELL_AURA_MOD_SHAPESHIFT))
        {
            handler->PSendSysMessage("You cannot morph when you are shapeshifted.");
            return false;
        }
        else if (player->InArena())
        {
            handler->PSendSysMessage("You cannot morph when you are in arena.");
            return false;
        }
        else
            player->SetNativeDisplayId(DWM);
            player->SetDisplayId(DWM);
        return true;
    }

    static bool HandleMorphNightElfMaleCommand(ChatHandler* handler, const char* /*args*/)
    {
        Player* player = handler->GetSession()->GetPlayer();
        if (player->HasAuraType(SPELL_AURA_TRANSFORM))
        {
            handler->PSendSysMessage("You cannot morph when you are transformed.");
            return false;
        }
        else if (player->getClass() == CLASS_DRUID && player->HasAuraType(SPELL_AURA_MOD_SHAPESHIFT))
        {
            handler->PSendSysMessage("You cannot morph when you are shapeshifted.");
            return false;
        }
        else if (player->InArena())
        {
            handler->PSendSysMessage("You cannot morph when you are in arena.");
            return false;
        }
        else
            player->SetNativeDisplayId(NEM);
            player->SetDisplayId(NEM);
        return true;
    }

    static bool HandleMorphGnomeMaleCommand(ChatHandler* handler, const char* /*args*/)
    {
        Player* player = handler->GetSession()->GetPlayer();
        if (player->HasAuraType(SPELL_AURA_TRANSFORM))
        {
            handler->PSendSysMessage("You cannot morph when you are transformed.");
            return false;
        }
        else if (player->getClass() == CLASS_DRUID && player->HasAuraType(SPELL_AURA_MOD_SHAPESHIFT))
        {
            handler->PSendSysMessage("You cannot morph when you are shapeshifted.");
            return false;
        }
        else if (player->InArena())
        {
            handler->PSendSysMessage("You cannot morph when you are in arena.");
            return false;
        }
        else
            player->SetNativeDisplayId(GNM);
            player->SetDisplayId(GNM);
        return true;
    }

    static bool HandleMorphGnomeFemaleCommand(ChatHandler* handler, const char* /*args*/)
    {
        Player* player = handler->GetSession()->GetPlayer();
        if (player->HasAuraType(SPELL_AURA_TRANSFORM))
        {
            handler->PSendSysMessage("You cannot morph when you are transformed.");
            return false;
        }
        else if (player->getClass() == CLASS_DRUID && player->HasAuraType(SPELL_AURA_MOD_SHAPESHIFT))
        {
            handler->PSendSysMessage("You cannot morph when you are shapeshifted.");
            return false;
        }
        else if (player->InArena())
        {
            handler->PSendSysMessage("You cannot morph when you are in arena.");
            return false;
        }
        else
            player->SetNativeDisplayId(GNF);
            player->SetDisplayId(GNF);
        return true;
    }

    static bool HandleMorphDraeneiFemaleCommand(ChatHandler* handler, const char* /*args*/)
    {
        Player* player = handler->GetSession()->GetPlayer();
        if (player->HasAuraType(SPELL_AURA_TRANSFORM))
        {
            handler->PSendSysMessage("You cannot morph when you are transformed.");
            return false;
        }
        else if (player->getClass() == CLASS_DRUID && player->HasAuraType(SPELL_AURA_MOD_SHAPESHIFT))
        {
            handler->PSendSysMessage("You cannot morph when you are shapeshifted.");
            return false;
        }
        else if (player->InArena())
        {
            handler->PSendSysMessage("You cannot morph when you are in arena.");
            return false;
        }
        else
            player->SetNativeDisplayId(DRF);
            player->SetDisplayId(DRF);
        return true;
    }

    static bool HandleMorphFelOrcMaleCommand(ChatHandler* handler, const char* /*args*/)
    {
        Player* player = handler->GetSession()->GetPlayer();
        if (player->HasAuraType(SPELL_AURA_TRANSFORM))
        {
            handler->PSendSysMessage("You cannot morph when you are transformed.");
            return false;
        }
        else if (player->getClass() == CLASS_DRUID && player->HasAuraType(SPELL_AURA_MOD_SHAPESHIFT))
        {
            handler->PSendSysMessage("You cannot morph when you are shapeshifted.");
            return false;
        }
        else if (player->InArena())
        {
            handler->PSendSysMessage("You cannot morph when you are in arena.");
            return false;
        }
        else
            player->SetNativeDisplayId(ORCM);
            player->SetDisplayId(ORCM);
        return true;
    }

    static bool HandleMorphOrcFemaleCommand(ChatHandler* handler, const char* /*args*/)
    {
        Player* player = handler->GetSession()->GetPlayer();
        if (player->HasAuraType(SPELL_AURA_TRANSFORM))
        {
            handler->PSendSysMessage("You cannot morph when you are transformed.");
            return false;
        }
        else if (player->getClass() == CLASS_DRUID && player->HasAuraType(SPELL_AURA_MOD_SHAPESHIFT))
        {
            handler->PSendSysMessage("You cannot morph when you are shapeshifted.");
            return false;
        }
        else if (player->InArena())
        {
            handler->PSendSysMessage("You cannot morph when you are in arena.");
            return false;
        }
        else
            player->SetNativeDisplayId(ORCF);
            player->SetDisplayId(ORCF);
        return true;
    }

    static bool HandleMorphTaurenMaleCommand(ChatHandler* handler, const char* /*args*/)
    {
        Player* player = handler->GetSession()->GetPlayer();
        if (player->HasAuraType(SPELL_AURA_TRANSFORM))
        {
            handler->PSendSysMessage("You cannot morph when you are transformed.");
            return false;
        }
        else if (player->getClass() == CLASS_DRUID && player->HasAuraType(SPELL_AURA_MOD_SHAPESHIFT))
        {
            handler->PSendSysMessage("You cannot morph when you are shapeshifted.");
            return false;
        }
        else if (player->InArena())
        {
            handler->PSendSysMessage("You cannot morph when you are in arena.");
            return false;
        }
        else
            player->SetNativeDisplayId(TAM);
            player->SetDisplayId(TAM);
        return true;
    }

    static bool HandleMorphTaurenFemaleCommand(ChatHandler* handler, const char* /*args*/)
    {
        Player* player = handler->GetSession()->GetPlayer();
        if (player->HasAuraType(SPELL_AURA_TRANSFORM))
        {
            handler->PSendSysMessage("You cannot morph when you are transformed.");
            return false;
        }
        else if (player->getClass() == CLASS_DRUID && player->HasAuraType(SPELL_AURA_MOD_SHAPESHIFT))
        {
            handler->PSendSysMessage("You cannot morph when you are shapeshifted.");
            return false;
        }
        else if (player->InArena())
        {
            handler->PSendSysMessage("You cannot morph when you are in arena.");
            return false;
        }
        else
            player->SetNativeDisplayId(TAF);
            player->SetDisplayId(TAF);
        return true;
    }

    static bool HandleMorphTrollMaleCommand(ChatHandler* handler, const char* /*args*/)
    {
        Player* player = handler->GetSession()->GetPlayer();
        if (player->HasAuraType(SPELL_AURA_TRANSFORM))
        {
            handler->PSendSysMessage("You cannot morph when you are transformed.");
            return false;
        }
        else if (player->getClass() == CLASS_DRUID && player->HasAuraType(SPELL_AURA_MOD_SHAPESHIFT))
        {
            handler->PSendSysMessage("You cannot morph when you are shapeshifted.");
            return false;
        }
        else if (player->InArena())
        {
            handler->PSendSysMessage("You cannot morph when you are in arena.");
            return false;
        }
        else
            player->SetNativeDisplayId(TRM);
            player->SetDisplayId(TRM);
        return true;
    }

    static bool HandleMorphBloodElfMaleCommand(ChatHandler* handler, const char* /*args*/)
    {
        Player* player = handler->GetSession()->GetPlayer();
        if (player->HasAuraType(SPELL_AURA_TRANSFORM))
        {
            handler->PSendSysMessage("You cannot morph when you are transformed.");
            return false;
        }
        else if (player->getClass() == CLASS_DRUID && player->HasAuraType(SPELL_AURA_MOD_SHAPESHIFT))
        {
            handler->PSendSysMessage("You cannot morph when you are shapeshifted.");
            return false;
        }
        else if (player->InArena())
        {
            handler->PSendSysMessage("You cannot morph when you are in arena.");
            return false;
        }
        else
            player->SetNativeDisplayId(BEM);
            player->SetDisplayId(BEM);
        return true;
    }

    static bool HandleMorphBloodElfFemaleCommand(ChatHandler* handler, const char* /*args*/)
    {
        Player* player = handler->GetSession()->GetPlayer();
        if (player->HasAuraType(SPELL_AURA_TRANSFORM))
        {
            handler->PSendSysMessage("You cannot morph when you are transformed.");
            return false;
        }
        else if (player->getClass() == CLASS_DRUID && player->HasAuraType(SPELL_AURA_MOD_SHAPESHIFT))
        {
            handler->PSendSysMessage("You cannot morph when you are shapeshifted.");
            return false;
        }
        else if (player->InArena())
        {
            handler->PSendSysMessage("You cannot morph when you are in arena.");
            return false;
        }
        else
            player->SetNativeDisplayId(BEF);
            player->SetDisplayId(BEF);
        return true;
    }

    static bool HandleMorphGoblinMaleCommand(ChatHandler* handler, const char* /*args*/)
    {
        Player* player = handler->GetSession()->GetPlayer();
        if (player->HasAuraType(SPELL_AURA_TRANSFORM))
        {
            handler->PSendSysMessage("You cannot morph when you are transformed.");
            return false;
        }
        else if (player->getClass() == CLASS_DRUID && player->HasAuraType(SPELL_AURA_MOD_SHAPESHIFT))
        {
            handler->PSendSysMessage("You cannot morph when you are shapeshifted.");
            return false;
        }
        else if (player->InArena())
        {
            handler->PSendSysMessage("You cannot morph when you are in arena.");
            return false;
        }
        else
            player->SetNativeDisplayId(GOBM);
            player->SetDisplayId(GOBM);
        return true;
    }

    static bool HandleMorphGoblinFemaleCommand(ChatHandler* handler, const char* /*args*/)
    {
        Player* player = handler->GetSession()->GetPlayer();
        if (player->HasAuraType(SPELL_AURA_TRANSFORM))
        {
            handler->PSendSysMessage("You cannot morph when you are transformed.");
            return false;
        }
        else if (player->getClass() == CLASS_DRUID && player->HasAuraType(SPELL_AURA_MOD_SHAPESHIFT))
        {
            handler->PSendSysMessage("You cannot morph when you are shapeshifted.");
            return false;
        }
        else if (player->InArena())
        {
            handler->PSendSysMessage("You cannot morph when you are in arena.");
            return false;
        }
        else
            player->SetNativeDisplayId(GOBF);
            player->SetDisplayId(GOBF);
        return true;
    }

    static bool HandleMorphNoneCommand(ChatHandler* handler, const char* /*args*/)
    {
        Player* player = handler->GetSession()->GetPlayer();
        if (player->HasAuraType(SPELL_AURA_TRANSFORM))
        {
            handler->PSendSysMessage("You cannot demorph when you are transformed.");
            return false;
        }
        else if (player->getClass() == CLASS_DRUID && player->HasAuraType(SPELL_AURA_MOD_SHAPESHIFT))
        {
            handler->PSendSysMessage("You cannot demorph when you are shapeshifted.");
            return false;
        }
        else if (player->InArena())
        {
            handler->PSendSysMessage("You cannot demorph when you are in arena.");
            return false;
        }
        else
            player->InitDisplayIds();
        return true;
    }
};

void AddSC_morph_commandscript()
{
    new morph_commandscript();
}