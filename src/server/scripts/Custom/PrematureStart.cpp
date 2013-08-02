#include "ScriptPCH.h"
#include "Battleground.h"
#include "Chat.h"

class PrematureStart : public GameObjectScript
{
    public:
        PrematureStart() : GameObjectScript("PrematureStart") {}

        bool OnGossipHello(Player* player, GameObject* go)
        {
            if (!player->HasGameMasterTagOn())
                if (!player->WantsPrematureBattleGroundStart() && !player->IsAddedToPrematureBattleGroundStartList())
                {
                    if (Battleground* bg = player->GetBattleground())
                    {
                        player->SetWantsPrematureBattleGroundStart(true);
                        ChatHandler(player).PSendSysMessage("You are now marked as ready");
                        bg->CheckForPrematureStart(player);
                    }
                }
            return true;
        }
};

void AddSC_PrematureStart()
{
    new PrematureStart();
}
