#include <Shader/ShaderManager.h>

ShaderManager* ShaderManager::_instance = 0;

ShaderManager*
ShaderManager::instance()
{
	if (_instance == nullptr)
	{
		_instance =  new ShaderManager();
	}
	return _instance;
}

void
ShaderManager::destroyObject(ShaderManager& manager)
{
	for (std::pair<std::string, Shader> shader : manager._shader)
	{
		Shader::destroyObject(shader.second);
	}
	manager._shader.clear();

	delete manager._instance;
}


void
ShaderManager::addShader(const std::string& name)
{
	const std::string vertexPath = SHADER_DIRECTORY + name + ".vert";
	const std::string fragmentPath = SHADER_DIRECTORY + name + ".frag";
	Shader shader = Shader::createObject(vertexPath.c_str(), fragmentPath.c_str());
	_shader.insert(std::pair<std::string, Shader>(name, shader));
}

Shader
ShaderManager::getShader(const std::string& name)
{
	return _shader[name];
}