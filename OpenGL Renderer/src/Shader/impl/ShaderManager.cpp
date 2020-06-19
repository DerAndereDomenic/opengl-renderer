#include <Shader/ShaderManager.h>


ShaderManager
ShaderManager::createObject()
{
	return ShaderManager();
}

void
ShaderManager::destroyObject(ShaderManager& manager)
{
	for (std::pair<std::string, Shader> shader : manager._shader)
	{
		Shader::destroyObject(shader.second);
	}
	manager._shader.clear();
}


void
ShaderManager::addShader(const std::string& name)
{

}

Shader
ShaderManager::getShader(const std::string& name)
{

}