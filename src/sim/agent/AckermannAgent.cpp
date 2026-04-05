#include "simulator/sim/agent/AckermannAgent.h"

#include <memory>

AckermannAgent::AckermannAgent(AckermannState initial,
    float wheelbase,
    float speed,
    float deltaMaxRad,
    std::unique_ptr<ITrajectory> trajectory,
    float gvfGain)
    : state(initial)
    , model(wheelbase)
    , controller(speed, deltaMaxRad)
    , gvf(gvfGain)
    , traj(std::move(trajectory))
{
}

void AckermannAgent::step(float dt) {
    AckermannControl u = controller.compute(state, *traj, gvf);
    state = model.step(state, u, dt);
}

Pos AckermannAgent::pos() const {
    return Pos{ state.x, state.y, state.theta };
}