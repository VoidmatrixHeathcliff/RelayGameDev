#pragma once
#ifndef _VEC2_H
#define _VEC2_H
#include<cmath>
#include"../common/common.h"


struct Vec2 {
	float x, y;

	Vec2() :x(0.f), y(0.f) {}
	Vec2(float x, float y) :x(x), y(y) {}
	Vec2(const Vec2& other) = default;

	Vec2& operator=(const Vec2& right) = default;
	bool operator==(const Vec2& right)const = default;
	bool operator!=(const Vec2& right)const = default;

	Vec2 operator+(const Vec2& right)const {
		return { x + right.x,y + right.y };
	}
	Vec2 operator-(const Vec2& right)const {
		return { x - right.x,y - right.y };
	}
	Vec2 operator-()const {
		return { -x,-y };
	}
	Vec2 operator*(float right)const {
		return { x * right,y * right };
	}
	Vec2 operator/(float right)const {
		return { x / right,y / right };
	}
	Vec2& operator+=(const Vec2& right) {
		x += right.x;
		y += right.y;
		return *this;
	}
	Vec2& operator-=(const Vec2& right) {
		x -= right.x;
		y -= right.y;
		return *this;
	}
	Vec2& operator*=(float right) {
		x *= right;
		y *= right;
		return *this;
	}
	Vec2& operator/=(float right) {
		x /= right;
		y /= right;
		return *this;
	}

	float length()const{
		return sqrtf(x * x + y * y);
	}
	float lengthSquared()const {
		return x * x + y * y;
	}
	float normalize() {
		float length = sqrtf(x * x + y * y);
		if (length < PEpsilon) {
			return 0.f;
		}
		float invLength = 1.f / length;
		x *= invLength;
		y *= invLength;
		return length;
	}

	float dot(const Vec2& other) const {
		return x * other.x + y * other.y;
	}
};

//Vec2 operator*(float left, const Vec2& right) {
//	return { left * right.x,left * right.y };
//}
//Vec2 operator/(float left, const Vec2& right) {
//	return { left / right.x,left / right.y };
//}

#endif