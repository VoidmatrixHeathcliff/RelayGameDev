#ifndef _ZHook_H_
#define _ZHook_H_

#include "Entity.h"
#include <cmath>

/*
	������ ZFishingScene ���㹳�ࡣ

	��д��PAnimation�����״̬����Ҳ����ֱ��ʹ�á�
	ʵ��û��ʱ���˾�ֻ����ʱ����д�˸���״̬�� ʵ�������� if else Ƕ�׵ķ�����
*/
class ZHook : public PEntity {
public:
	enum class ZHookState
	{
		Idle,			// ����״̬��������ת
		Chase,			// ׷��״̬��������ǰѰ����
		Retract			// ����״̬�������ջ�
	};

public:
	ZHook();
	~ZHook();

public:
	void draw(const RenderInfo& renderInfo) override;
	void update(float deltaTime) override;

public:
	/* ���õ�ǰ��״̬�� */
	void setCurrentState(ZHookState e) {
		eCurrentState = e;
	}

	/* ��ȡ��ǰ��״̬ */
	ZHookState getCurrentState() const {
		return eCurrentState;
	}

	/* ��ȡ��ǰ�Ƕ� */
	double getAngle() const { return angle; }

	/* ��ȡ����λ�� */
	const Vec2& getPosCenter() const { return posCenter; }

	/* ��ȡ�쳤�ٶ� */
	double getLengthVelocity() const { return dLengthVelocity; }

private:
	const double MAX_ANGLE = acos(-1.0) / 12.0 * 11.0;	// �������ƫ�ƽǶ�
	const double MIN_ANGLE = acos(-1.0) / 12.0;			// ������Сƫ�ƽǶ�
	const double DEFAULT_LENGTH;						// Ĭ�ϳ���
	const double ARROW_SIZE;							// ���Ӵ�С

	double dLength;						// ���ӳ���
	double dLengthVelocity = 8.0;		// �����쳤�ٶ�
	Vec2 posCenter;						// ������������
	double angle = acos(-1.0) / 2.0;	// ����ҡ�ڽǶ�
	double dAngularVelocity = 0.015;	// ҡ�ڽ��ٶ�

private:
	ZHookState eCurrentState = ZHookState::Idle;	// Ĭ������״̬
};

#endif // !_ZHook_H_
