#ifndef __OPENGLRENDERER_GUI_BUTTON_H
#define __OPENGLRENDERER_GUI_BUTTON_H

#include <cstdint>
#include <Renderer/TextRenderer.h>
#include <string>

class Button
{
	public:
		Button() = default;

		Button(const uint32_t& x, const uint32_t& y, const uint32_t& width, const uint32_t& height);

		void setText(const std::string& text);

		void render(const TextRenderer& renderer);
	private:
		uint32_t _posX = 0;
		uint32_t _posY = 0;

		uint32_t _width = 0;
		uint32_t _height = 0;

		std::string _text = std::string();
};

#endif