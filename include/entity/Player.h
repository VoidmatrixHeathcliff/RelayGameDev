#ifndef _PLAYER_H_
#define _PLAYER_H_

//
//玩家类
//

//？我只进行了图片的加载

#include"../beg/Beg.h"
#include "../../include/entity/Entity.h"
#include"../../new_animation.h"
#include"../game/collision/CollisionManager.h"
#include <unordered_map>

enum class PlayerAssets {
	HEAD_0 = 0,//无佩戴盔甲的头
	HEAD_1,//1r的头
	HEAD_2,//铁头
	HEAD_3,//金头
	HEAD_4,//钻石头
	HEAD_PL,//南瓜头

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

enum class PlayerState
{
	Alive = 0,	// 活着
	Dying,		// 濒死
	Dead		// 死透了
};

class PPlayer :public PEntity {
public:
	//该函数建议放在构造函数中，但因层层封装无法调用该类的构造函数
	//所以我将该函数的方法设为公开
	//（这部分建议提取出来，放在单例类实现）
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
		if (bag.Can_Add() == false)
			return false;
		bag.Add(thing);
		return true;
	}
	void onMessage(const ExMessage& msg) {
			bag.On_Message(msg);
			on_hand = bag.Get_On_Hand();
		//todo
		switch (msg.message) {
			case WM_KEYDOWN:
				switch (msg.vkcode) {
					case VK_LBUTTON:
						//todo	鼠标左键
						break;
					case VK_RBUTTON:
						//todo  鼠标右键
						break;
					case 0x41:
						isMovingLeft = true;
						break;
					case 0x44:
						isMovingRight = true;
						break;
					case 0x57:
						//滑不稽：按下W跳跃时，地面和跳跃的状态应该互斥，为了避免以后可能出现的奇怪BUG，我将下面if判断条件修改
						//（滑不稽）修改前：
						/*if (isGrounded)*/
						//（滑不稽）修改后：
						if (isGrounded && !isJumping)
						{
							isJumping = true;
							isGrounded = false;
						}
						break;
					case 0x4D:
						//todo M
						break;
					case VK_SPACE: //空格键
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

	PPlayer() :PEntity()
	{
		hb = PGetSingleton<CollisionManager>().createHitbox();
		hb->size = { 0.8f,1.5f };
		hb->position = { 5.f,0.f };
		hb->acceleration = { 0.f,9.8f };
		hb->addLayerDst(CollisionLayer::BlockLayer);
		hb->addLayerDst(CollisionLayer::EnemyLayer);
		hb->layerSrc = CollisionLayer::PlayerLayer;

		//妥协用的地面检测
		before_position_y = hb->position.y;
		//hb->setOnCollide([&]() { isGrounded = true; });
	}

	~PPlayer() {
		PGetSingleton<CollisionManager>().destroyHitbox(hb);
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
		bag.On_Draw();
		if(on_hand)
		on_hand->OnDraw();
	}
	Hitbox* get_hb()
	{
		return this->hb;
	}
	bool is_on_beg()
	{
		return bag.Is_Show();
	}
	void update(float deltatime) override {

		if (hb->position.y >= 35) {
			hb->position = { 5.f,0.f };
		}

		//妥协用的地面检测
		//滑不稽：将判断条件修改，恢复地面检测，防止左脚踩右脚上天（暂时没看懂妥协用的地面检测是什么意思）
		//（滑不稽）修改前：取消地面检测，左脚踩右脚上天
		/*
		if (hb->position.y != before_position_y)
		{
			isGrounded = true;
		}*/
		//（滑不稽）修改后：恢复地面检查，防止左脚踩右脚上天以及二连跳
		if (hb->position.y == before_position_y && !isJumping)
		{
			isGrounded = true;
		}

		before_position_y = hb->position.y;
		if (isJumping) {
			hb->velocity.y = -jumpForce; // 设置垂直速度为跳跃力量
			isJumping = false;
		}

		// 处理水平移动
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
	bool isMovingLeft = false;		//是否向左走
	bool isMovingRight = false;		//是否向右走

	///////////////////////////////////////////////////// 
	/// 妥协用的检测是否在地面上的参数，如果有更好的可以优化掉
	//先前的位置y，用于判断是否在地面上，如果两次更新y轴位置不变，则认为在
	//地面上(实际上，如果是在跳跃的最高点，也可能出现多次y轴位置不变的情况)
	float before_position_y;	
	///////////////////////////////////////////////////// 

	bool isJumping = false;			// 是否正在跳跃
	bool isGrounded = true;			// 是否在地面上，需要碰撞层回调检测才能实现
	float jumpForce = 8.0f;		// 跳跃力量

	bool run = false;				// 是否奔跑
	float runfast = 2.5f;			// 奔跑速度

	std::unordered_map<PlayerAssets, PAssets*>head_assets;		//头图集
	std::unordered_map<PlayerAssets, PAssets*>body_assets;		//身体图集
	std::unordered_map<PlayerAssets, PAssets*>arm_assets;		//胳膊图集
	PAssets* sleep = nullptr;			//睡觉图片
	PContent* on_hand= &Singleton<Hand>::instance();
	Bag bag;
	PlayerState state = PlayerState::Alive;
};


#endif // !_PLAYER_H_