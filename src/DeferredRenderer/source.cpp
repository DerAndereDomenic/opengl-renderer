#include <iostream>
#include <DLogger/Logger.h>
#include <Renderer/RenderWindow.h>
#include <Core/GLFunctions.h>
#include <GUI/WindowClose.h>

int main()
{
    const uint32_t width = 1280, height = 720;

    LOGGER::setProject("Deferred Renderer", "1.0");
    LOGGER::start();

    Camera camera = Camera::createObject(static_cast<float>(width)/static_cast<float>(height), 0.01f, 100.0f);
    RenderWindow window = RenderWindow::createObject(width, height, "DeferredRenderer", &camera);
    WindowClose close_callback(&window);
    window.registerKeyCallback(GLFW_KEY_ESCAPE, &close_callback);

    GL::enableDebugOutput();

    while(window.isOpen())
    {
        GL::clear();

        window.spinOnce();
    }

    RenderWindow::destroyObject(window);
    Camera::destroyObject(camera);

    LOGGER::end();

    return 0;
}