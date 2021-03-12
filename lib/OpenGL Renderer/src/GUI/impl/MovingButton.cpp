#include <GUI/MovingButton.h>

MovingButton::MovingButton(RenderWindow* window, Button* button)
    :_window(window),
    _button(button)
{

}

void 
MovingButton::onPress(const uint32_t& key)
{
	
}

void
MovingButton::onRelease(const uint32_t& key)
{
	
}

void
MovingButton::onHold(const uint32_t& key)
{
	double x,y;
    glfwGetCursorPos(_window->getWindow(), &x, &y);

    y = -y + _window->getHeight();

    _button->setPosition(x-5,y-5);

    //std::cout << x << ", " << y << std::endl;
}