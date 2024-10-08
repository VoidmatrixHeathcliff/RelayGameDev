#include "../../include/scene/ZFishingScene.h"
#include "../../include/game/PResourseManager.h"
#include "../../include/game/collision/CollisionManager.h"

#include <iostream>

ZFishingScene::ZFishingScene() :
	PScene()
{
	/* 预加载鱼图片 */
	PResourseManager* manager = &PGetSingleton<PResourseManager>();
	manager->loadImage("./assets/flyingfish/flyingfish.png", "flyingfish");
	manager->loadImage("./assets/flyingfish/fish_pufferfish_raw.png", "fish_pufferfish_raw");
	manager->loadImage("./assets/flyingfish/fish_clownfish_raw.png", "fish_clownfish_raw");
	manager->loadImage("./assets/flyingfish/fish_salmon_raw.png", "ish_salmon_raw");
	manager->loadImage("./assets/flyingfish/fish_cod_raw.png", "fish_cod_raw");
	manager->loadImage("./assets/flyingfish/fishingrod.png", "flyingFishsHook");
	manager->loadImage("./assets/flyingfish/bat_fish.png", "bat_fish");
	flyingFishsHookImage = new PImageLabel(manager->findImage("flyingFishsHook"));
	flyingFishsHookImage->Resize(getwidth() / 12, getheight() / 12);
	flyingFishsHookImage->Move(getwidth() / 2 - getwidth() / 13, getheight() / 9);
}

ZFishingScene::~ZFishingScene() {
	delete flyingFishsHookImage;
}

/* 绘制背景、文字 */
void ZFishingScene::_OnEnter() {
	scoreText = nullptr;
	timerText = nullptr;
	pZHook = new ZHook();
	iScore = 0;
	timer = 30.0f;
}

void ZFishingScene::_OnExit() {
	delete pZHook;
	if (scoreText) delete scoreText;
	if (timerText) delete timerText;

	for (auto fish : vecFishPool) {
		delete fish;
	}
	vecFishPool.clear();
}

void ZFishingScene::_OnMessage(ExMessage& Message) {
	// 鼠标左键按下 或者 空格 放下钩子
	if (Message.message == WM_LBUTTONDOWN || (Message.message == WM_KEYDOWN && Message.vkcode == VK_SPACE)) {
		if (pZHook->getCurrentState() == ZHook::ZHookState::Idle) {
			pZHook->setCurrentState(ZHook::ZHookState::Chase);
		}
	}

	if (Message.message == WM_LBUTTONDOWN || (Message.message == WM_KEYDOWN && Message.vkcode == VK_SPACE)) {
		if (pZHook->getCurrentState() == ZHook::ZHookState::Retract) {
			pZHook->changeRetractLengthVelocity(5.0f);
		}
	}
	// esc退出
	if (Message.message == WM_KEYDOWN && Message.vkcode == VK_ESCAPE) {
		if (_callback) _callback();
	}
}

void ZFishingScene::_OnDraw(PDevice* Device) {
	RenderInfo renderInfo;
	_drawBackground();
	scoreText->OnDraw();
	timerText->OnDraw();
	pZHook->draw(renderInfo);
	for (auto fish : vecFishPool) {
		fish->draw(renderInfo);
	}
}

void ZFishingScene::_OnUpdate(float deltaTime) {
	PGetSingleton<CollisionManager>().step(deltaTime);
	pZHook->update(deltaTime);

	// 随机生成鱼
	if (rand() % 100 == 0) {
		vecFishPool.push_back(new ZFish());
		vecFishPool[vecFishPool.size() - 1]->setHook(pZHook);				//在这里设置的钩子
	}
	// 更新鱼
	for (auto it = vecFishPool.begin(); it != vecFishPool.end();) {
		bool flag = false;
		if ((*it)->getCurrentState() == ZFish::ZFishState::Death) {
			iScore += 10;
		}


		if ((*it)->getCurrentState() == ZFish::ZFishState::Death || (*it)->getCurrentState() == ZFish::ZFishState::Disappear) {
			delete (*it);
			it = vecFishPool.erase(it);
			flag = true;
		}
		else {
			(*it)->update(deltaTime);
		}

		//因为erase的释放空间是把整体前移
		if (!flag) it++;
	}

	if (timer - deltaTime < 0)
	{
		timer = 0.0f;
		static TCHAR text[128];
		_stprintf_s(text, _T("最终得分: %d"), iScore);
		MessageBox(GetHWnd(), text, _T("游戏结束"), MB_OK);
		if (_callback) _callback();
		return;				//主要回调函数调用exit会删除字体，然后继续逻辑再次删除字体会出问题所以直接返回
	}
	else
		timer -=deltaTime;

	// 更新文字
	if (scoreText != nullptr) delete scoreText;
	scoreText = new PTextLabel(("Score: " + std::to_string(iScore)).c_str());
	scoreText->FontStyle.lfHeight = 20;
	scoreText->FontColor = RGB(0, 0, 0);
	scoreText->ResizeAsText();
	int iwidth = getwidth();
	int iheight = getheight();
	scoreText->Move(iwidth / 6 * 4, iheight / 20);

	if (timerText != nullptr) delete timerText;
	timerText = new PTextLabel(("Time: " + std::to_string((int)timer)).c_str());
	timerText->FontStyle.lfHeight = 20;
	timerText->FontColor = RGB(0, 0, 0);
	timerText->ResizeAsText();
	timerText->Move(iwidth / 6 * 4, iheight / 20+20);

}

void ZFishingScene::_drawBackground() {
	int width = getWindowWidth();
	int height = getWindowHeight();
	int lineY = height / 5;

	/* 上 1/5 绘制天蓝色背景 */
	setfillcolor(RGB(135, 206, 235));
	bar(0, 0, width, lineY);

	/* 下 4/5 绘制深蓝色背景 */
	setfillcolor(RGB(0, 191, 255));
	bar(0, lineY, width, height);

	/* 在上 1/5 处绘制直线 */
	setlinecolor(BLACK);
	setlinestyle(PS_SOLID, 5);
	line(0, lineY, width, lineY);

	/* 绘制飞鱼丸的鱼竿 */
	flyingFishsHookImage->OnDraw();
}