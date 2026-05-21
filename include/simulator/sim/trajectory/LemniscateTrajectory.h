#pragma once
#include "ITrajectory.h"
#include <cmath>

class LemniscateTrajectory : public ITrajectory {
    float a;
public:
    LemniscateTrajectory(float scale) : a(scale) {};

    float phi(const Vec2& p) const override {
        float x2y2 = p.x * p.x + p.y * p.y;
        return (x2y2 * x2y2) - (2 * a * a * (p.x * p.x - p.y * p.y));
    }

    Vec2 gradPhi(const Vec2& p) const override {
        float x2y2 = p.x * p.x + p.y * p.y;
        float a2 = a * a;
        // Derivative of phi with respect to x and y
        return Vec2{
            4 * p.x * (x2y2 - a2),
            4 * p.y * (x2y2 + a2)
        };
    }
};