#ifndef DATA_STRUCTURE_MATERIAL_H
#define DATA_STRUCTURE_MATERIAL_H

#include <glm/glm.hpp>
#include "OpenGLObjects/Texture.h"

/**
*	\brief A struct to model a material
*/
struct Material
{
	bool useTextures = false; /**<< Toggle the use of textures*/
	glm::vec3 ambient; /**<< The ambient part of the material*/
	glm::vec3 diffuse; /**<< The diffuse part of the material*/
	glm::vec3 specular; /**<< The specular part of the material*/

	Texture texture_diffuse; /**<< The diffuse texture*/
	Texture texture_specular; /**<< The specular texture*/
	Texture texture_normal; /**<< The normal map texture*/
	Texture texture_height; /**<< The displacement map texture*/

	float shininess; /**<< The shininess of the material*/
};

/**
*	\brief A struct to model a material using diffuse and specular maps
*/
struct MaterialMap
{
	unsigned int diffuse; /**<< The diffuse map*/
	unsigned int specular; /**<< The specular map*/
	unsigned int normal; /**<< The normal map*/
	unsigned int height; /**<< The height map*/
	float shininess; /*<< The shininess of the material*/
};

#endif