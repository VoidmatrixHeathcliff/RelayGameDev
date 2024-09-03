#ifndef _ZFish_H_
#define _ZFish_H_

#include "Entity.h"
#include "../gui/ImageLabel.h"

#include <functional>

class ZHook;
/*
	适用于 ZFishingScene 的 ZFish
*/
class ZFish : public PEntity {

public:
	enum class ZFishState
	{
		Idle,			// 闲置：游泳
		BeCaught,		// 被抓：朝钩子移动
		Death,			// 被抓上岸
		Disappear		// 消失
	};

public:
	ZFish();
	~ZFish();

public:
	void draw(const RenderInfo& renderInfo) override;
	void update(float deltaTime) override;

public:
	void setCurrentState(ZFishState e) {
		eCurrentState = e;
	}

	ZFishState getCurrentState() const {
		return eCurrentState;
	}

	void setHook(ZHook* pZHook) { this->pZHook = pZHook; }


private:
	PImageLabel* imageLabel;			// 用于绘制的ImageLabel
	ZHook* pZHook = nullptr;			// 与钩子联系

	int m_iFrameIndex;					// 随机动画帧
	int m_iWidth;
	int m_iHeight;
	ZFishState eCurrentState = ZFishState::Idle;
};



#endif // !_ZFish_H_
