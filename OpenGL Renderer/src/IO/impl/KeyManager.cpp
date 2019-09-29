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

bool
KeyManager::isKeyDown(unsigned int key)
{
	return glfwGetKey(_window.getWindow(), key) == GLFW_PRESS;
}

bool
KeyManager::leftClicked()
{
	int state = glfwGetMouseButton(_window.getWindow(), GLFW_MOUSE_BUTTON_LEFT);
	return state == GLFW_PRESS;
}

bool
KeyManager::rightClicked()
{
	int state = glfwGetMouseButton(_window.getWindow(), GLFW_MOUSE_BUTTON_RIGHT);
	return state == GLFW_PRESS;
}

void
KeyManager::setup(RenderWindow window)
{
	_window = window;
}