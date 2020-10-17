#ifndef __OPENGLRENDERER_DATASTRUCTURE_SKYBOX_H
#define __OPENGLRENDERER_DATASTRUCTURE_SKYBOX_H

#include <DataStructure/Mesh.h>
#include <OpenGLObjects/Texture.h>
#include <Shader/Shader.h>
#include <Renderer/Camera.h>

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
	static Skybox createObject(Texture cubemap);

	/**
	*	\brief Destroys the skybox and it's texture
	*/
	static void destroyObject(Skybox& skybox);

	/**
	*	\brief Renders the skybox to the given camera
	*	\param[in] camera The camera class
	*/
	void render(Camera camera);

private:
	Mesh _cube; /**<< A generic cube Mesh to render the skybox*/
	Texture _cubemap; /**<< The texture of the skybox*/
};

#endif