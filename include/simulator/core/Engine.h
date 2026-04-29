/*
 * Licensed under the Apache License, Version 2.0.
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

#include <memory>
#include <vector>
#include <string>
#include "simulator/sim/agent/IAgent.h"
#include "simulator/sim/common/Pos.h"



enum class SimulationType {
	Holonomic,
	Ackermann,
	Unicycle
};

struct InitialState {
    float x, y, theta;
};

class Engine {
public:
    // Constructor now takes type, count, and a vector of starting positions
    Engine(SimulationType type, int numAgents, const std::vector<InitialState>& initialStates);

    void Init(int numAgents, const std::vector<InitialState>& initialStates);
    std::vector<std::vector<float>> UpdateSim(float dt);

    // Public getter for the number of agents
    size_t getAgentCount() const { return agents.size(); }
    std::string getName() const;

private:
    std::vector<std::unique_ptr<IAgent>> agents;
    SimulationType simType;
    std::string name;
};