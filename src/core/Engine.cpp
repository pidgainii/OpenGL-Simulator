#include "simulator/core/Engine.h"
#include <cmath>
#include <vector>
#include <algorithm>

// simulator/core/Engine.cpp
#include "simulator/core/Engine.h"

#include "simulator/sim/agent/UnicycleAgent.h"        
#include "simulator/sim/trajectory/CircleTrajectory.h"   

Engine::Engine() : x(2.0f), y(0.0f), z(0.0f), theta(0.0f) {
    Init(); 
}

void Engine::Init() {
    agent = std::make_unique<UnicycleAgent>(
        UnicycleState{ x, y, theta },              
        1.0f,                                        
        2.0f,                                        
        std::unique_ptr<ITrajectory>(new CircleTrajectory(10.0f)), 
        0.2f                                         
    );
}

std::vector<float> Engine::UpdateSim(float dt) {

    agent->step(dt);
    Pos p = agent->pos();

    x = p.x;
    y = p.y;
    theta = p.theta;

    return { y, 0.0f, x, theta };
}