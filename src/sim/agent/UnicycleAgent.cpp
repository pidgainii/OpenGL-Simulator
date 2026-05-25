#include "simulator/sim/agent/UnicycleAgent.h"
#include <cmath>
#include <algorithm>

static constexpr float TWO_PI_U = 2.0f * 3.14159265358979323846f;

UnicycleAgent::UnicycleAgent(UnicycleState initial,
    float speed,
    float kTheta,
    std::unique_ptr<ITrajectory> trajectory,
    float gvfGain)
    : state(initial)
    , model()
    , controller(speed, kTheta)
    , gvf(gvfGain)
    , traj(std::move(trajectory))
    , v(speed)
    , k_theta(kTheta)
    , k(gvfGain)
{
    float best_w = 0.0f;
    float best_dist = 1e9f;
    for (int i = 0; i < 500; ++i) {
        float w_candidate = TWO_PI_U * i / 500.0f;
        Vec2  fp = traj->f(w_candidate);
        float dx = state.x - fp.x;
        float dy = state.y - fp.y;
        float d = dx * dx + dy * dy;
        if (d < best_dist) { best_dist = d; best_w = w_candidate; }
    }
    state.w = best_w;
}

void UnicycleAgent::step(float dt) {
    float x = state.x;
    float y = state.y;
    float theta = state.theta;
    float w = state.w;

    if (traj->hasParametric()) {
        Vec2 fw = traj->f(w);
        Vec2 dfw = traj->df(w);

        float phi_x = x - fw.x;
        float phi_y = y - fw.y;

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

        float theta_d = std::atan2(vy, vx);
        float e_theta = std::atan2(
            std::sin(theta_d - theta),
            std::cos(theta_d - theta)
        );
        float omega = k_theta * e_theta;

        float df_sq = dfw.x * dfw.x + dfw.y * dfw.y;
        if (df_sq < 1e-8f) df_sq = 1e-8f;
        float w_dot_phys = (v * std::cos(theta) * dfw.x + v * std::sin(theta) * dfw.y) / df_sq;

        state.x += v * std::cos(theta) * dt;
        state.y += v * std::sin(theta) * dt;
        state.theta += omega * dt;
        state.w += w_dot_phys * dt;

    }
    else {
        Vec2  grad = traj->gradPhi({ x, y });
        float phi = traj->phi({ x, y });

        float vx = -grad.y - k * phi * grad.x;
        float vy = grad.x - k * phi * grad.y;

        float theta_d = std::atan2(vy, vx);
        float e_theta = std::atan2(
            std::sin(theta_d - theta),
            std::cos(theta_d - theta)
        );
        float omega = k_theta * e_theta;

        state.x += v * std::cos(theta) * dt;
        state.y += v * std::sin(theta) * dt;
        state.theta += omega * dt;
    }

    state.theta = std::atan2(std::sin(state.theta), std::cos(state.theta));
    state.w = std::fmod(state.w, TWO_PI_U);
    if (state.w < 0.0f) state.w += TWO_PI_U;
}

Pos UnicycleAgent::pos() const {
    return Pos{ state.x, state.y, state.theta };
}