//
//玩家类
//
#pragma once
//#include<graphics.h>
#include "../../include/entity/Entity.h"

class PPlayer :public PEntity
{
public:
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
	void on_input(const ExMessage&msg)
	{
		switch (msg.message)
		{
		case WM_KEYDOWN:
			switch (msg.vkcode)
			{
			case 0x41:
				is_left_key_down = true;
				break;
			case 0x44:
				is_right_key_down = true;
				break;
			}
		}
	}
protected:
	bool is_left_key_down;//是否向左走
	bool is_right_key_down;//是否向右走
};