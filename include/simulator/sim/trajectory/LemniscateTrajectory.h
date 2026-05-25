#pragma once
#include "ITrajectory.h"
#include <cmath>

class LemniscateTrajectory : public ITrajectory {
    float a;
public:
    LemniscateTrajectory(float scale) : a(scale) {}

    float phi(const Vec2& p) const override {
        float x2y2 = p.x * p.x + p.y * p.y;
        return (x2y2 * x2y2) - (2 * a * a * (p.x * p.x - p.y * p.y));
    }
    Vec2 gradPhi(const Vec2& p) const override {
        float x2y2 = p.x * p.x + p.y * p.y;
        return Vec2{ 4 * p.x * (x2y2 - a * a), 4 * p.y * (x2y2 + a * a) };
    }

    // Parametrización f(w)
    Vec2 f(float w) const {
        float denom = 1.0f + std::sin(w) * std::sin(w);
        return Vec2{
            a * std::cos(w) / denom,
            a * std::sin(w) * std::cos(w) / denom
        };
    }

    Vec2 df(float w) const {
        float sw = std::sin(w), cw = std::cos(w);
        float denom = (1.0f + sw * sw) * (1.0f + sw * sw);

        float dx = -a * sw * (3.0f - sw * sw) / denom;

        float dy = a * (
            (cw * cw - sw * sw) * (1.0f + sw * sw)
            - 2.0f * sw * sw * cw * cw
            ) / denom;

        return Vec2{ dx, dy };
    }


    bool hasParametric() const override { return true; }

};