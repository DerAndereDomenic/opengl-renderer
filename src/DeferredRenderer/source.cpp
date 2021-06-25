#include <iostream>
#include <DLogger/Logger.h>
#include <Renderer/RenderWindow.h>
#include <Core/GLFunctions.h>
#include <GUI/WindowClose.h>
#include <DataStructure/MeshHelper.h>
#include <OpenGLRendererConfig.h>
#include <Shader/ShaderManager.h>
#include <OpenGLObjects/GBuffer.h>

int main()
{
    const uint32_t width = 1280, height = 720;

    LOGGER::setProject("Deferred Renderer", "1.0");
    LOGGER::start();

    Camera camera = Camera(static_cast<float>(width)/static_cast<float>(height), 0.01f, 100.0f);
    RenderWindow window = RenderWindow(width, height, "DeferredRenderer", &camera);
    WindowClose close_callback(&window);
    window.registerKeyCallback(GLFW_KEY_ESCAPE, &close_callback);

    GL::enableDebugOutput();

    std::shared_ptr<Mesh> crate = MeshHelper::cubeMesh(glm::vec4(1));
    crate->create();
    Texture diffuse_texture = Texture(RESOURCE_PATH + "crate_diffuse.png");
    Texture specuar_texture = Texture(RESOURCE_PATH + "crate_specular.png");

    ShaderManager::instance()->addShader("GeometryDeferred");
    ShaderManager::instance()->addShader("LightDeferred");

    GBuffer gbuffer = GBuffer(width, height);
    GL::updateDrawBuffers(3);

    std::shared_ptr<Mesh> quad = MeshHelper::quadMesh(2);
    quad->create();

    //Disable blending when using deferred rendering
    glDisable(GL_BLEND);

    while(window.isOpen())
    {
        gbuffer.bind();
        GL::clear();
        ShaderManager::instance()->getShader("GeometryDeferred")->bind();
        ShaderManager::instance()->getShader("GeometryDeferred")->setMVP(glm::mat4(1), camera.getView(), camera.getProjection());
        ShaderManager::instance()->getShader("GeometryDeferred")->setInt("texture_diffuse", 0);
        ShaderManager::instance()->getShader("GeometryDeferred")->setInt("texture_specular", 1);
        diffuse_texture.bind(0);
        specuar_texture.bind(1);
        crate->render();
        FrameBuffer::bindDefault();

        GL::clear();
        ShaderManager::instance()->getShader("LightDeferred")->bind();
        ShaderManager::instance()->getShader("LightDeferred")->setVec3("viewPos", camera.getPosition());
        ShaderManager::instance()->getShader("LightDeferred")->setInt("gPosition", 0);
        ShaderManager::instance()->getShader("LightDeferred")->setInt("gNormal", 1);
        ShaderManager::instance()->getShader("LightDeferred")->setInt("gAlbedoSpec", 2);
        gbuffer.bindTextures();
        quad->render();

        window.spinOnce();
    }

    ShaderManager::destroyObject(*ShaderManager::instance());

    LOGGER::end();

    return 0;
}