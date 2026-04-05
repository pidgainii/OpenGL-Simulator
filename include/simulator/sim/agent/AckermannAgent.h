#pragma once
#include "IAgent.h"
#include "simulator/sim/model/ackermann/AckermannState.h"
#include "simulator/sim/model/ackermann/AckermannModel.h"
#include "simulator/sim/model/ackermann/AckermannController.h"
#include "simulator/sim/controller/GVF.h"
#include "simulator/sim/trajectory/ITrajectory.h"
#include <memory>

class AckermannAgent final : public IAgent {
    AckermannState state;
    AckermannModel model;
    AckermannController controller;
    GVF gvf;
    std::unique_ptr<ITrajectory> traj;

public:
    AckermannAgent(AckermannState initial,
        float wheelbase,
        float speed,
        float deltaMaxRad,
        std::unique_ptr<ITrajectory> trajectory,
        float gvfGain = 0.2f);

    void step(float dt) override;
    Pos pos() const override;
};