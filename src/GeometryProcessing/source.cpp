#include <OpenGLRendererConfig.h>
#include <Core/Platform.h>
#include <Core/GLFunctions.h>
#include <DLogger/Logger.h>

#include <Renderer/RenderWindow.h>
#include <GUI/WindowClose.h>
#include <GUI/ModeControl.h>
#include <Shader/ShaderManager.h>
#include <DataStructure/MeshHelper.h>

int main()
{
    LOGGER::setProject("Geometry Processing", std::to_string(OpenGLRenderer_VERSION_MAJOR) + "." + std::to_string(OpenGLRenderer_VERSION_MINOR));
	LOGGER::start();
    
    uint32_t width = 1280, height = 720;
    RenderWindow window = RenderWindow::createObject(width, height, "Geometry");

    WindowClose close_callback(&window);
	ModeControl mode_callback(&window);

	window.registerKeyCallback(GLFW_KEY_ESCAPE, &close_callback);
	window.registerKeyCallback(GLFW_KEY_LEFT_ALT, &mode_callback);

    ShaderManager::instance()->addShader("basic");

    Mesh quad = MeshHelper::quadMesh(2.0f);
    quad.create();

    while(window.isOpen())
    {
        GL::clear();

        ShaderManager::instance()->getShader("basic").bind();
        ShaderManager::instance()->getShader("basic").setInt("u_set", 1);
        ShaderManager::instance()->getShader("basic").setMVP();
        quad.render();

        window.spinOnce();
    }

    RenderWindow::destroyObject(window);
    ShaderManager::destroyObject(*ShaderManager::instance());
    Mesh::destroyObject(quad);

    LOGGER::end();
    return 0;
}
