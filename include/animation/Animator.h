//
//每个PEntity实例的动画管理器组件
//
#pragma once

#include <unordered_map>
#include <string>

#include "../../include/animation/Animation.h"
#include "../EasyXBase.h"
//？这个类存在的必要性：未知，若需要管理可以建立一个大型的管理类

/*
	Z: 统一管理动画类的大类，用于注册和注销PAnimation类。
	目前动画类如果要添加帧需要手动get后添加。
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
		创建并注册PAnimation类。
		@param sName 注册PAnimation类的名字。
		@param isLoop 该动画是否循环。默认为循环。
		@param fInterval 动画播放的帧间隔。默认为0.2s。
		@return PAnimation<PImage>* 新注册的动画类。如果已经注册过相同的名字则返回 nullptr。
	*/
	PAnimation<PImage>* createAnimation(std::string sName, bool isLoop = true, float fInterval = 0.2f) {
		if (mapAnimations.find(sName) == mapAnimations.end()) {		// 没有注册过
			PAnimation<PImage>* newAnimation = new PAnimation<PImage>(isLoop, fInterval, sName);
			mapAnimations.insert({ sName, newAnimation });
			return newAnimation;
		}
		return nullptr;												// 已经注册过了
	}

	/*
		获取PAnimation类。
		@param sName 注册PAnimation类的名字。
		@return PAnimation<PImageLabel>* 注册过的动画类。如果没有注册过则返回 nullptr。
	*/
	PAnimation<PImage>* getAnimation(std::string sName) {
		auto it = mapAnimations.find(sName);
		if (it == mapAnimations.end()) return nullptr;
		return it->second;
	}

	/* 注销Animation类 */
	void removeAnimation(std::string sName) {
		auto it = mapAnimations.find(sName);
		if (it == mapAnimations.end()) return;
		// delete(it->second);		// 因为是使用资源管理器来控制内存，所以不应该删除这个图片。
		it = mapAnimations.erase(it);
	}

	/* 注销全部的Animation类 */
	void clear() {
		mapAnimations.clear();
	}

public:
	std::unordered_map<std::string, PAnimation<PImage>* > mapAnimations;
};