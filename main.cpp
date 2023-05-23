#include<iostream>
#include<math.h>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include"shaderClass.hpp"
#include"VAO.hpp"
#include"VBO.hpp"
#include"EBO.hpp"



// Vertices coordinates
// GLfloat vertices[] =
// {
// 	-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower left corner
// 	0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower right corner
// 	0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f, // Upper corner
// 	-0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // Inner left
// 	0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // Inner right
// 	0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f // Inner down
// };
	// -0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f,
	// 0.5f, 0.5f, 1.0f, 0.0f, 1.0f, 0.0f,
	// 0.2f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f
GLfloat vertices[] = {
	-1.0f, -1.0f, 1.0f, 1.0f, 0.0f, 0.0f, // bottom left front 	0
	1.0f, -1.0f, 1.0f, 1.0f, 0.0f, 0.0f, // bottom right front 	1
	-1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, // top left front 		2
	1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, // top right front 		3
	-0.8f, 0.75f, -0.8f, 1.0f, 0.0f, 0.0f, // top left back 	4
	0.8f, 0.75f, -0.8f, 1.0f, 0.0f, 0.0f, // top right back 	5
	-0.8f, -0.75f, -0.8f, 1.0f, 0.0f, 0.0f, // bottom left back	6
	0.8f, -0.75f, -0.8f, 1.0f, 0.0f, 0.0f // bottom right back	7
};
GLfloat vertices2[] = {
	-1.0f / 2, -1.0f / 2, 1.0f / 2, 1.0f, 1.0f, 0.0f, // bottom left front 	0
	1.0f / 2, -1.0f / 2, 1.0f / 2, 1.0f, 1.0f, 0.0f, // bottom right front 	1
	-1.0f / 2, 1.0f / 2, 1.0f / 2, 1.0f, 1.0f, 0.0f, // top left front 		2
	1.0f / 2, 1.0f / 2, 1.0f / 2, 1.0f, 1.0f, 0.0f, // top right front 		3
	-0.8f / 2, 0.75f / 2, -0.8f / 2, 1.0f, 1.0f, 0.0f, // top left back 	4
	0.8f / 2, 0.75f / 2, -0.8f / 2, 1.0f, 1.0f, 0.0f, // top right back 	5
	-0.8f / 2, -0.75f / 2, -0.8f / 2, 1.0f, 1.0f, 0.0f, // bottom left back	6
	0.8f / 2, -0.75f / 2, -0.8f / 2, 1.0f, 1.0f, 0.0f // bottom right back	7
};

// Indices for vertices order
// GLuint indices[] =
// {
// 	0, 3, 5, // Lower left triangle
// 	3, 2, 4, // Lower right triangle
// 	5, 4, 1 // Upper triangle
// };

// cube
GLuint indices[] = {
	4, 5, 5, 6, 6, 4, // back bottom triangle
	5, 6, 6, 7, 7, 5, // back top triangle
	0, 4, 6, 0, // left top triangle
	2, 4, 0, 4, // left bottom triangle
	3, 4, // top
	0, 7, // bottom
	3, 7, 7, 1, // right bottom triangle
	3, 5, 7, 3, // right top triangle
	0, 1, 1, 2, 2, 0, // front bottom triangle
	1, 2, 2, 3, 3, 1 // front top triangle
};

// GLuint indices2[] = {
// 	0, 0, 0, 1, 0, 2, 0, 3, 0, 4, 0, 5, 0, 6, 0, 7,
// 	1, 0, 1, 1, 1, 2, 1, 3, 1, 4, 1, 5, 1, 6, 1, 7,
// 	2, 0, 2, 2, 2, 2, 2, 3, 2, 4, 2, 5, 2, 6, 2, 7,
// 	3, 0, 3, 3, 3, 3, 3, 3, 3, 4, 3, 5, 3, 6, 3, 7,
// 	4, 0, 4, 4, 4, 4, 4, 4, 4, 4, 4, 5, 4, 6, 4, 7,
// 	5, 0, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 6, 5, 7,
// 	6, 0, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 7,
// 	7, 0, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
// };


int main()
{
	// Initialize GLFW
	if (!glfwInit())
	{
		std::cout << "Failed to init GLFW" << std::endl;
		glfwTerminate();
		return -1;
	}

	// Tell GLFW what version of OpenGL we are using 
	// In this case we are using OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	// Tell GLFW we are using the CORE profile
	// So that means we only have the modern functions
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif
	// Create a GLFWwindow object of 800 by 800 pixels, naming it "YoutubeOpenGL"
	GLFWwindow* window = glfwCreateWindow(800, 800, "cube", NULL, NULL);
	// Error check if the window fails to create
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	// Introduce the window into the current context
	glfwMakeContextCurrent(window);

	//Load GLAD so it configures OpenGL
	gladLoadGL();
	// Specify the viewport of OpenGL in the Window
	// In this case the viewport goes from x = 0, y = 0, to x = 800, y = 800
	glViewport(0, 0, 800, 800);


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

	// VAO VAO2;
	// VAO2.Bind();

	// // Generates Vertex Buffer Object and links it to vertices
	// VBO VBO2(vertices2, sizeof(vertices2));
	// // Generates Element Buffer Object and links it to indices
	// EBO EBO2(indices2, sizeof(indices2));

	// // Links VBO to VAO
	// VAO2.LinkAtr(VBO2, 0, 3, GL_FLOAT, 6 * sizeof(float), (void *)0);
	// VAO2.LinkAtr(VBO2, 1, 3, GL_FLOAT, 6 * sizeof(float), (void *)(3 * sizeof(float)));
	// // Unbind all to prevent accidentally modifying them
	// VAO2.Unbind();
	// VBO2.Unbind();
	// EBO2.Unbind();


	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		// Specify the color of the background
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		// Clean the back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT);
		// Tell OpenGL which Shader Program we want to use
		shaderProgram.Activate();
		// Bind the VAO so OpenGL knows to use it
		VAO1.Bind();
		// Draw primitives, number of indices, datatype of indices, index of indices
		glDrawElements(GL_LINES, sizeof(indices), GL_UNSIGNED_INT, 0);
		VAO1.Unbind();
		// VAO2.Bind();
		// glDrawElements(GL_LINES, sizeof(indices2), GL_UNSIGNED_INT, 0);
		// VAO2.Unbind();
		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();
	}



	// Delete all the objects we've created
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	// VAO2.Delete();
	// VBO2.Delete();
	// EBO2.Delete();
	shaderProgram.Delete();
	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
	return 0;
}