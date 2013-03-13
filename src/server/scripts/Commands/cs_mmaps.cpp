#include "ScriptMgr.h"
#include "Chat.h"
#include "ObjectMgr.h"
#include "Player.h"
#include "PointMovementGenerator.h"
#include "MMapFactory.h"
#include "Map.h"
#include "TargetedMovementGenerator.h"
#include "PathFinderMovementGenerator.h"

class mmaps_commandscript : public CommandScript
{
    public:
        mmaps_commandscript() : CommandScript("mmaps_commandscript") { }

        ChatCommand* GetCommands() const
        {
            static ChatCommand mmapCommandTable[] =
            {
                { "path",           SEC_GAMEMASTER,         false, &HandleMmapPathCommand,   "", NULL },
                { NULL,             0,                      false, NULL,                     "", NULL }
            };

            static ChatCommand commandTable[] =
            {
                { "mmaps",           SEC_GAMEMASTER,         true,  NULL,        "", mmapCommandTable  },
                { NULL,             SEC_GAMEMASTER,         false, NULL,                     "", NULL }
            };
            return commandTable;
        }

        static bool HandleMmapPathCommand(ChatHandler* handler, char const* args)
        {
            Player* player = handler->GetSession()->GetPlayer();
            Unit* target = handler->getSelectedUnit();
            if (!player || !target)
            {
                handler->PSendSysMessage("Invalid target/source selection.");
                return true;
            }

            if (!MMAP::MMapFactory::createOrGetMMapManager()->GetNavMesh(handler->GetSession()->GetPlayer()->GetMapId()))
            {
                handler->PSendSysMessage("NavMesh not loaded for current map.");
                return true;
            }

            handler->PSendSysMessage("mmap path:");

            char* para = strtok((char*)args, " ");

            bool useStraightPath = false;
            if (para && !strcmp(para, "true"))
                useStraightPath = true;

            float x, y, z;
            player->GetPosition(x, y, z);

            PathFinderMovementGenerator path(target);
            path.SetUseStrightPath(useStraightPath);
            path.Calculate(x, y, z);

            PointsArray pointPath = path.GetPath();
            handler->PSendSysMessage("%s's path to %s:", target->GetName(), player->GetName());
            handler->PSendSysMessage("Building %s", useStraightPath ? "StraightPath" : "SmoothPath");
            handler->PSendSysMessage("length %i type %u", pointPath.size(), path.GetPathType());

            Vector3 start = path.GetStartPosition();
            Vector3 end = path.GetEndPosition();
            Vector3 actualEnd = path.GetActualEndPosition();

            handler->PSendSysMessage("start      (%.3f, %.3f, %.3f)", start.x, start.y, start.z);
            handler->PSendSysMessage("end        (%.3f, %.3f, %.3f)", end.x, end.y, end.z);
            handler->PSendSysMessage("actual end (%.3f, %.3f, %.3f)", actualEnd.x, actualEnd.y, actualEnd.z);

            for (uint32 i = 0; i < pointPath.size(); ++i)
                player->SummonCreature(1, pointPath[i].x, pointPath[i].y, pointPath[i].z, 0, TEMPSUMMON_TIMED_DESPAWN, 9000);

            return true;
        }
};

void AddSC_mmaps_commandscript()
{
    new mmaps_commandscript();
}
