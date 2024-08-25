#include"../../include/scene/GameScene.h"
#include"../../include/game/collision/CollisionManager.h"


void GameScene::_OnMessage(ExMessage& Message) {
	player->onMessage(Message);
}

void GameScene::_OnDraw(PDevice* Device) {
	RenderInfo info;
	info.scale = 40.f;
	for (auto* block : blocks) {
		block->draw(info);
	}
	player->draw(info);
}

void GameScene::_OnUpdate(float deltaTime) {
	PGetSingleton<CollisionManager>().step(deltaTime);		//更新物理模拟
	player->update(deltaTime);
}

void GameScene::_OnEnter() {
	setbkcolor(RGB(200, 200, 200));
}

GameScene::GameScene() {
	blocks.push_back(new PBlock(nullptr, { 5.f,5.f }));
	blocks.push_back(new PBlock(nullptr, { 4.f,5.f }));
	blocks.push_back(new PBlock(nullptr, { 3.f,5.f }));
	blocks.push_back(new PBlock(nullptr, { 6.f,5.f }));
	blocks.push_back(new PBlock(nullptr, { 7.f,5.f }));
	blocks.push_back(new PBlock(nullptr, { 8.f,5.f }));

	player = new PPlayer();

	SetDrawPolicy(DrawPolicy::GUIAbove);
}

GameScene::~GameScene() {
	for (auto* block : blocks) {
		delete block;
	}
	delete player;
}
