#include <Shader/ShaderManager.h>
#include <DLogger/Logger.h>

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
ShaderManager::addShader(const std::string& name, const bool geometry)
{
	const std::string vertexPath = SHADER_DIRECTORY + name + ".vert";
	const std::string fragmentPath = SHADER_DIRECTORY + name + ".frag";

	Shader shader;
	if (geometry)
	{
		const std::string geometryPath = SHADER_DIRECTORY + name + ".geom";
		shader = Shader::createObject(vertexPath, geometryPath, fragmentPath);
	}
	else
	{
		shader = Shader::createObject(vertexPath.c_str(), fragmentPath.c_str());
	}
	_shader.insert(std::pair<std::string, Shader>(name, shader));
}

void
ShaderManager::removeShader(const std::string& name)
{
	auto& it = _shader.find(name);
	if (it == _shader.end())
	{
		LOGGER::ERROR("Shader with name: " + name + " does not exist. Rejecting...\n");
		return;
	}
	Shader::destroyObject(it->second);
	_shader.erase(it);
}

void 
ShaderManager::addComputeShader(const std::string& name)
{
	const std::string computePath = SHADER_DIRECTORY + name + ".glsl";

	Shader shader = Shader::createObject(computePath);

	_shader.insert(std::pair<std::string, Shader>(name, shader));
}

Shader
ShaderManager::getShader(const std::string& name)
{
	return _shader[name];
}

void 
ShaderManager::setShaderDir(const std::string& path)
{
	SHADER_DIRECTORY = path;
}