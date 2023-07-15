#include "AutoLog.h"

AutoLog::AutoLog() : IModule(0, Category::PLAYER, "Spams so many packets server kicks you") {
	registerIntSetting("Health", &health, health, 1, 20);
	registerBoolSetting("Log in Message", &message, message);
	registerEnumSetting("Text Modes", &ByeByeMessage, 0);
	ByeByeMessage = SettingEnum(this)
						.addEntry(EnumEntry("ByeBye!!", 0))
						.addEntry(EnumEntry("Good Bye!!", 1))
						.addEntry(EnumEntry("You Are an idiot!!", 2))
						.addEntry(EnumEntry("Nuke ON TOP # Buy NukeClient", 3));
}
AutoLog::~AutoLog() {
}

const char* AutoLog::getModuleName() {
	return ("AutoLog");
}

void AutoLog::onTick(C_GameMode* gm) {
	int healthy = g_Data.getLocalPlayer()->getHealth();
	if (healthy < health + 2) {
		clientMessageF("your health is almost low do something!");
	}

	if (healthy < health) {
		if (message == true) { 
			C_TextPacket textPacket;
			if (ByeByeMessage.selected == 0) {
				textPacket.message.setText("ByeBye!!");
			}
			if (ByeByeMessage.selected == 1) {
				textPacket.message.setText("Good Bye!!");
			}
			if (ByeByeMessage.selected == 2) {
				textPacket.message.setText("You Are an idiot!!");
			}
			if (ByeByeMessage.selected == 3) {
				textPacket.message.setText(" : ) #Don't harrass a pro like me");
			}
			textPacket.sourceName.setText(g_Data.getLocalPlayer()->getNameTag()->getText());
			textPacket.xboxUserId = std::to_string(g_Data.getLocalPlayer()->getUserId());
			g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&textPacket);
		};
		for (int pp = 0; pp < 2500; pp++) {
			C_MovePlayerPacket movePacket(g_Data.getLocalPlayer(), *g_Data.getLocalPlayer()->getPos());
			g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&movePacket);
		}
	}
}