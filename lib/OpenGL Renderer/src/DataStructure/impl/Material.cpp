#include "DataStructure/Material.h"
#include "Shader/Shader.h"
#include <DataStructure/EnvironmentMap.h>

Material::Material(const std::string& name, MaterialType type)
{
	_name = name;
	_type = type;
}
 
Material::~Material()
{
	ambient = glm::vec3(0, 0, 0);
	diffuse = glm::vec3(0, 0, 0);
	specular = glm::vec3(0, 0, 0);
	shininess = 0;
}

void 
Material::bind(std::shared_ptr<Shader> shader)
{
	shader->bind();
	shader->setBool(_name + ".useDiffuseTextures", useDiffuseTextures);
	shader->setBool(_name + ".useSpecularTextures", useSpecularTextures);
	shader->setBool(_name + ".useNormalTextures", useNormalTextures);
	shader->setBool(_name + ".useHeightTextures", useHeightTextures);
	if (useDiffuseTextures)
	{
		shader->setInt(_name + ".diffuse_map", 0);
		texture_diffuse->bind(0);
	}
	else
	{
		shader->setVec3(_name + ".diffuse", diffuse);
	}
		
	if (useSpecularTextures)
	{
		shader->setInt(_name + ".specular_map", 1);
		texture_specular->bind(1);
	}
	else
	{
		shader->setVec3(_name + ".specular", specular);
	}

	if (useNormalTextures)
	{
		shader->setInt(_name + ".normal_map", 2);
		texture_normal->bind(2);
	}
		
	if (useHeightTextures)
	{
		shader->setInt(_name + ".height_map", 3);
		texture_height->bind(3);
	}

	if (_type == GLASS)
	{
		shader->setInt(_name + ".environment", 4);
		environment->getCubeMap()->bind(4);
	}

	shader->setFloat(_name + ".shininess", shininess);
	shader->setVec3(_name + ".ambient", ambient);
	shader->setFloat(_name + ".shininess", shininess);
	shader->setInt(_name + ".type", _type);
	shader->setFloat(_name + ".roughness", roughness);
	shader->setFloat(_name + ".refractive_index", refractive_index);
}