#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include <GLAD/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat2x2.hpp>
#include <glm/mat3x3.hpp>
#include <glm/mat4x4.hpp>

#include "utils/readFile.hpp"

struct Material {
	uint 		diffuse;
	uint		specular;
	float		shininess;
};

struct DirLight {
   glm::vec3 direction;

   glm::vec3 ambient;
   glm::vec3 diffuse;
   glm::vec3 specular;
};

struct PointLight {
   glm::vec3 position;
   
   glm::vec3 ambient;
   glm::vec3 diffuse;
   glm::vec3 specular;

   float constant;
   float linear;
   float quadratic;
};

struct SpotLight {
   glm::vec3 position;
   glm::vec3 direction;

   glm::vec3 ambient;
   glm::vec3 diffuse;
   glm::vec3 specular;

   float cutOff;
   float outerCutOff;
};

struct Light {
	glm::vec3 position;
	glm::vec3 direction;

	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;

	float constant;
	float linear;
	float quadratic;

	float cutOff;
	float outerCutOff;
};

class Shader
{
public:
	// Reference ID of the Shader Program
	GLuint ID;
	// Constructor that build the Shader Program from 2 different shaders
	Shader(const char* vertexFile, const char* fragmentFile);

	// Activates the Shader Program
	void Activate();
	// Deletes the Shader Program
	void Delete();

	void setBool(const std::string &name, bool value) const;
	void setFloat(const std::string &name, float value) const;
	void setInt(const std::string &name, int value) const;
	void setVec2(const std::string &name, glm::vec2 &value) const;
	void setVec3(const std::string &name, glm::vec3 &value) const;
	void setVec4(const std::string &name, glm::vec4 &value) const;
	void setMat2(const std::string &name, glm::mat2 &value) const;
	void setMat3(const std::string &name, glm::mat3 &value) const;
	void setMat4(const std::string &name, glm::mat4 &value) const;
	void setMaterial(const std::string &name, Material &value) const;
	void setLight(const std::string &name, Light &value) const;
	void setDirLight(const std::string &name, DirLight &value) const;
	void setPointLight(const std::string &name, PointLight &value) const;
	void setSpotLight(const std::string &name, SpotLight &value) const;
};
#endif