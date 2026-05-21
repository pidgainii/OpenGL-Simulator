#include "simulator/core/Engine.h"
#include <cmath>
#include <vector>
#include <algorithm>
#include <string>


#include "simulator/core/Engine.h"

#include "simulator/sim/agent/HolonomicAgent.h"
#include "simulator/sim/agent/AckermannAgent.h"
#include "simulator/sim/agent/UnicycleAgent.h"
#include "simulator/sim/trajectory/CircleTrajectory.h"
#include "simulator/sim/trajectory/LemniscateTrajectory.h"
Engine::Engine(SimulationType type, int numAgents, const std::vector<InitialState>& initialStates, int trajectoryType)
    : simType(type)
{
    switch (simType) {
    case SimulationType::Holonomic: name = "Holonomic"; break;
    case SimulationType::Ackermann: name = "Ackermann"; break;
    case SimulationType::Unicycle:  name = "Unicycle";  break;
    }

    Init(numAgents, initialStates, trajectoryType);
}

void Engine::Init(int numAgents, const std::vector<InitialState>& initialStates, int trajectoryType) {
    agents.clear(); // Ensure the vector is empty before populating

    for (int i = 0; i < numAgents; ++i) {
        float startX = (i < initialStates.size()) ? initialStates[i].x : (float)(i * 2.0f);
        float startY = (i < initialStates.size()) ? initialStates[i].y : (float)(i * 2.0f);
        float startTheta = 0.0f; // Default starting orientation

        std::unique_ptr<ITrajectory> traj;
        if (trajectoryType == 0) {
            traj = std::make_unique<CircleTrajectory>(20.0f);
        }
        else {
            traj = std::make_unique<LemniscateTrajectory>(35.0f);
        }

        switch (simType) {
        case SimulationType::Holonomic:
            agents.push_back(std::make_unique<HolonomicAgent>(
                HolonomicState{ Vec2{ startX, startY } },
                std::move(traj),
                0.01f
            ));
            break;

        case SimulationType::Ackermann:
            agents.push_back(std::make_unique<AckermannAgent>(
                AckermannState{ startX, startY, startTheta },
                1.0f,             // Wheelbase
                0.5f,             // Speed
                0.6f,             // Max steering angle
                std::move(traj),
                0.1f
            ));
            break;

        case SimulationType::Unicycle:
            agents.push_back(std::make_unique<UnicycleAgent>(
                UnicycleState{ startX, startY, startTheta }, // Initial state
                1.0f,             // Speed
                0.05f,             // Angular velocity gain (kTheta)
                std::move(traj),  // Pass unique_ptr safely
                0.01f             // GVF Gain
            ));
            break;
        }
    }
}

std::vector<std::vector<float>> Engine::UpdateAgents(float dt) {
    std::vector<std::vector<float>> results;
    results.reserve(agents.size());

    for (auto& agent : agents) {
        if (agent) {
            agent->step(dt);
            Pos p = agent->pos();
            results.push_back({ p.y, 0.0f, p.x, p.theta });
        }
    }
    return results;
}

std::string Engine::getName() const {
    return name;
}