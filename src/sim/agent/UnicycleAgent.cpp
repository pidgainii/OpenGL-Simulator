#include "simulator/sim/agent/UnicycleAgent.h"

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
{
}

void UnicycleAgent::step(float dt) {
    UnicycleControl u = controller.compute(state, *traj, gvf);
    state = model.step(state, u, dt);
}

Pos UnicycleAgent::pos() const {
    return Pos{ state.x, state.y, state.theta };
}