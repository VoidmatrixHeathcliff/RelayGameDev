//
//Minecraft中的各种Buff的模板，比如燃烧、NightVision、Haste之类的
//
#pragma once

#define PENTITY_BASE_BUFF_DURATION 5.0 //基础的Buff持续时间

class PBuff
{
public:
	PBuff() = default;
	~PBuff() = default;

protected:
	float duration = PENTITY_BASE_BUFF_DURATION; //Buff的持续时长
};