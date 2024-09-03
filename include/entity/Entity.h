//
//实体类相关定义的声明；实体指的是：玩家（player）、敌对生物（mobs）、中立/友好生物（animals）
//
#pragma once

//？该类属于偏底层代码，这里有一些问题，没有深度研究，推荐优化

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
	PAnimator anim;					//实体动画的管理器
	PStateMachine stateMachine;		//管理实体状态转换的状态机
	PEntityStatsManager stats;		//实体数值的管理器
	PBuffManager buffs;				//实体的Buff管理器

	//POINT pos = { 0,0 }; //实体在屏幕上的坐标位置

	int facingDir = 1;				//实体朝向，-1左，1右

	Hitbox* hb = nullptr;			//实体碰撞箱


public:
	//void SetVelocity(int xVelocity, int yVelocity); //赋予实体以位移速度

	//void Flip(); //实体的贴图转向

	//virtual void Die() = 0; //实体死亡

	//是否存活
	virtual bool isAlive() {
		return stats.currentHealth.GetValue() > 0;
	}

	//获取当前血量
	int GetHealth() {
		return stats.currentHealth.GetValue();
	}

	//修改血量
	virtual void changeHealth(int x) {
		stats.currentHealth.SetValue(stats.currentHealth.GetValue() + x);
		if (stats.currentHealth.GetValue() > stats.maxHealth.GetValue())
			stats.currentHealth.SetValue(stats.maxHealth.GetValue());//如果当前血量超过最大血量则当前血量为最大血量
	}


	virtual void draw(const RenderInfo& renderInfo) = 0;

	virtual void update(float deltaTime) {
		buffs.CheckBuffs(this);//实时更新实体的Buff
	}
};