//
//Minecraft�еĸ���Buff��ģ�壬����ȼ�ա�NightVision��Haste֮���
//
#pragma once

#define PENTITY_BASE_BUFF_DURATION 5.0 //������Buff����ʱ��

class PBuff
{
public:
	PBuff() = default;
	~PBuff() = default;

protected:
	float duration = PENTITY_BASE_BUFF_DURATION; //Buff�ĳ���ʱ��
};