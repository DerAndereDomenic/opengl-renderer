#ifndef __OPENGLRENDERER_GUI_WINDOWCLOSE_H
#define __OPENGLRENDERER_GUI_WINDOWCLOSE_H

class RenderWindow;
#include <GUI/KeyPressFunction.h>

class WindowClose : public KeyPressFunction
{
	public:
		/**
		*	\brief Creates a Window close callback
		*	\param[in] window The window to close
		*/
		WindowClose(RenderWindow* window);

		//Override
		virtual void onPress(const int32_t& key);
	private:
		RenderWindow* _window = nullptr;	/**<< The window to close*/
};

#endif