#include <IO/KeyManager.h>

KeyManager* KeyManager::_instance = 0;

KeyManager*
KeyManager::instance()
{
	if (_instance == nullptr)
	{
		_instance = new KeyManager();
	}
	return _instance;
}

void 
KeyManager::destroy()
{
	if (_instance != nullptr)
	{
		delete _instance;
	}
}

bool
KeyManager::isKeyDown(const uint32_t& key)
{
	return glfwGetKey(_window.getWindow(), key) == GLFW_PRESS;
}

bool
KeyManager::leftClicked()
{
	int32_t state = glfwGetMouseButton(_window.getWindow(), GLFW_MOUSE_BUTTON_LEFT);
	return state == GLFW_PRESS;
}

bool
KeyManager::rightClicked()
{
	int32_t state = glfwGetMouseButton(_window.getWindow(), GLFW_MOUSE_BUTTON_RIGHT);
	return state == GLFW_PRESS;
}

void
KeyManager::setup(const RenderWindow& window)
{
	_window = window;
}