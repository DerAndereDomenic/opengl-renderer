#ifndef __OPENGLRENDERER_GUI_BUTTON_H
#define __OPENGLRENDERER_GUI_BUTTON_H

#include <cstdint>
#include <Renderer/TextRenderer.h>
#include <string>

enum class ButtonMode
{
	IDLE = 0,
	HOVER = 1,
	CLICK = 2
};

class Button
{
	public:
		Button() = default;

		Button(const uint32_t& x, const uint32_t& y, const uint32_t& width, const uint32_t& height);

		void setText(const std::string& text);

		void render(TextRenderer& renderer, const ButtonMode& mode = ButtonMode::IDLE) const;

		bool inside(const uint32_t& x, const uint32_t& y) const;

		bool operator==(const Button& button) const;

		inline std::string getText() const { return _text; }

		inline uint32_t getID() const { return _id; }

		inline ButtonMode getButtonMode() const { return _mode; }

		inline void setButtonMode(const ButtonMode& mode) { _mode = mode; }
	private:
		uint32_t _id;

		uint32_t _posX = 0;
		uint32_t _posY = 0;

		uint32_t _width = 0;
		uint32_t _height = 0;

		std::string _text = std::string();

		ButtonMode _mode = ButtonMode::IDLE;
};

struct ButtonHash
{
	std::size_t
	operator()(const Button& button) const;
};

#endif