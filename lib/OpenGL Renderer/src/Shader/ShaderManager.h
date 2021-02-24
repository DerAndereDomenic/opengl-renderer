#ifndef __OPENGLRENDERER_SHADER_SHADERMANAGER_H
#define __OPENGLRENDERER_SHADER_SHADERMANAGER_H

#include <Shader/Shader.h>
#include <unordered_map>
#include <string>
#include <OpenGLRendererConfig.h>

class ShaderManager
{
	public:
		/**
		*	\brief Gets a pointer to a ShaderManager instance (Singleton)
		*	\return The object
		*/
		static ShaderManager*
		instance();

		/**
		*	\brief Destroys the object and all used shader
		*	\param[in] manager The object to be destroyed
		*/
		static void
		destroyObject(ShaderManager& manager);

		/**
		*	\brief Adds a shader to the manager
		*	\param[in] name The name of the shader (Has to be like the filename)
		*	\param[in] geoemtry If this shader does also contain a geometry shader
		*/
		void
		addShader(const std::string& name, const bool geometry = false);

		/**
		*	\brief Removes the shader from the manager (destroys the shader object)
		*	\param[in] name The name of the shader
		*	\note: The underlying shader object is destroyed. Binding the shader via references is no longer possible.
		*/
		void
		removeShader(const std::string& name);

		/**
		* 	\brief Adds a compute shader to the manager
		*	\param[in] name The name of the shader (Has to be like the filename)
		*/ 
		void 
		addComputeShader(const std::string& name);

		/**
		*	\brief Get the shader corresponding to the name
		*	\param[in] name The name of the shader
		*	\return The Shader with the specified name
		*/
		Shader
		getShader(const std::string& name);

		/**
		*	\brief Sets a new path to the Shader files
		*	\param[in] path Path to the shader files
		*/
		void
		setShaderDir(const std::string& path);
	private:
		static ShaderManager* _instance;						/**<< The ShaderManager instance*/

		ShaderManager() = default;								/**<< Make constructor private*/

		ShaderManager(const ShaderManager&);					/**<< Make constructor private*/

		std::unordered_map<std::string, Shader> _shader;		/**<< The container holding the shaders*/

		std::string SHADER_DIRECTORY = SHADER_SOURCE_PATH; /**<< The path to the shader files*/
};

#endif
