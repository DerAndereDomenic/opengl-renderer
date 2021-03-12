#ifndef __OPENGLRENDERER_GUI_MOVINGBUTTON_H
#define __OPENGLRENDERER_GUI_MOVINGBUTTON_H

#include <GUI/KeyPressFunction.h>

class MovingButton : public KeyPressFunction
{
	public:
		/**
		*	\brief Default constructor
		*/
		MovingButton() = default;

		//Override
		void onPress(const uint32_t& key);

		//Override
		void onRelease(const uint32_t& key);

		//Override
		void onHold(const uint32_t& key);
	private:
		
};

#endif