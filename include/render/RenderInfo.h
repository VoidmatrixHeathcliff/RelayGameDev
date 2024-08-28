#pragma once

#include"../vec2/Vec2.h"
#include"../EasyXBase.h"

struct RenderInfo {
	Vec2 windowSize;
	Vec2 cameraPosition;
	PDevice* device;
	float scale;		//temporary£¨ÔÝÊ±µÄ£©
};