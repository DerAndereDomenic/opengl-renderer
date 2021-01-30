#include "DataStructure/Material.h"
#include "Shader/Shader.h"

Material
Material::createObject(const std::string& name, MaterialType type)
{
	Material result;
	result._name = name;
	result._type = type;
	return result;
}

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
	object.shininess = 0;
}

void 
Material::bind(Shader shader)
{
	shader.bind();
	shader.setBool(_name + ".useTextures", useTextures);
	if (useTextures)
	{
		shader.setInt(_name + ".diffuse_map", 0);
		shader.setInt(_name + ".specular_map", 1);
		shader.setInt(_name + ".normal_map", 2);
		shader.setInt(_name + ".height_map", 3);
		shader.setFloat(_name + ".shininess", shininess);

		texture_diffuse.bind(0);
		texture_specular.bind(1);
		texture_normal.bind(2);
		texture_height.bind(3);
	}
	else
	{
		shader.setVec3(_name + ".ambient", ambient);
		shader.setVec3(_name + ".diffuse", diffuse);
		shader.setVec3(_name + ".specular", specular);
		shader.setFloat(_name + ".shininess", shininess);
	}
	shader.setInt(_name + ".type", _type);
	shader.setFloat(_name + ".roughness", roughness);
	shader.setFloat(_name + ".refractive_index", refractive_index);
}