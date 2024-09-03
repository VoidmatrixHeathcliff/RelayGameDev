#include "../../../include/scene/SettingScene.h"
#include <codecvt>
#include <iostream>
SettingScene::SettingScene() :PScene() {
	auto buttonWidth = 0.309 * getwidth();
	auto buttonHeight = 0.113 * getheight();
	auto fontSize = getwidth() * 0.03125 > 28 ? 28 : getwidth() * 0.03125;
	_fpsButton_60 = new PButton((int)buttonWidth, (int)buttonHeight, "60fps");
	_fpsButton_144 = new PButton((int)buttonWidth, (int)buttonHeight, "144fps");
	_fpsButton_165 = new PButton((int)buttonWidth, (int)buttonHeight, "165fps");
	_blackgroundImage = new PImageLabel("./assets/ui/menu_background.png");
	_blackgroundImage->Resize(getwidth(), getheight());

	_fpsButton_60->FontStyle.lfHeight = (LONG)fontSize;
	_fpsButton_144->FontStyle.lfHeight = (LONG)fontSize;
	_fpsButton_165->FontStyle.lfHeight = (LONG)fontSize;

	_fpsButton_60->Move(getwidth() / 2 - _fpsButton_60->GetWidth() / 2, int(getheight() * 0.423));
	_fpsButton_144->Move(_fpsButton_144->GetX(), _fpsButton_144->GetY() + _fpsButton_144->GetHeight() + 20);
	_fpsButton_165->Move(_fpsButton_165->GetX(), _fpsButton_165->GetY() + _fpsButton_165->GetHeight() + 20);
	
	_settingUI.emplace_back(_blackgroundImage);
	_settingUI.emplace_back(_fpsButton_60);
	_settingUI.emplace_back(_fpsButton_144);
	_settingUI.emplace_back(_fpsButton_165);
	_settingUI.emplace_back(_backButton);

	//std::cout << "done\n";
	SetDrawPolicy(DrawPolicy::ContentAbove);
}
