#pragma once
#include "IAgent.h"
#include "simulator/sim/model/unicycle/UnicycleState.h"
#include "simulator/sim/model/unicycle/UnicycleModel.h"
#include "simulator/sim/model/unicycle/UnicycleController.h"
#include "simulator/sim/controller/GVF.h"
#include "simulator/sim/trajectory/ITrajectory.h"
#include <memory>

class UnicycleAgent final : public IAgent {
    UnicycleState state;
    UnicycleModel model;
    UnicycleController controller;
    GVF gvf;
    std::unique_ptr<ITrajectory> traj;

public:
    UnicycleAgent(UnicycleState initial,
        float speed,
        float kTheta,
        std::unique_ptr<ITrajectory> trajectory,
        float gvfGain = 0.2f);

    void step(float dt) override;
    Pos pos() const override;
};