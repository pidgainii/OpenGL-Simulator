#pragma once
#include "AckermannState.h"
#include "simulator/sim/trajectory/ITrajectory.h"
#include "simulator/sim/controller/GVF.h"
#include <algorithm>
#include <cmath>

class AckermannController {
    float v;
    float deltaMax;
    float L;
    float kHdg;
public:
    AckermannController(float speed, float deltaMaxRad,
        float wheelbase, float headingGain = 2.0f);
    AckermannControl compute(const AckermannState& s, const ITrajectory& traj, const GVF& gvf) const;
};