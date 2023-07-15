#pragma once

#include "../../ModuleManager.h"
#include "../Module.h"

class HoleFiller : public IModule {
private:
	bool obsidian = true;
	bool bedrock = true;
	bool onclick = false;

public:
	int range = 5;
	bool notarget = false;

	bool tryHoleFiller(vec3_ti blkPlacement);
	bool canpla(vec3_ti blockPos);

	HoleFiller();
	~HoleFiller();
	// Inherited via IModule
	virtual const char* getModuleName() override;
	//virtual const char* getModName() override;
	virtual void onTick(C_GameMode* gm) override;
	//virtual void onTick(C_GameMode* gm) override;
	//virtual const char* getRawModuleName() override;
};