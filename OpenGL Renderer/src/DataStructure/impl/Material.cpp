#include "DataStructure/Material.h"
#include "Shader/Shader.h"

void 
Material::destroyObject(Material& object)
{
	if (object.useTextures)
	{
		object.useTextures = false;
		Texture::destroyObject(object.texture_diffuse);
		Texture::destroyObject(object.texture_specular);
		Texture::destroyObject(object.texture_normal);
		Texture::destroyObject(object.texture_height);
	}
	object.ambient = glm::vec3(0, 0, 0);
	object.diffuse = glm::vec3(0, 0, 0);
	object.specular = glm::vec3(0, 0, 0);
}

void 
Material::bind(Shader shader)
{
	
}