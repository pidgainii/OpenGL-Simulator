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

#include <vector>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "simulator/graphics/Renderer.h"
#include "simulator/io/Loader.h"
#include "simulator/sim/Simulation.h"
#include "simulator/scene/Camera.h"
#include "simulator/scene/Renderable.h" // if you store std::vector<Renderable>

class Application {
public:
    Application();

    void Run(Engine engine);
    void Setup(Engine engine);
    void Terminate();

    GLFWwindow* window = nullptr;

    float time = 0.0f;

    Engine engine;

    Simulation sim;
    Renderer renderer;
    std::vector<Renderable> scene;
    Camera camera;
    Loader loader;

    glm::mat4 worldView{};
    glm::mat4 viewProj{};
};
