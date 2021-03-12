#ifndef __OPENGLRENDERER_GUI_MOVINGBUTTON_H
#define __OPENGLRENDERER_GUI_MOVINGBUTTON_H

#include <GUI/KeyPressFunction.h>
#include <GUI/Button.h>
#include <Renderer/RenderWindow.h>

class MovingButton : public KeyPressFunction
{
	public:
		/**
		*	\brief Constructor
        *   \param[in] window The render window
        *   \param[in] button A pointer to the button
		*/
		MovingButton(RenderWindow* window, Button* button);

		//Override
		void onPress(const uint32_t& key);

		//Override
		void onRelease(const uint32_t& key);

		//Override
		void onHold(const uint32_t& key);
	private:
		Button* _button;        /**<< The button */
        RenderWindow* _window;  /**<< The window */
};

#endif