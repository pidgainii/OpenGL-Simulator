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
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

#include "simulator/core/Engine.h"

#include "simulator/core/Application.h"
#include "simulator/core/Input.h"

#include "simulator/graphics/WindowManager.h"

#include <iostream>

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"




Application::Application()
	: sim(),
      renderer(),
      loader(),
      ui(&sim),
	  isSimulating(false),
	selectedEngineIndex(0)
{
	window = CreateWindow(1400, 900, "Simulation");

	// We give glfw pointer to this Application instance
	glfwSetWindowUserPointer(window, this);

	// ---------- IMGUI -----------
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	ImGuiIO& io = ImGui::GetIO();
	ImGui::StyleColorsDark();

	// Initialize backends
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");
	// -----------------------------




	// RENDERER
	renderer.Init();



	// CAMERA
	camera = Camera(
		0.0f, 3.0f, 0.0f,   // position
		0.0f, 1.0f, 0.0f,    // up vector
		90.0f,              // yaw
		-89.0f               // pitch (look straight down)
	);

	lastX = 0.0f;
	lastY = 0.0f;
	firstMouse = true;



	InitEnginesScenes();
}


void Application::Run()
{
		while (!glfwWindowShouldClose(window))
	{
		// ----------- IMGUI: Before rendering -> Start ImGui frame -----------
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		ui.Render(selectedEngineIndex, isSimulating, engines, configNumAgents, configSelectedModel, configSelectedTraj, triggerReset);

		// CHECK FOR RESET TRIGGER
		if (triggerReset) {
			isSimulating = false; // Pause while resetting
			InitEnginesScenes();  // Rebuild everything
			triggerReset = false; // Reset the flag
		}

		ImGuiIO& io = ImGui::GetIO();

		// Get mouse position every frame
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);

		if (!io.WantCaptureMouse && glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
		{
			if (firstMouse)
			{
				lastX = (float)xpos;
				lastY = (float)ypos;
				firstMouse = false;
			}

			float xoffset = (float)xpos - lastX;
			float yoffset = lastY - (float)ypos;

			lastX = (float)xpos;
			lastY = (float)ypos;

			camera.ProcessMouseMovement(xoffset, yoffset);
		}
		else
		{
			firstMouse = true;
		}
		// -----------------------------------------------------------------------

		static double lastTime = glfwGetTime();
		double currentTime = glfwGetTime();
		float dt = static_cast<float>(currentTime - lastTime);
		lastTime = currentTime;
		time += dt;


		// Only process camera/simulator input if ImGui isn't using the mouse
		if (!ImGui::GetIO().WantCaptureMouse) {
			processInput(window);
		}

		if (isSimulating && activeEngine && activeScene) {
			sim.Update(dt*10, *activeEngine, *activeScene);
		}
		if (activeScene)
		{
			renderer.Render(activeScene->scene, camera.GetViewMatrix(), camera.GetProjectionMatrix());
		}

		// --------------- IMGUI -----------------------
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		// ---------------------------------------------


		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	Terminate();
}


void Application::InitEnginesScenes() {
	// Generate starting coordinates based on the dynamic configNumAgents
	std::vector<InitialState> starts;
	for (int i = 0; i < configNumAgents; i++) {
		// Simple spread logic so they don't spawn exactly on top of each other
		starts.push_back({ (float)(30 + i * 4.0f), (float)(-35 + i * -2.0f), 1.5f });
	}

	// Clear old instances
	engines.clear();
	scenes.clear();

	// Build Engines with the new trajectory config
	engines.push_back(std::make_unique<Engine>(SimulationType::Holonomic, configNumAgents, starts, configSelectedTraj));
	engines.push_back(std::make_unique<Engine>(SimulationType::Ackermann, configNumAgents, starts, configSelectedTraj));
	engines.push_back(std::make_unique<Engine>(SimulationType::Unicycle, configNumAgents, starts, configSelectedTraj));

	// Map the UI model index to an actual file path
	std::string objFiles[] = {
		"assets/models/airplane.obj",
		"assets/models/car2.obj",
		"assets/models/drone.obj"
	};
	std::string selectedObjPath = objFiles[configSelectedModel];

	// Build Scenes with the dynamic path
	scenes.push_back(std::make_unique<Scene>(loader.LoadScene(engines[0]->getAgentCount(), selectedObjPath, configSelectedTraj)));
	scenes.push_back(std::make_unique<Scene>(loader.LoadScene(engines[1]->getAgentCount(), selectedObjPath, configSelectedTraj)));
	scenes.push_back(std::make_unique<Scene>(loader.LoadScene(engines[2]->getAgentCount(), selectedObjPath, configSelectedTraj)));

	// Reset Active Pointers
	if (!engines.empty()) activeEngine = engines[selectedEngineIndex].get();
	if (!scenes.empty())  activeScene = scenes[selectedEngineIndex].get();
}


void Application::Terminate()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwTerminate();
	glfwDestroyWindow(window);
	renderer.Clean();
}


void Application::TogglePause()
{
	isSimulating = !isSimulating;
}