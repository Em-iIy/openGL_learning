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
#include "Camera.hpp"
#include "utils/glmPrintUtils.hpp"
#include "utils/loadTex.hpp"
#include "inputProcessing.hpp"
#include <stdio.h>


Camera camera(glm::vec3(0.0f, 0.0f, 6.0f));

glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);

glm::vec3	randVec3()
{
	return (glm::vec3((rand() / 2147483647.0f) * 2 - 1.0f, (rand() / 2147483647.0f) * 2 - 1.0f, (rand() / 2147483647.0f) * 2 - 1.0f));
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
	glfwSetScrollCallback(window, input::scroll_callback);
	glfwSetCursorPosCallback(window, input::mouse_callback);

	std::vector<Vertex> vertexTriangles;
	fill_vertices(vertexTriangles);

	VAO	vao;
	vao.Bind();
	VBO vbo(vertexTriangles);
	vao.LinkAtr(vbo, 0, 3, GL_FLOAT, sizeof(Vertex), (void *)0);
	vao.LinkAtr(vbo, 1, 3, GL_FLOAT, sizeof(Vertex), (void *)(sizeof(glm::vec3)));
	vao.LinkAtr(vbo, 2, 3, GL_FLOAT, sizeof(Vertex), (void *)(sizeof(glm::vec3) * 2));
	vao.LinkAtr(vbo, 3, 2, GL_FLOAT, sizeof(Vertex), (void *)(sizeof(glm::vec3) * 3));
	vao.Unbind();
	vbo.Unbind();

	VAO	lightVao;
	lightVao.Bind();
	VBO lightVbo(vertexTriangles);
	lightVao.LinkAtr(lightVbo, 0, 3, GL_FLOAT, sizeof(Vertex), (void *)0);
	lightVao.Unbind();
	lightVbo.Unbind();

	Shader containerShader("resources/shaders/light.vert", "resources/shaders/default.frag");
	Shader lightShader("resources/shaders/light.vert", "resources/shaders/light.frag");

	Material material = {
		.diffuse = loadTex("resources/textures/steel_container.png", GL_RGBA),
		.specular = loadTex("resources/textures/container2_specular.png", GL_RGBA),
		.shininess = 32.0f
	};
	Light light = {
		.position = glm::vec3(1.2f, 1.0f, 2.0f),
		.ambient = glm::vec3(0.2f),
		.diffuse = glm::vec3(0.5f),
		.specular = glm::vec3(1.0f)
	};

	int x, y;
	glfwGetWindowSize(window, &x, &y);
	glViewport(0, 0, x, y);
	glEnable(GL_DEPTH_TEST);

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.1f, 0.1f, 0.1f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		input::deltaTimeUpdate();
		input::processInput(window);

		glm::mat4 view = camera.getViewMatrix();
		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);

		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::rotate(model, (float)glfwGetTime() * glm::radians(120.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(2.0f));

		containerShader.Activate();
		containerShader.setMaterial("material", material);
		containerShader.setLight("light", light);
		containerShader.setVec3("viewPos", camera.Position);
		containerShader.setMat4("view", view);
		containerShader.setMat4("projection", projection);
		containerShader.setMat4("model", model);
	
		// Draw the container
		vao.Bind();
		glDrawArrays(GL_TRIANGLES, 0, vertexTriangles.size() * sizeof(Vertex));
		vao.Unbind();

		// Create cube where the light is
		model = glm::mat4(1.0f);
		model = glm::translate(model, light.position);
		model = glm::scale(model, glm::vec3(0.2f));

		// Set lightshader uniforms
		lightShader.Activate();
		lightShader.setMat4("view", view);
		lightShader.setMat4("projection", projection);
		lightShader.setMat4("model", model);
		lightShader.setVec3("lightColor", lightColor);

		// Draw light cube
		lightVao.Bind();
		glDrawArrays(GL_TRIANGLES, 0, vertexTriangles.size() * sizeof(Vertex));
		lightVao.Unbind();

		// Swap the front and back buffers to put the new frame in the window
		glfwSwapBuffers(window);

		// Calls the callback functions
		glfwPollEvents();
	}

	// Clean up
	{
		vao.Delete();
		vbo.Delete();
		lightVao.Delete();
		lightVbo.Delete();
		containerShader.Delete();
		lightShader.Delete();
		glfwDestroyWindow(window);
		glfwTerminate();
	}
	return 0;
}