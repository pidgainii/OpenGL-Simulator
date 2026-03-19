#pragma once


#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);