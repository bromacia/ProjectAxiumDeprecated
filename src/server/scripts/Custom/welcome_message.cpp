#include "ScriptPCH.h"

class welcome_message : public PlayerScript
{
   public:
	   welcome_message() : PlayerScript("welcome_message") { }

	   void OnLogin(Player* player)
	   {
		   char msg[250];
		   snprintf(msg, 250, "|cFFEE82EEWelcome on Axium-WoW ! %s", player->GetName());
		   sWorld->SendNotification(msg, NULL);
	   }
};

void AddSC_welcome_message()
{
	new welcome_message;
}