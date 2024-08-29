#ifndef _PLAYER_H_
#define _PLAYER_H_

//
//�����
//

//����ֻ������ͼƬ�ļ���

#include"../beg/Beg.h"
#include "../../include/entity/Entity.h"
#include"../../new_animation.h"
#include"../game/collision/CollisionManager.h"
#include <unordered_map>

enum class PlayerAssets {
	HEAD_0 = 0,//��������׵�ͷ
	HEAD_1,//1r��ͷ
	HEAD_2,//��ͷ
	HEAD_3,//��ͷ
	HEAD_4,//��ʯͷ
	HEAD_PL,//�Ϲ�ͷ

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

enum class PlayerState
{
	Alive = 0,	// ����
	Dying,		// ����
	Dead		// ��͸��
};

class PPlayer :public PEntity {
public:
	//�ú���������ڹ��캯���У��������װ�޷����ø���Ĺ��캯��
	//�����ҽ��ú����ķ�����Ϊ����
	//���ⲿ�ֽ�����ȡ���������ڵ�����ʵ�֣�
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

	void set_move_speed(int x) {
		stats.moveSpeed = Stat(x);
	}
	void set_maxHealth(int x) {
		stats.maxHealth = (Stat)x;
	}
	void set_attackDamage(int x) {
		stats.attackDamage = (Stat)x;
	}
	Stat get_maxHealth() const {
		return stats.maxHealth;
	}
	Stat get_currentHealth()const {
		return stats.currentHealth;
	}
	Stat get_move_speed()const {
		return stats.moveSpeed;
	}
	bool catch_content(PContent* thing)
	{
		if (beg.Can_Add() == false)
			return false;
		beg.Add(thing);
		return true;
	}
	void onMessage(const ExMessage& msg) {
			beg.On_Message(msg);
			on_hand = beg.Get_On_Hand();
		//todo
		switch (msg.message) {
			case WM_KEYDOWN:
				switch (msg.vkcode) {
					case VK_LBUTTON:
						//todo	������
						break;
					case VK_RBUTTON:
						//todo  ����Ҽ�
						break;
					case 0x41:
						isMovingLeft = true;
						break;
					case 0x44:
						isMovingRight = true;
						break;
					case 0x57:
						//if(isGrounded)//��Ҫ��ײ��ص�������ʵ��
						isJumping = true;
						break;
					case 0x4D:
						//todo M
						break;
					case VK_SPACE: //�ո��
						run = true;
						break;
				}
				break;
			case WM_KEYUP:
				switch (msg.vkcode) {
					case 0x41:
						isMovingLeft = false;
						break;
					case 0x44:
						isMovingRight = false;
						break;
					case VK_SPACE:
						run = false;
						break;
				}
				break;
		}
	}

	PPlayer() :PEntity() {
		hb = PGetSingleton<CollisionManager>().createHitbox();
		hb->size = { 0.8f,1.5f };
		hb->position = { 5.f,0.f };
		hb->acceleration = { 0.f,9.8f };
		hb->addLayerDst(CollisionLayer::BlockLayer);
		hb->addLayerDst(CollisionLayer::EnemyLayer);
		hb->layerSrc = CollisionLayer::PlayerLayer;
	}

	void draw(const RenderInfo& renderInfo)override {
		setfillcolor(RGB(200, 0, 0));
		setlinecolor(LIGHTGRAY);
		setlinestyle(PS_SOLID, 3);
		float scale = renderInfo.scale;
		fillrectangle((int)(scale * hb->position.x),
					  (int)(scale * hb->position.y),
					  (int)(scale * (hb->position.x + hb->size.x)),
					  (int)(scale * (hb->position.y + hb->size.y)));
		beg.On_Draw();
		if(on_hand)
		on_hand->OnDraw();
	}
	Hitbox* get_hb()
	{
		return this->hb;
	}
	bool is_on_beg()
	{
		return beg.Is_Show();
	}
	void update(float deltatime) override {
		if (isJumping && isGrounded) {
			hb->velocity.y = -jumpForce; // ���ô�ֱ�ٶ�Ϊ��Ծ����
			isJumping = false;
		}

		// ����ˮƽ�ƶ�
		float speed = 0.f;
		if (isMovingLeft) speed -= 2.f;
		if (isMovingRight) speed += 2.f;
		if (run) speed *= runfast;
		hb->velocity.x = speed ;

	}
	bool isAlive() override
	{
		static const Vec2& pos = this->get_hb()->position;
		static const Vec2& size = this->get_hb()->size;
		return this->get_currentHealth().GetValue() > 0 && pos.y + size.y < 35.0f;
	}
	PlayerState get_player_state() { return state; }
	void set_player_state(PlayerState player_state) { state = player_state; }

protected:
	bool isMovingLeft = false;		//�Ƿ�������
	bool isMovingRight = false;		//�Ƿ�������

	bool isJumping = false;			// �Ƿ�������Ծ
	bool isGrounded = true;			// �Ƿ��ڵ����ϣ���Ҫ��ײ��ص�������ʵ��
	float jumpForce = 10.0f;		// ��Ծ����

	bool run = false;				// �Ƿ���
	float runfast = 2.5f;			// �����ٶ�

	std::unordered_map<PlayerAssets, PAssets*>head_assets;		//ͷͼ��
	std::unordered_map<PlayerAssets, PAssets*>body_assets;		//����ͼ��
	std::unordered_map<PlayerAssets, PAssets*>arm_assets;		//�첲ͼ��
	PAssets* sleep = nullptr;			//˯��ͼƬ
	PContent* on_hand= &Singleton<Hand>::instance();
	Beg beg;
	PlayerState state = PlayerState::Alive;
};

#endif // !_PLAYER_H_