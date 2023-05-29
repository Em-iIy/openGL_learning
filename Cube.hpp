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
		GLfloat	_size;
		std::vector<GLfloat> _base_vertices;
		std::vector<GLuint>	_base_indices;
		GLfloat	*_vertices;
		GLuint	*_indices;
		void loadMesh(const char *filename);
	public:
		void	Delete(void);
		Cube(void);
		Cube(GLfloat coords[3], GLfloat size);
		~Cube(void);
		Cube(Cube const &src);
		Cube	&operator=(Cube const &rhs);
};

#endif
