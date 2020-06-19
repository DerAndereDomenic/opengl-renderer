#ifndef SHADER_SHADERMANAGER_H
#define SHADER_SHADERMANAGER_H

#include <Shader/Shader.h>
#include <unordered_map>

class ShaderManager
{
	public:
		/**
		*	\brief Default constructor
		*/
		ShaderManager() = default;

		/**
		*	\brief Creates a Shader Manager object
		*	\return The object
		*/
		static ShaderManager();
		createObject();

		/**
		*	\brief Destroys the object and all used shader
		*	\param[in] manager The object to be destroyed
		*/
		static void
		destroyObject(ShaderManager& manager);

		/**
		*	\brief Adds a shader to the manager
		*	\param[in] name The name of the shader (Has to be like the filename)
		*/
		void
		addShader(const std::string& name);

		/**
		*	\brief Get the shader corresponding to the name
		*	\param[in] name The name of the shader
		*	\return The Shader with the specified name
		*/
		Shader
		getShader(const std::string& name);
	private:
		std::unordererd_map<std::string, Shader> _shader;	/**<< The container holding the shaders*/
};

#endif