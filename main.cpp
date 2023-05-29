#include <iostream>
#include <cmath>
#include <cstring>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "shaderClass.hpp"
#include "window.hpp"
#include "VAO.hpp"
#include "VBO.hpp"
#include "EBO.hpp"

#define DISTANCE 4

GLfloat vertices[] = {
	-1.0f, -1.0f, 1.0f, 1.0f, 0.0f, 1.0f, // bottom left front 	0
	1.0f, -1.0f, 1.0f, 1.0f, 0.0f, 1.0f, // bottom right front 	1
	-1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, // top left front 		2
	1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, // top right front 		3
	-1.0f, 1.0f, -1.0f, 0.0f, 1.0f, 1.0f, // top left back 		4
	1.0f, 1.0f, -1.0f, 0.0f, 1.0f, 1.0f, // top right back 		5
	-1.0f, -1.0f, -1.0f, 0.0f, 1.0f, 0.0f, // bottom left back	6
	1.0f, -1.0f, -1.0f, 0.0f, 1.0f, 0.0f // bottom right back	7
};
GLfloat temp[sizeof(vertices)];

// cube
GLuint indices[] = {
	4, 5, 6, 4, // back bottom triangle
	6, 7, 7, 5, // back top triangle
	6, 0, // left top triangle
	2, 4, // left bottom triangle
	7, 1, // right bottom triangle
	3, 5, // right top triangle
	0, 1, 2, 0, // front bottom triangle
	2, 3, 3, 1 // front top triangle
};

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
	initGlfw();
	GLFWwindow* window = initWindow(800, 800, "cube", NULL, NULL);

	Shader shaderProgram("resources/shaders/default.vert", "resources/shaders/default.frag");
	
	// Generates Shader object using shaders defualt.vert and default.frag


	// Generates Vertex Array Object and binds it
	VAO VAO1;
	VAO1.Bind();

	// Generates Vertex Buffer Object and links it to vertices
	VBO VBO1(vertices, sizeof(vertices));
	// Generates Element Buffer Object and links it to indices
	EBO EBO1(indices, sizeof(indices));

	// Links VBO to VAO
	VAO1.LinkAtr(VBO1, 0, 3, GL_FLOAT, 6 * sizeof(float), (void *)0);
	VAO1.LinkAtr(VBO1, 1, 3, GL_FLOAT, 6 * sizeof(float), (void *)(3 * sizeof(float)));
	// Unbind all to prevent accidentally modifying them
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();


	// Main while loop
	float angle = 0.01f;
	int width, height;
	std::memcpy(temp, vertices, sizeof(vertices));
	while (!glfwWindowShouldClose(window))
	{
		glfwGetWindowSize(window, &width, &height);
		glViewport(0, 0, width, height);
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
		// GLfloat rotate[3][3] = {
		// 	{1, 0, 0},
		// 	{0, 1, 0},
		// 	{0, 0, 1}
		// };
		// for (uint64_t i = 0; i < sizeof(vertices); i += 3)
		// {
		// 	matmul(rotateY, &vertices[i], &temp[i]);
		// }
		for (uint64_t i = 0; i < sizeof(vertices) / sizeof(GLfloat); i += 6)
		{
			matmul(rotateY, &vertices[i], &temp[i]);
			matmul(rotateX, &temp[i], &temp[i]);
			matmul(rotateZ, &temp[i], &temp[i]);
			GLfloat z = 1 / (DISTANCE - temp[i + 2]);
			GLfloat projection[3][3] = {
				{z, 0, 0},
				{0, z, 0},
				{0, 0, 0}
			};
			matmul(projection, &temp[i], &temp[i]);
		}
		// if (vertices[0] < -0.5f)
		// 	angle = 0.01f;
		// if (vertices[0] > 0.5f)
		// 	angle = -0.01f;
		// for (uint64_t i = 0; i < sizeof(vertices); ++i)
		// 	vertices[i] += angle;

		
		// Specify the color of the background
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		// Clean the back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT);
		// Tell OpenGL which Shader Program we want to use
		shaderProgram.Activate();
		// Bind the VAO so OpenGL knows to use it
		VAO1.Bind();
		VBO1.Update(temp, sizeof(temp));
		// Draw primitives, number of indices, datatype of indices, index of indices
		glDrawElements(GL_LINES, sizeof(indices), GL_UNSIGNED_INT, 0);
		VAO1.Unbind();
		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();
		angle += 0.01f;
	}



	// Delete all the objects we've created
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();

	shaderProgram.Delete();
	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
	return 0;
}