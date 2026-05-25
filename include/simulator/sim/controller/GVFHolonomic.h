#pragma once
#include "simulator/sim/trajectory/ITrajectory.h"
#include <cmath>
#include <algorithm>

class GVFHolonomic {
    float k;
public:
    GVFHolonomic(float gain = 1.0f) : k(gain) {}

    struct Field3 { float vx, vy, w_dot; };

    Field3 field(const Vec2& p, float w, const ITrajectory& traj) const {
        Vec2  fp = traj.f(w);
        Vec2  df = traj.df(w);

        float ex = p.x - fp.x;
        float ey = p.y - fp.y;

        float vx = df.x - k * ex;
        float vy = df.y - k * ey;

        float nrm2 = std::sqrt(vx * vx + vy * vy);
        if (nrm2 > 1e-8f) { vx /= nrm2; vy /= nrm2; }

        float df_sq = std::max(df.x * df.x + df.y * df.y, 1e-8f);
        float w_dot = (vx * df.x + vy * df.y) / df_sq;

        return { vx, vy, w_dot };
    }
};