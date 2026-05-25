#include "simulator/sim/agent/HolonomicAgent.h"
#include <cmath>
#include <algorithm>

static constexpr float TWO_PI = 2.0f * 3.14159265358979323846f;

HolonomicAgent::HolonomicAgent(HolonomicState initial,
    std::unique_ptr<ITrajectory> trajectory,
    float gvfGain)
    : state(initial)
    , model()
    , controller()
    , gvf(gvfGain)
    , traj(std::move(trajectory))
    , k(gvfGain)
{
    // inicializa w al punto más cercano de la curva
    float best_w = 0.0f;
    float best_dist = 1e9f;
    for (int i = 0; i < 500; ++i) {
        float w_candidate = TWO_PI * i / 500.0f;
        Vec2  fp = traj->f(w_candidate);
        float dx = state.p.x - fp.x;
        float dy = state.p.y - fp.y;
        float d = dx * dx + dy * dy;
        if (d < best_dist) { best_dist = d; best_w = w_candidate; }
    }
    state.w = best_w;
}

void HolonomicAgent::step(float dt)
{
    float x = state.p.x;
    float y = state.p.y;
    float w = state.w;

    Vec2 f = traj->f(w);
    Vec2 df = traj->df(w);

    float fx = f.x;
    float fy = f.y;

    float dfx = df.x;
    float dfy = df.y;

    float phi1 = x - fx;
    float phi2 = y - fy;

    Vec3 g1 = { 1.0f, 0.0f, -dfx };
    Vec3 g2 = { 0.0f, 1.0f, -dfy };

    Vec3 Vtan;
    Vtan.x = g1.y * g2.w - g1.w * g2.y;
    Vtan.y = g1.w * g2.x - g1.x * g2.w;
    Vtan.w = g1.x * g2.y - g1.y * g2.x;

    float k = this->k;

    Vec3 Vnorm;
    Vnorm.x = -k * (phi1 * g1.x + phi2 * g2.x);
    Vnorm.y = -k * (phi1 * g1.y + phi2 * g2.y);
    Vnorm.w = -k * (phi1 * g1.w + phi2 * g2.w);

    Vec3 V;
    V.x = Vtan.x + Vnorm.x;
    V.y = Vtan.y + Vnorm.y;
    V.w = Vtan.w + Vnorm.w;

    float norm = std::sqrt(V.x * V.x + V.y * V.y + V.w * V.w);
    if (norm > 1e-8f) {
        V.x /= norm;
        V.y /= norm;
        V.w /= norm;
    }

    state.p.x += V.x * dt;
    state.p.y += V.y * dt;
    state.w += V.w * dt;

    lastTheta = std::atan2(V.y, V.x);
}

Pos HolonomicAgent::pos() const {
    return Pos{ state.p.x, state.p.y, lastTheta };
}