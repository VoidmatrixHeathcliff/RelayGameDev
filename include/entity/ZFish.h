#ifndef _ZFish_H_
#define _ZFish_H_

#include "Entity.h"
#include "../gui/ImageLabel.h"

#include <functional>

class ZHook;
/*
	������ ZFishingScene �� ZFish
*/
class ZFish : public PEntity {

public:
	enum class ZFishState
	{
		Idle,			// ���ã���Ӿ
		BeCaught,		// ��ץ���������ƶ�
		Death,			// ��ץ�ϰ�
		Disappear		// ��ʧ
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
	PImageLabel* imageLabel;			// ���ڻ��Ƶ�ImageLabel
	ZHook* pZHook = nullptr;			// �빳����ϵ

	int m_iFrameIndex;					// �������֡
	int m_iWidth;
	int m_iHeight;
	ZFishState eCurrentState = ZFishState::Idle;
};



#endif // !_ZFish_H_
