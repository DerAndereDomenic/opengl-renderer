#ifndef __OPENGLRENDERER_DATASTRUCTURE_MATERIAL_H
#define __OPENGLRENDERER_DATASTRUCTURE_MATERIAL_H

#include <glm/glm.hpp>
#include "OpenGLObjects/Texture.h"
#include <memory>

class Shader;

enum MaterialType
{
	LAMBERT,
	PHONG,
	GGX
};

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
	*	\brief Create an object with a given name
	*	\param[in] name The name of the material (used in shader)
	*/
	static Material createObject(const std::string& name, MaterialType type = MaterialType::PHONG);

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

	bool useTextures = false;														/**<< Toggle the use of textures*/
	glm::vec3 ambient = glm::vec3(0, 0, 0);											/**<< The ambient part of the material*/
	glm::vec3 diffuse = glm::vec3(0, 0, 0);											/**<< The diffuse part of the material*/
	glm::vec3 specular = glm::vec3(0, 0, 0);										/**<< The specular part of the material*/

	std::shared_ptr<Texture> texture_diffuse = std::make_shared<Texture>();			/**<< The diffuse texture*/
	std::shared_ptr<Texture> texture_specular = std::make_shared<Texture>();		/**<< The specular texture*/
	std::shared_ptr<Texture> texture_normal = std::make_shared<Texture>();			/**<< The normal map texture*/
	std::shared_ptr<Texture> texture_height = std::make_shared<Texture>();			/**<< The displacement map texture*/

	MaterialType _type = MaterialType::PHONG;										/**<< The material type*/

	float shininess = 0;															/**<< The shininess of the material*/
	float roughness = 0;															/**<< The roughness of the material (GGX)*/
	float refractive_index = 1;														/**<< The refractive index*/
private:
	std::string _name;
};

#endif