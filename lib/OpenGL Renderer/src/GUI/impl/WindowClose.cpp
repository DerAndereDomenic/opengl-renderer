#include <GUI/WindowClose.h>

WindowClose::WindowClose(RenderWindow* window)
	:_window(window)
{

}

void 
WindowClose::onPress(const int32_t& key)
{
	_window->close();
}