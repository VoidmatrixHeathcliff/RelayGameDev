//
//每个PEntity实例用此类来管理自身受到的的Buff
//
#pragma once

#include "../../../include/entity_attr/buff/Buff.h"
//#include "../../../include/entity_attr/buff/Buff_Ignited.h"
#include "../../../include/time/Timer.h"
class PEntity;

class PBuffManager
{
public:
	PBuffManager() = default;
	~PBuffManager() = default;

protected:
	bool isIgnited = false; //对燃烧Buff的记录
	bool isPoison = false;  //对中毒Buff的记录
	bool isWither = false;	//对凋零Buff的记录
	//bool isXXX

	int Poison_level = 1;	//中毒Buff的等级（默认为1）
	int Wither_level = 1;	//凋零Buff的等级（默认为1）
	//int Xxx_level

public:

	//放入主循环，用于实时更新实体的Buff
	void CheckBuffs(PEntity* e) {}

	//放入CheckBuffs内，通过某些数据分析，实际检测并赋予实体各种Buff
	void ApplyBuffs(PEntity* e) {} 
};