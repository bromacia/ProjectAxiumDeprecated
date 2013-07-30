#include "Chat.h"

enum MorphIds
{
    NOG      = 7550,
    HUM      = 19723,
    HUF      = 19724,
    DWM      = 20317,
    NEM      = 20318,
    GNM      = 20580,
    GNF      = 20581,
    DRF      = 20323,
    ORM      = 21267,
    ORF      = 20316,
    TAM      = 20585,
    TAF      = 20584,
    TRM      = 20321,
    BEM      = 20578,
    BEF      = 20579,
    GOM      = 20582,
    GOF      = 20583
};

class morph_commandscript : public CommandScript
{
public:
    morph_commandscript() : CommandScript("morph_commandscript") { }

    ChatCommand* GetCommands() const
    {
        static ChatCommand morphCommandTable[] =
        {
            { "nog",        SEC_PLAYER,         false, &HandleMorphNoggenfoggerCommand,     "", NULL },
            { "hum",        SEC_VIP,            false, &HandleMorphHumanMaleCommand,        "", NULL },
            { "huf",        SEC_VIP,            false, &HandleMorphHumanFemaleCommand,      "", NULL },
            { "dwm",        SEC_VIP,            false, &HandleMorphDwarfMaleCommand,        "", NULL },
            { "nem",        SEC_VIP,            false, &HandleMorphNightElfMaleCommand,     "", NULL },
            { "gnm",        SEC_VIP,            false, &HandleMorphGnomeMaleCommand,        "", NULL },
            { "gnf",        SEC_VIP,            false, &HandleMorphGnomeFemaleCommand,      "", NULL },
            { "drf",        SEC_VIP,            false, &HandleMorphDraeneiFemaleCommand,    "", NULL },
            { "orm",        SEC_VIP,            false, &HandleMorphFelOrcMaleCommand,       "", NULL },
            { "orf",        SEC_VIP,            false, &HandleMorphOrcFemaleCommand,        "", NULL },
            { "tam",        SEC_VIP,            false, &HandleMorphTaurenMaleCommand,       "", NULL },
            { "taf",        SEC_VIP,            false, &HandleMorphTaurenFemaleCommand,     "", NULL },
            { "trm",        SEC_VIP,            false, &HandleMorphTrollMaleCommand,        "", NULL },
            { "bem",        SEC_VIP,            false, &HandleMorphBloodElfMaleCommand,     "", NULL },
            { "bef",        SEC_VIP,            false, &HandleMorphBloodElfFemaleCommand,   "", NULL },
            { "gom",        SEC_VIP,            false, &HandleMorphGoblinMaleCommand,       "", NULL },
            { "gof",        SEC_VIP,            false, &HandleMorphGoblinFemaleCommand,     "", NULL },
            { "none",       SEC_VIP,            false, &HandleMorphNoneCommand,             "", NULL },
            { "help",       SEC_PLAYER,         false, &HandleMorphHelpCommand,             "", NULL },
            { NULL,         0,                  false, NULL,                                "", NULL }
        };
        static ChatCommand commandTable[] =
        {
            { "morph",      SEC_GAMEMASTER,     false, NULL,                   "", morphCommandTable },
            { NULL,         0,                  false, NULL,                                "", NULL }
        };
        return commandTable;
    }

    static void Morph(ChatHandler* handler, uint32 morphId)
    {
        Player* player = handler->GetSession()->GetPlayer();

        if (player->HasAuraType(SPELL_AURA_TRANSFORM))
        {
            handler->PSendSysMessage("You cannot morph when you are transformed.");
            return;
        }

        if (player->getClass() == CLASS_DRUID && player->HasAuraType(SPELL_AURA_MOD_SHAPESHIFT))
        {
            handler->PSendSysMessage("You cannot morph when you are shapeshifted.");
            return;
        }

        if (player->InArena())
        {
            handler->PSendSysMessage("You cannot morph when you are in arena.");
            return;
        }

        player->SetNativeDisplayId(morphId);
        player->SetDisplayId(morphId);
        player->SetMorphed(true);

    }

    static void Demorph(ChatHandler* handler)
    {
        Player* player = handler->GetSession()->GetPlayer();

        if (player->HasAuraType(SPELL_AURA_TRANSFORM))
        {
            handler->PSendSysMessage("You cannot demorph when you are transformed.");
            return;
        }

        if (player->getClass() == CLASS_DRUID && player->HasAuraType(SPELL_AURA_MOD_SHAPESHIFT))
        {
            handler->PSendSysMessage("You cannot demorph when you are shapeshifted.");
            return;
        }

        if (player->InArena())
        {
            handler->PSendSysMessage("You cannot demorph when you are in arena.");
            return;
        }

        player->InitDisplayIds();
        player->SetNoggenfoggerMorphed(false);
        player->SetMorphed(false);
    }

    static bool HandleMorphNoggenfoggerCommand(ChatHandler* handler, const char* /*args*/)
    {
        Player* player = handler->GetSession()->GetPlayer();

        if (!player->IsNoggenfoggerMorphed())
        {
            Morph(handler, NOG);
            player->SetNoggenfoggerMorphed(true);
        }
        else
            Demorph(handler);

        return true;
    }

    static bool HandleMorphHumanMaleCommand(ChatHandler* handler, const char* /*args*/)
    {
        Morph(handler, HUM);
        return true;
    }

    static bool HandleMorphHumanFemaleCommand(ChatHandler* handler, const char* /*args*/)
    {
        Morph(handler, HUF);
        return true;
    }

    static bool HandleMorphDwarfMaleCommand(ChatHandler* handler, const char* /*args*/)
    {
        Morph(handler, DWM);
        return true;
    }

    static bool HandleMorphNightElfMaleCommand(ChatHandler* handler, const char* /*args*/)
    {
        Morph(handler, NEM);
        return true;
    }

    static bool HandleMorphGnomeMaleCommand(ChatHandler* handler, const char* /*args*/)
    {
        Morph(handler, GNM);
        return true;
    }

    static bool HandleMorphGnomeFemaleCommand(ChatHandler* handler, const char* /*args*/)
    {
        Morph(handler, GNF);
        return true;
    }

    static bool HandleMorphDraeneiFemaleCommand(ChatHandler* handler, const char* /*args*/)
    {
        Morph(handler, DRF);
        return true;
    }

    static bool HandleMorphFelOrcMaleCommand(ChatHandler* handler, const char* /*args*/)
    {
        Morph(handler, ORM);
        return true;
    }

    static bool HandleMorphOrcFemaleCommand(ChatHandler* handler, const char* /*args*/)
    {
        Morph(handler, ORF);
        return true;
    }

    static bool HandleMorphTaurenMaleCommand(ChatHandler* handler, const char* /*args*/)
    {
        Morph(handler, TAM);
        return true;
    }

    static bool HandleMorphTaurenFemaleCommand(ChatHandler* handler, const char* /*args*/)
    {
        Morph(handler, TAF);
        return true;
    }

    static bool HandleMorphTrollMaleCommand(ChatHandler* handler, const char* /*args*/)
    {
        Morph(handler, TRM);
        return true;
    }

    static bool HandleMorphBloodElfMaleCommand(ChatHandler* handler, const char* /*args*/)
    {
        Morph(handler, BEM);
        return true;
    }

    static bool HandleMorphBloodElfFemaleCommand(ChatHandler* handler, const char* /*args*/)
    {
        Morph(handler, BEF);
        return true;
    }

    static bool HandleMorphGoblinMaleCommand(ChatHandler* handler, const char* /*args*/)
    {
        Morph(handler, GOM);
        return true;
    }

    static bool HandleMorphGoblinFemaleCommand(ChatHandler* handler, const char* /*args*/)
    {
        Morph(handler, GOF);
        return true;
    }

    static bool HandleMorphNoneCommand(ChatHandler* handler, const char* /*args*/)
    {
        Demorph(handler);
        return true;
    }

    static bool HandleMorphHelpCommand(ChatHandler* handler, const char* /*args*/)
    {
        Player* player = handler->GetSession()->GetPlayer();

        if (player->GetSession()->GetSecurity() > SEC_PLAYER)
        {
            handler->PSendSysMessage("As a VIP you have access to morphs. The naming structure for morphs "
                                     "is based on the first two/three letters of the race and the first letter "
                                     "of the gender with the only exception being `nog` which stands for Noggenfogger. (e.g. Human Male = Hum)");
            handler->PSendSysMessage("In order to demorph type in `.morph none`. When morphed into a Skeleton via the "
                                     "`.morph nog` command you can type the command in again to demorph, just remember "
                                     "that this will only work for the `.morph nog` command.");
            handler->PSendSysMessage("You are also unable to use morph commands in an arena match or "
                                     "while already transformed. (e.g. Druid Forms, Deathbringer's will procs, etc.)");
            handler->PSendSysMessage("Another thing to note is that when you morph you will remain morphed until you "
                                     "demorph, logout or until you enter an arena match");
            handler->PSendSysMessage("If you have any additional questions feel free to create a ticket "
                                     "and a staff member will assist you when he/she is available.");
        }
        else
        {
            handler->PSendSysMessage("As a player you have access to `.morph nog`. When morphed into a "
                                     "Skeleton you can type in `.morph nog` again to demorph. Other commands "
                                     "such as race morph commands are only available for VIPs.");
            handler->PSendSysMessage("If you have any additional questions feel free to create a ticket "
                                     "and a staff member will assist you when he/she is available.");
        }

        return true;
    }
};

void AddSC_morph_commandscript()
{
    new morph_commandscript();
}