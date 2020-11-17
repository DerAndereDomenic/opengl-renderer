#ifndef __OPENGLRENDERER_GUI_EXPOSURECONTROL_H
#define __OPENGLRENDERER_GUI_EXPOSURECONTROL_H

#include <GUI/KeyPressFunction.h>

class ExposureControl : public KeyPressFunction
{
	public:
		/**
		*	\brief Default constructor
		*/
		ExposureControl() = default;

		//Override
		void onPress(const uint32_t& key);

		/**
		*	\brief Get the current exposure level
		*	\return The exposure
		*/
		inline float getExposure() { return _exposure; }
	private:
		float _exposure = 1.0f;	/**<< The exposure*/
};

#endif