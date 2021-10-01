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
	*	\param[in] scene_shader The shader the scene should be rendered with
	*	\param[in] skybox_shader The shader the skybox should be rendered with
	*/
	void renderTo(Scene* scene, std::shared_ptr<Shader>& scene_shader, std::shared_ptr<Shader>& skybox_shader);

	/**
	*	\brief Renders the cubemap as a skybox
	*	\param[in] camera The fps camera
	*	\param[in] skybox_shader The shader used to render the skybox
	*/
	void renderAsSkybox(Camera* camera, std::shared_ptr<Shader>& skybox_shader);

	/**
	*	\brief Renders the cubemap as a skybox
	*	\param[in] view The view matrix
	*	\param[in] projection The projection matrix
	*	\param[in] skybox_shader The shader used to render the skybox
	*/
	void renderAsSkybox(const glm::mat4& view, const glm::mat4& projection, std::shared_ptr<Shader>& skybox_shader);

	/**
	*	\brief Renders the given scene onto the cube map
	*	\param[in] prefilter_shader The prefilter shader
	*/
	void prefilter(std::shared_ptr<Shader> prefilter_shader);

	/**
	*	\brief Set the position of the environment map
	*	\param[in] position The new position
	*/
	void setPosition(const glm::vec3& position);

	/**
	*	\brief Set a cubemap texture
	*	\param[in] skybox An optional skybox
	*/
	void setSkybox(std::shared_ptr<EnvironmentMap>& skybox);

	/**
	*	\brief Set the cube map
	*	\param[in] cube_map The cube map
	*/
	void setCubeMap(std::shared_ptr<Texture>& cube_map);

	/**
	*	\brief Get the cubemap texture
	*	\return The cube map
	*/
	inline std::shared_ptr<Texture> getCubeMap() {return _cube_map;}

private:
	std::shared_ptr<Texture> _cube_map = {};				/**<< The texture cube map*/
	std::shared_ptr<FrameBuffer> _environment_map = {};		/**<< The framebuffer used to render to the cubemap*/
	std::shared_ptr<EnvironmentMap> _skybox;						/**<< The skybox */
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