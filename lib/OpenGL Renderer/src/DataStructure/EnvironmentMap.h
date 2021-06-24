#ifndef __OPENGLRENDERER_DATASTRUCTURE_ENVIRONMENTMAP_H
#define __OPENGLRENDERER_DATASTRUCTURE_ENVIRONMENTMAP_H

#include <glm/glm.hpp>
#include <DataStructure/Scene.h>
#include <DataStructure/Skybox.h>
#include <OpenGLObjects/Texture.h>
#include <OpenGLObjects/FrameBuffer.h>
#include <Renderer/Camera.h>
#include <memory>

struct ViewAngle
{
	float pitch;
	float yaw;
};

class EnvironmentMap
{
public:
	/**
	*	\brief Create an empry environment map
	*/
	EnvironmentMap() = default;

	/**
	*	\brief Create an environment map at the given position
	*	\param[in] position The position of the environment map
	*/
	EnvironmentMap(glm::vec3 position);

	/**
	*	\brief Renders the given scene onto the cube map
	*	\param[in] scene The scene to be rendered
	*	\param[in] shader The shader used to render the scene
	*/
	void render(Scene scene, Skybox skybox, std::shared_ptr<Shader> shader);

	/**
	*	\brief Get the cubemap texture
	*	\return The cube map
	*/
	inline std::shared_ptr<Texture> getCubeMap() {return _cube_map;}

private:
	std::shared_ptr<Texture> _cube_map = {};				/**<< The texture cube map*/
	std::shared_ptr<FrameBuffer> _environment_map = {};		/**<< The framebuffer used to render to the cubemap*/
	std::shared_ptr<Camera> _camera = {};					/**<< The camera of the environment map used to the scene*/
	ViewAngle angles[6] =
	{
		{0,0},
		{0,180},
		{90,-90},
		{-90,-90},
		{0,90},
		{0,-90}

	};														/**<< An array to easily store pitch and yaw angles*/
};

#endif