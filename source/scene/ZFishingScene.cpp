#include "../../include/scene/ZFishingScene.h"
#include "../../include/game/PResourseManager.h"
#include "../../include/game/collision/CollisionManager.h"

#include <iostream>

ZFishingScene::ZFishingScene() :
	PScene()
{
	/* Ԥ������ͼƬ */
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

/* ���Ʊ��������� */
void ZFishingScene::_OnEnter() {
	scoreText = nullptr;
	pZHook = new ZHook();
	iScore = 0;
}

void ZFishingScene::_OnExit() {
	delete pZHook;
	if (scoreText) delete scoreText;

	for (auto fish : vecFishPool) {
		delete fish;
	}
	vecFishPool.clear();
}

void ZFishingScene::_OnMessage(ExMessage& Message) {
	// ���������� ���� �ո� ���¹���
	if (Message.message == WM_LBUTTONDOWN || (Message.message == WM_KEYDOWN && Message.vkcode == VK_SPACE)) {
		if (pZHook->getCurrentState() == ZHook::ZHookState::Idle) {
			pZHook->setCurrentState(ZHook::ZHookState::Chase);
		}
	}
	// esc�˳�
	if (Message.message == WM_KEYDOWN && Message.vkcode == VK_ESCAPE) {
		if (_callback) _callback();
	}
}

void ZFishingScene::_OnDraw(PDevice* Device) {
	RenderInfo renderInfo;
	_drawBackground();
	scoreText->OnDraw();
	pZHook->draw(renderInfo);
	for (auto fish : vecFishPool) {
		fish->draw(renderInfo);
	}
}

void ZFishingScene::_OnUpdate(float deltaTime) {
	PGetSingleton<CollisionManager>().step(deltaTime);
	pZHook->update(deltaTime);

	// ���������
	if (rand() % 100 == 0) {
		vecFishPool.push_back(new ZFish());
		vecFishPool[vecFishPool.size() - 1]->setHook(pZHook);
	}
	// ������
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

		if (!flag) it++;
	}

	// ��������
	if (scoreText != nullptr) delete scoreText;
	scoreText = new PTextLabel(("Score: " + std::to_string(iScore)).c_str());
	scoreText->FontStyle.lfHeight = 20;
	scoreText->FontColor = RGB(0, 0, 0);
	scoreText->ResizeAsText();
	int iwidth = getwidth();
	int iheight = getheight();
	scoreText->Move(iwidth / 6 * 4, iheight / 20);
}

void ZFishingScene::_drawBackground() {
	int width = getWindowWidth();
	int height = getWindowHeight();
	int lineY = height / 5;

	/* �� 1/5 ��������ɫ���� */
	setfillcolor(RGB(135, 206, 235));
	bar(0, 0, width, lineY);

	/* �� 4/5 ��������ɫ���� */
	setfillcolor(RGB(0, 191, 255));
	bar(0, lineY, width, height);

	/* ���� 1/5 ������ֱ�� */
	setlinecolor(BLACK);
	setlinestyle(PS_SOLID, 5);
	line(0, lineY, width, lineY);

	/* ���Ʒ��������� */
	flyingFishsHookImage->OnDraw();
}