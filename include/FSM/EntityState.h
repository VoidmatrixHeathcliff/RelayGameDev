//
//PEntity���״̬���࣬������д����״̬
//
#pragma once

#include "../../include/animation/Animation.h"

class PEntityState
{
public:
	PEntityState(PAnimation<> _animation) : animation(_animation) {}
	~PEntityState() = default;

public:
	PAnimation<> animation; //ÿ��״̬��Ӧ�Ķ���
};