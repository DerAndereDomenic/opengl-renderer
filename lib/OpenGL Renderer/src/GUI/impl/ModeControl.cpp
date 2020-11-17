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
		glfwSetInputMode(_window->getWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}
	else if (current_mode == ViewerMode::EDIT)
	{
		_window->setMode(ViewerMode::VIEWER);
		glfwSetInputMode(_window->getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}
}