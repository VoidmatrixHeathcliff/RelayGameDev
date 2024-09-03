#pragma once

#include"../../singleton/singleton.h"
#include"Hitbox.h"
#include<unordered_set>

#pragma push_macro("min")
#undef min


//目前仅支持矩形碰撞箱
class CollisionManager :public Singleton<CollisionManager> {
private:
	friend class Singleton<CollisionManager>;

	std::unordered_set<Hitbox*> hitboxList;

	bool isColliding(const Hitbox* a, const Hitbox* b) const {
		// Z：解决上下抽搐！
		return (a->position.x <= (b->position.x + b->size.x)) &&
			((a->position.x + a->size.x) >= b->position.x) &&
			(a->position.y <= (b->position.y + b->size.y)) &&
			((a->position.y + a->size.y) >= b->position.y);
	}

	void separate(Hitbox* dynamicHitbox, const Hitbox* staticHitbox) {
		// 计算碰撞的重叠量
		float overlapX1 = (dynamicHitbox->position.x + dynamicHitbox->size.x) - staticHitbox->position.x;
		float overlapX2 = (staticHitbox->position.x + staticHitbox->size.x) - dynamicHitbox->position.x;
		float overlapY1 = (dynamicHitbox->position.y + dynamicHitbox->size.y) - staticHitbox->position.y;
		float overlapY2 = (staticHitbox->position.y + staticHitbox->size.y) - dynamicHitbox->position.y;

		// 取最小的重叠量用于分离
		float overlapX = std::min(overlapX1, overlapX2);
		float overlapY = std::min(overlapY1, overlapY2);

		// 判断在X方向还是Y方向上分离
		if (overlapX < overlapY) {
			// 分离在X方向
			if (overlapX1 < overlapX2) {
				dynamicHitbox->position.x -= overlapX;
			}
			else {
				dynamicHitbox->position.x += overlapX;
			}
			// 停止在X方向上的速度
			dynamicHitbox->velocity.x = 0;
		}
		else {
			// 分离在Y方向
			if (overlapY1 < overlapY2) {
				dynamicHitbox->position.y -= overlapY;
			}
			else {
				dynamicHitbox->position.y += overlapY;
			}
		}
		// 停止动态实体在该方向上的速度
		if (overlapX < overlapY) {
			dynamicHitbox->velocity.x = 0;
		}
		else {
			dynamicHitbox->velocity.y = 0;
		}
	}

	/// <summary>
	/// 遍历处理相同碰撞层的碰撞
	/// </summary>
	void handleCollision() {
		//主要是蝙蝠的我想要🐟的碰撞的回调先触发，先把逃跑速度传给鱼钩
		
		for (Hitbox* src : hitboxList) {
			if (!src->enabled || src->layerDst == CollisionLayer::NoneLayer) {
				continue;
			}

			for (Hitbox* dst : hitboxList) {
				if (!dst->enabled || src == dst || !hasLayer(dst->layerSrc, src->layerDst)) {
					continue;
				}
				if (isColliding(src, dst)) {

					//当动态碰撞箱子遇到了静态碰撞箱子就需要分离
					if (src->type == HitboxType::Dynamic && dst->type == HitboxType::Static) {
						separate(src, dst);
						//printf("found collision\n");
					}

					
					if(dst->layerSrc==CollisionLayer::EnemyLayer)
					{
						dst->onCollide();
					}

					src->onCollide();

				}
				//printf("found collision\n");
			}
		}


	}

	void move(float deltaTime) {
		for (Hitbox* hb : hitboxList) {
			if (hb->type == HitboxType::Dynamic) {
				hb->lastPosition = hb->position;
				hb->position += hb->velocity * deltaTime;
				hb->velocity += hb->acceleration * deltaTime;
			}
		}
	}

	bool hasLayer(layer_t src, layer_t dst) {
		return (dst & src) != 0;
	}

	~CollisionManager() {
		for (Hitbox* hb : hitboxList) {
			delete hb; // 释放内存  
		}
		hitboxList.clear();
		//TODO
	}

public:

	Hitbox* createHitbox() {
		Hitbox* ret = new Hitbox();
		hitboxList.insert(ret);
		return ret;
	}


	void destroyHitbox(Hitbox* hb) {
		hitboxList.erase(hb);
		delete hb;
	}

	void step(float deltaTime) {
		if (hitboxList.empty() || deltaTime <= 0) { return; }
		move(deltaTime);
		handleCollision();
	}

};

#pragma pop_macro("min")