#include <OpenGLRendererConfig.h>
#include <Core/Platform.h>
#include <Core/GLFunctions.h>
#include <DLogger/Logger.h>

#include <Renderer/RenderWindow.h>
#include <GUI/WindowClose.h>
#include <GUI/ModeControl.h>
#include <Shader/ShaderManager.h>
#include <OpenGLObjects/VertexArray.h>

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

    float vertices[28] = 
    {
        -0.5,-0.5,0,0,1,0,1,
        0.5,-0.5,0,0,1,0,1,
        0.5,0.5,0,0,1,0,1,
        -0.5,0.5,0,0,1,0,1
    };

    uint32_t indices[6] = 
    {
        0,1,2,0,2,3
    };

    VertexBuffer vbo = VertexBuffer::createObject(vertices, 28);
    VertexBufferLayout layout;
    layout.add(GL_FLOAT, 3);
    layout.add(GL_FLOAT, 4);

    VertexArray vao = VertexArray::createObject(GL_POINTS);
    vao.addBuffer(vbo, layout);

    IndexBuffer ibo = IndexBuffer::createObject(indices, 6);
    vao.setIndexBuffer(ibo);

    while(window.isOpen())
    {
        GL::clear();

        ShaderManager::instance()->getShader("basic").bind();
        ShaderManager::instance()->getShader("basic").setInt("u_set", 1);
        ShaderManager::instance()->getShader("basic").setMVP();
        vao.render();

        window.spinOnce();
    }

    RenderWindow::destroyObject(window);
    ShaderManager::destroyObject(*ShaderManager::instance());

    LOGGER::end();
    return 0;
}
