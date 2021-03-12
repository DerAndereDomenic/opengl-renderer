#ifndef __OPENGLRENDERER_GUI_DEBUGCONTROL_H
#define __OPENGLRENDERER_GUI_DEBUGCONTROL_H

#include <GUI/KeyPressFunction.h>

class DebugControl : public KeyPressFunction
{
	public:
		/**
		*	\brief Default constructor
		*/
		DebugControl() = default;

		//Override
		void onPress(const uint32_t& key);

		//Override
		void onRelease(const uint32_t& key);

		/**
		*	\brief Get the debug mode
		*	\return Wether debug is enabled or not
		*/
		inline bool getDebug() { return _debug; }
	private:
		bool _debug = false;	/**<< The debug level*/
};

#endif