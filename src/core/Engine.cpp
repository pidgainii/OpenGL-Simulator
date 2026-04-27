#include "simulator/core/Engine.h"
#include <cmath>
#include <vector>
#include <algorithm>
#include <string>


#include "simulator/core/Engine.h"

#include "simulator/sim/agent/HolonomicAgent.h"        
#include "simulator/sim/trajectory/CircleTrajectory.h"   

Engine::Engine(SimulationType type)
    : x(2.0f), y(0.0f), z(0.0f), theta(0.0f),
    simType(type)
{
    switch (simType) {
    case SimulationType::Holonomic:
        name = "Holonomic";
        break;
    case SimulationType::Ackermann:
        name = "Ackermann";
        break;
    case SimulationType::Unicycle:
        name = "Unicycle";
        break;
    }

    Init();
}

void Engine::Init() {
    switch (simType) {

    case SimulationType::Holonomic:
        agent = std::make_unique<HolonomicAgent>(
            HolonomicState{ Vec2{ x, y } },
            std::unique_ptr<ITrajectory>(new CircleTrajectory(10.0f)),
            0.1f
        );
        break;

    case SimulationType::Ackermann:
        // TODO: implement AckermannAgent
        agent = nullptr;
        break;

    case SimulationType::Unicycle:
        // TODO: implement UnicycleAgent
        agent = nullptr;
        break;
    }
}

std::vector<float> Engine::UpdateSim(float dt) {

    agent->step(dt);
    Pos p = agent->pos();

    x = p.x;
    y = p.y;
    theta = p.theta;

    return { y, 0.0f, x, theta };
}

std::string Engine::getName() const {
    return name;
}