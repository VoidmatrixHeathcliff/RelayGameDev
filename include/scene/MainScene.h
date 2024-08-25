#pragma once
#include"../gui/Scene.h"
#include "../gui/Button.h"
#include "../gui/ImageLabel.h"
#include "../assets/AssetManager.h"
#include "../singleton/Singleton.h"
#include "../gui/GUIManager.h"
#include "../../thirdparty/mINI/src/mini/ini.h"
#include "../EasyXBase.h"
#include "../gui/Scene.h"


class MainScene :public PScene {
protected:
	void _OnDraw(PDevice* Device)override;
	void _OnUpdate(float deltaTime)override;

private:
	std::vector<std::wstring> _punList;
	LOGFONT titleFont;
	int punX, punY;
	const wchar_t* pun;
	float punAnimation = 0.1f;

	void ReadPuns();

public:
	std::vector<PGUIObject*> _menuUI;
	PImageLabel* _backgroundImage;
	PImageLabel* _gameLogoImage;
	PButton* _playButton;
	PButton* _settingButton;
	PButton* _quitButton;


public:
	MainScene();
};