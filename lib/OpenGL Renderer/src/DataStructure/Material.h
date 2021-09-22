#ifndef __OPENGLRENDERER_DATASTRUCTURE_MATERIAL_H
#define __OPENGLRENDERER_DATASTRUCTURE_MATERIAL_H

#include <glm/glm.hpp>
#include "OpenGLObjects/Texture.h"
#include <memory>

class EnvironmentMap;
class Shader;

enum MaterialType
{
	LAMBERT,
	PHONG,
	GGX,
	GLASS
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
	Material(const std::string& name, MaterialType type = MaterialType::PHONG);

	/**
	*	\brief Destroys the object
	*	\note Also destroys the texture instances
	*/
	~Material();

	/**
	*	\brief Binds the material (i.e. the textures)
	*	\param[in] shader The shader the material should get binded to
	*/
	void bind(std::shared_ptr<Shader> shader);

	bool useDiffuseTextures = false;													/**<< Toggle the use of diffuse textures*/
	bool useSpecularTextures = false;													/**<< Toggle the use of specular textures*/
	bool useNormalTextures = false;														/**<< Toggle the use of normal textures*/
	bool useHeightTextures = false;														/**<< Toggle the use of height textures*/
	bool useMetallicTextures = false;													/**<< Toggle the use of metallic textures */
	bool useRoughnessTextures = false;													/**<< Toggle the use of roughness textures */
	bool useIBLTextures= false;															/**<< Toggle the use of IBL */
	bool useAmbienOcclusionTextures = false;											/**<< Toggle the use of ao textures */
	bool dynamic = false;																/**<< If the environment map of this object should be updated*/

	glm::vec3 ambient = glm::vec3(0, 0, 0);												/**<< The ambient part of the material*/
	glm::vec3 diffuse = glm::vec3(0, 0, 0);												/**<< The diffuse part of the material*/
	glm::vec3 specular = glm::vec3(0, 0, 0);											/**<< The specular part of the material*/

	std::shared_ptr<Texture> texture_diffuse = std::make_shared<Texture>();				/**<< The diffuse texture*/
	std::shared_ptr<Texture> texture_specular = std::make_shared<Texture>();			/**<< The specular texture*/
	std::shared_ptr<Texture> texture_normal = std::make_shared<Texture>();				/**<< The normal map texture*/
	std::shared_ptr<Texture> texture_height = std::make_shared<Texture>();				/**<< The displacement map texture*/
	std::shared_ptr<Texture> texture_metallic = std::make_shared<Texture>();			/**<< The metallic texture */
	std::shared_ptr<Texture> texture_roughness = std::make_shared<Texture>();			/**<< The roughness texture */
	std::shared_ptr<Texture> texture_irradiance =										/**<< The irradiance map */
		Texture::createTexture(32, 32, (float*)NULL, CUBEMAP, GL_RGB16F, RGB, GL_FLOAT);		
	std::shared_ptr<Texture> texture_prefilter =										/**<< The prefiltered texture */
		Texture::createTexture(128, 128, (float*)NULL, CUBEMAP, GL_RGB16F, RGB, GL_FLOAT);
	std::shared_ptr<Texture> LUT =														/**<< The LUT texture */
		Texture::createTexture(512, 512, (float*)nullptr, TEXTURE, GL_RGB16F, GL_RGB, GL_FLOAT);
	std::shared_ptr<Texture> texture_ao = std::make_shared<Texture>();					/**<< The AO texture */
	std::shared_ptr<EnvironmentMap> environment;										/**<< The environment map */

	MaterialType _type = MaterialType::PHONG;											/**<< The material type*/

	float shininess = 0;																/**<< The shininess of the material*/
	float roughness = 0;																/**<< The roughness of the material (GGX)*/
	float metallic = 0;
	float refractive_index = 1;															/**<< The refractive index*/
private:
	std::string _name;
};

#endif