#include <iostream>
#include <cmath>
#include <cstring>
#include <GLAD/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stb/stb_image.h>
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

#include <stdio.h>

int selectVect = 0;


/*
TO DO:
	- Look into "Wireframe mode"
		- glPolygonMode(GL_FRONT_AND_BACK, GL_LINE) // enables
		- glPolygonMode(GL_FRONT_AND_BACK, GL_FILL) // disables
	- implement vertex struct (coords, rgb, texcoords, etc)
	
*/

std::ostream &operator<<(std::ostream &o, glm::vec3 &v)
{
	o << "(" << v.x << ", " << v.y << ", " << v.z << ")";
	return (o);
}

glm::vec3	randVec3()
{
	return (glm::vec3((rand() / 2147483647.0f) * 2 - 1.0f, (rand() / 2147483647.0f) * 2 - 1.0f, (rand() / 2147483647.0f) * 2 - 1.0f));
}

static uint	load_tex(const char *img, int format)
{
	int width, height, nrChannels;
	uint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	stbi_set_flip_vertically_on_load(true);
	u_char *data = stbi_load(img, &width, &height, &nrChannels, 0);
	if (!data)
	{
		std::cout << "load_tex: could not open: " << img << std::endl;
		exit(EXIT_FAILURE);
	}
	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(texture);
	stbi_image_free(data);
	return (texture);
	
}

void	processInput(GLFWwindow *window)
{
	static int key_minus_state = GLFW_RELEASE;
	static int key_equal_state = GLFW_RELEASE;
	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if(glfwGetKey(window, GLFW_KEY_MINUS) == GLFW_PRESS)
		key_minus_state = GLFW_PRESS;
	else if(glfwGetKey(window, GLFW_KEY_MINUS) == GLFW_RELEASE && key_minus_state == GLFW_PRESS)
	{
		key_minus_state = GLFW_RELEASE;
		if (selectVect == 0)
			selectVect = 3;
		else
			--selectVect;
		if (selectVect % 2 == 0)
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		else
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		std::cout << "- pressed " << selectVect << std::endl;
	}
	if(glfwGetKey(window, GLFW_KEY_EQUAL) == GLFW_PRESS)
		key_equal_state = GLFW_PRESS;
	if(glfwGetKey(window, GLFW_KEY_EQUAL) == GLFW_RELEASE && key_equal_state == GLFW_PRESS)
	{
		key_equal_state = GLFW_RELEASE;
		selectVect = ++selectVect % 4;
		if (selectVect % 2 == 0)
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		else
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		std::cout << "+ pressed " << selectVect << std::endl;
	}
}

int main()
{
	srand(time(NULL));
	initGlfw();
	GLFWwindow* window = initWindow(WIDTH, HEIGHT, "cube", NULL, NULL);
	std::vector<uint> idxTriangles;
	std::vector<Vertex> vertexTriangles;
	vertexTriangles.push_back(Vertex{glm::vec3(0.5f, 0.5f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(1.0f, 1.0f)});
	vertexTriangles.push_back(Vertex{glm::vec3(0.5f, -0.5f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(1.0f, 0.0f)});
	vertexTriangles.push_back(Vertex{glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f)});
	vertexTriangles.push_back(Vertex{glm::vec3(-0.5f, 0.5f, 0.0f), glm::vec3(1.0f, 1.0f, 0.0f), glm::vec2(0.0f, 1.0f)});

	idxTriangles.push_back(0);
	idxTriangles.push_back(1);
	idxTriangles.push_back(3);
	idxTriangles.push_back(1);
	idxTriangles.push_back(2);
	idxTriangles.push_back(3);

	VAO	vao;
	vao.Bind();
	VBO vbo(vertexTriangles);
	EBO ebo(idxTriangles);
	vao.LinkAtr(vbo, 0, 3, GL_FLOAT, sizeof(Vertex), (void *)0);
	vao.LinkAtr(vbo, 1, 3, GL_FLOAT, sizeof(Vertex), (void *)(sizeof(glm::vec3)));
	vao.LinkAtr(vbo, 2, 2, GL_FLOAT, sizeof(Vertex), (void *)(sizeof(glm::vec3) * 2));
	vao.Unbind();
	vbo.Unbind();
	ebo.Unbind();
;
	Shader shaderProgram("resources/shaders/default.vert", "resources/shaders/default.frag");

	uint texture1, texture2;
	texture1 = load_tex("resources/textures/container.jpg", GL_RGB);
	texture2 = load_tex("resources/textures/awesomeface.png", GL_RGBA);
    shaderProgram.Activate();
    shaderProgram.setInt("texture1", 0);
    shaderProgram.setInt("texture2", 1);

	// // int uniLocMyColor = glGetUniformLocation(shaderProgram.ID, "myColor");
	int x, y;
	glfwGetWindowSize(window, &x, &y);
	glViewport(0, 0, x, y);
	glEnable(GL_DEPTH_TEST);
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		glClearColor(0.f, 0.f, 0.f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);

		shaderProgram.Activate();

		vao.Bind();
		glDrawElements(GL_TRIANGLES, idxTriangles.size(), GL_UNSIGNED_INT, 0);
		vao.Unbind();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	vao.Delete();
	vbo.Delete();
	ebo.Delete();
	shaderProgram.Delete();
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}