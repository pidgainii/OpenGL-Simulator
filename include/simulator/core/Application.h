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
#include "simulator/cam/Camera.h"
#include "simulator/scene/Renderable.h"
#include "simulator/scene/Scene.h"
#include "simulator/ui/UI.h"

class Application {
public:
    Application();

    void Run();
    void Terminate();
    void TogglePause();
    void InitEnginesScenes();

    GLFWwindow* window = nullptr;

    float time = 0.0f;

    Simulation sim;
    Renderer renderer;
    
    Loader loader;
    UI ui;

    Camera camera;


    std::vector<std::unique_ptr<Engine>> engines;
    Engine* activeEngine = nullptr;
    
    std::vector<std::unique_ptr<Scene>> scenes;
    Scene* activeScene = nullptr;
    
    bool isSimulating = false;
    int selectedEngineIndex = 0;

private:
    float lastX;
    float lastY;
    bool firstMouse;

    int configNumAgents = 7;
    int configSelectedModel = 0;
    int configSelectedTraj = 0;
    bool triggerReset = false;

};
