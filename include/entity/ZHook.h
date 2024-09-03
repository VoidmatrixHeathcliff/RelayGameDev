#ifndef _ZHook_H_
#define _ZHook_H_

#include "Entity.h"
#include <cmath>

/*
	适用于 ZFishingScene 的鱼钩类。

	在写完PAnimation类后发现状态机类也不能直接使用。
	实在没有时间了就只能临时给它写了个类状态机 实际上是用 if else 嵌套的方法。
*/
class ZHook : public PEntity {
public:
	enum class ZHookState
	{
		Idle,			// 闲置状态，钩子旋转
		Chase,			// 追逐状态，钩子往前寻找鱼
		Retract			// 回收状态，钩子收回
	};

public:
	ZHook();
	~ZHook();

public:
	void draw(const RenderInfo& renderInfo) override;
	void update(float deltaTime) override;

public:
	/* 设置当前的状态。 */
	void setCurrentState(ZHookState e) {
		eCurrentState = e;
	}

	/* 获取当前的状态 */
	ZHookState getCurrentState() const {
		return eCurrentState;
	}

	/* 获取当前角度 */
	double getAngle() const { return angle; }

	/* 获取中心位置 */
	const Vec2& getPosCenter() const { return posCenter; }

	/* 获取伸长速度 */
	double getLengthVelocity() const { return dLengthVelocity; }

private:
	const double MAX_ANGLE = acos(-1.0) / 12.0 * 11.0;	// 钩子最大偏移角度
	const double MIN_ANGLE = acos(-1.0) / 12.0;			// 钩子最小偏移角度
	const double DEFAULT_LENGTH;						// 默认长度
	const double ARROW_SIZE;							// 钩子大小

	double dLength;						// 钩子长度
	double dLengthVelocity = 8.0;		// 钩子伸长速度
	Vec2 posCenter;						// 钩子中心坐标
	double angle = acos(-1.0) / 2.0;	// 钩子摇摆角度
	double dAngularVelocity = 0.015;	// 摇摆角速度

private:
	ZHookState eCurrentState = ZHookState::Idle;	// 默认闲置状态
};

#endif // !_ZHook_H_
