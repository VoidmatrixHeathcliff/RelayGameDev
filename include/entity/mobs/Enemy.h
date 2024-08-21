//
//�ж�������
//
#pragma once

#include "../../../include/entity/Entity.h"

class PEnemy :public PEntity
{
public:
	//���ó�ް뾶��С
	void set_hatred_radius(int x,int y)
	{
		hatred_radius_x = x;
		hatred_radius_y = y;
	}
	//�����Ƿ񱻹���
	void set_is_pursuing_enemy(bool flag) 
	{
		is_pursuing_enemy = flag;
	}
	//�����ǹ����뾶��С
	void set_attack_radius(int x, int y)
	{
		attack_radius_x = x;
		attack_radius_y = y;
	}
	//��ȡ�Ƿ�������״̬
	bool get_is_pursuing_enemy() 
	{
		return is_pursuing_enemy;
	}
	//���ù�����ƶ��ٶȣ���Ϊ��ͬ�Ĺ����ٶȲ�ͬ
	void set_move_speed(int x)
	{
	 stats.moveSpeed = Stat(x);
	}
	//���ù�������Ѫ��
	void set_maxHealth(int x)
	{
		stats.maxHealth = (Stat)x;
	}
	//���ù�����˺�
	void set_attackDamage(int x)
	{
		stats.attackDamage = (Stat)x;
	}
	//��ȡ�����������ֵ
	Stat get_maxHealth() const
	{
		return stats.maxHealth;
	}
	//��ȡ���ﵱǰ����ֵ
	Stat get_currentHealth()const
	{
		return stats.currentHealth;
	}
	//��ȡ������ٶ�
	Stat get_move_speed()const
	{
		return stats.moveSpeed;
	}
	//�����ܵ��˺� ����з�������ȥ�ģ��Ҹо���������������ˣ�ֻ����ҵ��㷨��Ҫ����
	void is_attacked(int damage)
	{
		stats.currentHealth.IncreaseValueBy(-damage);
	}
	virtual void attack() = 0;//���������������Լ�ʵ��
	virtual void Idle() = 0;//�����������������д�����ʱ�ٶ�
	virtual void on_run() = 0;//�ܲ�����
protected:
	int hatred_radius_x;//��ް뾶X
	int hatred_radius_y;//��ް뾶Y
	bool is_pursuing_enemy;//�Ƿ�������״̬
	int attack_radius_x;//�����뾶X
	int attack_radius_y;//�����뾶Y
	

};