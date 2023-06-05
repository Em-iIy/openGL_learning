#include <iostream>
#include <cmath>
#include <cstring>
#include <GLAD/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "shaderClass.hpp"
#include "window.hpp"
#include "Cube_vec3.hpp"
#include "VAO.hpp"
#include "VBO.hpp"
#include "EBO.hpp"
#include "screen.hpp"

int main()
{
	srand(time(NULL));
	initGlfw();
	GLFWwindow* window = initWindow(WIDTH, HEIGHT, "cube", NULL, NULL);

	Shader shaderProgram("resources/shaders/default.vert", "resources/shaders/default.frag");
	
	Cube cube(glm::vec3(-0.5f, 0.3f, 0.f), 0.5f);
	Cube cube2(glm::vec3(0.5f, 0.5f, 0.f), 0.5f);

	float angle = 0.01f;
	float x_speed = 0.01f;
	float y_speed = 0.01f;
	int width, height;
	glLineWidth(5.f);
	glfwGetWindowSize(window, &width, &height);
	glViewport(0, 0, width, height);
	glPointSize(10.f);
	glEnable(GL_DEPTH_TEST);
	while (!glfwWindowShouldClose(window))
	{

		cube.Transform(glm::rotate(glm::mat4(1.0f), angle, glm::vec3(1.f, 1.f, 0.f)));
		cube2.Transform(glm::rotate(glm::mat4(1.0f), angle, glm::vec3(1.f, 0.5f, 0.f)));
		// Specify the color of the background
		glClearColor(0.f, 0.f, 0.f, 1.f);
		// Clean the back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// Tell OpenGL which Shader Program we want to use
		shaderProgram.Activate();
		cube.DrawMesh(DISTANCE);
		cube.Clear();
		cube2.DrawMesh(DISTANCE);
		cube2.Clear();
		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();
		angle += 0.01f;
	}

	cube.Delete();
	cube2.Delete();
	shaderProgram.Delete();

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}