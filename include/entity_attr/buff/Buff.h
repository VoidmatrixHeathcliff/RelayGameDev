//
//Minecraft�еĸ���Buff��ģ�壬����ȼ�ա�NightVision��Haste֮���
//
#pragma once

class PBuff
{
public:
	PBuff() = default;
	~PBuff() = default;

protected:
	static constexpr float PENTITY_BASE_BUFF_DURATION = 5.0;

	float duration = PENTITY_BASE_BUFF_DURATION; //Buff�ĳ���ʱ��
};