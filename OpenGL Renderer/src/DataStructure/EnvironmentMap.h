#ifndef DATASTRUCTURE_ENVIRONMENTMAP_H
#define DATASTRUCTURE_ENVIRONMENTMAP_H

#include <glm/glm.hpp>
#include <DataStructure/Scene.h>
#include <DataStructure/Texture.h>
#include <DataStructure/FrameBuffer.h>
#include <Renderer/Camera.h>

class EnvironmentMap
{
public:
	/**
	*	\brief Create an empry environment map
	*/
	EnvironmentMap();

	/**
	*	\brief Create an environment map at the given position
	*	\param[in] position The position of the environment map
	*	\return The environment map
	*/
	static EnvironmentMap createObject(glm::vec3 position);

	/**
	*	\brief Destroys the environment map
	*	\param[in] object The environment map
	*/
	static void destroyObject(EnvironmentMap& object);

	/**
	*	\brief Renders the given scene onto the cube map
	*	\param[in] scene The scene to be rendered
	*	\param[in] shader The shader used to render the scene
	*/
	void render(Scene scene, Shader shader);

	/**
	*	\brief Get the cubemap texture
	*	\return The cube map
	*/
	inline Texture getCubeMap() {return _cube_map;}

private:
	Texture _cube_map; /**<< The texture cube map*/
	FrameBuffer _environment_map; /**<< The framebuffer used to render to the cubemap*/
	Camera _camera; /**<< The camera of the environment map used to the scene*/
};

#endif