#define _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS		//stupid c++

#include"../../include/scene/MainScene.h"
#include <codecvt>
#include<iostream>


void MainScene::_OnDraw(PDevice* Device) {
	settextstyle(&titleFont);

	settextcolor(RGB(34, 34, 34));
	outtextxy(punX + 2, punY + 2, pun);

	settextcolor(YELLOW);
	outtextxy(punX, punY, pun);
}

void MainScene::_OnUpdate(float deltaTime) {
	titleFont.lfEscapement = static_cast<LONG>(140 * cos(punAnimation)) + 209;
	punAnimation += 2.f * deltaTime;
	constexpr float _PI = 3.14159f;
	if (punAnimation > _PI * 10.f) {
		punAnimation -= _PI * 10.f;
	}
}

static std::wstring toWstring(const std::string& str) {
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
	return converter.from_bytes(str);
}

void MainScene::ReadPuns() {
	std::wifstream file("./assets/texts/splashes.txt");
	file.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t>));
	std::wstring line;
	while (!file.eof()) {
		std::getline(file, line);
		_punList.emplace_back(line);
	}
}

MainScene::MainScene() :PScene() {
	srand(static_cast<unsigned int>(time(nullptr)));

	// 0.639 0.338

	auto buttonWidth = 0.309 * getwidth();
	auto buttonHeight = 0.113 * getheight();
	auto fontSize = getwidth() * 0.03125 > 28 ? 28 : getwidth() * 0.03125;
	_playButton = new PButton((int)buttonWidth, (int)buttonHeight, "Play");
	_settingButton = new PButton((int)buttonWidth, (int)buttonHeight, "Setting");
	_quitButton = new PButton((int)buttonWidth, (int)buttonHeight, "Quit");
	_backgroundImage = new PImageLabel("./assets/ui/menu_background.png");
	_gameLogoImage = new PImageLabel("./assets/ui/title.png");
	_backgroundImage->Resize(getwidth(), getheight());

	_playButton->FontStyle.lfHeight = (LONG)fontSize;
	_settingButton->FontStyle.lfHeight = (LONG)fontSize;
	_quitButton->FontStyle.lfHeight = (LONG)fontSize;

	_playButton->Move(getwidth() / 2 - _playButton->GetWidth() / 2, int(getheight() * 0.423));
	_settingButton->Move(_playButton->GetX(), _playButton->GetY() + _playButton->GetHeight() + 20);
	_quitButton->Move(_settingButton->GetX(), _settingButton->GetY() + _settingButton->GetHeight() + 20);
	_quitButton->OnClick.Connect([]{
		exit(0);	//for now
	});

	_gameLogoImage->Resize(int(getwidth() * 0.569), int(getheight() * 0.1224));
	_gameLogoImage->Move(int(getwidth() * 0.234), int(getheight() * 0.208));

	_menuUI.emplace_back(_backgroundImage);
	_menuUI.emplace_back(_playButton);
	_menuUI.emplace_back(_settingButton);
	_menuUI.emplace_back(_quitButton);
	_menuUI.emplace_back(_gameLogoImage);

	for (auto& object : _menuUI) {
		AddObject(object);
		object->Show();
	}

	gettextstyle(&titleFont);
	_tcscpy_s(titleFont.lfFaceName, _T("Minecraft"));
	titleFont.lfHeight = (LONG)(getwidth() * 0.0375);
	titleFont.lfEscapement = 209;
	titleFont.lfOrientation = 209;

	ReadPuns();

	punX = static_cast<int>(getwidth() * 0.639);
	punY = static_cast<int>(getheight() * 0.338);
	if (_punList.empty()) {
		throw std::runtime_error("wait what?, pun list is empty, check /assets/texts/splashes.txt");
	}
	pun = _punList[rand() % _punList.size()].c_str();
	punAnimation = 0.f;

	//std::cout << "done\n";
	SetDrawPolicy(DrawPolicy::ContentAbove);
}
