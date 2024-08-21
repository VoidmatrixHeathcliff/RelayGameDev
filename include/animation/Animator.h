//
//每个PEntity实例的动画管理器组件
//
#pragma once

#include "../../include/animation/Animation.h"

class PAnimator
{
public:
	PAnimator() = default;
	~PAnimator() = default;

public:
	PAnimationList list; //存储所有动画
};