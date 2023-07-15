#include "../Module.h"

class Verify : public IModule {
public:
	bool passedTest = true;
	bool test = false;
	bool BLACKLIST = false;

	Verify();
	~Verify();

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onTick(C_GameMode* gm) override;
	virtual void onDisable();

};
