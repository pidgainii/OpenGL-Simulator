#pragma once
#include "AckermannState.h"
#include "simulator/sim/trajectory/ITrajectory.h"
#include "simulator/sim/controller/GVF.h"
#include <algorithm>
#include <cmath>

class AckermannController {
    float v;
    float deltaMax;
public:
    AckermannController(float speed, float deltaMaxRad);
    AckermannControl compute(const AckermannState& s, const ITrajectory& traj, const GVF& gvf) const;
};