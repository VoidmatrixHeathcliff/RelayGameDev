//
//������
//
#pragma once

//��������û����ϸ�о�

#include "../../../include/entity/Entity.h"

class PAnimal :public PEntity
{
	//�͹�������Щ����һ��
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
	virtual void Idle() = 0;//��������
	virtual void on_run() = 0;//���ߺ���
	virtual void attack() = 0;//��������
	virtual void on_run_away() = 0;//���ܺ���
protected:
	bool is_attacked = false;//�����Ƿ񱻹���
	bool is_aggressiveness;//�����Ƿ��й�����
};