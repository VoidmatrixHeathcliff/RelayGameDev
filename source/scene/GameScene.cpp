#include"../../include/game/Block.h"
#include"../../include/scene/GameScene.h"
#include"../../include/game/collision/CollisionManager.h"
#include"../../../include/beg/Weapon.h"
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
	if (player->is_on_beg())
		return;
	PGetSingleton<CollisionManager>().step(deltaTime);		//更新物理模拟
	player->update(deltaTime);
	if (!player->isAlive() && player->get_player_state() == PlayerState::Alive) {
		player->set_player_state(PlayerState::Dying);
	}
}

void GameScene::_OnExit() {
	if (player != nullptr) {
		if (player->get_player_state() == PlayerState::Dead)
		{
			//TODO 玩家死透了
		}
		delete player;
	}
	for (auto* block : blocks) {
		delete block;
	}
}

/*
	Z：将创建GameScene而创建blocks 改成 进入GameScene才创建blocks
*/

void GameScene::_OnEnter() {
	setbkcolor(RGB(200, 200, 200));

	player = new PPlayer();

	SetDrawPolicy(DrawPolicy::GUIAbove);
	blocks.push_back(new PBlock(new PImageLabel("./assets/textures/blocks/end_bricks.png"), { 5.f, 5.f }));
	blocks.push_back(new PBlock(new PImageLabel("./assets/textures/blocks/end_bricks.png"), { 4.f,5.f }));
	blocks.push_back(new PBlock(new PImageLabel("./assets/textures/blocks/end_bricks.png"), { 3.f,5.f }));
	blocks.push_back(new PBlock(new PImageLabel("./assets/textures/blocks/end_bricks.png"), { 6.f,5.f }));
	blocks.push_back(new PBlock(new PImageLabel("./assets/textures/blocks/end_bricks.png"), { 7.f,5.f }));
	blocks.push_back(new PBlock(new PImageLabel("./assets/textures/blocks/end_bricks.png"), { 8.f,5.f }));

	blocks.push_back(new PBlock(new PImageLabel("./assets/textures/blocks/wool_colored_gray.png"), { 5.f,10.f }));
	blocks.push_back(new PBlock(new PImageLabel("./assets/textures/blocks/wool_colored_gray.png"), { 9.f,10.f }));
	blocks.push_back(new PBlock(new PImageLabel("./assets/textures/blocks/wool_colored_gray.png"), { 10.f,10.f }));
	blocks.push_back(new PBlock(new PImageLabel("./assets/textures/blocks/wool_colored_gray.png"), { 6.f,10.f }));
	blocks.push_back(new PBlock(new PImageLabel("./assets/textures/blocks/wool_colored_gray.png"), { 7.f,10.f }));
	blocks.push_back(new PBlock(new PImageLabel("./assets/textures/blocks/wool_colored_gray.png"), { 8.f,10.f }));
}

GameScene::GameScene() : PScene() {
	player = nullptr;
}

GameScene::~GameScene() {
}

PlayerState GameScene::get_player_state()
{
	if (player != nullptr) return player->get_player_state();
	return PlayerState::Dead;
	
}

PPlayer*& GameScene::get_player()
{
	return player;
}
