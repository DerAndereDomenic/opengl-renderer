#ifndef __OPENGLRENDERER_GUI_MODECONTROL_H
#define __OPENGLRENDERER_GUI_MODECONTROL_H

class RenderWindow;
#include <GUI/KeyPressFunction.h>

class ModeControl : public KeyPressFunction
{
	public:
		/**
		*	\brief Construct a Mode control callback
		*	\param[in] window The window
		*/
		ModeControl(RenderWindow* window);

		//Override
		void onPress(const uint32_t& key);

	private:
		RenderWindow* _window = nullptr;		/**<< The window */
};

#endif