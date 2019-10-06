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

	/**
	*	\brief Set the material of the objects in the next draw call
	*	\param[in] name The name of the material struct in the shader
	*	\param[in] material The material for the next draw call
	*/
	void setMaterial(const std::string& name, Material material);

	/**
	*	\brief Set the material map of the objects in the next draw call
	*	\param[in] name The name of the material map struct in the shader
	*	\param[in] material The material map for the next draw call
	*/
	void setMaterial(const std::string& name, MaterialMap material);

	/**
	*	\brief Set the light for the next draw call
	*	\param[in] name The name of the light struct in the shader
	*	\param[in] light The light for the next draw call
	*/
	void setLight(const std::string& name, Light light);
private:
	unsigned int _ID; /**<< The internal OpenGL handle for the shader*/
};

#endif