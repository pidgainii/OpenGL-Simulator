#pragma once
#include "HolonomicState.h"
#include "simulator/sim/controller/GVFHolonomic.h"
#include "simulator/sim/trajectory/ITrajectory.h"

class HolonomicController {
    float speed;
public:
    explicit HolonomicController() {}

    HolonomicControl compute(const HolonomicState& s,
        const ITrajectory& traj,
        const GVFHolonomic& gvf) const;
};