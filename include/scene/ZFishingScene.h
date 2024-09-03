#ifndef _Z_FISHING_SCENE_H_
#define _Z_FISHING_SCENE_H_

#include "../gui/Scene.h"

#include "../../include/animation/Animator.h"
#include "../../include/gui/ImageLabel.h"
#include "../../include/gui/TextLabel.h"
#include "../entity/ZHook.h"
#include "../entity/ZFish.h"

class ZFishingScene : public PScene {
public:
	ZFishingScene();
	~ZFishingScene();

protected:
	void _OnMessage(ExMessage& Message) override;
	void _OnDraw(PDevice* Device) override;
	void _OnUpdate(float deltaTime) override;
	void _OnEnter() override;
	void _OnExit() override;

	/* ªÊ÷∆±≥æ∞ */
	void _drawBackground();

private:
	ZHook* pZHook = nullptr;
	std::vector<ZFish*> vecFishPool;
	int iScore;
	PTextLabel* scoreText = nullptr;

	PImageLabel* flyingFishsHookImage;
};


#endif // !_Z_FISHING_SCENE_H_
