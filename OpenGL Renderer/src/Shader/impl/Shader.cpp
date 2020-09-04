#include <Shader/Shader.h>

Shader
Shader::createObject(const GLchar* vertexPath, const GLchar* fragmentPath)
{
	Shader result;
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;

	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);
		std::stringstream vShaderStream, fShaderStream;

		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();

		vShaderFile.close();
		fShaderFile.close();

		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cerr << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}
	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();

	//Compiling
	unsigned int vertex, fragment;
	
	vertex = result.compileShader(GL_VERTEX_SHADER, vShaderCode);
	fragment = result.compileShader(GL_FRAGMENT_SHADER, fShaderCode);

	//Linking
	unsigned int shaders[] = { vertex,fragment };
	result.linkShader(shaders, 2);

	glDeleteShader(vertex);
	glDeleteShader(fragment);

	return result;
}

unsigned int 
Shader::compileShader(GLenum shaderType, const char* shader_source)
{
	unsigned int shader;
	int success;

	shader = glCreateShader(shaderType);
	glShaderSource(shader, 1, &shader_source, NULL);
	glCompileShader(shader);

	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		int length;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
		char* infoLog = (char*)malloc(sizeof(char) * length);
		glGetShaderInfoLog(shader, length, &length, infoLog);
		std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		free(infoLog);
	}

	return shader;
}

void 
Shader::linkShader(unsigned int* shaders, unsigned int num_shaders)
{
	int success;

	_ID = glCreateProgram();
	for (unsigned int i = 0; i < num_shaders; ++i)
	{
		glAttachShader(_ID, shaders[i]);
	}
	glLinkProgram(_ID);

	glGetProgramiv(_ID, GL_LINK_STATUS, &success);
	if (!success)
	{
		int length;
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
Shader::setInt(const std::string& name, int value)
{
	glUniform1i(glGetUniformLocation(_ID, name.c_str()), value);
}

void
Shader::setFloat(const std::string& name, float value)
{
	glUniform1f(glGetUniformLocation(_ID, name.c_str()), value);
}

void
Shader::setBool(const std::string& name, bool value)
{
	glUniform1i(glGetUniformLocation(_ID, name.c_str()), value);
}

void
Shader::setVec2(const std::string& name, glm::vec2 value)
{
	glUniform2f(glGetUniformLocation(_ID, name.c_str()), value.x, value.y);
}

void
Shader::setVec3(const std::string& name, glm::vec3 value)
{
	glUniform3f(glGetUniformLocation(_ID, name.c_str()), value.x, value.y, value.z);
}

void
Shader::setVec4(const std::string& name, glm::vec4 value)
{
	glUniform4f(glGetUniformLocation(_ID, name.c_str()), value.x, value.y, value.z, value.w);
}

void
Shader::setMat4(const std::string&name, glm::mat4 value, bool transpose)
{
	glUniformMatrix4fv(glGetUniformLocation(_ID, name.c_str()), 1, transpose, &value[0][0]);
}

void 
Shader::setMVP(glm::mat4 M, glm::mat4 V, glm::mat4 P)
{
	setMat4("M", M);
	setMat4("V", V);
	setMat4("P", P);
}

void
Shader::setLight(const std::string& name, Light light)
{
	setVec3(name + ".ambient", light.ambient);
	setVec3(name + ".diffuse", light.diffuse);
	setVec3(name + ".specular", light.specular);
	setVec3(name + ".position", light.position);
}