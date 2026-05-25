#pragma once
#include "simulator/sim/trajectory/ITrajectory.h"
#include "simulator/sim/common/Vec3.h"
#include <cmath>
#include <algorithm>

class GVFHolonomic {
    float k;
public:
    GVFHolonomic(float gain = 1.0f) : k(gain) {}

    struct Field3 { float vx, vy, w_dot; };

Field3 field(const Vec2& p, float w, const ITrajectory& traj) const {
    Vec2 fp = traj.f(w);
    Vec2 df = traj.df(w);

    float ex = p.x - fp.x;
    float ey = p.y - fp.y;

    Vec3 g1 = {1.f, 0.f, -df.x};
    Vec3 g2 = {0.f, 1.f, -df.y};

    Vec3 Vtan = cross(g1, g2);

    Vec3 Vnorm = {
        -k * (ex * g1.x + ey * g2.x),
        -k * (ex * g1.y + ey * g2.y),
        -k * (ex * g1.w + ey * g2.w)
    };

    Vec3 V = {
        Vtan.x + Vnorm.x,
        Vtan.y + Vnorm.y,
        Vtan.w + Vnorm.w
    };

    float nrm = std::sqrt(V.x*V.x + V.y*V.y + V.w*V.w);
    if (nrm > 1e-8f) {
        V.x /= nrm;
        V.y /= nrm;
        V.w /= nrm;
    }

    return { V.x, V.y, V.w };
}
};