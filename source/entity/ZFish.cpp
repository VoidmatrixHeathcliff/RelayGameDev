#include "../../include/entity/ZFish.h"
#include "../../include/game/collision/CollisionManager.h"
#include "../../include/game/PResourseManager.h"
#include "../../include/entity/ZHook.h"


/// <summary>
/// 生成一个🐟的操作
/// </summary>
ZFish::ZFish() :
	m_iWidth(getwidth() / 13.0f),
	m_iHeight(getwidth() / 13.0f)
{
	// 随机朝向
	if (rand() % 2) facingDir = 1;			// 右
	else facingDir = -1;					// 左

	// 碰撞箱
	hb = PGetSingleton<CollisionManager>().createHitbox();

	if (facingDir == -1) hb->position.x = (float)getwidth();
	else hb->position.x = -hb->size.x * 1.0f;

	hb->position.y = (float)((rand() % (getheight() / 5 * 4)) + getheight() / 5);
	hb->size = { m_iWidth * 1.0f, m_iHeight * 1.0f };

	//设置自己的所在的层，和要检查的碰撞层
	hb->layerSrc = CollisionLayer::EnemyLayer;
	hb->layerDst = CollisionLayer::PlayerLayer;

	//设置回调函数，改变🐟的状态
	hb->setOnCollide([&]() {
		if (eCurrentState == ZFishState::Idle) {
			setCurrentState(ZFishState::BeCaught);
			pZHook->setFishEscapeVelocity(escape_velocity);
		}
	});
	hb->acceleration = { 0.0f, 0.0f };
	hb->velocity = { (100 + rand() % 100) * facingDir * 1.0f, 0.0f };	//100~199

	// 动画机
	PResourseManager* manager = &PGetSingleton<PResourseManager>();
	PAnimation<PImage> animation = anim.createAnimation("skin");
	animation.addFrame(manager->findImage("flyingfish"));
	animation.addFrame(manager->findImage("fish_pufferfish_raw"));
	animation.addFrame(manager->findImage("fish_clownfish_raw"));
	animation.addFrame(manager->findImage("ish_salmon_raw"));
	animation.addFrame(manager->findImage("fish_cod_raw"));
	animation.addFrame(manager->findImage("bat_fish"));
	m_iFrameIndex = rand() % 6;		// 随机图片

	// 绘制imageLabel
	imageLabel = new PImageLabel(animation.getFrame(m_iFrameIndex));
	imageLabel->Resize(m_iWidth, m_iHeight);

	//设置不同🐟的挣扎强度
	switch (m_iFrameIndex)
	{
	case 0:
		escape_velocity = 8.5f;
		break;
	case 1:
		escape_velocity = 9.0f;
		break;
	case 2:
		escape_velocity = 9.5f;
		break;
	case 3:
		escape_velocity = 10.0f;
		break;
	case 4:
		escape_velocity = 10.5f;
		break;
	case 5:
		escape_velocity = 11.0f;
		break;

	}
	
}

//删除对应的碰撞盒，删除图片资源
ZFish::~ZFish() {
	if (hb != nullptr) PGetSingleton<CollisionManager>().destroyHitbox(hb);
	delete imageLabel;
}


void ZFish::draw(const RenderInfo& renderInfo) {
	imageLabel->Move((int)hb->position.x, (int)hb->position.y);
	imageLabel->OnDraw();
	
	// 绘制碰撞箱
	// rectangle(hb->position.x, hb->position.y, hb->position.x + hb->size.x, hb->position.y + hb->size.y);
}


/// <summary>
/// 正常的刷新和被抓的更新逻辑
/// </summary>
/// <param name="deltaTime"></param>
void ZFish::update(float deltaTime) {
	if (eCurrentState == ZFishState::Idle) {
		if (facingDir == 1) {	// 向右移动到终点
			if (hb->position.x >= getwidth()) eCurrentState = ZFishState::Disappear;
		} 
		else {
			if (hb->position.x < -hb->size.x) eCurrentState = ZFishState::Disappear;
		}
	}
	else if (eCurrentState == ZFishState::BeCaught) {
		if (pZHook != nullptr) {
			// 判断是否超过边界,超过就解锁钩子和🐟的关系
			if (hb->position.x < 0 || hb->position.x >= getwidth() || hb->position.y < 0 || hb->position.y >= getheight()) {
				pZHook->setCurrentState(ZHook::ZHookState::Retract_empty);
				eCurrentState = ZFishState::Disappear;

			}




			if (pZHook->getCurrentState() == ZHook::ZHookState::Idle) {
				eCurrentState = ZFishState::Death;
			}
			else {
				pZHook->setFishEscapeVelocity(escape_velocity);
				double hookVelocity = pZHook->getRetractLengthVelocity() / deltaTime;
				double hookAngle = pZHook->getAngle();
				hb->velocity = { -(float)(hookVelocity * cos(hookAngle)), -(float)(hookVelocity * sin(hookAngle)) };
			}
		}
	}
}