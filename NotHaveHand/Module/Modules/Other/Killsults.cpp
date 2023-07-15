#include "Killsults.h"

using namespace std;
Killsults::Killsults() : IModule(0, Category::OTHER, "Insults people you kill lol") {
    registerEnumSetting("Mode", &mode, 0);
    mode.addEntry("Normal", 0);
    mode.addEntry("Sigma", 1);
    //mode.addEntry("Custom", 2);
}

const char* Killsults::getRawModuleName() {
    return "Killsults";
}

const char* Killsults::getModuleName() {
    if (mode.getSelectedValue() == 0) name = string("Killsults ") + string(GRAY) + string("Normal");
    if (mode.getSelectedValue() == 1) name = string("Killsults ") + string(GRAY) + string("Custom");
    return name.c_str();
}

string normalMessages[36] = {
    "TONY IS STILL THE BEST: TONY DEVELOP!!!: )) sucker",
    
};

string cheaterMessages[9] = {
    "TONY IS STILL THE BEST: TONY DEVELOP!!!: )) sucker",
    
};

string sigmaMessages[2] = {
    "TONY IS STILL THE BEST: TONY DEVELOP!!!: )) sucker",
};

void Killsults::onEnable() {
    killed = false;
}

void Killsults::onPlayerTick(C_Player* plr) {
    auto player = g_Data.getLocalPlayer();
    if (player == nullptr) return;

    int random = 0;
    srand(time(NULL));
    if (killed) {
        C_TextPacket textPacket;
        switch (mode.getSelectedValue()) {
        case 0: // Normal
            random = rand() % 36;
            textPacket.message.setText(normalMessages[random]);
            break;
        case 1: // Sigma
            random = rand() % 2;
            textPacket.message.setText(sigmaMessages[random]);
            break;
        }
        textPacket.sourceName.setText(player->getNameTag()->getText());
        textPacket.xboxUserId = to_string(player->getUserId());
        g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&textPacket);
        killed = false;
    }
}