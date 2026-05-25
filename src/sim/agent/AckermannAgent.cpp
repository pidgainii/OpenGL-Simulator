#include "simulator/sim/agent/AckermannAgent.h"

#include <memory>

AckermannAgent::AckermannAgent(AckermannState initial,
    float wheelbase,
    float speed,
    float deltaMaxRad,
    float khdg,
    std::unique_ptr<ITrajectory> trajectory,
    float gvfGain)
    : state(initial)
    , model(wheelbase)
    , controller(speed, deltaMaxRad, wheelbase, khdg)
    , gvf(gvfGain)
    , traj(std::move(trajectory))
{
}

void AckermannAgent::step(float dt) {
    AckermannControl u = controller.compute(state, *traj, gvf);
    state = model.step(state, u, dt);

    // w_dot con el estado ya actualizado
    Vec2 vel{ u.v * std::cos(state.theta), u.v * std::sin(state.theta) };
    float w_dot = gvf.updateW(vel, state.w, *traj);
    state.w += w_dot * dt;
}

Pos AckermannAgent::pos() const {
    return Pos{ state.x, state.y, state.theta };
}