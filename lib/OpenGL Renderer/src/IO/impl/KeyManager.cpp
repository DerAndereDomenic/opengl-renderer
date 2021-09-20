#include <IO/KeyManager.h>

KeyManager* KeyManager::_instance = new KeyManager;

bool
KeyManager::isKeyDownImpl(const uint32_t& key)
{
	return glfwGetKey(_window.getWindow(), key) == GLFW_PRESS;
}

bool
KeyManager::leftClickedImpl()
{
	int32_t state = glfwGetMouseButton(_window.getWindow(), GLFW_MOUSE_BUTTON_LEFT);
	return state == GLFW_PRESS;
}

bool
KeyManager::rightClickedImpl()
{
	int32_t state = glfwGetMouseButton(_window.getWindow(), GLFW_MOUSE_BUTTON_RIGHT);
	return state == GLFW_PRESS;
}

void
KeyManager::setupImpl(const RenderWindow& window)
{
	_window = window;
}