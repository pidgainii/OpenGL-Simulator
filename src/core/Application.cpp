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
      config(),
      ui(&sim, &config)
{
	// TODO: Make width and heigh configurable in a different place
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



	// TEMPORARY
	worldView = glm::mat4(1.0f);
	viewProj = glm::mat4(1.0f);
	viewProj = glm::perspective(glm::radians(100.0f), 800.0f / 600.0f, 0.1f, 500.0f);




	camera = Camera(
		0.0f, 3.0f, 0.0f,   // position
		0.0f, 1.0f, 0.0f,    // up vector
		90.0f,              // yaw
		-89.0f               // pitch (look straight down)
	);
}


void Application::Run(Engine& engine)
{
	Setup(engine);

	// --------------------------- TEMPORARY -------------------------------
	float lastX = 0.0f;
	float lastY = 0.0f;
	bool firstMouse = true;

	// maybe some functions will be moved to a different class, not the renderer
	while (!glfwWindowShouldClose(window))
	{
		// ----------- IMGUI: Before rendering -> 1. Start ImGui frame -----------
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		ui.Render();

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

		// Maybe i should move this somewhere else
		// Real dt calculations
		static double lastTime = glfwGetTime();
		double currentTime = glfwGetTime();
		float dt = static_cast<float>(currentTime - lastTime);
		lastTime = currentTime;
		time += dt;


		// Only process camera/simulator input if ImGui isn't using the mouse
		if (!ImGui::GetIO().WantCaptureMouse) {
			processInput(window);
		}

		sim.Update(0.1, engine, scene);
		renderer.Render(scene, camera.GetViewMatrix(), viewProj);


		// --------------- IMGUI -----------------------
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		// ---------------------------------------------

		// TODO: maybe create window class to manage all of this glfw stuff
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	Terminate();
}


void Application::Setup(Engine& engine)
{
	renderer.Init();
	loader.LoadScene(scene);
}


void Application::Terminate()
{
	// we should clean every mesh here
	// TODO: CLEAN MESH OR RENDERABLE OBJECTS

	// tell renderer to clear resources
	glfwTerminate();
	renderer.Clean();
}







