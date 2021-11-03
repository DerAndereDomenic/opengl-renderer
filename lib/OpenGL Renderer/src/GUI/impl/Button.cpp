#include <GUI/Button.h>

namespace detail
{
	uint32_t global_button_id = 0;
}

Button::Button(const uint32_t& x, const uint32_t& y, const uint32_t& width, const uint32_t& height)
	:_posX(x),
	 _posY(y),
	 _width(width),
	 _height(height),
	 _id(detail::global_button_id++)
{

}

void 
Button::setText(const std::string& text)
{
	_text = text;
}

void 
Button::render(const std::shared_ptr<TextRenderer>& renderer, const ButtonMode& mode) const
{
	if (mode == ButtonMode::IDLE)
	{
		renderer->render(_text, _posX, _posY, 1, glm::vec3(0.25));
	}
	else if(mode == ButtonMode::HOVER)
	{
		renderer->render(_text, _posX, _posY, 1, glm::vec3(0.5));
	}
	else if (mode == ButtonMode::CLICK)
	{
		renderer->render(_text, _posX, _posY, 1, glm::vec3(1));
	}
}

bool 
Button::inside(const uint32_t& x, const uint32_t& y) const
{
	const uint32_t cx = x - _posX;
	const uint32_t cy = y - _posY;

	return cx <= _width && cy <= _height;
}

bool 
Button::operator==(const Button& button) const
{
	return button.getID() == _id;
}

std::size_t
ButtonHash::operator()(Button* button) const
{
	std::hash<uint32_t> hasher;
	return hasher(button->getID());
}