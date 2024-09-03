#pragma once
#include "../../vec2/Vec2.h"
#include "CollisionLayer.h"
#include <functional>

class Hitbox {
private:
	friend class CollisionManager;
	Hitbox() = default;
	~Hitbox() = default;

public:
	Vec2 lastPosition;		//上一帧的位置
	Vec2 position;			//位置
	Vec2 size;				//碰撞箱子大小
	Vec2 velocity;			//速度
	Vec2 acceleration;		//加速度

	bool enabled = true;	//碰撞箱子目前是否有效
	std::function<void()> _onCollide;

	layer_t layerSrc = 0;
	layer_t layerDst = 0;

	HitboxType type = HitboxType::Dynamic;

	
	//设置碰撞层
	void addLayerDst(layer_t layer) {
		layerDst ^= layer;
	}

	//设置碰撞发生的回调函数
	void setOnCollide(const std::function<void()> _onCollide) {
		this->_onCollide = _onCollide;
	}
	
	//碰撞发生的回调函数
	void onCollide() const {
		if (_onCollide) {
			_onCollide();
		}
	}
};