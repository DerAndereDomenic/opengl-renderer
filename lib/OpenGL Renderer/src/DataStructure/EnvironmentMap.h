#ifndef __OPENGLRENDERER_DATASTRUCTURE_ENVIRONMENTMAP_H
#define __OPENGLRENDERER_DATASTRUCTURE_ENVIRONMENTMAP_H

#include <glm/glm.hpp>
#include <DataStructure/Scene.h>
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
	*	\param[in] width The width
	*	\param[in] height The height
	*/
	EnvironmentMap(const glm::vec3& position, const uint32_t& width = 1024, const uint32_t& height = 1024);

	/**
	*	\brief Renders the given scene onto the cube map
	*	\param[in] scene The scene to be rendered
	*	\param[in] skybox An optional skybox
	*	\param[in] shader The shader used to render the scene
	*/
	void renderTo(Scene* scene, EnvironmentMap* skybox, std::shared_ptr<Shader>& shader);

	/**
	*	\brief Renders the cubemap as a skybox
	*	\param[in] camera The fps camera
	*/
	void renderSkybox(Camera* camera);

	/**
	*	\brief Set the position of the environment map
	*	\param[in] position The new position
	*/
	void setPosition(const glm::vec3& position);

	/**
	*	\brief Set a cubemap texture
	*	\param[in] cube_map The cube map texture
	*/
	void setCubeMap(std::shared_ptr<Texture> cube_map);

	/**
	*	\brief Get the cubemap texture
	*	\return The cube map
	*/
	inline std::shared_ptr<Texture> getCubeMap() {return _cube_map;}

private:
	std::shared_ptr<Texture> _cube_map = {};				/**<< The texture cube map*/
	std::shared_ptr<FrameBuffer> _environment_map = {};		/**<< The framebuffer used to render to the cubemap*/
	std::shared_ptr<Camera> _camera = {};					/**<< The camera of the environment map used to the scene*/
	uint32_t _width, _height;								/**<< The resolution */
	std::shared_ptr<Mesh> _cube;							/**<< A generic cube Mesh to render the skybox*/
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