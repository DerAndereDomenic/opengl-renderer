#ifndef __OPENGLRENDERER_RENDERER_CAMERA_H
#define __OPENGLRENDERER_RENDERER_CAMERA_H

#include <Renderer/RenderWindow.h>
#include <glm/glm.hpp>

/**
*	\brief A class to model a camera
*/
class Camera
{
public:
	/**
	*	\brief Create an empty Camera
	*/
	Camera() = default;

	/**
	*	\brief Create a camera object
	*	\param[in] window The camera the window should be bound to
	*	\param[in] near The near plane
	*	\param[in] far The far plane
	*	\return The camera object
	*/
	static Camera createObject(const RenderWindow& window, const float& near, const float& far);

	/**
	*	\brief Create a camera object
	*	\param[in] positon The position of the camera
	*	\param[in] fov The fov of the camera
	*	\param[in] aspect_ratio The apsect ratio of the screen
	*	\param[in] near The near plane
	*	\param[in] far The far plane
	*	\return The camera object
	*/
	static Camera createObject(const glm::vec3& position, const float& fov, const float& aspect_ratio, const float& near, const float& far);

	/**
	*	\brief Destroys the given camera
	*	\param[in] camera The camera to be destroyed
	*/
	static void destroyObject(Camera& camera);

	/**
	*	\brief Processes the input of button presses, mouse movement and window resize
	*	\param[in] deltaTime The time between two frames
	*/
	void processInput(const float& deltaTime);

	/**
	*	\brief Change view direction based on pitch and yaw
	*	\param[in] pitch The pitch angle
	*	\param[in] yaw The yaw angle
	*/
	void updateDirection(const float& pitch, const float& yaw);

	/**
	*	\brief The Projection Matrix of the camera
	*	\return The Projection Matrix
	*/
	inline glm::mat4 getProjection() const { return _projection; }

	/**
	*	\brief The View Matrix of the camera
	*	\return the View Matrix
	*/
	inline glm::mat4 getView() const { return _view; }

	/**
	*	\brief The Position of the camera
	*	\return The Position
	*/
	inline glm::vec3 getPosition() const { return _cameraPos; }

	/**
	*	\brief The front facing vector of the camera
	*	\return The front facing vector
	*/
	inline glm::vec3 getFront() const { return _cameraFront; }
private:
	/**
	*	\brief Processes the mouse movement
	*	\param[in] xpos The X Position of the mouse
	*	\param[in] ypos The Y Position of the mouse
	*/
	void processMouse(const float& xpos, const float& ypos);

	bool _firstMouse = true;								/**<< Check if the mouse is processed for the first time (special case)*/
	float _lastX = 0.0f;									/**<< Last X position of the mouse*/
	float _lastY = 0.0f;									/**<< Last Y position of the mouse*/
	float _yaw = -90.0f;									/**<< Initial yaw angle of the camera*/
	float _pitch = 0.0f;									/**<< Initial pitch angle of the camera*/

	float _sensitivity = 0.25f;								/**<< The mouse sensitivity*/

	float _near = 0.0f;										/**<< The near plane*/
	float _far = 0.0f;										/**<< The far plane*/

	RenderWindow _window = {};								/**<< The window the camera is operating at*/
	glm::mat4 _view = glm::mat4(1);							/**<< The view matrix*/
	glm::mat4 _projection = glm::mat4(1);					/**<< The projection matrix*/
	glm::vec3 _cameraPos = glm::vec3(0.0f, 0.0f, 0.0f);		/**<< The initial camera position*/
	glm::vec3 _cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);	/**<< The initial camera front*/
	glm::vec3 _cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);		/**<< The direction that defines the y-axis of the camera*/

};

#endif