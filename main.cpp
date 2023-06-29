#include <iostream>
#include <cmath>
#include <cstring>
#include <GLAD/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stb/stb_image.h>
#include <unistd.h>

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
#include "glmPrintUtils.hpp"
#include "Camera.hpp"

#include <stdio.h>

int selectVect = 0;
float lastX = WIDTH / 2.0f;
float lastY = HEIGHT / 2.0f;
bool firstMouse = true;

float deltaTime = 0.0f;
float lastFrame = 0.0f;


glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

Camera camera(glm::vec3(0.0f, 0.0f, 6.0f));


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

void	mouse_callback(GLFWwindow *window, double xposIn, double yposIn)
{
	float xpos = static_cast<float>(xposIn);
	float ypos = static_cast<float>(yposIn);

	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}
	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;

	lastX = xpos;
	lastY = ypos;

	camera.processMouseMovement(xoffset, yoffset);
}

void	scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
{
	camera.processMouseScroll(yoffset);
}

void	processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.processKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.processKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.processKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.processKeyboard(RIGHT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		camera.processKeyboard(UP, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		camera.processKeyboard(DOWN, deltaTime);

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

void	fill_vertices(std::vector<Vertex> &vertices)
{
	vertices.push_back(Vertex{glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2( 0.0f, 0.0f)});
	vertices.push_back(Vertex{glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f)});
	vertices.push_back(Vertex{glm::vec3(0.5f,  0.5f, -0.5f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 1.0f)});
	vertices.push_back(Vertex{glm::vec3(0.5f,  0.5f, -0.5f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 1.0f)});
	vertices.push_back(Vertex{glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2( 0.0f, 1.0f)});
	vertices.push_back(Vertex{glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2( 0.0f, 0.0f)});
	vertices.push_back(Vertex{glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2( 0.0f, 0.0f)});
	vertices.push_back(Vertex{glm::vec3(0.5f, -0.5f,  0.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f)});
	vertices.push_back(Vertex{glm::vec3(0.5f,  0.5f,  0.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 1.0f)});
	vertices.push_back(Vertex{glm::vec3(0.5f,  0.5f,  0.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 1.0f)});
	vertices.push_back(Vertex{glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2( 0.0f, 1.0f)});
	vertices.push_back(Vertex{glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2( 0.0f, 0.0f)});
	vertices.push_back(Vertex{glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2( 1.0f, 0.0f)});
	vertices.push_back(Vertex{glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2( 1.0f, 1.0f)});
	vertices.push_back(Vertex{glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2( 0.0f, 1.0f)});
	vertices.push_back(Vertex{glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2( 0.0f, 1.0f)});
	vertices.push_back(Vertex{glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2( 0.0f, 0.0f)});
	vertices.push_back(Vertex{glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2( 1.0f, 0.0f)});
	vertices.push_back(Vertex{glm::vec3(0.5f,  0.5f,  0.5f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f)});
	vertices.push_back(Vertex{glm::vec3(0.5f,  0.5f, -0.5f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 1.0f)});
	vertices.push_back(Vertex{glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 1.0f)});
	vertices.push_back(Vertex{glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 1.0f)});
	vertices.push_back(Vertex{glm::vec3(0.5f, -0.5f,  0.5f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f)});
	vertices.push_back(Vertex{glm::vec3(0.5f,  0.5f,  0.5f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f)});
	vertices.push_back(Vertex{glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2( 0.0f, 1.0f)});
	vertices.push_back(Vertex{glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 1.0f)});
	vertices.push_back(Vertex{glm::vec3(0.5f, -0.5f,  0.5f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f)});
	vertices.push_back(Vertex{glm::vec3(0.5f, -0.5f,  0.5f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f)});
	vertices.push_back(Vertex{glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2( 0.0f, 0.0f)});
	vertices.push_back(Vertex{glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2( 0.0f, 1.0f)});
	vertices.push_back(Vertex{glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2( 0.0f, 1.0f)});
	vertices.push_back(Vertex{glm::vec3(0.5f,  0.5f, -0.5f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 1.0f)});
	vertices.push_back(Vertex{glm::vec3(0.5f,  0.5f,  0.5f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f)});
	vertices.push_back(Vertex{glm::vec3(0.5f,  0.5f,  0.5f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f)});
	vertices.push_back(Vertex{glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2( 0.0f, 0.0f)});
	vertices.push_back(Vertex{glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2( 0.0f, 1.0f)});
}

int main()
{
	srand(time(NULL));
	initGlfw();
	GLFWwindow* window = initWindow(WIDTH, HEIGHT, "cube", NULL, NULL);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	// trans = glm::scale(trans, glm::vec3(0.5f, 0.5f, 0.5f));

	std::vector<uint> idxTriangles;
	std::vector<Vertex> vertexTriangles;
	std::vector<Vertex> lightCube;
	std::vector<glm::vec3> cubePosition;

	for (uint i = 0; i < 100; ++i)
	{
		cubePosition.push_back(randVec3() * 10.0f);
	}
	fill_vertices(vertexTriangles);
	fill_vertices(lightCube);

	VAO	vao;
	vao.Bind();
	VBO vbo(vertexTriangles);
	EBO ebo(idxTriangles);
	vao.LinkAtr(vbo, 0, 3, GL_FLOAT, sizeof(Vertex), (void *)0);
	vao.LinkAtr(vbo, 1, 3, GL_FLOAT, sizeof(Vertex), (void *)(sizeof(glm::vec3)));
	vao.LinkAtr(vbo, 2, 3, GL_FLOAT, sizeof(Vertex), (void *)(sizeof(glm::vec3) * 2));
	vao.LinkAtr(vbo, 3, 2, GL_FLOAT, sizeof(Vertex), (void *)(sizeof(glm::vec3) * 3));
	vao.Unbind();
	vbo.Unbind();
	ebo.Unbind();

	VAO	lightVao;
	lightVao.Bind();
	VBO lightVbo(lightCube);
	lightVao.LinkAtr(lightVbo, 0, 3, GL_FLOAT, sizeof(Vertex), (void *)0);
	lightVao.Unbind();
	lightVbo.Unbind();


	Shader shaderProgram("resources/shaders/light.vert", "resources/shaders/default.frag");
	Shader lightShader("resources/shaders/light.vert", "resources/shaders/light.frag");
	// uint texture1, texture2;
	// texture1 = load_tex("resources/textures/container.jpg", GL_RGB);
	// texture2 = load_tex("resources/textures/awesomeface.png", GL_RGBA);
    // shaderProgram.Activate();
    // shaderProgram.setInt("texture1", 0);
    // shaderProgram.setInt("texture2", 1);


	// // int uniLocMyColor = glGetUniformLocation(shaderProgram.ID, "myColor");
	int x, y;
	glfwGetWindowSize(window, &x, &y);
	glViewport(0, 0, x, y);
	glEnable(GL_DEPTH_TEST);
	glm::vec3 objColor = glm::vec3(1.0f, 0.5f, 0.31f);
	while (!glfwWindowShouldClose(window))
	{
		float currentFrame = static_cast<float>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		processInput(window);

		glClearColor(0.1f, 0.1f, 0.1f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        // glActiveTexture(GL_TEXTURE0);
        // glBindTexture(GL_TEXTURE_2D, texture1);
        // glActiveTexture(GL_TEXTURE1);
        // glBindTexture(GL_TEXTURE_2D, texture2);

		glm::mat4 view = camera.getViewMatrix();
		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);

		// lightPos = camera.Position - camera.Front;
		// lightColor = glm::vec3(1.0f, abs(sin(glfwGetTime())), abs(cos(glfwGetTime())));

		shaderProgram.Activate();
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, sin(glfwGetTime()) * 15, cos(glfwGetTime()) * 15));
		model = glm::rotate(model, (float)glfwGetTime() * glm::radians(45.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(10.0f, 4.0f, 2.0f));
		shaderProgram.setVec3("objectColor", objColor);
		shaderProgram.setVec3("lightColor", lightColor);
		shaderProgram.setVec3("lightPos", lightPos);
		shaderProgram.setVec3("viewPos", camera.Position);
		shaderProgram.setMat4("view", view);
		shaderProgram.setMat4("projection", projection);
		shaderProgram.setMat4("model", model);
	
		vao.Bind();
		glDrawArrays(GL_TRIANGLES, 0, vertexTriangles.size() * sizeof(Vertex));
		vao.Unbind();

		lightShader.Activate();
		model = glm::mat4(1.0f);
		model = glm::translate(model, lightPos);
		model = glm::scale(model, glm::vec3(0.2f));
		lightShader.setMat4("view", view);
		lightShader.setVec3("lightColor", lightColor);
		lightShader.setMat4("projection", projection);
		lightShader.setMat4("model", model);

		lightVao.Bind();
		glDrawArrays(GL_TRIANGLES, 0, lightCube.size() * sizeof(Vertex));
		lightVao.Unbind();


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