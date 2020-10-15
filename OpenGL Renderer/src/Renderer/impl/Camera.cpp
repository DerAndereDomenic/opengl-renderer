#include <Renderer/Camera.h>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <IO/KeyManager.h>

Camera
Camera::createObject(const RenderWindow& window, const float& near, const float& far)
{
	Camera result;
	result._near = near;
	result._far = far;
	result._window = window;
	result._projection = glm::perspective(glm::radians(90.0f), window.getAspectRatio(), near, far);
	result._view = glm::lookAt(result._cameraPos, result._cameraPos + result._cameraFront, result._cameraUp);
	return result;
}

Camera
Camera::createObject(const glm::vec3& position, const float& fov, const float& aspect_ratio, const float& near, const float& far)
{
	Camera result;
	result._near = near;
	result._far = far;
	result._cameraPos = position;
	result._cameraUp = -result._cameraUp;
	result._projection = glm::perspective(glm::radians(fov), aspect_ratio, near, far);
	result._view = glm::lookAt(result._cameraPos, result._cameraPos + result._cameraFront, result._cameraUp);
	return result;
}

void
Camera::destroyObject(Camera& camera)
{
	camera._firstMouse = true; 
	camera._lastX; 
	camera._lastY; 
	camera._yaw = -90.0f; 
	camera._pitch = 0.0f; 

	camera._cameraPos = glm::vec3(8.0f, 66.0f, 8.0f); 
	camera._cameraFront = glm::vec3(0.0f, 0.0f, -1.0f); 
	camera._cameraUp = glm::vec3(0.0f, 1.0f, 0.0f); 

	camera._near = 0.0f;
	camera._far = 0.0f;
}

void
Camera::processInput(const float& deltaTime)
{

	double xpos, ypos;
	glfwGetCursorPos(_window.getWindow(), &xpos, &ypos);

	processMouse(xpos, ypos);

	float cameraSpeed = 4.0f*deltaTime;
	if (KeyManager::instance()->isKeyDown(GLFW_KEY_LEFT_SHIFT))
		cameraSpeed *= 8.0f;
	if (KeyManager::instance()->isKeyDown(GLFW_KEY_W))
		_cameraPos += cameraSpeed * _cameraFront;
	if (KeyManager::instance()->isKeyDown(GLFW_KEY_S))
		_cameraPos -= cameraSpeed * _cameraFront;
	if (KeyManager::instance()->isKeyDown(GLFW_KEY_A))
		_cameraPos -= glm::normalize(glm::cross(_cameraFront, _cameraUp)) * cameraSpeed;
	if (KeyManager::instance()->isKeyDown(GLFW_KEY_D))
		_cameraPos += glm::normalize(glm::cross(_cameraFront, _cameraUp)) * cameraSpeed;
	if (KeyManager::instance()->isKeyDown(GLFW_KEY_SPACE))
		_cameraPos += cameraSpeed * _cameraUp;
	if (KeyManager::instance()->isKeyDown(GLFW_KEY_LEFT_CONTROL))
		_cameraPos -= cameraSpeed * _cameraUp;
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
