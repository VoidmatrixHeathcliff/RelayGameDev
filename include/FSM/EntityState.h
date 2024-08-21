//
//PEntity类的状态基类，用于重写各种状态
//
#pragma once

#include "../../include/animation/Animation.h"

class PEntityState
{
public:
	PEntityState(PAnimation<> _animation) : animation(_animation) {}
	~PEntityState() = default;

public:
	PAnimation<> animation; //每个状态对应的动画
};