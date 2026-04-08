#include "simulator/sim/agent/HolonomicAgent.h"

HolonomicAgent::HolonomicAgent(HolonomicState initial,
    std::unique_ptr<ITrajectory> trajectory,
    float gvfGain)
    : state(initial)
    , model()
    , controller()
    , gvf(gvfGain)
    , traj(std::move(trajectory))
{
}

void HolonomicAgent::step(float dt) {
    HolonomicControl u = controller.compute(state, *traj, gvf);
    state = model.step(state, u, dt);

    // orientation for rendering (direction of motion)
    if (std::abs(u.v.x) > 1e-6f || std::abs(u.v.y) > 1e-6f) {
        lastTheta = std::atan2(u.v.y, u.v.x);
    }
}

Pos HolonomicAgent::pos() const {
    return Pos{ state.p.x, state.p.y, lastTheta };
}