#ifndef VECTORCLASS_HPP
# define VECTORCLASS_HPP

#include <vector>
#include <GLAD/glad.h>
#include <glm/vec3.hpp>
#include "VAO.hpp"
#include "EBO.hpp"
#include "EBO.hpp"

class VectorClass
{
	private:
		VAO						_VAO;
		VBO						_VBO;
		EBO						_EBO;
		std::vector<glm::vec3>	_vertices;
		std::vector<uint>		_indices;
	public:
		VectorClass(void);
		void	Delete(void);

		void	Draw(void);
		
		void	AddVector(glm::vec3 origin, glm::vec3 vect);
		void	Clear(void);
		size_t	size(void) const;
		~VectorClass();
};

#endif
