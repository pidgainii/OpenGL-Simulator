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



#include "Input.h"
#include "Application.h"
#include "Camera.h"



static float lastX = 0.0f;
static float lastY = 0.0f;
static bool firstMouse = true;

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    Application* app =
        static_cast<Application*>(glfwGetWindowUserPointer(window));

    float x = static_cast<float>(xpos);
    float y = static_cast<float>(ypos);

    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
    {
        if (firstMouse)
        {
            lastX = x;
            lastY = y;
            firstMouse = false;
            return;
        }

        float xoffset = x - lastX;
        float yoffset = lastY - y;

        lastX = x;
        lastY = y;

        app->camera.ProcessMouseMovement(xoffset, yoffset);
    }
    else
    {
        firstMouse = true;
    }
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    // We take the Application instance that glfw has access to
    Application* app =
        static_cast<Application*>(glfwGetWindowUserPointer(window));

    float y = static_cast<float>(yoffset);

    app->camera.ProcessMouseScroll(y);
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    Application* app =
        static_cast<Application*>(glfwGetWindowUserPointer(window));


    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        app->camera.ProcessKeyboard(FORWARD, 0.02);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        app->camera.ProcessKeyboard(BACKWARD, 0.02);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        app->camera.ProcessKeyboard(LEFT, 0.02);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        app->camera.ProcessKeyboard(RIGHT, 0.02);
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        app->camera.ProcessKeyboard(DOWN, 0.02);
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        app->camera.ProcessKeyboard(UP, 0.02);
}