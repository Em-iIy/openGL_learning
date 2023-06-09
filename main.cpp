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
#include "VAO.hpp"
#include "VBO.hpp"
#include "EBO.hpp"
#include "screen.hpp"
#include "Curve.hpp"
#include "VectorClass.hpp"
#include "Cube_vec3.hpp"
#include <unistd.h>

int selectVect = 0;

std::ostream &operator<<(std::ostream &o, glm::vec3 &v)
{
	o << "(" << v.x << ", " << v.y << ", " << v.z << ")";
	return (o);
}

glm::vec3	randVec3()
{
	return (glm::vec3(rand() / 2147483647.0f, rand() / 2147483647.0f, rand() / 2147483647.0f));
}

void	processInput(GLFWwindow *window)
{
	static int key_minus_state = GLFW_RELEASE;
	static int key_equal_state = GLFW_RELEASE;
	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if(glfwGetKey(window, GLFW_KEY_MINUS) == GLFW_PRESS)
	{
		key_minus_state = GLFW_PRESS;
		std::cout << "- pressed " << selectVect << std::endl;
	}
	else if(glfwGetKey(window, GLFW_KEY_MINUS) == GLFW_RELEASE && key_minus_state == GLFW_PRESS)
	{
		key_minus_state = GLFW_RELEASE;
		if (selectVect == 0)
			selectVect = 3;
		else
			--selectVect;
		std::cout << "- pressed " << selectVect << std::endl;
	}
	if(glfwGetKey(window, GLFW_KEY_EQUAL) == GLFW_PRESS)
		key_equal_state = GLFW_PRESS;
	if(glfwGetKey(window, GLFW_KEY_EQUAL) == GLFW_RELEASE && key_equal_state == GLFW_PRESS)
	{
		key_equal_state = GLFW_RELEASE;
		selectVect = ++selectVect % 4;
		std::cout << "+ pressed " << selectVect << std::endl;
	}
}

int main()
{
	srand(time(NULL));
	initGlfw();
	GLFWwindow* window = initWindow(WIDTH, HEIGHT, "cube", NULL, NULL);

	Shader shaderProgram("resources/shaders/default.vert", "resources/shaders/default.frag");
	
	std::vector<glm::vec3> curveVecs;
	glm::vec3 a(-0.5f, -0.5f, .5f);
	curveVecs.push_back(a);
	glm::vec3 cont1(.5f, 0.8f, .5f);
	curveVecs.push_back(cont1);
	glm::vec3 cont2(-.5f, 0.8f, -.5f);
	curveVecs.push_back(cont2);
	glm::vec3 b(.5f, -0.5f, -.5f);
	curveVecs.push_back(b);
	// std::cout << b << std::endl;
	VectorClass vects;
	Cube cube(glm::vec3(0,0,0), 0.5f);
	float angle = 0.01f;
	int sign = 1;
	int width, height;
	double xPos = 0, yPos = 0;
	std::vector<Curve> curves;
	uint steps = 50;
	glLineWidth(5.f);
	glfwGetWindowSize(window, &width, &height);
	glViewport(0, 0, width, height);
	glPointSize(10.f);
	glEnable(GL_DEPTH_TEST);
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);
		vects.Clear();
		curves.clear();
		glfwGetCursorPos(window, &xPos, &yPos);
		xPos = toNDC(xPos, WIDTH);
		yPos = toNDC(yPos, HEIGHT) * -1;
		curveVecs[selectVect] = glm::vec3(xPos, yPos, 0.0f);
		curves.push_back(Curve(steps, curveVecs[0], curveVecs[1], curveVecs[2], curveVecs[3]));
		float step_size = 1.f / steps;
		// for (float i = 0.f; i <= .50001f; i += step_size)
		// {
		// 	curves.push_back(Curve(steps, curves[0].getPos(i), curveVecs[1], curveVecs[2], curves[0].getPos(1.f - i)));
		// 	// curves.push_back(Curve(steps, curves[curves.size() - 1].getPos(i), cont1, cont2, curves[curves.size() - 1].getPos(1.f - i)));
		// }
		glClearColor(0.f, 0.f, 0.f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// Tell OpenGL which Shader Program we want to use
		shaderProgram.Activate();
		vects.AddVector(curveVecs[0], curveVecs[1]);
		vects.AddVector(curveVecs[2], curveVecs[3]);
		vects.Draw();
		for (auto it = curves.begin(); it != curves.end(); ++it)
			(*it).Draw();
		cube.setCoord(curves[0].getPos(angle));
		cube.Transform(glm::rotate(glm::mat4(1.0f), angle * 5, glm::vec3(1.0f, 1.0f, 0.0f)));
		cube.DrawMesh(DISTANCE);
		cube.Clear();
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