#include "simulator/sim/model/holonomic/HolonomicController.h"

HolonomicControl HolonomicController::compute(const HolonomicState& s,
    const ITrajectory& traj,
    const GVFHolonomic& gvf) const
{
    Vec2 V = gvf.field(s.p, traj);
    return HolonomicControl{ V };
}