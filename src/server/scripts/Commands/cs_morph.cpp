#include "Chat.h"

enum MorphIds
{
    NOG = 7550,
    HUM = 49,
    HUF = 50,
    DWM = 53,
    DWF = 54,
    NEM = 55,
    NEF = 56,
    GNM = 1563,
    GNF = 1564,
    DRM = 16125,
    DRF = 16126,
    ORM = 51,
    ORF = 52,
    UDM = 57,
    UDF = 58,
    TAM = 59,
    TAF = 60,
    TRM = 1478,
    TRF = 1479,
    BEM = 15476,
    BEF = 15475
};

class morph_commandscript : public CommandScript
{
public:
    morph_commandscript() : CommandScript("morph_commandscript") { }

    static uint8 GetRaceByDisplayId(uint32 morphId)
    {
        switch (morphId)
        {
            case HUM: case HUF: return 1;
            case DWM: case DWF: return 3;
            case NEM: case NEF: return 4;
            case GNM: case GNF: return 7;
            case DRM: case DRF: return 11;
            case ORM: case ORF: return 2;
            case UDM: case UDF: return 5;
            case TAM: case TAF: return 6;
            case TRM: case TRF: return 8;
            case BEM: case BEF: return 10;
            default: return 0;
        }
    }

    static uint8 GetGenderByDisplayId(uint32 morphId)
    {
        switch (morphId)
        {
            case HUM:
            case DWM:
            case NEM:
            case GNM:
            case DRM:
            case ORM:
            case UDM:
            case TAM:
            case TRM:
            case BEM:
                return 0;
            case HUF:
            case DWF:
            case NEF:
            case GNF:
            case DRF:
            case ORF:
            case UDF:
            case TAF:
            case TRF:
            case BEF:
                return 1;
            default:
                return 0;
        }
    }

    ChatCommand* GetCommands() const
    {
        static ChatCommand morphCommandTable[] =
        {
            { "nog",        SEC_PLAYER,         false, &HandleMorphNoggenfoggerCommand,     "", NULL },
            /*{ "hum",        SEC_VIP,            false, &HandleMorphHumanMaleCommand,        "", NULL },
            { "huf",        SEC_VIP,            false, &HandleMorphHumanFemaleCommand,      "", NULL },
            { "dwm",        SEC_VIP,            false, &HandleMorphDwarfMaleCommand,        "", NULL },
            { "dwf",        SEC_VIP,            false, &HandleMorphDwarfFemaleCommand,      "", NULL },
            { "nem",        SEC_VIP,            false, &HandleMorphNightElfMaleCommand,     "", NULL },
            { "nef",        SEC_VIP,            false, &HandleMorphNightElfFemaleCommand,   "", NULL },
            { "gnm",        SEC_VIP,            false, &HandleMorphGnomeMaleCommand,        "", NULL },
            { "gnf",        SEC_VIP,            false, &HandleMorphGnomeFemaleCommand,      "", NULL },
            { "drm",        SEC_VIP,            false, &HandleMorphDraeneiMaleCommand,      "", NULL },
            { "drf",        SEC_VIP,            false, &HandleMorphDraeneiFemaleCommand,    "", NULL },
            { "orm",        SEC_VIP,            false, &HandleMorphOrcMaleCommand,          "", NULL },
            { "orf",        SEC_VIP,            false, &HandleMorphOrcFemaleCommand,        "", NULL },
            { "udm",        SEC_VIP,            false, &HandleMorphUndeadMaleCommand,       "", NULL },
            { "udf",        SEC_VIP,            false, &HandleMorphUndeadFemaleCommand,     "", NULL },
            { "tam",        SEC_VIP,            false, &HandleMorphTaurenMaleCommand,       "", NULL },
            { "taf",        SEC_VIP,            false, &HandleMorphTaurenFemaleCommand,     "", NULL },
            { "trm",        SEC_VIP,            false, &HandleMorphTrollMaleCommand,        "", NULL },
            { "trf",        SEC_VIP,            false, &HandleMorphTrollFemaleCommand,      "", NULL },
            { "bem",        SEC_VIP,            false, &HandleMorphBloodElfMaleCommand,     "", NULL },
            { "bef",        SEC_VIP,            false, &HandleMorphBloodElfFemaleCommand,   "", NULL },*/
            { "none",       SEC_VIP,            false, &HandleMorphNoneCommand,             "", NULL },
            { "help",       SEC_PLAYER,         false, &HandleMorphHelpCommand,             "", NULL },
            { NULL,         0,                  false, NULL,                                "", NULL }
        };
        static ChatCommand commandTable[] =
        {
            { "morph",      SEC_VIP,            false, NULL,                   "", morphCommandTable },
            { NULL,         0,                  false, NULL,                                "", NULL }
        };
        return commandTable;
    }

    static void Morph(ChatHandler* handler, uint32 morphId)
    {
        Player* player = handler->GetSession()->GetPlayer();

        if (player->HasAuraType(SPELL_AURA_TRANSFORM))
        {
            handler->PSendSysMessage("You can't morph when you are transformed.");
            return;
        }

        if (player->getClass() == CLASS_DRUID && player->HasAuraType(SPELL_AURA_MOD_SHAPESHIFT))
        {
            handler->PSendSysMessage("You can't morph when you are shapeshifted.");
            return;
        }

        if (player->InArena())
        {
            handler->PSendSysMessage("You can't morph when you are in arena.");
            return;
        }

        if (morphId == NOG)
        {
            player->SetDisplayId(morphId);
            player->SetNativeDisplayId(morphId);
            player->SetMorphed(true);
            player->SetNoggenfoggerMorphed(true);
            return;
        }

        uint32 bytes0 = 0;
        uint32 oldBytes0 = player->GetUInt32Value(UNIT_FIELD_BYTES_0);
        bytes0 |= GetRaceByDisplayId(morphId);
        bytes0 |= player->getClass() << 8;
        bytes0 |= GetGenderByDisplayId(morphId) << 16;
        player->SetUInt32Value(UNIT_FIELD_BYTES_0, bytes0);
        player->SetDisplayId(morphId);
        player->SetNativeDisplayId(morphId);
        player->SetUInt32Value(UNIT_FIELD_BYTES_0, oldBytes0);
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

        player->SetNoggenfoggerMorphed(false);
        player->SetMorphed(false);
        player->InitDisplayIds();
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

    static bool HandleMorphDwarfFemaleCommand(ChatHandler* handler, const char* /*args*/)
    {
        Morph(handler, DWF);
        return true;
    }

    static bool HandleMorphNightElfMaleCommand(ChatHandler* handler, const char* /*args*/)
    {
        Morph(handler, NEM);
        return true;
    }

    static bool HandleMorphNightElfFemaleCommand(ChatHandler* handler, const char* /*args*/)
    {
        Morph(handler, NEF);
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

    static bool HandleMorphDraeneiMaleCommand(ChatHandler* handler, const char* /*args*/)
    {
        Morph(handler, DRM);
        return true;
    }

    static bool HandleMorphDraeneiFemaleCommand(ChatHandler* handler, const char* /*args*/)
    {
        Morph(handler, DRF);
        return true;
    }

    static bool HandleMorphOrcMaleCommand(ChatHandler* handler, const char* /*args*/)
    {
        Morph(handler, ORM);
        return true;
    }

    static bool HandleMorphOrcFemaleCommand(ChatHandler* handler, const char* /*args*/)
    {
        Morph(handler, ORF);
        return true;
    }

    static bool HandleMorphUndeadMaleCommand(ChatHandler* handler, const char* /*args*/)
    {
        Morph(handler, UDM);
        return true;
    }

    static bool HandleMorphUndeadFemaleCommand(ChatHandler* handler, const char* /*args*/)
    {
        Morph(handler, UDF);
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

    static bool HandleMorphTrollFemaleCommand(ChatHandler* handler, const char* /*args*/)
    {
        Morph(handler, TRF);
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
                                     "is based on the first two/three letters of the race and the first letter of the gender "
                                     "with the with some exceptions like UDM which stands for Undead Male. (e.g. Human Male = Hum)");
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