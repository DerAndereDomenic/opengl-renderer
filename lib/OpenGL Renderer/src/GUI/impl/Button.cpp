#include <GUI/Button.h>


Button::Button(const uint32_t& x, const uint32_t& y, const uint32_t& width, const uint32_t& height)
	:_posX(x),
	 _posY(y),
	 _width(width),
	 _height(height)
{

}

void 
Button::setText(const std::string& text)
{
	_text = text;
}

void 
Button::render(TextRenderer& renderer)
{
	renderer.render(_text, _posX, _posY, 1, glm::vec3(1));
}