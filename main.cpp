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
	
	// Cube cube(glm::vec3(-0.5f, 0.3f, 0.f), 0.5f);
	// // Cube cube2(glm::vec3(0.5f, 0.5f, 0.f), 0.5f);


	glm::vec3 a(-0.7f, 0.5f, 0.0f);
	glm::vec3 cont1(-0.7f, -0.5f, 0.0f);
	glm::vec3 cont2(0.7f, -0.5f, 0.0f);
	glm::vec3 b(0.7f, 0.5f, 0.0f);



	float angle = 0.01f;
	uint steps = 1;
	int step = 1;
	int width, height;
	// glLineWidth(5.f);
	glfwGetWindowSize(window, &width, &height);
	glViewport(0, 0, width, height);
	glPointSize(10.f);
	glEnable(GL_DEPTH_TEST);
	while (!glfwWindowShouldClose(window))
	{
		Curve curve(steps, a, cont1, cont2, b);
		// cube.Transform(glm::rotate(glm::mat4(1.0f), angle, glm::vec3(1.f, 1.f, 0.f)));
		// cube2.Transform(glm::rotate(glm::mat4(1.0f), angle, glm::vec3(1.f, 0.5f, 0.f)));
		// Specify the color of the background
		glClearColor(0.f, 0.f, 0.f, 1.f);
		// Clean the back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// Tell OpenGL which Shader Program we want to use
		shaderProgram.Activate();
		curve.Draw();
		// VAO1.Bind();
		// glDrawElements(GL_LINES, (indc.size() - 1) * sizeof(uint), GL_UNSIGNED_INT, 0);
		// glDrawElements(GL_POINTS, indc.size() * sizeof(uint), GL_UNSIGNED_INT, 0);
		// VAO1.Unbind();
		// cube.DrawMesh(DISTANCE);
		// cube.Clear();
		// cube2.DrawMesh(DISTANCE);
		// cube2.Clear();
		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();
		angle += 0.01f;
		if (steps >= 10)
			step = -1;
		else if (steps <= 1)
			step = 1;
		steps += step;
		sleep(1);
	}

	// cube.Delete();
	// cube2.Delete();
	shaderProgram.Delete();

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}