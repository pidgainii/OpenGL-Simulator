#include "simulator/core/Engine.h"
#include <cmath>
#include <vector>
#include <algorithm>
#include <string>


#include "simulator/core/Engine.h"

#include "simulator/sim/agent/HolonomicAgent.h"        
#include "simulator/sim/trajectory/CircleTrajectory.h"   

Engine::Engine(SimulationType type, int numAgents, const std::vector<InitialState>& initialStates)
    : simType(type)
{
    switch (simType) {
    case SimulationType::Holonomic: name = "Holonomic"; break;
    case SimulationType::Ackermann: name = "Ackermann"; break;
    case SimulationType::Unicycle:  name = "Unicycle";  break;
    }

    Init(numAgents, initialStates);
}

void Engine::Init(int numAgents, const std::vector<InitialState>& initialStates) {
    agents.clear();

    // Loop up to numAgents, ensuring we don't go out of bounds of the initialStates vector
    for (int i = 0; i < numAgents; ++i) {

        // Default to 0,0,0 if the provided vector is shorter than numAgents
        float startX = (i < initialStates.size()) ? initialStates[i].x : 0.0f;
        float startY = (i < initialStates.size()) ? initialStates[i].y : 0.0f;

        switch (simType) {
        case SimulationType::Holonomic:
            agents.push_back(std::make_unique<HolonomicAgent>(
                HolonomicState{ Vec2{ startX, startY } },
                std::unique_ptr<ITrajectory>(new CircleTrajectory(10.0f)),
                0.1f
            ));
            break;

        case SimulationType::Ackermann:
            // agent = nullptr; // Or push_back(nullptr)
            break;

            // ... other cases
        }
    }
}

std::vector<std::vector<float>> Engine::UpdateSim(float dt) {
    std::vector<std::vector<float>> results;
    results.reserve(agents.size());

    for (auto& agent : agents) {
        if (agent) {
            agent->step(dt);
            Pos p = agent->pos();
            // Returning {y, z, x, theta} per your original signature
            results.push_back({ p.y, 0.0f, p.x, p.theta });
        }
    }
    return results;
}

std::string Engine::getName() const {
    return name;
}