#ifndef __OPENGLRENDERER_GUI_KEYPRESSFUNCTION_H
#define __OPENGLRENDERER_GUI_KEYPRESSFUNCTION_H

#include <cstdint>

class KeyPressFunction
{
	public:
		/**
		*	\brief The function called when a key press is invoked.
		*	\param[in] key The invoked key (default = 0)
		*/
		virtual void onPress(const uint32_t& key = 0) = 0;
};

#endif