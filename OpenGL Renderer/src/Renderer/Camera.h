#ifndef RENDERER_CAMERA_H
#define RENDERER_CAMERA_H

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
	*	\return The camera object
	*/
	static Camera createObject(RenderWindow window);

	/**
	*	\brief Destroys the given camera
	*	\param[in] camera The camera to be destroyed
	*/
	static void destroyObject(Camera& camera);

	/**
	*	\brief Processes the input of button presses and mouse movement
	*	\param[in] deltaTime The time between two frames
	*/
	void processInput(float deltaTime);

	/**
	*	\brief The Projection Matrix of the camera
	*	\return The Projection Matrix
	*/
	inline glm::mat4 getProjection() { return _projection; }

	/**
	*	\brief The View Matrix of the camera
	*	\return the View Matrix
	*/
	inline glm::mat4 getView() { return _view; }

	/**
	*	\brief The Position of the camera
	*	\return The Position
	*/
	inline glm::vec3 getPosition() { return _cameraPos; }

	/**
	*	\brief The front facing vector of the camera
	*	\return The front facing vector
	*/
	inline glm::vec3 getFront() { return _cameraFront; }
private:
	/**
	*	\brief Processes the mouse movement
	*	\param[in] xpos The X Position of the mouse
	*	\param[in] ypos The Y Position of the mouse
	*/
	void processMouse(float xpos, float ypos);

	bool _firstMouse = true; /**<< Check if the mouse is processed for the first time (special case)*/
	float _lastX; /**<< Last X position of the mouse*/
	float _lastY; /**<< Last Y position of the mouse*/
	float _yaw = -90.0f; /**<< Initial yaw angle of the camera*/
	float _pitch = 0.0f; /**<< Initial pitch angle of the camera*/

	const float _sensitivity = 0.25f; /**<< The mouse sensitivity*/

	RenderWindow _window; /**<< The window the camera is operating at*/
	glm::mat4 _view; /**<< The view matrix*/
	glm::mat4 _projection; /**<< The projection matrix*/
	glm::vec3 _cameraPos = glm::vec3(0.0f, 0.0f, 0.0f); /**<< The initial camera position*/
	glm::vec3 _cameraFront = glm::vec3(0.0f, 0.0f, -1.0f); /**<< The initial camera front*/
	glm::vec3 _cameraUp = glm::vec3(0.0f, 1.0f, 0.0f); /**<< The direction that defines the y-axis of the camera*/

};

#endif