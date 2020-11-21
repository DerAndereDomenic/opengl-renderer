#ifndef __OPENGLRENDERER_GUI_BUTTON_H
#define __OPENGLRENDERER_GUI_BUTTON_H

#include <cstdint>
#include <Renderer/TextRenderer.h>

class Button
{
	public:
		Button(const uint32_t& x, const uint32_t& y, const uint32_t& width, const uint32_t& height);

		void setText(const std::string& text);

		void render(const TextRenderer& renderer);
	private:
		uint32_t _poxX;
		uint32_t _posY;

		uint32_t _width;
		uint32_t _height;

		std::string _text;
};

#endif