#include <GUI/ExposureControl.h>
#include <GLFW/glfw3.h>

void 
ExposureControl::onPress(const uint32_t& key)
{
	if (key == GLFW_KEY_KP_ADD)
	{
		_exposure += 0.01f;
	}
	
	if (key == GLFW_KEY_KP_SUBTRACT)
	{
		if (_exposure > 0.01f)
		{
			_exposure -= 0.01f;
		}
	}
	
}

void
ExposureControl::onRelease(const uint32_t& key)
{
	
}