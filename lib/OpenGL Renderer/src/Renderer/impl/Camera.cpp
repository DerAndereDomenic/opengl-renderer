#include <Renderer/Camera.h>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <IO/KeyManager.h>

Camera::Camera(const float& aspect_ratio, const float& near, const float& far)
{
	_near = near;
	_far = far;
	_projection = glm::perspective(glm::radians(90.0f), aspect_ratio, near, far);
	_view = glm::lookAt(_cameraPos, _cameraPos + _cameraFront, _cameraUp);
}

Camera::Camera(const glm::vec3& position, const float& fov, const float& aspect_ratio, const float& near, const float& far)
{
	_near = near;
	_far = far;
	_cameraPos = position;
	_cameraUp = -_cameraUp;
	_projection = glm::perspective(glm::radians(fov), aspect_ratio, near, far);
	_view = glm::lookAt(_cameraPos, _cameraPos + _cameraFront, _cameraUp);
}

Camera::~Camera()
{
	_firstMouse = true; 
	_lastX; 
	_lastY; 
	_yaw = -90.0f; 
	_pitch = 0.0f; 

	_cameraPos = glm::vec3(8.0f, 66.0f, 8.0f); 
	_cameraFront = glm::vec3(0.0f, 0.0f, -1.0f); 
	_cameraUp = glm::vec3(0.0f, 1.0f, 0.0f); 

	_near = 0.0f;
	_far = 0.0f;
}

void
Camera::processInput(const float& deltaTime, const double& xpos, const double& ypos)
{
	float cameraSpeed = 4.0f*deltaTime;
	if (KeyManager::isKeyDown(GLFW_KEY_LEFT_SHIFT))
		cameraSpeed *= 8.0f;
	if (KeyManager::isKeyDown(GLFW_KEY_W))
		_cameraPos += cameraSpeed * _cameraFront;
	if (KeyManager::isKeyDown(GLFW_KEY_S))
		_cameraPos -= cameraSpeed * _cameraFront;
	if (KeyManager::isKeyDown(GLFW_KEY_A))
		_cameraPos -= glm::normalize(glm::cross(_cameraFront, _cameraUp)) * cameraSpeed;
	if (KeyManager::isKeyDown(GLFW_KEY_D))
		_cameraPos += glm::normalize(glm::cross(_cameraFront, _cameraUp)) * cameraSpeed;
	if (KeyManager::isKeyDown(GLFW_KEY_SPACE))
		_cameraPos += cameraSpeed * _cameraUp;
	if (KeyManager::isKeyDown(GLFW_KEY_LEFT_CONTROL))
		_cameraPos -= cameraSpeed * _cameraUp;


	processMouse(xpos, ypos);
	//if (_window.updateSize())
	//{
	//	_projection = glm::perspective(glm::radians(90.0f), _window.getAspectRatio(), _near, _far);
	//}
}

void 
Camera::updateDirection(const float& pitch, const float& yaw)
{

	_pitch = pitch;
	_yaw = yaw;

	glm::vec3 front;
	front.x = cos(glm::radians(_yaw)) * cos(glm::radians(_pitch));
	front.y = sin(glm::radians(_pitch));
	front.z = sin(glm::radians(_yaw)) * cos(glm::radians(_pitch));
	_cameraFront = glm::normalize(front);
	//std::cout << _cameraFront.x << ", " << _cameraFront.y << ", " << _cameraFront.z << std::endl;
	_view = glm::lookAt(_cameraPos, _cameraPos + _cameraFront, _cameraUp);
}

void
Camera::teleport(const glm::vec3& position)
{
	_cameraPos = position; 
	_view = glm::lookAt(_cameraPos, _cameraPos + _cameraFront, _cameraUp);
}

void
Camera::processMouse(const float& xpos, const float& ypos)
{
	if (_firstMouse)
	{
		_lastX = xpos;
		_lastY = ypos;
		_firstMouse = false;
	}

	float xoffset = xpos - _lastX;
	float yoffset = _lastY - ypos;
	_lastX = xpos;
	_lastY = ypos;

	xoffset *= _sensitivity;
	yoffset *= _sensitivity;

	_yaw += xoffset;
	_pitch += yoffset;

	if (_pitch > 89.0f)
		_pitch = 89.0f;
	if (_pitch < -89.0f)
		_pitch = -89.0f;

	updateDirection(_pitch, _yaw);

}
