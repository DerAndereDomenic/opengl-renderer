#ifndef __OPENGLRENDERER_GUI_MOVINGBUTTON_H
#define __OPENGLRENDERER_GUI_MOVINGBUTTON_H

#include <GUI/KeyPressFunction.h>
#include <GUI/Button.h>

class MovingButton : public KeyPressFunction
{
	public:
		/**
		*	\brief Constructor
        *   \param[in] button A pointer to the button
		*/
		MovingButton(Button* button);

		//Override
		void onPress(const uint32_t& key);

		//Override
		void onRelease(const uint32_t& key);

		//Override
		void onHold(const uint32_t& key);
	private:
		Button* _button;
};

#endif