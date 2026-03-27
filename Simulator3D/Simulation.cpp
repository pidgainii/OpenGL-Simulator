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

#include "Simulation.h"

#include "../Simulator3D/Engine.h"



Simulation::Simulation() {}



void Simulation::Update(float dt, Engine& engine, std::vector<Renderable>& scene)
{
	// We call Sim.Update(dt), which gives us a vector of 3 coordinates (for our plane)
	std::vector<float> coordinates = engine.UpdateSim(dt);

	scene.at(0).SetCoords(coordinates.at(0), coordinates.at(1), coordinates.at(2), coordinates.at(3));
	
}