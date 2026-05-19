// LemniscateTrajectory.h
#pragma once
#include "ITrajectory.h"
#include <cmath>

class LemniscateTrajectory : public ITrajectory {
    float a; // scale
public:
    LemniscateTrajectory(float scale) : a(scale) {}

    // phi = (x^2 + y^2)^2 - a^2*(x^2 - y^2)
    float phi(const Vec2& p) const override {
        float r2 = p.x * p.x + p.y * p.y;
        return r2 * r2 - a * a * (p.x * p.x - p.y * p.y);
    }
    Vec2 gradPhi(const Vec2& p) const override {
        float x = p.x, y = p.y;
        float r2 = x * x + y * y;
        return Vec2{
            4.0f * x * r2 - 2.0f * a * a * x,
            4.0f * y * r2 + 2.0f * a * a * y
        };
    }
};