#include <iostream>
#include <cmath>
#include <cstring>
#include <GLAD/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "lerp.hpp"
#include "shaderClass.hpp"
#include "window.hpp"
#include "Cube_vec3.hpp"
#include "VAO.hpp"
#include "VBO.hpp"
#include "EBO.hpp"
#include "screen.hpp"
#include "Curve.hpp"
#include <unistd.h>


std::ostream &operator<<(std::ostream &o, glm::vec3 &v)
{
	o << "(" << v.x << ", " << v.y << ", " << v.z << ")";
	return (o);
}

int main()
{
	srand(time(NULL));
	initGlfw();
	GLFWwindow* window = initWindow(WIDTH, HEIGHT, "cube", NULL, NULL);

	Shader shaderProgram("resources/shaders/default.vert", "resources/shaders/default.frag");
	
	glm::vec3 a(-1.f, 0.0f, .5f);
	glm::vec3 cont1(-0.3f, -1.0f, -.5f);
	glm::vec3 cont2(0.3f, .5f, .5f);
	glm::vec3 b(1.0f, 0.0f, -.5f);

	float angle = 0.01f;
	int sign = 1;
	int width, height;
	double xPos = 0, yPos = 0;
	std::vector<Curve> curves;
	uint steps = 100;
	// glLineWidth(5.f);
	glfwGetWindowSize(window, &width, &height);
	glViewport(0, 0, width, height);
	glPointSize(10.f);
	glEnable(GL_DEPTH_TEST);
	while (!glfwWindowShouldClose(window))
	{
		curves.clear();
		glfwGetCursorPos(window, &xPos, &yPos);
		xPos = toNDC(xPos, WIDTH);
		yPos = toNDC(yPos, HEIGHT) * -1;
		// cont1 = glm::vec3(xPos, yPos, 0.0f);
		curves.push_back(Curve(steps, a, cont1, cont2, b));
		float step_size = 1.f / steps;
		for (float i = 0.f; i <= .50001f; i += step_size)
		{
			curves.push_back(Curve(steps, curves[0].getPos(i), cont1, cont2, curves[0].getPos(1.f - i)));
			// curves.push_back(Curve(steps, curves[curves.size() - 1].getPos(i), cont1, cont2, curves[curves.size() - 1].getPos(1.f - i)));
		}
		glClearColor(0.f, 0.f, 0.f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// Tell OpenGL which Shader Program we want to use
		shaderProgram.Activate();
		for (auto it = curves.begin(); it != curves.end(); ++it)
			(*it).Draw();
		glfwSwapBuffers(window);
		glfwPollEvents();
		angle += 0.01f * sign;
		if (angle >= .99999f)
			sign = -1;
		else if (angle <= 0.00001f)
			sign = 1;
		for (auto it = curves.begin(); it != curves.end(); ++it)
			(*it).Delete();
	}

	shaderProgram.Delete();

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}