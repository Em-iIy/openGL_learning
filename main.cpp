#include <iostream>
#include <cmath>
#include <cstring>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm/glm.hpp>
#include "shaderClass.hpp"
#include "window.hpp"
#include "Cube.hpp"
#include "VAO.hpp"
#include "VBO.hpp"
#include "EBO.hpp"

#define DISTANCE 3

void matmul(GLfloat matrix[3][3], GLfloat *in, GLfloat *out)
{
	GLfloat temp[3];
	for (uint i = 0; i < 3; ++i)
		temp[i] = in[0] * matrix[0][i] + in[1] * matrix[1][i] + in[2] * matrix[2][i];
	for (uint i = 0; i < 3; ++i)
		out[i] = temp[i];
}

int main()
{
	srand(time(NULL));
	initGlfw();
	GLFWwindow* window = initWindow(1000, 1000, "cube", NULL, NULL);

	Shader shaderProgram("resources/shaders/default.vert", "resources/shaders/default.frag");
	// glm::vec2 test(1.0f);
	// test.x += 10.0f;
	GLfloat coord[3] = {0,0,0};
	Cube cube(coord, 20.0f);
	// Cube cube2(coord, 1.0f);
	// Cube cube3(coord, 1.0f);

	float angle = 0.01f;
	int width, height;
	glLineWidth(5.0f);
	glfwGetWindowSize(window, &width, &height);
	glViewport(0, 0, width, height);
	glPointSize(10.0f);
	glEnable(GL_DEPTH_TEST);
	while (!glfwWindowShouldClose(window))
	{
		GLfloat rotateY[3][3] = {
			{cosf(angle), 0, sinf(angle)},
			{0, 1, 0},
			{-sinf(angle), 0, cosf(angle)}
		};
		GLfloat rotateX[3][3] = {
			{1, 0, 0},
			{0, cosf(angle), -sinf(angle)},
			{0, sinf(angle), cosf(angle)}
		};
		GLfloat rotateZ[3][3] = {
			{cosf(angle),-sinf(angle), 0},
			{sinf(angle), cosf(angle), 0},
			{0, 0, 1}
		};
		cube.Transform(rotateY);
		cube.Transform(rotateX);
		cube.Transform(rotateZ);
		// cube2.Transform(rotateZ);
		// cube3.Transform(rotateX);
	
		// Specify the color of the background
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		// Clean the back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// Tell OpenGL which Shader Program we want to use
		shaderProgram.Activate();
		cube.DrawMesh(DISTANCE);
		cube.Clear();
		// cube2.DrawMesh(DISTANCE);
		// cube2.Clear();
		// cube3.DrawMesh(DISTANCE);
		// cube3.Clear();
		// Bind the VAO so OpenGL knows to use it
		// VAO1.Bind();
		// VBO1.Update(temp, sizeof(temp));
		// Draw primitives, number of indices, datatype of indices, index of indices
		// glDrawElements(GL_LINE_STRIP, sizeof(indices), GL_UNSIGNED_INT, 0);
		// glDrawElements(GL_POINTS, sizeof(indices), GL_UNSIGNED_INT, 0);
		// VAO1.Unbind();
		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();
		angle += 0.01f;
	}



	// VAO1.Delete();
	// VBO1.Delete();
	// EBO1.Delete();

	shaderProgram.Delete();

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}