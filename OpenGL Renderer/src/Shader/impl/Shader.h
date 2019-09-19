#ifndef SHADER_SHADER_H
#define SHADER_SHADER_H

#include <GL/glew.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm/glm.hpp>

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
	void setMat4(const std::string& name, glm::mat4 value, bool transpose);
private:
	unsigned int _ID; /**<< The internal OpenGL handle for the shader*/
};

#endif