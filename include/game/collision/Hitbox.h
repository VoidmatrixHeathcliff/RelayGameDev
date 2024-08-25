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
	Vec2 lastPosition;
	Vec2 position;
	Vec2 size;
	Vec2 velocity;
	Vec2 acceleration;

	bool enabled = true;
	std::function<void()> _onCollide;

	layer_t layerSrc = 0;
	layer_t layerDst = 0;

	HitboxType type = HitboxType::Dynamic;

	void addLayerDst(layer_t layer) {
		layerDst ^= layer;
	}

	void setOnCollide(const std::function<void()> _onCollide) {
		this->_onCollide = _onCollide;
	}
	void onCollide() const {
		if (_onCollide) {
			_onCollide();
		}
	}
};