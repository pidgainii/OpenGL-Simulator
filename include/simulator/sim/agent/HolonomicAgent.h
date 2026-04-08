#pragma once
#include "IAgent.h"
#include "simulator/sim/model/holonomic/HolonomicState.h"
#include "simulator/sim/model/holonomic/HolonomicModel.h"
#include "simulator/sim/model/holonomic/HolonomicController.h"
#include "simulator/sim/controller/GVFHolonomic.h"
#include "simulator/sim/trajectory/ITrajectory.h"
#include <memory>
#include <cmath>

class HolonomicAgent final : public IAgent {
    HolonomicState state;
    HolonomicModel model;
    HolonomicController controller;
    GVFHolonomic gvf;                 
    std::unique_ptr<ITrajectory> traj;

    float lastTheta = 0.0f; 

public:
    HolonomicAgent(HolonomicState initial,
        std::unique_ptr<ITrajectory> trajectory,
        float gvfGain = 0.1f);

    void step(float dt) override;
    Pos pos() const override;
};