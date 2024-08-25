//
//每个PEntity实例的动画管理器组件
//
#pragma once

#include "../../include/animation/Animation.h"
//？这个类存在的必要性：未知，若需要管理可以建立一个大型的管理类
class PAnimator
{
public:
	PAnimator() = default;
	~PAnimator() = default;

public:
	PAnimationList list; //存储所有动画
};