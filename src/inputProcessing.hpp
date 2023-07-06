#pragma once

#include "Camera.hpp"


namespace input {

extern float deltaTime;

void	deltaTimeUpdate(void);
void	mouse_callback(GLFWwindow *window, double xposIn, double yposIn);
void	scroll_callback(GLFWwindow *window, double xoffset, double yoffset);
void	processInput(GLFWwindow *window);

}