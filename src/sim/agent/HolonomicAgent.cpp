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

void HolonomicAgent::step(float dt) {
    Vec2  p = state.p;
    float w = state.w;

    Vec2  fw = traj->f(w);
    Vec2  dfw = traj->df(w);

    float phi_x = p.x - fw.x;
    float phi_y = p.y - fw.y;

    float vx = dfw.x - k * phi_x;
    float vy = dfw.y - k * phi_y;
    float w_dot = 1.0f + k * (phi_x * dfw.x + phi_y * dfw.y);

    float norm = std::hypot(vx, vy);
    if (norm > 1e-8f) {
        float scale = 1.0f / norm;
        vx *= scale;
        vy *= scale;
        w_dot *= scale;  
    }

    state.p.x += vx * dt;
    state.p.y += vy * dt;
    state.w += w_dot * dt;

    state.w = std::fmod(state.w, TWO_PI);
    if (state.w < 0.0f) state.w += TWO_PI;

    if (std::abs(vx) > 1e-6f || std::abs(vy) > 1e-6f)
        lastTheta = std::atan2(vy, vx);
}

Pos HolonomicAgent::pos() const {
    return Pos{ state.p.x, state.p.y, lastTheta };
}