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



#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include "simulator/sim/Simulation.h"
#include "simulator/core/Engine.h"
#include "simulator/scene/Scene.h"



Simulation::Simulation() {}



void Simulation::Update(float dt, Engine& engine, Scene& scene)
{
    // Get the list of coordinates for ALL agents
    // Now returns std::vector<std::vector<float>>
    std::vector<std::vector<float>> allAgentsCoords = engine.UpdateAgents(dt);

    // Iterate through the agents and update their corresponding scene objects
    for (size_t i = 0; i < allAgentsCoords.size(); ++i)
    {
        if (i < scene.scene.size())
        {
            const std::vector<float>& coords = allAgentsCoords.at(i);

            scene.scene.at(i).SetCoords(
                coords.at(0), // y
                coords.at(1), // z
                coords.at(2), // x
                coords.at(3)  // theta
            );
        }
    }
}