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

#include <iostream>



const int width = 700;
const int height = 700;


int main()
{
	// Let's initialize glfw
	glfwInit();


	// We specify the minor and major version -> 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);

	// We select the core profile (modern version of OpenGL)
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	
	// ----------------------------------------------------------- 


	// Now we are going to create the window, make it part of current context and add some fail logic
	// The context is where OpenGL has all it's state.
	// It's like saying to OPENGL: "Hey, here is where you should draw"
	GLFWwindow* window = glfwCreateWindow(width, height, "MyWindow", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Error while trying to create window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);


	// ----------------------------------------------------------- 


	// Now we will activate OpenGL functions with GLAD loader
	gladLoadGL();


	// -----------------------------------------------------------


	// Now we are going to configure our window (viewport, color) and will swap buffers
	glViewport(0, 0, width, height);
	glClearColor(0.1f, 0.0f, 0.1f, 1.0f);
	
	// We have to clear the color buffer bit
	glClear(GL_COLOR_BUFFER_BIT);

	// We have to swap buffers so that OpenGL displays this window on screen
	glfwSwapBuffers(window);


	// -----------------------------------------------------------


	// Now we want to make sure our window remains open
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.1f, 0.0f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(window);

		// This function processes events in the event queue and then returns immediately
		glfwPollEvents();
	}


	// -----------------------------------------------------------

	
	// Now we free resources
	glfwDestroyWindow(window);
	glfwTerminate();


	
	return 0;
}



