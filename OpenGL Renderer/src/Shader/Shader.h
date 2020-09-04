#ifndef SHADER_SHADER_H
#define SHADER_SHADER_H

#include <GL/glew.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm/glm.hpp>
#include <DataStructure/Light.h>
#include <DataStructure/Material.h>

/**
*	\brief Class to model an OpenGL Shader
*/
class Shader
{
public:
	/**
	*	\brief Creates an empty Shader object
	*/
	Shader() = default;

	/**
	*	\brief Create a Shader Object
	*	\param[in] vertexPath Path to the Vertex Shader
	*	\param[in] fragmentPath Path to the Fragment Shader
	*	\return The compiled and linked Shader
	*/
	static Shader createObject(const GLchar* vertexPath, const GLchar* fragmentPath);

	/**
	*	\brief Destroys the object
	*	\param[in] The shader object
	*/
	static void destroyObject(Shader& shader);

	/**
	*	\brief Bind the shader
	*/
	void bind();

	/**
	*	\brief Unbind the shader (bind 0)
	*/
	void unbind();

	/**
	*	\brief Set a uniform int
	*	\param[in] name The name of the uniform variable at the shader
	*	\param[in] value The value the variable should be initialized with
	*/
	void setInt(const std::string& name, int value);

	/**
	*	\brief Set a uniform float
	*	\param[in] name The name of the uniform variable at the shader
	*	\param[in] value The value the variable should be initialized with
	*/
	void setFloat(const std::string& name, float value);

	/**
	*	\brief Set a uniform bool
	*	\param[in] name The name of the uniform variable at the shader
	*	\param[in] value The value the variable should be initialized with
	*/
	void setBool(const std::string& name, bool value);

	/**
	*	\brief Set a uniform Vector2
	*	\param[in] name The name of the uniform variable at the shader
	*	\param[in] value The value the variable should be initialized with
	*/
	void setVec2(const std::string& name, glm::vec2 value);

	/**
	*	\brief Set a uniform Vector3
	*	\param[in] name The name of the uniform variable at the shader
	*	\param[in] value The value the variable should be initialized with
	*/
	void setVec3(const std::string& name, glm::vec3 value);

	/**
	*	\brief Set a uniform Vector4
	*	\param[in] name The name of the uniform variable at the shader
	*	\param[in] value The value the variable should be initialized with
	*/
	void setVec4(const std::string& name, glm::vec4 value);

	/**
	*	\brief Set a uniform Matrix4x4
	*	\param[in] name The name of the uniform variable at the shader
	*	\param[in] value The value the variable should be initialized with
	*/
	void setMat4(const std::string& name, glm::mat4 value, bool transpose = GL_FALSE);

	/**
	*	\brief Set Model view and projection matrix
	*	\param[in] M The model matrix
	*	\param[in] V The view matrix
	*	\param[in] P The projection matrix
	*/
	void setMVP(glm::mat4 M = glm::mat4(1), glm::mat4 V = glm::mat4(1), glm::mat4 P = glm::mat4(1));

	/**
	*	\brief Set the light for the next draw call
	*	\param[in] name The name of the light struct in the shader
	*	\param[in] light The light for the next draw call
	*/
	void setLight(const std::string& name, Light light);
private:

	/**
	*	\brief Reads shader code from disk
	*	\param[in] path The path to the shader file
	*	\return The source code of the shader as c-String
	*/
	const char* readShaderCode(const GLchar* path);

	/**
	*	\brief Compiles the shader code
	*	\param[in] shaderType The type of the shader (Vertex, Fragment, Geometry)
	*	\param[in] shader_source The source code of the shader
	*	\return The handle of the shader 
	*/
	unsigned int compileShader(GLenum shaderType, const char* shader_source);

	/**
	*	\brief Links given shaders into a shader program
	*	\param[in] shaders An array with the shader handles
	*	\param[in] num_shaders The number of shaders to link
	*/
	void linkShader(unsigned int* shaders, unsigned int num_shaders);

	unsigned int _ID; /**<< The internal OpenGL handle for the shader*/
};

#endif