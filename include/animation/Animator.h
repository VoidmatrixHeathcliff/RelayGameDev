//
//ÿ��PEntityʵ���Ķ������������
//
#pragma once

#include <unordered_map>
#include <string>

#include "../../include/animation/Animation.h"
#include "../EasyXBase.h"
//���������ڵı�Ҫ�ԣ�δ֪������Ҫ������Խ���һ�����͵Ĺ�����

/*
	Z: ͳһ��������Ĵ��࣬����ע���ע��PAnimation�ࡣ
	Ŀǰ���������Ҫ���֡��Ҫ�ֶ�get����ӡ�
*/
class PAnimator
{
public:
	PAnimator() = default;

	~PAnimator() {
		for (auto it = mapAnimations.begin(); it != mapAnimations.end(); it++) {
			delete it->second;
		}
	}

public:
	/* 
		������ע��PAnimation�ࡣ
		@param sName ע��PAnimation������֡�
		@param isLoop �ö����Ƿ�ѭ����Ĭ��Ϊѭ����
		@param fInterval �������ŵ�֡�����Ĭ��Ϊ0.2s��
		@return PAnimation<PImage>* ��ע��Ķ����ࡣ����Ѿ�ע�����ͬ�������򷵻� nullptr��
	*/
	PAnimation<PImage>* createAnimation(std::string sName, bool isLoop = true, float fInterval = 0.2f) {
		if (mapAnimations.find(sName) == mapAnimations.end()) {		// û��ע���
			PAnimation<PImage>* newAnimation = new PAnimation<PImage>(isLoop, fInterval, sName);
			mapAnimations.insert({ sName, newAnimation });
			return newAnimation;
		}
		return nullptr;												// �Ѿ�ע�����
	}

	/*
		��ȡPAnimation�ࡣ
		@param sName ע��PAnimation������֡�
		@return PAnimation<PImageLabel>* ע����Ķ����ࡣ���û��ע����򷵻� nullptr��
	*/
	PAnimation<PImage>* getAnimation(std::string sName) {
		auto it = mapAnimations.find(sName);
		if (it == mapAnimations.end()) return nullptr;
		return it->second;
	}

	/* ע��Animation�� */
	void removeAnimation(std::string sName) {
		auto it = mapAnimations.find(sName);
		if (it == mapAnimations.end()) return;
		// delete(it->second);		// ��Ϊ��ʹ����Դ�������������ڴ棬���Բ�Ӧ��ɾ�����ͼƬ��
		it = mapAnimations.erase(it);
	}

	/* ע��ȫ����Animation�� */
	void clear() {
		mapAnimations.clear();
	}

public:
	std::unordered_map<std::string, PAnimation<PImage>* > mapAnimations;
};