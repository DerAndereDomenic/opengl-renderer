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
	*	\return A skybox
	*/
	static Skybox createObject(std::shared_ptr<Texture> cubemap);

	/**
	*	\brief Destroys the skybox and it's texture
	*/
	static void destroyObject(Skybox& skybox);

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
	Mesh _cube;							/**<< A generic cube Mesh to render the skybox*/
	std::shared_ptr<Texture> _cubemap;	/**<< The texture of the skybox*/
};

#endif