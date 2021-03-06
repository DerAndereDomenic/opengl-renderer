#include <Shader/Shader.h>
#include <DLogger/Logger.h>

Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath)
{
	//File reading
	std::string vertex_buffer, fragment_buffer;

	readShaderCode(vertexPath, &vertex_buffer);
	const char* vShaderCode = vertex_buffer.c_str();

	readShaderCode(fragmentPath, &fragment_buffer);
	const char* fShaderCode = fragment_buffer.c_str();

	//Compiling
	uint32_t vertex, fragment;
	
	vertex = compileShader(GL_VERTEX_SHADER, vShaderCode);
	fragment = compileShader(GL_FRAGMENT_SHADER, fShaderCode);

	//Linking
	uint32_t shaders[] = { vertex,fragment };
	linkShader(shaders, 2);

	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

Shader::Shader(const std::string& vertexPath, const std::string& geometryPath, const std::string& fragmentPath)
{
	//File reading
	std::string vertex_buffer, fragment_buffer, geometry_buffer;

	readShaderCode(vertexPath, &vertex_buffer);
	const char* vShaderCode = vertex_buffer.c_str();

	readShaderCode(fragmentPath, &fragment_buffer);
	const char* fShaderCode = fragment_buffer.c_str();

	readShaderCode(geometryPath, &geometry_buffer);
	const char* gShaderCode = geometry_buffer.c_str();

	//Compiling
	uint32_t vertex, geometry, fragment;

	vertex = compileShader(GL_VERTEX_SHADER, vShaderCode);
	geometry = compileShader(GL_GEOMETRY_SHADER, gShaderCode);
	fragment = compileShader(GL_FRAGMENT_SHADER, fShaderCode);

	//Linking
	uint32_t shaders[] = { vertex, geometry, fragment };
	linkShader(shaders, 3);

	glDeleteShader(vertex);
	glDeleteShader(fragment);
	glDeleteShader(geometry);

}

std::shared_ptr<Shader> 
Shader::createComputeShader(const std::string& computePath)
{
	std::shared_ptr<Shader> result = std::make_shared<Shader>();

	std::string compute_buffer;

	result->readShaderCode(computePath, &compute_buffer);
	const char* cShaderCode = compute_buffer.c_str();

	uint32_t compute;

	compute = result->compileShader(GL_COMPUTE_SHADER, cShaderCode);

	result->linkShader(&compute, 1);

	glDeleteShader(compute);
	
	return result;
}

void
Shader::readShaderCode(const std::string& path, std::string* code)
{
	std::ifstream shaderFile;

	shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		shaderFile.open(path);
		std::stringstream shaderStream;

		shaderStream << shaderFile.rdbuf();

		shaderFile.close();

		*code = shaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		LOGGER::ERROR("ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ\n");
	}
}

uint32_t 
Shader::compileShader(GLenum shaderType, const std::string& shader_source)
{
	uint32_t shader;
	int32_t success;

	shader = glCreateShader(shaderType);
	const char* shader_source_c_str = shader_source.c_str();
	glShaderSource(shader, 1, &shader_source_c_str, NULL);
	glCompileShader(shader);

	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		int32_t length;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
		char* infoLog = (char*)malloc(sizeof(char) * length);
		glGetShaderInfoLog(shader, length, &length, infoLog);
		if (shaderType == GL_VERTEX_SHADER)
		{
			LOGGER::ERROR("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" + std::string(infoLog) + "\n");
		}
		else if (shaderType == GL_FRAGMENT_SHADER)
		{
			LOGGER::ERROR("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" + std::string(infoLog) + "\n");
		}
		else if (shaderType == GL_GEOMETRY_SHADER)
		{
			LOGGER::ERROR("ERROR::SHADER::GEOMETRY::COMPILATION_FAILED\n" + std::string(infoLog) + "\n");
		}
		else
		{
			LOGGER::ERROR("ERROR::SHADER::COMPILATION_FAILED\nUnknown shader type");
		}
		
		free(infoLog);
	}

	return shader;
}

void 
Shader::linkShader(const uint32_t* shaders, const uint32_t& num_shaders)
{
	int32_t success;

	_ID = glCreateProgram();
	for (uint32_t i = 0; i < num_shaders; ++i)
	{
		glAttachShader(_ID, shaders[i]);
	}
	glLinkProgram(_ID);

	glGetProgramiv(_ID, GL_LINK_STATUS, &success);
	if (!success)
	{
		int32_t length;
		glGetProgramiv(_ID, GL_INFO_LOG_LENGTH, &length);
		char* infoLog = (char*)malloc(sizeof(char) * length);
		glGetProgramInfoLog(_ID, length, &length, infoLog);
		LOGGER::ERROR("ERROR::SHADER::PROGRAM::LINKING_FAILED\n" + std::string(infoLog));
		free(infoLog);
	}
}

Shader::~Shader()
{
	glDeleteProgram(_ID);
}

void
Shader::bind()
{
	glUseProgram(_ID);
}

void
Shader::unbind()
{
	glUseProgram(0);
}

void
Shader::setInt(const std::string& name, const int& value)
{
	glUniform1i(glGetUniformLocation(_ID, name.c_str()), value);
}

void
Shader::setFloat(const std::string& name, const float& value)
{
	glUniform1f(glGetUniformLocation(_ID, name.c_str()), value);
}

void
Shader::setBool(const std::string& name, const bool& value)
{
	glUniform1i(glGetUniformLocation(_ID, name.c_str()), value);
}

void
Shader::setVec2(const std::string& name, const glm::vec2& value)
{
	glUniform2f(glGetUniformLocation(_ID, name.c_str()), value.x, value.y);
}

void
Shader::setVec3(const std::string& name, const glm::vec3& value)
{
	glUniform3f(glGetUniformLocation(_ID, name.c_str()), value.x, value.y, value.z);
}

void
Shader::setVec4(const std::string& name, const glm::vec4& value)
{
	glUniform4f(glGetUniformLocation(_ID, name.c_str()), value.x, value.y, value.z, value.w);
}

void
Shader::setMat4(const std::string&name, const glm::mat4& value, const bool& transpose)
{
	glUniformMatrix4fv(glGetUniformLocation(_ID, name.c_str()), 1, transpose, &value[0][0]);
}

void 
Shader::setMVP(const glm::mat4& M, const glm::mat4& V, const glm::mat4& P)
{
	setMat4("M", M);
	setMat4("V", V);
	setMat4("P", P);
}

void
Shader::setLight(const std::string& name, const Light& light)
{
	setVec3(name + ".ambient", light.ambient);
	setVec3(name + ".diffuse", light.diffuse);
	setVec3(name + ".specular", light.specular);
	setVec3(name + ".position", light.position);
}

void 
Shader::dispatch(const Texture& texture)
{
	bind();
	glBindImageTexture(0, texture.getID(), 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_RGBA32F);

	glDispatchCompute((GLuint)texture.getWidth(), (GLuint)texture.getHeight(), 1);

	glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);
}