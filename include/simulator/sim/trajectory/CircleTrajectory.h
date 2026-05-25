#pragma once
#include "ITrajectory.h"
#include <cmath>

class CircleTrajectory : public ITrajectory {
	float r;
public:
	CircleTrajectory(float radius) : r(radius) {};

	float phi(const Vec2& p) const override {
		return p.x * p.x + p.y * p.y - r * r;
	}

	Vec2 gradPhi(const Vec2& p) const override {
		return Vec2{ 2 * p.x, 2 * p.y };
	}

	bool hasParametric() const override { return true; }
	Vec2 f(float w)  const override { return { r * std::cos(w),  r * std::sin(w) }; }
	Vec2 df(float w) const override { return { -r * std::sin(w),  r * std::cos(w) }; }
};