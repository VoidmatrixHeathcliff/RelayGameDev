//
//ÿ��PEntityʵ���ô��������������ܵ��ĵ�Buff
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
	bool isIgnited = false; //��ȼ��Buff�ļ�¼
	bool isPoison = false;  //���ж�Buff�ļ�¼
	bool isWither = false;	//�Ե���Buff�ļ�¼
	//bool isXXX

	int Poison_level = 1;	//�ж�Buff�ĵȼ���Ĭ��Ϊ1��
	int Wither_level = 1;	//����Buff�ĵȼ���Ĭ��Ϊ1��
	//int Xxx_level

public:

	//������ѭ��������ʵʱ����ʵ���Buff
	void CheckBuffs(PEntity* e) {}

	//����CheckBuffs�ڣ�ͨ��ĳЩ���ݷ�����ʵ�ʼ�Ⲣ����ʵ�����Buff
	void ApplyBuffs(PEntity* e) {} 
};