#include <GLAD/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>


void	initGlfw(void)
{
	if (!glfwInit())
	{
		std::cerr << "Glfw init error" << std::endl;
		exit(EXIT_FAILURE);
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
}

GLFWwindow	*initWindow(int width, int height, const char *title, GLFWmonitor *monitor, GLFWwindow *share)
{
	int x, y;
	GLFWwindow	*window = glfwCreateWindow(width, height, title, monitor, share);
	if (!window)
	{
		std::cerr << "Glfw window error" << std::endl;
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(window);
	if (!gladLoadGL())
	{
		std::cerr << "Glad couldn't load GL" << std::endl;
		glfwTerminate();
		glfwDestroyWindow(window);
		exit(EXIT_FAILURE);
	}
	glfwGetFramebufferSize(window, &x, &y);
	glViewport(0, 0, x, y);
	return (window);
}
