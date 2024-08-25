#ifndef _PLAYER_H_
#define _PLAYER_H_

//
//�����
//

//����ֻ������ͼƬ�ļ���

#include "../../include/entity/Entity.h"
#include"../../new_animation.h"
#include <unordered_map>

enum class PlayerAssets
{
	HEAD_0 = 0,//��������׵�ͷ
	HEAD_1 ,//1r��ͷ
	HEAD_2 ,//��ͷ
	HEAD_3 ,//��ͷ
	HEAD_4 ,//��ʯͷ
	HEAD_PL ,//�Ϲ�ͷ

	BODY_0,//��ͨ����
	BODY_1,//��������
	BODY_2,//��������
	BODY_3,//��ʯ����

	ARM_0,
	ARM_1,
	ARM_2,
	ARM_3,

	SLEEP
};

class PPlayer:public PEntity
{
public:
	//�ú���������ڹ��캯���У��������װ�޷����ø���Ĺ��캯��
	//�����ҽ��ú����ķ�����Ϊ����
	void load_player_assets()//����ͼ�� 
	{
		//�����ʾ����ʧ�ܣ�����һ�²㼶�Ƿ���ȷ
		head_assets[PlayerAssets::HEAD_0] = new PAssets(L"assets/spirt/Right.png", L"��ͨͷͼƬ����ʧ��");
		head_assets[PlayerAssets::HEAD_1] = new PAssets(L"assets/spirt/Crown1r.png", L"Crown1rͼƬ����ʧ��");
		head_assets[PlayerAssets::HEAD_2] = new PAssets(L"assets/spirt/Head2r.png", L"��ͷͼƬ����ʧ��");
		head_assets[PlayerAssets::HEAD_3] = new PAssets(L"assets/spirt/Head3r.png", L"��ͷͼƬ����ʧ��");
		head_assets[PlayerAssets::HEAD_4] = new PAssets(L"assets/spirt/Head4r.png", L"��ʯͷͼƬ����ʧ��");
		head_assets[PlayerAssets::HEAD_PL] = new PAssets(L"assets/spirt/HeadPl.png", L"�Ϲ�ͷͼƬ����ʧ��");

		body_assets[PlayerAssets::BODY_0] = new PAssets(L"assets/spirt/Body4.png", L"��ͨ����ͼƬ����ʧ��");
		body_assets[PlayerAssets::BODY_1] = new PAssets(L"assets/spirt/Body_cp_2.png", L"��������ͼƬ����ʧ��");
		body_assets[PlayerAssets::BODY_2] = new PAssets(L"assets/spirt/Body_cp_3.png", L"��������ͼƬ����ʧ��");
		body_assets[PlayerAssets::BODY_3] = new PAssets(L"assets/spirt/Body_cp_4.png", L"��ʯ����ͼƬ����ʧ��");

		arm_assets[PlayerAssets::ARM_0] = new PAssets(L"assets/spirt/Arm4.png", L"��ͨ�첲ͼƬ����ʧ��");
		arm_assets[PlayerAssets::ARM_1] = new PAssets(L"assets/spirt/Body_cp_2.png", L"���첲ͼƬ����ʧ��");
		arm_assets[PlayerAssets::ARM_2] = new PAssets(L"assets/spirt/Body_cp_3.png", L"��첲ͼƬ����ʧ��");
		arm_assets[PlayerAssets::ARM_3] = new PAssets(L"assets/spirt/Body_cp_4.png", L"��ʯ�첲ͼƬ����ʧ��");

		sleep = new PAssets(L"assets/spirt/Sleep.png", L"˯��ͼƬ����ʧ��");

	}

	void delete_player_assets()//����������ͷŵ����ٵ��ڴ�
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

	void Die()//ע�⣡���������ʵ��
	{

	}

protected:
	bool is_left_key_down;//�Ƿ�������
	bool is_right_key_down;//�Ƿ�������

	std::unordered_map<PlayerAssets,PAssets*>head_assets;//ͷͼ��
	std::unordered_map<PlayerAssets,PAssets*>body_assets;//����ͼ��
	std::unordered_map<PlayerAssets,PAssets*>arm_assets;//�첲ͼ��
	PAssets* sleep;//˯��ͼƬ

};

#endif // !_PLAYER_H_