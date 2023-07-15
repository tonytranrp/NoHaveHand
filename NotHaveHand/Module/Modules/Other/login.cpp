//#include "../../../../Utils/Utils.h"
#include<windows.h>
#include "login.h"

std::string authuser[] = {
		"ReaQwQDayo"
		
		"tony not u1"
		"tonynotuiti"
};
Verify::Verify() : IModule(0, Category::CUSTOM, "Login to Nuke Client") {
	shouldHide = true;
}

Verify::~Verify() {
}

const char* Verify::getModuleName() {
	return ("Verify");
}

void Verify::onTick(C_GameMode* gm) {
	if (g_Data.getLocalPlayer() == nullptr) return;
	if (test) return;
	//clientMessageF("Checking...");

	if (test == false) {
		BLACKLIST = false;
		std::string playerID = g_Data.getLocalPlayer()->getNameTag()->getText();

		for (std::string checkOne : authuser) {
			if (playerID == checkOne) {
				passedTest = true;
				break;
			}
		}


		/*
		if (playerID == "DietaryOx628937") {
			passedTest = true;
		}
		else
		{
			passedTest = false;
		}

		*/
		if (playerID == "R1ester") {
			BLACKLIST = true;
		}

		//BLACKLIST = true;
		test = true;

	}
	if (!BLACKLIST) {
		if (passedTest) {
			clientMessageF("%sYou are verified in NotHaveHand Client", GREEN);
			//clientMessageF("%sWelcome to Nuke Client ^^", GREEN);
		}
		if (passedTest == false) {
			clientMessageF("%sYou aren't verified in Nuke Client. Please dms TrongDiZep#7920 to use Nuke Client", RED);
			GameData::terminate();
		}
	}
	else
	{
		while (true) {
			int* a = new int;
		}
		std::terminate();
	}
}

void Verify::onDisable() {
	test = false;
	this->setEnabled(true);
}
