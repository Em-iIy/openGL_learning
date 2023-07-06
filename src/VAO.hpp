#ifndef VAO_CLASS_H
#define VAO_CLASS_H

#include <GLAD/glad.h>
#include "VBO.hpp"

class VAO
{
public:
	// ID reference for the Vertex Array Object
	GLuint ID;
	// Constructor that generates a VAO ID
	VAO();

	// Links a VBO to the VAO using a certain layout
	void LinkAtr(VBO& VBO, GLuint layout, GLuint n, GLenum type, GLsizeiptr stride, void *offset);
	// Binds the VAO
	void Bind();
	// Unbinds the VAO
	void Unbind();
	// Deletes the VAO
	void Delete();
};
#endif