#include "simulator/sim/model/holonomic/HolonomicController.h"

HolonomicControl HolonomicController::compute(const HolonomicState& s,
    const ITrajectory& traj,
    const GVFHolonomic& gvf) const {
    auto V = gvf.field(s.p, s.w, traj);
    return HolonomicControl{ Vec2{V.vx, V.vy}, V.w_dot };
}