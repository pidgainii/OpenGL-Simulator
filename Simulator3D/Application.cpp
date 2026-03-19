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

#include "Application.h"
#include "Input.h"

#include <iostream>




Application::Application()
{
	time = 0.0f;

	sim = Simulation();
	renderer = Renderer();
	loader = Loader();
	//camera = Camera();


	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// TODO: make variables for width and height
	window = glfwCreateWindow(1400, 900, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
	}
	glfwMakeContextCurrent(window);


	// We give glfw pointer to this Application instance
	glfwSetWindowUserPointer(window, this);

	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);



	// Smoother rendering
	glfwSwapInterval(1);




	// TEMPORARY UNTIL WE CREATE CAMERA
	worldView = glm::mat4(1.0f);
	viewProj = glm::mat4(1.0f);
	worldView = glm::translate(worldView, glm::vec3(0.0f, 0.1f, -10.0f));
	worldView = glm::translate(worldView, glm::vec3(0.0f, -1.0f, 0.0f));
	viewProj = glm::perspective(glm::radians(120.0f), 800.0f / 600.0f, 0.1f, 30.0f);



	Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
	float lastX = 1400 / 2.0f;
	float lastY = 900 / 2.0f;
	bool firstMouse = true;
}


void Application::Run()
{
	Setup();

	// maybe some functions will be moved to a different class, not the renderer
	while (!glfwWindowShouldClose(window))
	{
		// Maybe i should move this somewhere else
		// Real dt calculations
		static double lastTime = glfwGetTime();
		double currentTime = glfwGetTime();
		float dt = static_cast<float>(currentTime - lastTime);
		lastTime = currentTime;
		time += dt;


		processInput(window);


		sim.Update(0.1, scene);
		renderer.Render(scene, camera.GetViewMatrix(), viewProj);

		// TODO: maybe create window class to manage all of this glfw stuff
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	Terminate();
}


void Application::Setup()
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







