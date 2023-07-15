#pragma once

#include "../Module.h"
#include "../../ModuleManager.h"
#include "../../../../SDK/CClientInstance.h"

class AutoCrystal : public IModule {
private:
	bool gapplehb = false;
	int gappleSlot = 1;


	bool obsidianhb = false;
	int obsidianSlot = 1;

	bool crystalhb = false;
	int crystalSlot = 1;

	bool anvilhb = false;
	int anvilSlot = 1;

	bool Buttonhb = false;
	int ButtonSlot = 1;

	bool Swordhb = false;
	int SwordSlot = 1;


	bool woodhb = false;
	int woodSlot = 1;

	//bool Pickaxehb = false;
	//int PickaxeSlot = 1;





	bool Nodelay = false;





	bool dagapple = false;

	bool daob = false;

	bool dacry = false;

	bool daanvil = false;

	bool dabut = false;

	bool daSword = false;

	bool dawood = false;

	//bool daPickaxe = false;

public:
	AutoCrystal();
	virtual const char* getModuleName() override;
	virtual const char* getRawModuleName() override;
	virtual void onTick(C_GameMode* gm) override;
};
