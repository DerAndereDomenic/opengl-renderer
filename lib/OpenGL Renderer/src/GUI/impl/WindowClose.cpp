#include <GUI/WindowClose.h>
#include <Renderer/RenderWindow.h>

WindowClose::WindowClose(RenderWindow* window)
	:_window(window)
{

}

void 
WindowClose::onPress(const int32_t& key)
{
	_window->close();
}