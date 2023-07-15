#pragma once

#include "../../ModuleManager.h"
#include "../Module.h"
class AntiCrystal : public IModule {
public:
	float Height = 0.1f;
	bool Bypass = true;

	AntiCrystal() : IModule(0x0, Category::COMBAT, "AntiCrystal") {
		registerBoolSetting("bypass", &Bypass, Bypass);
		registerFloatSetting("Height", &Height, Height, 0.f, 1.f);
	};
	~AntiCrystal(){};

    void onSendPacket(C_Packet* packet) {
        if (g_Data.getLocalPlayer() == nullptr) return;
        vec3_t* pos = g_Data.getLocalPlayer()->getPos();
        if (!Bypass) {
            if (packet->isInstanceOf<C_MovePlayerPacket>() || packet->isInstanceOf<PlayerAuthInputPacket>()) {
                auto* InputPacket = reinterpret_cast<PlayerAuthInputPacket*>(packet);
                InputPacket->yawUnused -= Height;
            }
            else if (packet->isInstanceOf<C_MovePlayerPacket>()) {
                auto* movePacket = reinterpret_cast<C_MovePlayerPacket*>(packet);
                movePacket->Position.y -= Height;
            }
        }
    }

	virtual const char* getModuleName() override {
		return "AntiCrystal";
	}
};