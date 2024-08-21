//
//敌对生物类
//
#pragma once

#include "../../../include/entity/Entity.h"

class PEnemy :public PEntity
{
public:
	//设置仇恨半径大小
	void set_hatred_radius(int x,int y)
	{
		hatred_radius_x = x;
		hatred_radius_y = y;
	}
	//设置是否被攻击
	void set_is_pursuing_enemy(bool flag) 
	{
		is_pursuing_enemy = flag;
	}
	//设置是攻击半径大小
	void set_attack_radius(int x, int y)
	{
		attack_radius_x = x;
		attack_radius_y = y;
	}
	//获取是否处于索敌状态
	bool get_is_pursuing_enemy() 
	{
		return is_pursuing_enemy;
	}
	//设置怪物的移动速度，因为不同的怪物速度不同
	void set_move_speed(int x)
	{
	 stats.moveSpeed = Stat(x);
	}
	//设置怪物的最大血量
	void set_maxHealth(int x)
	{
		stats.maxHealth = (Stat)x;
	}
	//设置怪物的伤害
	void set_attackDamage(int x)
	{
		stats.attackDamage = (Stat)x;
	}
	//获取怪物最大生命值
	Stat get_maxHealth() const
	{
		return stats.maxHealth;
	}
	//获取怪物当前生命值
	Stat get_currentHealth()const
	{
		return stats.currentHealth;
	}
	//获取怪物的速度
	Stat get_move_speed()const
	{
		return stats.moveSpeed;
	}
	//怪物受到伤害 如果有防御的再去改，我感觉可以让玩家是真伤，只有玩家的算法需要防御
	void is_attacked(int damage)
	{
		stats.currentHealth.IncreaseValueBy(-damage);
	}
	virtual void attack() = 0;//攻击函数，具体自己实现
	virtual void Idle() = 0;//待机函数，里面可以写入待机时速度
	virtual void on_run() = 0;//跑步函数
protected:
	int hatred_radius_x;//仇恨半径X
	int hatred_radius_y;//仇恨半径Y
	bool is_pursuing_enemy;//是否处于锁敌状态
	int attack_radius_x;//攻击半径X
	int attack_radius_y;//攻击半径Y
	

};