//
//ÿ��PEntityʵ���ô��������������ܵ��ĵ�Buff
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
	bool isIgnited = false; //��ȼ��Buff�ļ�¼
	//bool isXXX

public:
	void CheckBuffs(); //������ѭ��������ʵʱ����ʵ���Buff
	void ApplyBuffs(); //����CheckBuffs�ڣ�ͨ��ĳЩ���ݷ�����ʵ�ʼ�Ⲣ����ʵ�����Buff
};