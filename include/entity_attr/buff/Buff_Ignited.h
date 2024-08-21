//
//燃烧Buff
//
#pragma once

#include "../../entity_attr/buff/BuffManager.h"
#include "../../../include/entity_attr/buff/Buff.h"

class PBuff_Ignited :PBuff
{
	friend class PBuffManger; //让管理器得以调用此处成员
protected:
	float burningFrequency = 1.0f; //在Buff持续时间内每隔多长时间造成一次燃烧伤害
	int burningDamage = 2; //每次燃烧扣掉的伤害
};