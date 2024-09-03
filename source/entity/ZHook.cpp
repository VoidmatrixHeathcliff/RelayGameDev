#include "../../include/entity/ZHook.h"
#include "../../include/game/collision/CollisionManager.h"

ZHook::ZHook() :
	DEFAULT_LENGTH(getheight() / 5.0),
	ARROW_SIZE(DEFAULT_LENGTH / 8.0),
	dLength(DEFAULT_LENGTH)
{
	hb = PGetSingleton<CollisionManager>().createHitbox();
	posCenter = { getwidth() / 2.0f, getheight() / 20.0f * 3.0f };
	// 获取钩子尾部坐标
	Vec2 posEnd = { (float)(posCenter.x + dLength * cos(angle)), (float)(posCenter.y + dLength * sin(angle)) };
	hb->position = { posEnd.x - 2.0f, posEnd.y - 2.0f };
	hb->size = { 4.0f, 4.0f };
	hb->acceleration = { 0.0f, 0.0f };
	hb->velocity = { 0.0f, 0.0f };
	hb->layerSrc = CollisionLayer::PlayerLayer;
	hb->layerDst = CollisionLayer::EnemyLayer;
	hb->setOnCollide([&]() {
		// 与鱼碰撞
		if (eCurrentState == ZHookState::Chase) eCurrentState = ZHookState::Retract;
	});
}

ZHook::~ZHook() 
{
	if (hb != nullptr) PGetSingleton<CollisionManager>().destroyHitbox(hb);
}

void ZHook::update(float deltaTime) {
	// 伪自动机 而是if else嵌套
	// 获取钩子尾部坐标
	Vec2 posEnd = { (float)(posCenter.x + dLength * cos(angle)), (float)(posCenter.y + dLength * sin(angle)) };

	// 闲置状态：钩子摇摆
	if (eCurrentState == ZHookState::Idle) {
		hb->enabled = false;
		angle += dAngularVelocity;
		if (angle <= MIN_ANGLE) {
			angle = MIN_ANGLE;
			dAngularVelocity = -dAngularVelocity;
		}
		else if (angle >= MAX_ANGLE) {
			angle = MAX_ANGLE;
			dAngularVelocity = -dAngularVelocity;
		}
	}
	// 抓鱼状态：钩子向前伸直
	else if (eCurrentState == ZHookState::Chase) {
		hb->enabled = true;
		// 伸长
		dLength += dLengthVelocity;
		// 判断是否超过边界
		if (posEnd.x < 0 || posEnd.x >= getwidth() || posEnd.y < 0 || posEnd.y >= getheight()) {
			eCurrentState = ZHookState::Retract;
		}
	}
	// 缩回状态：钩子往回缩
	else if (eCurrentState == ZHookState::Retract) {
		hb->enabled = false;
		dLength -= dLengthVelocity;
		if (dLength <= DEFAULT_LENGTH) {
			dLength = DEFAULT_LENGTH;
			eCurrentState = ZHookState::Idle;
		}
	}
	// 更新钩子碰撞箱
	hb->position = { posEnd.x - 2.0f, posEnd.y - 2.0f };
}

void ZHook::draw(const RenderInfo& renderInfo) {
	//获取钩子尾部坐标
	Vec2 posEnd = { (float)(posCenter.x + dLength * cos(angle)), (float)(posCenter.y + dLength * sin(angle)) };

	// 绘制主线
	setlinecolor(BLACK);
	setlinestyle(PS_SOLID, 2);
	line(posCenter.x, posCenter.y, posEnd.x, posEnd.y);

	// 绘制钩子头部
	double angle1 = angle + acos(-1.0) / 6.0;
	double angle2 = angle - acos(-1.0) / 6.0;
	int arrowX1 = posEnd.x - static_cast<int>(ARROW_SIZE * cos(angle1));
	int arrowY1 = posEnd.y - static_cast<int>(ARROW_SIZE * sin(angle1));

	int arrowX2 = posEnd.x - static_cast<int>(ARROW_SIZE * cos(angle2));
	int arrowY2 = posEnd.y - static_cast<int>(ARROW_SIZE * sin(angle2));

	line(arrowX1, arrowY1, posEnd.x, posEnd.y);
	line(arrowX2, arrowY2, posEnd.x, posEnd.y);

	// 绘制碰撞箱
// #define _HOOK_HITBOX_DEBUG_
#ifdef _HOOK_HITBOX_DEBUG_
	rectangle(hb->position.x, hb->position.y, hb->position.x + hb->size.x, hb->position.y + hb->size.y);


#endif // _HOOK_HITBOX_DEBUG_

}