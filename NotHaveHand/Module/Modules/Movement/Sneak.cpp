#include "Sneak.h"
#include "../pch.h"

Sneak::Sneak() : IModule(0, Category::MOVEMENT, "Automatically sneaks") {
	registerBoolSetting("Silent", &silentlol, silentlol);
}

const char* Sneak::getRawModuleName() {
	return "AutoSneak";
}

const char* Sneak::getModuleName() {
	if (!silentlol) {
		name = std::string("AutoSneak ") + std::string(GRAY) + std::string("[") + std::string(WHITE) + std::string("Normal") + std::string(GRAY) + std::string("]");
	}
	else
	{
		name = std::string("AutoSneak ") + std::string(GRAY) + std::string("[") + std::string(WHITE) + std::string("Silent") + std::string(GRAY) + std::string("]");
	}
	return name.c_str();
}

void Sneak::onTick(C_GameMode* gm) {

	if (!silentlol)
		g_Data.getClientInstance()->getMoveTurnInput()->isSneakDown = true;
}

void Sneak::onDisable() {
	if (g_Data.getLocalPlayer() == nullptr)
		return;

	if (!silentlol) {
		g_Data.getClientInstance()->getMoveTurnInput()->isSneakDown = false;
		return;
	}

	C_PlayerActionPacket p;
	p.action = 12;  //stop crouch packet
	p.entityRuntimeId = g_Data.getLocalPlayer()->entityRuntimeId;
	g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&p);
}

void Sneak::onEnable() {
	if (g_Data.getLocalPlayer() == nullptr)
		return;

	if (silentlol) {
		C_PlayerActionPacket p;
		p.action = 11;  //start crouch packet
		p.entityRuntimeId = g_Data.getLocalPlayer()->entityRuntimeId;
		g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&p);
	}
}