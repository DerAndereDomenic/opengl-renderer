#ifndef DATA_STRUCTURE_MATERIAL_H
#define DATA_STRUCTURE_MATERIAL_H

#include <glm/glm.hpp>
#include "OpenGLObjects/Texture.h"

class Shader;

/**
*	\brief A struct to model a material
*/
class Material
{
public:
	/**
	*	\brief Creates an empty object
	*/
	Material() = default;

	/**
	*	\brief Destroys the object
	*	\note Also destroys the texture instances
	*/
	static void destroyObject(Material& object);

	/**
	*	\brief Binds the material (i.e. the textures)
	*	\param[in] shader The shader the material should get binded to
	*/
	void bind(Shader shader);

	bool useTextures = false; /**<< Toggle the use of textures*/
	glm::vec3 ambient = glm::vec3(0, 0, 0); /**<< The ambient part of the material*/
	glm::vec3 diffuse = glm::vec3(0, 0, 0);; /**<< The diffuse part of the material*/
	glm::vec3 specular = glm::vec3(0, 0, 0);; /**<< The specular part of the material*/

	Texture texture_diffuse; /**<< The diffuse texture*/
	Texture texture_specular; /**<< The specular texture*/
	Texture texture_normal; /**<< The normal map texture*/
	Texture texture_height; /**<< The displacement map texture*/

	float shininess; /**<< The shininess of the material*/
};

#endif