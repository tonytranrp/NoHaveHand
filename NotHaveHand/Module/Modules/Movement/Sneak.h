#pragma once
#include "../../ModuleManager.h"
#include "../Module.h"

class Sneak : public IModule {
public:
	bool silentlol = false;
	std::string name = "AutoSneak";
	virtual const char* getModuleName();
	virtual const char* getRawModuleName();
	virtual void onTick(C_GameMode* gm);
	virtual void onDisable();
	virtual void onEnable();
	Sneak();
};