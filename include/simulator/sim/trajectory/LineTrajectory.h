// LineTrajectory.h  — agents follow a horizontal line at y = offset
#pragma once
#include "ITrajectory.h"

class LineTrajectory : public ITrajectory {
    float offset; // y-intercept of the line
public:
    LineTrajectory(float yOffset = 0.0f) : offset(yOffset) {}

    // phi = y - offset  (zero on the line, positive above)
    float phi(const Vec2& p) const override {
        return p.y - offset;
    }
    Vec2 gradPhi(const Vec2& p) const override {
        return Vec2{ 0.0f, 1.0f };
    }
};