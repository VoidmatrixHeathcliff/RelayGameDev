#pragma once

#include"../gui/Scene.h"
#include"../game/Block.h"
#include"../entity/Player.h"

class GameScene :public PScene {
private:
	void _OnMessage(ExMessage& Message) override;
	void _OnDraw(PDevice* Device) override;
	void _OnUpdate(float deltaTime)override;
	void _OnEnter()override;

	std::vector<PBlock*> blocks;
	PPlayer* player;

public:
	GameScene();
	~GameScene();
};