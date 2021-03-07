#include <OpenGLRendererConfig.h>
#include <Core/Platform.h>
#include <Core/GLFunctions.h>
#include <DLogger/Logger.h>

#include <Renderer/RenderWindow.h>

int main()
{
    LOGGER::setProject("Geometry Processing", std::to_string(OpenGLRenderer_VERSION_MAJOR) + "." + std::to_string(OpenGLRenderer_VERSION_MINOR));
	LOGGER::start();
    
    uint32_t width = 1280, height = 720;
    RenderWindow window = RenderWindow::createObject(width, height, "Geometry");

    while(window.isOpen())
    {
        GL::clear();

        window.spinOnce();
    }

    RenderWindow::destroyObject(window);
    LOGGER::end();
    return 0;
}
