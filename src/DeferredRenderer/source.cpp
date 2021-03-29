#include <iostream>
#include <DLogger/Logger.h>
#include <Renderer/RenderWindow.h>
#include <Core/GLFunctions.h>
#include <GUI/WindowClose.h>
#include <DataStructure/MeshHelper.h>
#include <OpenGLRendererConfig.h>
#include <Shader/ShaderManager.h>

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

    Mesh crate = MeshHelper::cubeMesh(glm::vec4(1));
    crate.create();
    Texture diffuse_texture = Texture::createObject(RESOURCE_PATH + "crate_diffuse.png");
    Texture specuar_texture = Texture::createObject(RESOURCE_PATH + "crate_specular.png");

    ShaderManager::instance()->addShader("basic");

    while(window.isOpen())
    {
        GL::clear();

        ShaderManager::instance()->getShader("basic").bind();
        ShaderManager::instance()->getShader("basic").setMVP(glm::mat4(1), camera.getView(), camera.getProjection());
        crate.render();

        window.spinOnce();
    }

    RenderWindow::destroyObject(window);
    Camera::destroyObject(camera);

    LOGGER::end();

    return 0;
}