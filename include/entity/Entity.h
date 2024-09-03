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
#include "../../include/render/RenderInfo.h"
#include "../game/collision/Hitbox.h"


class PEntity {
public:
	PEntity() = default;
	~PEntity() = default;

protected:
	PAnimator anim;					//ʵ�嶯���Ĺ�����
	PStateMachine stateMachine;		//����ʵ��״̬ת����״̬��
	PEntityStatsManager stats;		//ʵ����ֵ�Ĺ�����
	PBuffManager buffs;				//ʵ���Buff������

	//POINT pos = { 0,0 }; //ʵ������Ļ�ϵ�����λ��

	int facingDir = 1;				//ʵ�峯��-1��1��

	Hitbox* hb = nullptr;			//ʵ����ײ��


public:
	//void SetVelocity(int xVelocity, int yVelocity); //����ʵ����λ���ٶ�

	//void Flip(); //ʵ�����ͼת��

	//virtual void Die() = 0; //ʵ������

	//�Ƿ���
	virtual bool isAlive() {
		return stats.currentHealth.GetValue() > 0;
	}

	//��ȡ��ǰѪ��
	int GetHealth() {
		return stats.currentHealth.GetValue();
	}

	//�޸�Ѫ��
	virtual void changeHealth(int x) {
		stats.currentHealth.SetValue(stats.currentHealth.GetValue() + x);
		if (stats.currentHealth.GetValue() > stats.maxHealth.GetValue())
			stats.currentHealth.SetValue(stats.maxHealth.GetValue());//�����ǰѪ���������Ѫ����ǰѪ��Ϊ���Ѫ��
	}


	virtual void draw(const RenderInfo& renderInfo) = 0;

	virtual void update(float deltaTime) {
		buffs.CheckBuffs(this);//ʵʱ����ʵ���Buff
	}
};