//
//ȼ��Buff
//
#pragma once

#include "../../entity_attr/buff/BuffManager.h"
#include "../../../include/entity_attr/buff/Buff.h"

class PBuff_Ignited :PBuff
{
	friend class PBuffManger; //�ù��������Ե��ô˴���Ա
protected:
	float burningFrequency = 1.0f; //��Buff����ʱ����ÿ���೤ʱ�����һ��ȼ���˺�
	int burningDamage = 2; //ÿ��ȼ�տ۵����˺�
};