#include <OpenGLRendererConfig.h>
#include <Core/Platform.h>
#include <Core/GLFunctions.h>
#include <DLogger/Logger.h>

#include <Renderer/RenderWindow.h>
#include <GUI/WindowClose.h>
#include <GUI/ModeControl.h>
#include <Shader/ShaderManager.h>
#include <OpenGLObjects/VertexArray.h>

glm::vec2 to_screen_space(const uint32_t& x, const uint32_t& y, const uint32_t& width, const uint32_t& height)
{
    double x_screen = (x+1)*(width/2);
    double y_screen = -(y+1)*(height/2) + height;
    return glm::vec2(x_screen, y_screen);
}

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
    ShaderManager::instance()->addShader("Curve", true);

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

    uint32_t discretization = 100;

    while(window.isOpen())
    {
        GL::clear();

        ShaderManager::instance()->getShader("basic").bind();
        ShaderManager::instance()->getShader("basic").setInt("u_set", 1);
        ShaderManager::instance()->getShader("basic").setMVP();
        vao.render();

        ShaderManager::instance()->getShader("Curve").bind();
        ShaderManager::instance()->getShader("Curve").setVec3("points[0]", glm::vec3(vertices[0],vertices[1],vertices[2]));
        ShaderManager::instance()->getShader("Curve").setVec3("points[1]", glm::vec3(vertices[0+7],vertices[1+7],vertices[2+7]));
        ShaderManager::instance()->getShader("Curve").setVec3("points[2]", glm::vec3(vertices[0+14],vertices[1+14],vertices[2+14]));
        ShaderManager::instance()->getShader("Curve").setVec3("points[3]", glm::vec3(vertices[0+21],vertices[1+21],vertices[2+21]));
        ShaderManager::instance()->getShader("Curve").setInt("discretization", discretization);
        ShaderManager::instance()->getShader("Curve").setInt("render_bezier", 1);
        ShaderManager::instance()->getShader("Curve").setVec3("color", glm::vec3(1,0,0));
        vao.renderInstanced(1, discretization);

        ShaderManager::instance()->getShader("Curve").setInt("render_bezier", 0);
        ShaderManager::instance()->getShader("Curve").setVec3("color", glm::vec3(0,0,1));
        vao.renderInstanced(1, discretization);

        window.spinOnce();
    }

    RenderWindow::destroyObject(window);
    ShaderManager::destroyObject(*ShaderManager::instance());
    VertexArray::destroyObject(vao);
    IndexBuffer::destroyObject(ibo);
    VertexBuffer::destroyObject(vbo);

    LOGGER::end();
    return 0;
}
