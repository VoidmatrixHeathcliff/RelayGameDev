//
//受PAnimtor管理的各动画
//
#pragma once
//？这个动画类提供的模板只在状态机里会调用
#include <string>
#include <vector>

template<typename T = int>
class PAnimation
{
public:
	PAnimation(std::string _animName, T _animParm) : animName(_animName), animParm(_animParm) {}
	~PAnimation() = default;

private:
	std::string animName = ""; //动画的名字
	bool isPlaying = false; //决定动画是否在播放

	T animParm; //动画的参数，可以是bool、int、float等
};

//封装一个存储动画的数据类型
class PAnimationList
{
public:
	PAnimationList() = default;
	~PAnimationList() = default;

public:
	std::vector<PAnimation<int>> intParmList; //存储参数为整型的动画
	std::vector<PAnimation<bool>> boolParmList; //存储参数为布尔的动画
	std::vector<PAnimation<float>> floatParmList; //存储参数为浮点的动画
};