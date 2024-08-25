//
//���ڹ���ʹ洢��PEntityʵ���ĸ���ͳ�����ݣ��������ֻ�������ֵ���繥���˺����ƶ��ٶȵ�
//������ҡ��ж�����ȵ�PEntity����������Ҫ������ĳ�Ա������ֵ�������ѡ��Ϊ���¿�һ���̳��ڴ�PEntityStatsManager�������
//
#pragma once

#include "../../entity_attr/buff/BuffManager.h"

//��װһ���������ͣ���������չ����ϲ���Ļ�ɾ��Ҳ���ԣ��Ǿͼǵð�Stat������int����size_t��
class Stat {
public:
	Stat(int val) { value = val; }
	~Stat() = default;
	Stat& operator=(const Stat& stat) = default;
private:
	int value = 0;
public:
	int GetValue() { return value; }
	void SetValue(int val) { this->value = val; }
	void IncreaseValueBy(int val) { this->value += val; }
};



inline constexpr int PENTITY_BASE_HEALTH = 20;//����������ֵ
inline constexpr int PENTITY_BASE_MOVE_SPEED = 10;//�������ƶ��ٶȣ���û�ж����������д����ϵͳ��ͬѧ���޸�ֵ��
inline constexpr int PENTITY_BASE_JUMP_FORCE = 10;//��������Ծ����
inline constexpr float PENTITY_GRAVITY = 9.8f; //�������ٶȣ�����д����ϵͳ���Ÿ��������ȣ���


class PEntityStatsManager {
public:
	PEntityStatsManager() = default;
	~PEntityStatsManager() = default;

public:
	Stat maxHealth = Stat(PENTITY_BASE_HEALTH); //ʵ���ʼ���Ѫ��
	Stat currentHealth = maxHealth; //ʵ�嵱ǰѪ��

	Stat moveSpeed = Stat(PENTITY_BASE_MOVE_SPEED); //ʵ��ĳ�ʼ�ƶ��ٶ�
	Stat jumpForce = Stat(PENTITY_BASE_JUMP_FORCE); //ʵ��ĳ�ʼ��Ծ����
	//Stat miningSpeed = Stat(0); //�ھ��ٶ�

	Stat attackDamage = Stat(0); //ʵ��Ĺ�������0��ʾ�޹�������Ĭ��Ϊ��
	//Stat armor = Stat(0); //ʵ��ķ�����������Ͳ������ô���ˣ�����Ҫ�Լ����ϼ���

public:
	//�������ĳʵ��������BuffЧ�����Ǿ���Ҫͨ��ĳ�ַ�ʽ���õ����������ڱ������ߵ��˺�ֵ
	//int GetFinalAttackDamage()
	//	return attackDamage.GetValue() + strength * dmgPerStrength;
};