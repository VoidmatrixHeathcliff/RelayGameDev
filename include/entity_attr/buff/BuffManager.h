//
//每个PEntity实例用此类来管理自身受到的的Buff
//
#pragma once

#include "../../../include/entity_attr/buff/Buff.h"
#include "../../../include/entity_attr/buff/Buff_Ignited.h"

class PBuffManager
{
public:
	PBuffManager() = default;
	~PBuffManager() = default;

protected:
	bool isIgnited = false; //对燃烧Buff的记录
	//bool isXXX

public:
	void CheckBuffs(); //放入主循环，用于实时更新实体的Buff
	void ApplyBuffs(); //放入CheckBuffs内，通过某些数据分析，实际检测并赋予实体各种Buff
};