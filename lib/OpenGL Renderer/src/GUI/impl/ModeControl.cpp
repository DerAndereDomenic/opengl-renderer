#include <GUI/ModeControl.h>
#include <Renderer/RenderWindow.h>

ModeControl::ModeControl(RenderWindow* window)
	:_window(window)
{

}

void 
ModeControl::onPress(const uint32_t& key)
{
	ViewerMode current_mode = _window->getMode();

	if (current_mode == ViewerMode::VIEWER)
	{
		_window->setMode(ViewerMode::EDIT);
		glfwGetCursorPos(_window->getWindow(), &_lastX, &_lastY);
		glfwSetInputMode(_window->getWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		glfwSetCursorPos(_window->getWindow(), _window->getWidth() / 2.0f, _window->getHeight() / 2.0f);
	}
	else if (current_mode == ViewerMode::EDIT)
	{
		_window->setMode(ViewerMode::VIEWER);
		glfwSetInputMode(_window->getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		glfwSetCursorPos(_window->getWindow(), _lastX, _lastY);
	}
}