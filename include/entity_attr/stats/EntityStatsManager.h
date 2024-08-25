//
//用于管理和存储各PEntity实例的各种统计数据，包括各种基础属性值，如攻击伤害、移动速度等
//对于玩家、敌对生物等等PEntity的子类所需要的特殊的成员变量数值，你可以选择为其新开一个继承于此PEntityStatsManager类的子类
//
#pragma once

#include "../../entity_attr/buff/BuffManager.h"

//封装一个数据类型，方便大家拓展，不喜欢的话删掉也可以（那就记得把Stat都换成int或者size_t）
class Stat {
public:
	Stat(int val) { value = val; }
	~Stat() = default;
	Stat& operator=(const Stat& stat) = default;
private:
	int value = 0;
public:
	int GetValue() { return value; }
	void SetValue(int val) { this->value = val; }
	void IncreaseValueBy(int val) { this->value += val; }
};



inline constexpr int PENTITY_BASE_HEALTH = 20;//基本的生命值
inline constexpr int PENTITY_BASE_MOVE_SPEED = 10;//基本的移动速度（我没有度量概念，交给写物理系统的同学来修改值）
inline constexpr int PENTITY_BASE_JUMP_FORCE = 10;//基本的跳跃力度
inline constexpr float PENTITY_GRAVITY = 9.8f; //重力加速度，不会写物理系统，放个宏在这先（）


class PEntityStatsManager {
public:
	PEntityStatsManager() = default;
	~PEntityStatsManager() = default;

public:
	Stat maxHealth = Stat(PENTITY_BASE_HEALTH); //实体初始最大血量
	Stat currentHealth = maxHealth; //实体当前血量

	Stat moveSpeed = Stat(PENTITY_BASE_MOVE_SPEED); //实体的初始移动速度
	Stat jumpForce = Stat(PENTITY_BASE_JUMP_FORCE); //实体的初始跳跃力度
	//Stat miningSpeed = Stat(0); //挖掘速度

	Stat attackDamage = Stat(0); //实体的攻击力，0表示无攻击力，默认为无
	//Stat armor = Stat(0); //实体的防御力，这里就不搞的那么多了，有需要自己加上即可

public:
	//比如你的某实体有力量Buff效果，那就需要通过某种方式来得到最终作用在被攻击者的伤害值
	//int GetFinalAttackDamage()
	//	return attackDamage.GetValue() + strength * dmgPerStrength;
};