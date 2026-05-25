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

    // velocidad actual
    Vec2 vel{ u.v * std::cos(state.theta), u.v * std::sin(state.theta) };

    // actualiza w antes de mover el estado
    float w_dot = gvf.updateW(vel, state.w, *traj);

    state = model.step(state, u, dt);
    state.w += w_dot * dt;
}

Pos AckermannAgent::pos() const {
    return Pos{ state.x, state.y, state.theta };
}