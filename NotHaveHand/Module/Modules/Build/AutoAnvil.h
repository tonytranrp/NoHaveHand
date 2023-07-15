#pragma once
#include "../Module.h"
class AutoAnvil : public IModule {
private:
	int obsiheight = 3;
	int anvilheight = 3;
	bool Bypass = true;
	bool tryAutoAnvil(vec3_t AutoAnvil);

public:
	AutoAnvil();
	~AutoAnvil();

	int range = 10;
	bool multiplace = false;
	bool onClick = false;
	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onTick(C_GameMode* gm) override;
};
