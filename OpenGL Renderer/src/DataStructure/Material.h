#ifndef DATA_STRUCTURE_MATERIAL_H
#define DATA_STRUCTURE_MATERIAL_H

#include <glm/glm.hpp>

/**
*	\brief A struct to model a material
*/
struct Material
{
	glm::vec3 ambient; /**<< The ambient part of the material*/
	glm::vec3 diffuse; /**<< The diffuse part of the material*/
	glm::vec3 specular; /**<< The specular part of the material*/
	float shininess; /**<< The shininess of the material*/
};

/**
*	\brief A struct to model a material using diffuse and specular maps
*/
struct MaterialMap
{
	unsigned int diffuse; /**<< The diffuse map*/
	unsigned int specular; /**<< The specular map*/
	float shininess; /*<< The shininess of the material*/
};

#endif