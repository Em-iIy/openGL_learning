#ifndef CUBE_HPP
# define CUBE_HPP

#include <glad/glad.h>
#include <vector>
#include "VBO.hpp"
#include "EBO.hpp"
#include "VAO.hpp"
#include "readFile.hpp"

class Cube
{
	private:
		VAO		_VAO;
		VBO		_VBO;
		EBO		_EBO;
		GLfloat	_coords[3];
		

	public:
		Cube(GLfloat x, GLfloat y, GLfloat z);
		~Cube(void);
		Cube(Cube const &src);
		Cube	&operator=(Cube const &rhs);
};

#endif
