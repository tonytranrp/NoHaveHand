#pragma once
#include "../Module.h"
class ChatSuffix : public IModule {
public:
	ChatSuffix();
	~ChatSuffix();
	std::string Suffix = "NotHaveHand++";
	inline std::string& getCustomMessage2() { return Suffix; };

	virtual const char* getModuleName() override;
	virtual void onSendPacket(C_Packet* packet) override;
};