//
//受PAnimtor管理的各动画
//
#pragma once
//？这个动画类提供的模板只在状态机里会调用
#include <string>
#include <vector>

#include "../time/Timer.h"

/*
	Z：重构大部分动画类。
*/
template<typename T = int>
class PAnimation
{
public:
	PAnimation(bool isLoopFlag = true, float fInterval = 0.2f, std::string name = "") :
		bIsLoop(isLoopFlag),
		animName(name),
		oTimer()
	{
		oTimer.set(fInterval, [&]() {
			switchToNext();
		});
		oTimer.start();
	}
	~PAnimation() = default;
	
public:
	/*
		添加动画帧。
	*/
	void addFrame(T* oFrame) { vecFrameList.push_back(oFrame); }

	/*
		删除动画帧。
	*/
	void removeFrame(int iIndex) {
		if (iIndex >= vecFrameList.size() || iIndex < 0) return;
		vecFrameList.erase(vecFrameList.begin() + iIndex);
	}

	/*
		切换到下一个动画帧。
	*/
	void switchToNext() {
		int iSize = (int)vecFrameList.size();
		iFrameIndex++;
		// 非循环动画
		if (iFrameIndex >= iSize && !bIsLoop) {
			iFrameIndex = 0;
			oTimer.pause();
			if (fCallback) fCallback();
			return;
		}
		iFrameIndex %= iSize;
	}

	/*
		更新动画。
	*/
	void onUpdate(float deltaTime) {
		oTimer.update(deltaTime);
	}
	
	/*
		因为没有修改前人的模板类，干脆直接返回当前索引指向的指针。
		或者写一个 Renderable 的抽象接口，然后让模板改为 Renderable 接口。
	*/
	T* getCurrentFrame() const {
		int iSize = (int)vecFrameList.size();
		if (iFrameIndex < 0 || iFrameIndex >= iSize) return nullptr;
		return vecFrameList[iFrameIndex];
	}

	/*
		根据index获取动画帧。
		可用于随机获取图片。
	*/
	T* getFrame(int _iIndex) const {
		int iSize = (int)vecFrameList.size();
		if (_iIndex < 0 || _iIndex >= iSize) return nullptr;
		return vecFrameList[_iIndex];
	}


public:
	/*
		是否循环播放。
	*/
	bool isLoop() const { return bIsLoop; }

	/*
		更改是否循环播放。
	*/
	void setLoop(bool flag) { bIsLoop = flag; }

	/*
		设置回调函数。
	*/
	void setCallback(std::function<void()> fCallback) {
		this->fCallback = fCallback;
	}

	/*
		设置更新间隔。
	*/
	void setInterval(float fInterval) { 
		oTimer.set(fInterval);
	}


private:
	std::string animName;				// 动画的名字
	bool bIsLoop;						// 是否循环播放动画
	std::function<void()> fCallback;	// 动画结束回调函数

	int iFrameIndex = 0;				// 动画帧索引
	std::vector<T*> vecFrameList;		// 动画帧列表
	Timer oTimer;						// 动画更新计时器
};