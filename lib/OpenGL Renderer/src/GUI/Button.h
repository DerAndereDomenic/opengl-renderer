#ifndef __OPENGLRENDERER_GUI_BUTTON_H
#define __OPENGLRENDERER_GUI_BUTTON_H

#include <cstdint>
#include <Renderer/TextRenderer.h>
#include <string>
#include <glm/glm.hpp>
#include <memory>

/**
*	\brief A enum to model button modes
*/
enum class ButtonMode
{
	IDLE = 0,		/**<< If the button is idle */
	HOVER = 1,		/**<< If the mouse hovers over the button */
	CLICK = 2		/**<< If the button is clicked */
};

/**
*	\brief A class to model a button
*/
class Button
{
	public:
		/**
		*	\brief Creates a default button
		*/
		Button() = default;

		/**
		*	\brief Creates a button
		*	\param[in] x The x position
		*	\param[in] y The y position
		*	\param[in] width The width
		*	\param[in] height The height
		*	\note (0,0) is the lower left corner
		*/
		Button(const uint32_t& x, const uint32_t& y, const uint32_t& width, const uint32_t& height);

		/**
		*	\brief Set the text of the button
		*	\param[in] text The button text
		*/
		void setText(const std::string& text);

		/**
		*	\brief Set the position of the button
		*	\param[in] x The x coordinate
		*	\param[in] y The y coordinate 
		*/ 
		inline void 
		setPosition(const uint32_t& x, const uint32_t& y) {_posX = x; _posY = y;}

		/**
		*	\brief Render the button
		*	\param[in] renderer The Text Renderer for rendering the button text
		*	\param[in] mode The button mode
		*/
		void render(std::shared_ptr<TextRenderer> renderer, const ButtonMode& mode = ButtonMode::IDLE) const;

		/**
		*	\brief Check if the position is inside the button
		*	\param[in] x The x position
		*	\param[in] y The y position
		*	\return True if it lies inside, false otherwise
		*	\note: The glfw coordinate system does not correspond with the opengl screen space
		*		   y has to be translated by the height, i.e. y = button_height - glfw_y
		*/
		bool inside(const uint32_t& x, const uint32_t& y) const;

		/**
		*	\brief Check if two buttons are equal
		*	\param[in] button The button to check against
		*	\return True if the button id matches
		*/
		bool operator==(const Button& button) const;

		/**
		*	\brief Get the Button text
		*	\return The text
		*/
		inline std::string getText() const { return _text; }

		/**
		*	\brief Get the button id
		*	\return The id
		*/
		inline uint32_t getID() const { return _id; }

		/**
		*	\brief Get the position of the button
		*	\return A vector containing the position 
		*/ 
		inline glm::vec2 getPosition() {return glm::vec2(_posX, _posY);}
	private:
		uint32_t _id;							/**<< The button ID */

		uint32_t _posX = 0;						/**<< The x position */
		uint32_t _posY = 0;						/**<< The y position */

		uint32_t _width = 0;					/**<< The button width */
		uint32_t _height = 0;					/**<< The button height */

		std::string _text = std::string();		/**<< The button text */
};

/**
*	\brief The hash function for a button
*/
struct ButtonHash
{
	/**
	*	\brief Hash a button (i.e. int hash for the id)
	*	\param[in] button The button to hash
	*	\return The hash value
	*/
	std::size_t
	operator()(Button* button) const;
};

#endif