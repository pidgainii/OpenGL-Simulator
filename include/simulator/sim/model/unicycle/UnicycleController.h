#pragma once

#include "UnicycleState.h"
#include "simulator/sim/trajectory/ITrajectory.h"
#include "simulator/sim/controller/GVF.h"
#include <cmath>

class UnicycleController {
    float v; 
    float k_theta; 

public:
    UnicycleController(float speed, float kTheta);

    UnicycleControl compute(const UnicycleState& s, const ITrajectory& traj, const GVF& gvf) const;
};