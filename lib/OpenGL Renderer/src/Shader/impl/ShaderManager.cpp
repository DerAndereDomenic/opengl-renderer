#include <Shader/ShaderManager.h>
#include <DLogger/Logger.h>

ShaderManager* ShaderManager::_instance = new ShaderManager;

void
ShaderManager::addShaderImpl(const std::string& name, const bool geometry)
{
	const std::string vertexPath = SHADER_DIRECTORY + name + ".vert";
	const std::string fragmentPath = SHADER_DIRECTORY + name + ".frag";

	std::shared_ptr<Shader> shader;
	if (geometry)
	{
		const std::string geometryPath = SHADER_DIRECTORY + name + ".geom";
		shader = std::make_shared<Shader>(vertexPath, geometryPath, fragmentPath);
	}
	else
	{
		shader = std::make_shared<Shader>(vertexPath.c_str(), fragmentPath.c_str());
	}
	_shader.insert(std::pair<std::string, std::shared_ptr<Shader>>(name, shader));
}

void
ShaderManager::removeShaderImpl(const std::string& name)
{
	auto it = _shader.find(name);
	if (it == _shader.end())
	{
		LOGGER::ERROR("Shader with name: " + name + " does not exist. Rejecting...");
		return;
	}
	_shader.erase(it);
}

void 
ShaderManager::addComputeShaderImpl(const std::string& name)
{
	const std::string computePath = SHADER_DIRECTORY + name + ".glsl";

	std::shared_ptr<Shader> shader = Shader::createComputeShader(computePath);

	_shader.insert(std::pair<std::string, std::shared_ptr<Shader>>(name, shader));
}

std::shared_ptr<Shader>
ShaderManager::getShaderImpl(const std::string& name)
{
	return _shader[name];
}

void 
ShaderManager::setShaderDirImpl(const std::string& path)
{
	SHADER_DIRECTORY = path;
}
