//
//动物类
//
#pragma once

//？这里我没有仔细研究

#include "../../../include/entity/Entity.h"

class PAnimal :public PEntity
{
	//和怪物类那些方法一样
	void set_move_speed(int x)
	{
		stats.moveSpeed = Stat(x);
	}
	void set_maxHealth(int x)
	{
		stats.maxHealth = (Stat)x;
	}
	void set_attackDamage(int x)
	{
		stats.attackDamage = (Stat)x;
	}
	Stat get_maxHealth()const
	{
		return stats.maxHealth;
	}
	Stat get_currentHealth()const
	{
		return stats.currentHealth;
	}
	Stat get_move_speed()const
	{
		return stats.moveSpeed;
	}
	void is_Attacked(int damage)
	{
		is_attacked = true;
		stats.currentHealth.IncreaseValueBy(-damage);
	}
	void set_is_aggressiveness(bool flag) 
	{
		is_aggressiveness = flag;
	}
	bool get_is_aggressiveness()const
	{
		return is_aggressiveness;
	}
	virtual void Idle() = 0;//待机函数
	virtual void on_run() = 0;//行走函数
	virtual void attack() = 0;//攻击函数
	virtual void on_run_away() = 0;//逃跑函数
protected:
	bool is_attacked = false;//动物是否被攻击
	bool is_aggressiveness;//动物是否有攻击性
};