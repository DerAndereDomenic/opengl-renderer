#ifndef __OPENGLRENDERER_GUI_KEYPRESSFUNCTION_H
#define __OPENGLRENDERER_GUI_KEYPRESSFUNCTION_H

class KeyPressFunction
{
	public:
		/**
		*	\brief The function called when a key press is invoked.
		*/
		virtual void onPress() = 0;
};

#endif