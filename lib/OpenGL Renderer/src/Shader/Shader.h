#ifndef __OPENGLRENDERER_SHADER_SHADER_H
#define __OPENGLRENDERER_SHADER_SHADER_H

#include <glad/glad.h>

#include <string>
#include <memory>
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
	*/
	Shader(const std::string& vertexPath, const std::string& fragmentPath);

	/**
	*	\brief Create a Shader Object
	*	\param[in] vertexPath Path to the Vertex Shader
	*	\param[in] geometryPath Path to the Geometry Shader
	*	\param[in] fragmentPath Path to the Fragment Shader
	*/
	Shader(const std::string& vertexPath, const std::string& geometryPath, const std::string& fragmentPath);

	/**
	*	\brief Creats a Shader object
	*	\param[in] computePath The path to the Compute Shader
	*	\note: This function is used to create compute shaders 
	*/
	static std::shared_ptr<Shader> 
	createComputeShader(const std::string& computePath);

	/**
	*	\brief Destroys the object
	*	\param[in] The shader object
	*/
	~Shader();

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
	void setInt(const std::string& name, const int& value);

	/**
	*	\brief Set a uniform float
	*	\param[in] name The name of the uniform variable at the shader
	*	\param[in] value The value the variable should be initialized with
	*/
	void setFloat(const std::string& name, const float& value);

	/**
	*	\brief Set a uniform bool
	*	\param[in] name The name of the uniform variable at the shader
	*	\param[in] value The value the variable should be initialized with
	*/
	void setBool(const std::string& name, const bool& value);

	/**
	*	\brief Set a uniform Vector2
	*	\param[in] name The name of the uniform variable at the shader
	*	\param[in] value The value the variable should be initialized with
	*/
	void setVec2(const std::string& name, const glm::vec2& value);

	/**
	*	\brief Set a uniform Vector3
	*	\param[in] name The name of the uniform variable at the shader
	*	\param[in] value The value the variable should be initialized with
	*/
	void setVec3(const std::string& name, const glm::vec3& value);

	/**
	*	\brief Set a uniform Vector4
	*	\param[in] name The name of the uniform variable at the shader
	*	\param[in] value The value the variable should be initialized with
	*/
	void setVec4(const std::string& name, const glm::vec4& value);

	/**
	*	\brief Set a uniform Matrix4x4
	*	\param[in] name The name of the uniform variable at the shader
	*	\param[in] value The value the variable should be initialized with
	*/
	void setMat4(const std::string& name, const glm::mat4& value, const bool& transpose = GL_FALSE);

	/**
	*	\brief Set Model view and projection matrix
	*	\param[in] M The model matrix
	*	\param[in] V The view matrix
	*	\param[in] P The projection matrix
	*/
	void setMVP(const glm::mat4& M = glm::mat4(1), const glm::mat4& V = glm::mat4(1), const glm::mat4& P = glm::mat4(1));

	/**
	*	\brief Set the light for the next draw call
	*	\param[in] name The name of the light struct in the shader
	*	\param[in] light The light for the next draw call
	*/
	void setLight(const std::string& name, const Light& light);

	/**
	*	\brief Dispatch compute on the given texture
	*	\param[in] texture The texture to compute to
	*	\note: This should only be called if the shader is a compute shader 
	*/
	void dispatch(const Texture& texture);
private:

	/**
	*	\brief Reads shader code from disk
	*	\param[in] path The path to the shader file
	*	\param[out] code The output code
	*/
	void readShaderCode(const std::string& path, std::string* code);

	/**
	*	\brief Compiles the shader code
	*	\param[in] shaderType The type of the shader (Vertex, Fragment, Geometry)
	*	\param[in] shader_source The source code of the shader
	*	\return The handle of the shader 
	*/
	uint32_t compileShader(GLenum shaderType, const std::string& shader_soruce);

	/**
	*	\brief Links given shaders into a shader program
	*	\param[in] shaders An array with the shader handles
	*	\param[in] num_shaders The number of shaders to link
	*/
	void linkShader(const uint32_t* shaders, const uint32_t& num_shaders);

	uint32_t _ID; /**<< The internal OpenGL handle for the shader*/
};

#endif