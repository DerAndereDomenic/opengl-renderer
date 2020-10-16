#include <Shader/Shader.h>

Shader
Shader::createObject(const GLchar* vertexPath, const GLchar* fragmentPath)
{
	Shader result;
	//File reading
	std::string vertex_buffer, fragment_buffer;

	result.readShaderCode(vertexPath, &vertex_buffer);
	const char* vShaderCode = vertex_buffer.c_str();

	result.readShaderCode(fragmentPath, &fragment_buffer);
	const char* fShaderCode = fragment_buffer.c_str();

	//Compiling
	uint32_t vertex, fragment;
	
	vertex = result.compileShader(GL_VERTEX_SHADER, vShaderCode);
	fragment = result.compileShader(GL_FRAGMENT_SHADER, fShaderCode);

	//Linking
	uint32_t shaders[] = { vertex,fragment };
	result.linkShader(shaders, 2);

	glDeleteShader(vertex);
	glDeleteShader(fragment);

	return result;
}

Shader
Shader::createObject(const GLchar* vertexPath, const GLchar* geometryPath, const GLchar* fragmentPath)
{
	Shader result;
	//File reading
	std::string vertex_buffer, fragment_buffer, geometry_buffer;

	result.readShaderCode(vertexPath, &vertex_buffer);
	const char* vShaderCode = vertex_buffer.c_str();

	result.readShaderCode(fragmentPath, &fragment_buffer);
	const char* fShaderCode = fragment_buffer.c_str();

	result.readShaderCode(geometryPath, &geometry_buffer);
	const char* gShaderCode = geometry_buffer.c_str();

	//Compiling
	uint32_t vertex, geometry, fragment;

	vertex = result.compileShader(GL_VERTEX_SHADER, vShaderCode);
	geometry = result.compileShader(GL_GEOMETRY_SHADER, gShaderCode);
	fragment = result.compileShader(GL_FRAGMENT_SHADER, fShaderCode);

	//Linking
	uint32_t shaders[] = { vertex, geometry, fragment };
	result.linkShader(shaders, 3);

	glDeleteShader(vertex);
	glDeleteShader(fragment);
	glDeleteShader(geometry);

	return result;
}

void
Shader::readShaderCode(const GLchar* path, std::string* code)
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
		std::cerr << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}
}

uint32_t 
Shader::compileShader(GLenum shaderType, const char* shader_source)
{
	uint32_t shader;
	int32_t success;

	shader = glCreateShader(shaderType);
	glShaderSource(shader, 1, &shader_source, NULL);
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
			std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		}
		else if (shaderType == GL_FRAGMENT_SHADER)
		{
			std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
		}
		else if (shaderType == GL_GEOMETRY_SHADER)
		{
			std::cerr << "ERROR::SHADER::GEOMETRY::COMPILATION_FAILED\n" << infoLog << std::endl;
		}
		else
		{
			std::cerr << "ERROR::SHADER::COMPILATION_FAILED\n" << "Unknown shader type" << std::endl;
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
		std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
		free(infoLog);
	}
}

void
Shader::destroyObject(Shader& shader)
{
	glDeleteProgram(shader._ID);
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