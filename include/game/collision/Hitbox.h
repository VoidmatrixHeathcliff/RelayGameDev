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
	Vec2 lastPosition;		//��һ֡��λ��
	Vec2 position;			//λ��
	Vec2 size;				//��ײ���Ӵ�С
	Vec2 velocity;			//�ٶ�
	Vec2 acceleration;		//���ٶ�

	bool enabled = true;	//��ײ����Ŀǰ�Ƿ���Ч
	std::function<void()> _onCollide;

	layer_t layerSrc = 0;
	layer_t layerDst = 0;

	HitboxType type = HitboxType::Dynamic;

	
	//������ײ��
	void addLayerDst(layer_t layer) {
		layerDst ^= layer;
	}

	//������ײ�����Ļص�����
	void setOnCollide(const std::function<void()> _onCollide) {
		this->_onCollide = _onCollide;
	}
	
	//��ײ�����Ļص�����
	void onCollide() const {
		if (_onCollide) {
			_onCollide();
		}
	}
};