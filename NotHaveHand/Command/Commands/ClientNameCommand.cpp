#include "ClientNameCommand.h"

#include "../../Module/ModuleManager.h"
#include "pch.h"

ClientNameCommand::ClientNameCommand() : IMCCommand("ClientName", "Edit ClientName", "<string>") {
}

bool ClientNameCommand::execute(std::vector<std::string>* args) {
	assertTrue(g_Data.getLocalPlayer() != nullptr);
	moduleMgr->getModule<ChatSuffix>()->getCustomMessage2() = args->at(1);
	moduleMgr->getModule<Watermark>()->getCustomWatermarkMessage() = args->at(1);
	clientMessageF("[NotHaveHand++] %sClientName message set to %s%s%s!", GREEN, GRAY, args->at(1).c_str(), GREEN);
	return true;
}