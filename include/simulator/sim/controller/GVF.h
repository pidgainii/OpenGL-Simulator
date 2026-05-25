#pragma once
#include "simulator/sim/trajectory/ITrajectory.h"
#include <cmath>

class GVF {
    float k;
public:
    GVF(float gain = 1.0f) : k(gain) {}

    float desiredHeading(const Vec2& p, float w, const ITrajectory& path) const {
        Vec2 fw = path.f(w);
        Vec2 dfw = path.df(w);

        float phi_x = p.x - fw.x;
        float phi_y = p.y - fw.y;

        float vx = dfw.x - k * phi_x;
        float vy = dfw.y - k * phi_y;

        float norm = std::hypot(vx, vy);
        if (norm > 1e-8f) { vx /= norm; vy /= norm; }

        return std::atan2(vy, vx);
    }

    float updateW(const Vec2& vel, float w, const ITrajectory& path) const {
        Vec2 dfw = path.df(w);
        float df_sq = dfw.x * dfw.x + dfw.y * dfw.y;
        if (df_sq < 1e-8f) df_sq = 1e-8f;
        return (vel.x * dfw.x + vel.y * dfw.y) / df_sq;
    }

    float getK() const { return k; }
};