#ifndef __OPENGLRENDERER_DATASTRUCTURE_SKYBOX_H
#define __OPENGLRENDERER_DATASTRUCTURE_SKYBOX_H

#include <DataStructure/Mesh.h>
#include <OpenGLObjects/Texture.h>
#include <Shader/Shader.h>
#include <Renderer/Camera.h>
#include <memory>

class Skybox
{
public:
	/**
	*	\brief Creates an empty skybox
	*/
	Skybox() = default;

	/**
	*	\brief Create a skybox with the given texture
	*/
	Skybox(std::shared_ptr<Texture> cubemap);

	/**
	*	\brief Renders the skybox to the given camera
	*	\param[in] camera The camera class
	*/
	void render(std::shared_ptr<Camera> camera);

	/**
	*	\brief Renders the skybox to the given camera
	*	\param[in] view The view matrix
	*	\param[in] projection The projection matrix
	*/
	void render(const glm::mat4& view, const glm::mat4& projection);

	/**
	*	\brief Get the cubemap texture.
	*	\return The underlying cubemap texture
	*/
	inline std::shared_ptr<Texture> getCubemap() { return _cubemap; }
private:
	std::shared_ptr<Mesh> _cube;							/**<< A generic cube Mesh to render the skybox*/
	std::shared_ptr<Texture> _cubemap;	/**<< The texture of the skybox*/
};

#endif