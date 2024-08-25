//
//Minecraft中的各种Buff的模板，比如燃烧、NightVision、Haste之类的
//
#pragma once

class PBuff
{
public:
	PBuff() = default;
	~PBuff() = default;

protected:
	static constexpr float PENTITY_BASE_BUFF_DURATION = 5.0;

	float duration = PENTITY_BASE_BUFF_DURATION; //Buff的持续时长
};