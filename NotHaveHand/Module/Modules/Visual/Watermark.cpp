#include "Watermark.h"
#include "../pch.h"
#include <chrono>

using namespace std;
Watermark::Watermark() : IModule(0, Category::VISUAL, "Displays the watermark") {
	registerIntSetting("Opacity", &opacity, opacity, 0, 255);
	registerBoolSetting("Outline", &outlinec, outlinec);
	shouldHide = true;
}

const char* Watermark::getModuleName() {
	return ("Watermark");
}

void Watermark::onEnable() {
}

void Watermark::onPostRender(C_MinecraftUIRenderContext* renderCtx) {
	message = getCustomWatermarkMessage();
	std::string playerName = std::string(g_Data.getLocalPlayer()->getNameTag()->getText());
	auto player = g_Data.getLocalPlayer();
	if (player == nullptr || moduleMgr->getModule<DebugMenu>()->isEnabled()) return;
	auto interfaceMod = moduleMgr->getModule<Interface>();
	auto clickGUI = moduleMgr->getModule<ClickGUIMod>();
	if (g_Data.canUseMoveKeys() && !clickGUI->hasOpenedGUI) {
		float cc = 0;
		std::string Release;
		Release = "Paid";
#ifdef _DEBUG
		Release = "Dev";
#endif
		float hai = DrawUtils::getFont(Fonts::SMOOTH)->getLineHeight() * scale;
		float wit = DrawUtils::getTextWidth(&std::string(message + " - V1.0 " + Release + " | " + playerName), 1.f);
		auto interfaceColor = ColorUtil::interfaceColor(1);
		DrawUtils::drawText(vec2_t(2, 2), &std::string(message + " - V1.0 " + Release + " | " + playerName), MC_Color(interfaceColor), 1.f, 1.f, true);
		if (outlinec) {
			DrawUtils::drawRectangle(vec4_t(cc - 3, cc - 3, cc + wit + 3, cc + hai + 2), MC_Color(interfaceColor), 1.f);
		}
		if (opacity != 0) {
			DrawUtils::fillRectangleA(vec4_t(cc - 3, cc - 3, cc + wit + 3, cc + hai + 2), MC_Color(0, 0, 0, opacity));
		}
	}
}