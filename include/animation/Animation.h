//
//��PAnimtor����ĸ�����
//
#pragma once
//������������ṩ��ģ��ֻ��״̬��������
#include <string>
#include <vector>

template<typename T = int>
class PAnimation
{
public:
	PAnimation(std::string _animName, T _animParm) : animName(_animName), animParm(_animParm) {}
	~PAnimation() = default;

private:
	std::string animName = ""; //����������
	bool isPlaying = false; //���������Ƿ��ڲ���

	T animParm; //�����Ĳ�����������bool��int��float��
};

//��װһ���洢��������������
class PAnimationList
{
public:
	PAnimationList() = default;
	~PAnimationList() = default;

public:
	std::vector<PAnimation<int>> intParmList; //�洢����Ϊ���͵Ķ���
	std::vector<PAnimation<bool>> boolParmList; //�洢����Ϊ�����Ķ���
	std::vector<PAnimation<float>> floatParmList; //�洢����Ϊ����Ķ���
};