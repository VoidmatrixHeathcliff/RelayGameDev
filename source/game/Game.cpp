﻿#include "../../include/game/Game.h"
#include "../../include/keyboard/keyboard.h"
#include "../../include/notPiano/notPiano.h"

#include <codecvt>
#include <numeric>
#include "../../include/time/Timer.h"
//#define UI_DEMO


PLGame::PLGame(const int& Width, const int& Height, const PString& PlayerName)
	: PWindow(Width, Height, ostr::format("PaperCraft : {}'s World", PlayerName)), _playerName(PlayerName), _assetManager(PGetSingleton<PAssetManager>()) {

	_windowDevice = GetDevice();

	mainScene = new MainScene();
	loadScene = new LoadScene();
	gameScene = new GameScene();
	fishingScene = new FishingScene();
	fishingScene->SetCustomCallback([&]() {
		SetCurrentScene(mainScene);
		});

	zFishingScene = new ZFishingScene();
	zFishingScene->setWindowWidth(Width);
	zFishingScene->setWindowHeight(Height);
	zFishingScene->SetCustomCallback([&]() {
		SetCurrentScene(mainScene);
	});

	loadScene->SetCustomCallback([this] {
		SetCurrentScene(mainScene);
	});
	mainScene->_playButton->OnClick.Connect(this, &PLGame::SwitchToGameScene);
	mainScene->_zFishingButton->OnClick.Connect(this, &PLGame::SwitchToZFishingScene);

	SetCurrentScene(loadScene);

	setbkcolor(RGB(240, 56, 67));
}

PLGame::~PLGame() {
	delete mainScene;
	delete loadScene;
	delete gameScene;
	delete fishingScene;
	NotKeyBoard::KeyBoardControl::quit();
}

void PLGame::Loop() {
#ifdef _DEBUG
	LOGFONT debugFont;
	gettextstyle(&debugFont);
	_tcscpy_s(debugFont.lfFaceName, _T("Minecraft"));
	debugFont.lfHeight = 16;

	std::array<float, 200> frameTimes = {};
	int avgFPS = 0;
	size_t index = 0;
	Timer fpsCalcTimer(1.f, [&] {
		float total = std::accumulate(frameTimes.begin(), frameTimes.end(), 0.F);
		avgFPS = static_cast<int>(frameTimes.size() / total);
	});
	fpsCalcTimer.start();
#endif

	auto previousTime = std::chrono::high_resolution_clock::now();

	NotPiano::Piano notSimplePiano;
	unsigned char notes_down = 0;

	while (true) {
		if (gameScene->get_player_state() == PlayerState::Dying)
		{
			FishingScene* fs = (FishingScene*)fishingScene;
			fs->set_fishing_state(FishingState::SavingYourLive);
			SwitchToFishingScene();
			if (fs->get_is_saved() == HasSaved::Successed)
			{
				gameScene->get_player()->set_player_state(PlayerState::Alive);
				fs->set_fishing_state(FishingState::Play);
				fs->set_is_saved(HasSaved::None);
				SwitchToGameScene();
			}
			else if (fs->get_is_saved() == HasSaved::Failed)
			{
				gameScene->get_player()->set_player_state(PlayerState::Dead);
				fs->set_is_saved(HasSaved::None);
				SwitchToMainScene();
				fs->set_fishing_state(FishingState::Play);
			}

		}

		//handle message
		ExMessage message;
		while (peekmessage(&message)) {
			NotKeyBoard::KeyBoardControl::manager()->OnMessage(message);

			currentScene->OnMessage(message);
		}

		if (currentScene == fishingScene && NotKeyBoard::KeyBoardControl::manager()->isDown(NotKeyBoard::F))//F: 这样写的主要是想要能在任意场景按F都可以立即开始钓鱼并且不影响当前场景,希望后面的同学不要怪我，我真不知道咋办了555555
		{
			PScene* a = currentScene;
			currentScene->OnExit();
			currentScene = fishingScene;
			currentScene->OnEnter();
			fishingScene = a;
		}

		for (int k = 1; k <= 7; k++)
		{
			if (!(notes_down & (1 << k)) && NotKeyBoard::KeyBoardControl::manager()->isDown((NotKeyBoard::NotVK)(k + NotKeyBoard::N0)))
			{
				notes_down |= 1 << k;
				notSimplePiano.play(k);
			}
			else if (NotKeyBoard::KeyBoardControl::manager()->isUp((NotKeyBoard::NotVK)(k + NotKeyBoard::N0)))
			{
				notes_down &= ~(1 << k);
				notSimplePiano.stop();
			}
		}

		//calculate deltaTime
		auto currentTime = std::chrono::high_resolution_clock::now();
		std::chrono::duration<float> dt = currentTime - previousTime;
		previousTime = currentTime;
		float deltaTime = std::min(dt.count(), 0.1f);
		if (deltaTime < 1000 / 60)
			Sleep(1000 / 60 - deltaTime);

		//update
		currentScene->OnUpdate(deltaTime);

		//render
		cleardevice();
		currentScene->OnDraw(_windowDevice);

	#ifdef _DEBUG
		settextstyle(&debugFont);
		settextcolor(BLACK);
		outtextxy(getwidth() / 2 - textwidth(_T("PAPERCRAFT DEBUG MODE")) / 2 + 1, 1, _T("PAPERCRAFT DEBUG MODE"));
		settextcolor(WHITE);
		outtextxy(getwidth() / 2 - textwidth(_T("PAPERCRAFT DEBUG MODE")) / 2, 0, _T("PAPERCRAFT DEBUG MODE"));

		frameTimes[index] = deltaTime;
		index++;
		if (index >= frameTimes.size())index = 0;
		fpsCalcTimer.update(deltaTime);
		auto fpsText = PStringToCStr<TCHAR>(ostr::format("FPS: {}", avgFPS));
		settextcolor(WHITE);
		outtextxy(0, 0, fpsText);
		delete fpsText;
	#endif

		_windowDevice->Flush();

	}
}

void PLGame::SetCurrentScene(PScene* scene) {
	if (!scene)return;
	if (currentScene) {
		currentScene->OnExit();
	}
	currentScene = scene;
	currentScene->OnEnter();
}

void PLGame::SwitchToGameScene() {
	
	SetCurrentScene(gameScene);
}

void PLGame::SwitchToMainScene() {
	gameScene->get_player()->set_player_state(PlayerState::Alive);
	SetCurrentScene(mainScene);
}

void PLGame::SwitchToFishingScene() {
	SetCurrentScene(fishingScene);
}

void PLGame::SwitchToZFishingScene() {
	SetCurrentScene(zFishingScene);
}