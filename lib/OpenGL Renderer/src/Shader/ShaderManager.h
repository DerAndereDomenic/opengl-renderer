#ifndef __OPENGLRENDERER_SHADER_SHADERMANAGER_H
#define __OPENGLRENDERER_SHADER_SHADERMANAGER_H

#include <Shader/Shader.h>
#include <unordered_map>
#include <string>
#include <memory>

class ShaderManager
{
	public:
		/**
		*	\brief Adds a shader to the manager
		*	\param[in] name The name of the shader (Has to be like the filename)
		*	\param[in] geoemtry If this shader does also contain a geometry shader
		*/
		inline static void
		addShader(const std::string& name, const bool geometry = false) { _instance->addShaderImpl(name, geometry); }

		/**
		*	\brief Removes the shader from the manager (destroys the shader object)
		*	\param[in] name The name of the shader
		*	\note: The underlying shader object is destroyed. Binding the shader via references is no longer possible.
		*/
		inline static void
		removeShader(const std::string& name) { _instance->removeShaderImpl(name); }

		/**
		* 	\brief Adds a compute shader to the manager
		*	\param[in] name The name of the shader (Has to be like the filename)
		*/ 
		inline static void
		addComputeShader(const std::string& name) { _instance->addComputeShaderImpl(name); }

		/**
		*	\brief Get the shader corresponding to the name
		*	\param[in] name The name of the shader
		*	\return The Shader with the specified name
		*/
		inline static std::shared_ptr<Shader>
		getShader(const std::string& name) { return _instance->getShaderImpl(name); }

		/**
		*	\brief Sets a new path to the Shader files
		*	\param[in] path Path to the shader files
		*/
		inline static void
		setShaderDir(const std::string& path) { _instance->setShaderDir(path); }
	private:
		void addShaderImpl(const std::string& name, const bool geometry = false);
		void removeShaderImpl(const std::string& name);
		void addComputeShaderImpl(const std::string& name);
		std::shared_ptr<Shader> getShaderImpl(const std::string& name);
		void setShaderDirImpl(const std::string& path);


		static ShaderManager* _instance;										/**<< The ShaderManager instance*/
		ShaderManager() = default;												/**<< Make constructor private*/
		ShaderManager(const ShaderManager&);									/**<< Make constructor private*/

		std::unordered_map<std::string, std::shared_ptr<Shader>> _shader;		/**<< The container holding the shaders*/

		std::string SHADER_DIRECTORY = "lib/OpenGL Renderer/src/Shader/GLShaders/";					/**<< The path to the shader files*/
};

#endif
