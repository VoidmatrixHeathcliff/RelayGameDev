//
//ʵ������ض����������ʵ��ָ���ǣ���ң�player�����ж����mobs��������/�Ѻ����animals��
//
#pragma once

//����������ƫ�ײ���룬������һЩ���⣬û������о����Ƽ��Ż�

#include "../../include/EasyXBase.h"
#include "../../include/animation/Animator.h"
#include "../../include/FSM/StateMachine.h"
#include "../../include/entity_attr/stats/EntityStatsManager.h"
#include "../../include/entity_attr/buff/BuffManager.h"

class PEntity
{
protected:
	PEntity() = default;
	~PEntity() = default;

protected:
	PAnimator anim; //ʵ�嶯���Ĺ�����
	PStateMachine stateMachine; //����ʵ��״̬ת����״̬��
	PEntityStatsManager stats; //ʵ����ֵ�Ĺ�����
	PBuffManager buffs; //ʵ���Buff������

	POINT pos = { 0,0 }; //ʵ������Ļ�ϵ�����λ��

	int facingDir = 1; //ʵ�峯��-1��1��


public:
	void SetVelocity(int xVelocity, int yVelocity); //����ʵ����λ���ٶ�

	void Flip(); //ʵ�����ͼת��

	virtual void Die() = 0; //ʵ������
};