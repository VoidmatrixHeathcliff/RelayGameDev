#include "../../include/game/Game.h"

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

	loadScene->SetCustomCallback([this] {
		SetCurrentScene(mainScene);
	});
	mainScene->_playButton->OnClick.Connect(this, &PLGame::SwitchToGameScene);

	SetCurrentScene(loadScene);

	setbkcolor(RGB(240, 56, 67));
}

PLGame::~PLGame() {
	delete mainScene;
	delete loadScene;
	delete gameScene;
	delete fishingScene;
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


	while (true) {

		//handle message
		ExMessage message;
		while (peekmessage(&message)) {
			if (message.message==WM_KEYDOWN&&message.vkcode == 0x46)//F: 这样写的主要是想要能在任意场景按F都可以立即开始钓鱼并且不影响当前场景,希望后面的同学不要怪我，我真不知道咋办了555555
			{
				PScene* a = currentScene;
				currentScene = fishingScene;
				fishingScene = a;
			}

			currentScene->OnMessage(message);
		}

		//calculate deltaTime
		auto currentTime = std::chrono::high_resolution_clock::now();
		std::chrono::duration<float> dt = currentTime - previousTime;
		previousTime = currentTime;
		float deltaTime = std::min(dt.count(), 0.1f);

	
		
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
	SetCurrentScene(mainScene);
}
