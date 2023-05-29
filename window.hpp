#ifndef WINDOW_HPP
# define WINDOW_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>

void	initGlfw(void);
GLFWwindow	*initWindow(int width, int height, const char *title, GLFWmonitor *monitor, GLFWwindow *share);

#endif
