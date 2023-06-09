#ifndef MESH_HPP
# define MESH_HPP

#include <GLAD/glad.h>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <vector>
#include "VBO.hpp"
#include "EBO.hpp"
#include "VAO.hpp"

struct Vertex {
	glm::vec3	vector;
	glm::vec3	color = glm::vec3(1.0f);
};

class Mesh
{
	private:
		VAO					_VAO;
		VBO					_VBO;
		EBO					_EBO;
		std::vector<Vertex>	_vertices;
		std::vector<uint>	_indices;

	public:
		void	del(void);
		void	draw(void);

		Mesh(void);
		~Mesh(void);
		Mesh(Mesh const &src);
		Mesh	&operator=(Mesh const &rhs);
};

#endif
