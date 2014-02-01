#include "ScriptMgr.h"
#include "ObjectMgr.h"
#include "Player.h"
#include "Item.h"

class item_playerhandbook : public ItemScript
{
    public:
        item_playerhandbook() : ItemScript("item_playerhandbook") {}

        bool OnGossipHello(Player* player, Item* item)
        {
            infoTexts = sObjectMgr->GetInfoTextMap();

            for (InfoTextMap::const_iterator itr = infoTexts.begin(); itr != infoTexts.end(); ++itr)
                if (!itr->second.SubMenuId)
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, itr->second.MenuTitle.c_str(), GOSSIP_SENDER_MAIN, itr->first);

            player->SEND_GOSSIP_MENU(1, item->GetGUID());
            return true;
        }

        bool OnGossipSelect(Player* player, Item* item, uint32 sender, uint32 action)
        {
            player->PlayerTalkClass->ClearMenus();

            switch (action)
            {
                case GOSSIP_SENDER_MAIN:
                {
                    OnGossipHello(player, item);
                    break;
                }
                default:
                {
                    for (InfoTextMap::const_iterator itr = infoTexts.begin(); itr != infoTexts.end(); ++itr)
                        if (itr->second.SubMenuId == action)
                            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, itr->second.MenuTitle.c_str(), action, itr->first);

                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Back", GOSSIP_SENDER_MAIN, GOSSIP_SENDER_MAIN);

                    const InfoText* infoText = sObjectMgr->GetInfoText(action);
                    player->SEND_GOSSIP_MENU(infoText->NpcTextId ? infoText->NpcTextId : 1, item->GetGUID());
                    break;
                }
            }

            return true;
        }

    private:
        InfoTextMap infoTexts;
};

void AddSC_item_playerhandbook()
{
    new item_playerhandbook();
}
