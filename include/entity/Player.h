#ifndef _PLAYER_H_
#define _PLAYER_H_

//
//玩家类
//

//？我只进行了图片的加载

#include "../../include/entity/Entity.h"
#include"../../new_animation.h"
#include <unordered_map>

enum class PlayerAssets
{
	HEAD_0 = 0,//无佩戴盔甲的头
	HEAD_1 ,//1r的头
	HEAD_2 ,//铁头
	HEAD_3 ,//金头
	HEAD_4 ,//钻石头
	HEAD_PL ,//南瓜头

	BODY_0,//普通身体
	BODY_1,//铁制身体
	BODY_2,//金制身体
	BODY_3,//钻石身体

	ARM_0,
	ARM_1,
	ARM_2,
	ARM_3,

	SLEEP
};

class PPlayer:public PEntity
{
public:
	//该函数建议放在构造函数中，但因层层封装无法调用该类的构造函数
	//所以我将该函数的方法设为公开
	void load_player_assets()//加载图集 
	{
		//如果显示加载失败，请检查一下层级是否正确
		head_assets[PlayerAssets::HEAD_0] = new PAssets(L"assets/spirt/Right.png", L"普通头图片加载失败");
		head_assets[PlayerAssets::HEAD_1] = new PAssets(L"assets/spirt/Crown1r.png", L"Crown1r图片加载失败");
		head_assets[PlayerAssets::HEAD_2] = new PAssets(L"assets/spirt/Head2r.png", L"铁头图片加载失败");
		head_assets[PlayerAssets::HEAD_3] = new PAssets(L"assets/spirt/Head3r.png", L"金头图片加载失败");
		head_assets[PlayerAssets::HEAD_4] = new PAssets(L"assets/spirt/Head4r.png", L"钻石头图片加载失败");
		head_assets[PlayerAssets::HEAD_PL] = new PAssets(L"assets/spirt/HeadPl.png", L"南瓜头图片加载失败");

		body_assets[PlayerAssets::BODY_0] = new PAssets(L"assets/spirt/Body4.png", L"普通身体图片加载失败");
		body_assets[PlayerAssets::BODY_1] = new PAssets(L"assets/spirt/Body_cp_2.png", L"铁制身体图片加载失败");
		body_assets[PlayerAssets::BODY_2] = new PAssets(L"assets/spirt/Body_cp_3.png", L"金制身体图片加载失败");
		body_assets[PlayerAssets::BODY_3] = new PAssets(L"assets/spirt/Body_cp_4.png", L"钻石身体图片加载失败");

		arm_assets[PlayerAssets::ARM_0] = new PAssets(L"assets/spirt/Arm4.png", L"普通胳膊图片加载失败");
		arm_assets[PlayerAssets::ARM_1] = new PAssets(L"assets/spirt/Body_cp_2.png", L"铁胳膊图片加载失败");
		arm_assets[PlayerAssets::ARM_2] = new PAssets(L"assets/spirt/Body_cp_3.png", L"金胳膊图片加载失败");
		arm_assets[PlayerAssets::ARM_3] = new PAssets(L"assets/spirt/Body_cp_4.png", L"钻石胳膊图片加载失败");

		sleep = new PAssets(L"assets/spirt/Sleep.png", L"睡觉图片加载失败");

	}

	void delete_player_assets()//这个是用来释放掉开辟的内存
	{
		for (auto& pair : head_assets) {
			delete pair.second;
		}
		head_assets.clear();

		for (auto& pair : body_assets) {
			delete pair.second;
		}
		body_assets.clear();

		for (auto& pair : arm_assets) {
			delete pair.second;
		}
		arm_assets.clear();

		delete sleep;
		sleep = nullptr;
	}

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
	void on_input(const ExMessage& msg)
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

	void Die()//注意！！！这里空实现
	{

	}

protected:
	bool is_left_key_down;//是否向左走
	bool is_right_key_down;//是否向右走

	std::unordered_map<PlayerAssets,PAssets*>head_assets;//头图集
	std::unordered_map<PlayerAssets,PAssets*>body_assets;//身体图集
	std::unordered_map<PlayerAssets,PAssets*>arm_assets;//胳膊图集
	PAssets* sleep;//睡觉图片

};

#endif // !_PLAYER_H_