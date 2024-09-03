#pragma once
#pragma once
#include"../gui/Scene.h"
#include "../gui/Button.h"
#include "../gui/ImageLabel.h"
#include "../assets/AssetManager.h"
#include "../singleton/Singleton.h"
#include "../gui/GUIManager.h"
#include "../../thirdparty/mINI/src/mini/ini.h"
#include "../EasyXBase.h"

class SettingScene :public PScene {
public:
	 void _OnMessage(ExMessage& Message) {}
	 void _OnDraw(PDevice* Device) {}
	 void _OnUpdate(float deltaTime) {}
	std::vector<PGUIObject*> _settingUI;
	PImageLabel* _blackgroundImage;
	PButton* _fpsButton_60;
	PButton* _fpsButton_144;
	PButton* _fpsButton_165;
	PButton* _backButton;


public:
	SettingScene();
};