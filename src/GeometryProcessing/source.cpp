#include <OpenGLRendererConfig.h>
#include <Core/Platform.h>
#include <Core/GLFunctions.h>
#include <DLogger/Logger.h>

int main()
{
    LOGGER::setProject("Geometry Processing", std::to_string(OpenGLRenderer_VERSION_MAJOR) + "." + std::to_string(OpenGLRenderer_VERSION_MINOR));
	LOGGER::start();
    
    LOGGER::end();
    return 0;
}
