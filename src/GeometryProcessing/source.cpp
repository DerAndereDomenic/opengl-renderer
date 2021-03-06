#include <Core/Platform.h>
#include <Core/GLFunctions.h>
#include <DLogger/Logger.h>

#include <Renderer/RenderWindow.h>
#include <GUI/WindowClose.h>
#include <GUI/ModeControl.h>
#include <GUI/Button.h>
#include <GUI/MovingButton.h>
#include <GUI/ExposureControl.h>
#include <Shader/ShaderManager.h>
#include <OpenGLObjects/VertexArray.h>
#include <DataStructure/Mesh.h>
#include <IO/ObjLoader.h>
#include <algorithm>

/*glm::vec2 to_screen_space(const float& x, const float& y, const float& width, const float& height)
{
    double x_screen = (x+1)*(width/2);
    double y_screen = (y+1)*(height/2);
    LOGGER::DEBUG(std::to_string(x) + ", " + std::to_string(y)+ "\n");
    return glm::vec2(x_screen, y_screen);
}

glm::vec2 to_ndc_space(const float& x, const float& y, const float& width, const float& height)
{
    double x_ndc = x/(width/2)-1;
    double y_ndc = y/(height/2)-1;
    return glm::vec2(x_ndc, y_ndc);
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

    ShaderManager::addShader("basic");
    ShaderManager::addShader("Curve", true);

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

    ExposureControl exposureControl;

    window.registerKeyCallback(GLFW_KEY_KP_ADD, &exposureControl);
    window.registerKeyCallback(GLFW_KEY_KP_SUBTRACT, &exposureControl);

    glm::vec2 screen_space = to_screen_space(vertices[0], vertices[1], width,height); 
    Button button1(screen_space.x, screen_space.y, 10, 10);
    LOGGER::INFO(std::to_string(screen_space.x) + ", " + std::to_string(screen_space.y) + "\n");

    screen_space = to_screen_space(vertices[7], vertices[8], width,height); 
    Button button2(screen_space.x, screen_space.y, 10, 10);
    LOGGER::INFO(std::to_string(screen_space.x) + ", " + std::to_string(screen_space.y) + "\n");

    screen_space = to_screen_space(vertices[14], vertices[15], width,height); 
    Button button3(screen_space.x, screen_space.y, 10, 10);
    LOGGER::INFO(std::to_string(screen_space.x) + ", " + std::to_string(screen_space.y) + "\n");

    screen_space = to_screen_space(vertices[21], vertices[22], width,height); 
    Button button4(screen_space.x, screen_space.y, 10, 10);
    LOGGER::INFO(std::to_string(screen_space.x) + ", " + std::to_string(screen_space.y) + "\n");

    MovingButton butt1(&window, &button1);
    MovingButton butt2(&window, &button2);
    MovingButton butt3(&window, &button3);
    MovingButton butt4(&window, &button4);

    button1.setText("1");

    window.registerButtonCallback(&button1, &butt1);
    window.registerButtonCallback(&button2, &butt2);
    window.registerButtonCallback(&button3, &butt3);
    window.registerButtonCallback(&button4, &butt4);

    VertexBuffer vbo = VertexBuffer::createObject(vertices, 28);
    VertexBufferLayout layout;
    layout.add(GL_FLOAT, 3);
    layout.add(GL_FLOAT, 4);

    VertexArray vao = VertexArray::createObject(GL_POINTS);
    vao.addBuffer(vbo, layout);

    IndexBuffer ibo = IndexBuffer::createObject(indices, 6);
    vao.setIndexBuffer(ibo);

    uint32_t discretization = 10;

    glm::vec2 button_pos;

    while(window.isOpen())
    {
        GL::clear();

        discretization = exposureControl.getExposure()*10;

        ShaderManager::getShader("basic").bind();
        ShaderManager::getShader("basic").setInt("u_set", 1);
        ShaderManager::getShader("basic").setMVP();
        vao.render();

        ShaderManager::getShader("Curve").bind();
        ShaderManager::getShader("Curve").setVec3("points[0]", glm::vec3(vertices[0],vertices[1],vertices[2]));
        ShaderManager::getShader("Curve").setVec3("points[1]", glm::vec3(vertices[0+7],vertices[1+7],vertices[2+7]));
        ShaderManager::getShader("Curve").setVec3("points[2]", glm::vec3(vertices[0+14],vertices[1+14],vertices[2+14]));
        ShaderManager::getShader("Curve").setVec3("points[3]", glm::vec3(vertices[0+21],vertices[1+21],vertices[2+21]));
        ShaderManager::getShader("Curve").setInt("discretization", discretization);
        ShaderManager::getShader("Curve").setInt("render_bezier", 1);
        ShaderManager::getShader("Curve").setVec3("color", glm::vec3(1,0,0));
        vao.renderInstanced(1, discretization);

        ShaderManager::getShader("Curve").setInt("render_bezier", 0);
        ShaderManager::getShader("Curve").setVec3("color", glm::vec3(0,0,1));
        vao.renderInstanced(1, discretization);

        window.spinOnce();

        button_pos = button1.getPosition();
        button_pos = to_ndc_space(button_pos.x, button_pos.y, width, height);
        
        vertices[0] = button_pos.x;
        vertices[1] = button_pos.y;

        button_pos = button2.getPosition();
        button_pos = to_ndc_space(button_pos.x, button_pos.y, width, height);
        
        vertices[7] = button_pos.x;
        vertices[8] = button_pos.y;

        button_pos = button3.getPosition();
        button_pos = to_ndc_space(button_pos.x, button_pos.y, width, height);
        
        vertices[14] = button_pos.x;
        vertices[15] = button_pos.y;

        button_pos = button4.getPosition();
        button_pos = to_ndc_space(button_pos.x, button_pos.y, width, height);
        
        vertices[21] = button_pos.x;
        vertices[22] = button_pos.y;

        vbo.changeData(vertices, 28);
    }

    RenderWindow::destroyObject(window);
    ShaderManager::destroyObject(*ShaderManager::instance());
    VertexArray::destroyObject(vao);
    IndexBuffer::destroyObject(ibo);
    VertexBuffer::destroyObject(vbo);

    LOGGER::end();
    return 0;
}*/

float f(const glm::vec3 v)
{
    return v.x * v.x + v.y * v.y * v.y;
}

float laplacef(const glm::vec3 v)
{
    return 2.0f + 6.0f*v.y;
}

//HARD CODED
void build_graphlaplace(float** L, const uint32_t* indices)
{
    float diagonals[6] = {0,};
    for (uint32_t f = 0; f < 5; ++f)
    {
        L[indices[3 * f]][indices[3 * f + 1]] = -1.0f;
        L[indices[3 * f + 1]][indices[3 * f]] = -1.0f;
                                              
        L[indices[3 * f]][indices[3 * f + 2]] = -1.0f;
        L[indices[3 * f + 2]][indices[3 * f]] = -1.0f;

        L[indices[3 * f + 2]][indices[3 * f + 1]] = -1.0f;
        L[indices[3 * f + 1]][indices[3 * f + 2]] = -1.0f;
    }

    for (uint32_t i = 0; i < 6; ++i)
    {
        float sum = 0;
        for (uint32_t j = 0; j < 6; ++j)
        {
            sum += L[i][j];
        }
        L[i][i] = -sum;
    }

    for (int i = 0; i < 6; ++i)
    {
        for (int j = 0; j < 6; ++j)
        {
            std::cout << L[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

//HARD CODED
void graphlaplacef(float** L, const float* f, float* graphlapacef_values)
{
    for (uint32_t i = 0; i < 6; ++i)
    {
        for (uint32_t j = 0; j < 6; ++j)
        {
            graphlapacef_values[i] += L[i][j] * f[j];
        }
    }
}

int main()
{
    LOGGER::setProject("Geometry Processing", "1.0");
    LOGGER::start();

    const uint32_t width = 1280, height = 720;
    RenderWindow window = RenderWindow(width, height, "Laplace");
    WindowClose close_callback(&window);

    GL::enableDebugOutput();

    window.registerKeyCallback(GLFW_KEY_ESCAPE, &close_callback);

    Mesh mesh = Mesh();
    glm::vec3 vertices[6] =
    {
        glm::vec3(0.0f, 0.0f, 0.0f)/5.0f,
        glm::vec3(4.0f, -2.0f, 0.0f)/5.0f,
        glm::vec3(4.0f, 2.0f, 0.0f)/5.0f,
        glm::vec3(0.5f, 2.0f, 0.0f)/5.0f,
        glm::vec3(-2.0f, 1.0f, 0.0f)/5.0f,
        glm::vec3(-2.0f, -1.0f, 0.0f)/5.0f,
    };

    float f_values[6] =
    {
        f(glm::vec3(vertices[0])),
        f(glm::vec3(vertices[1])),
        f(glm::vec3(vertices[2])),
        f(glm::vec3(vertices[3])),
        f(glm::vec3(vertices[4])),
        f(glm::vec3(vertices[5])),
    };

    /*float max_f = *std::max_element(f_values, f_values + 5);
    for (uint32_t i = 0; i < 6; ++i)
    {
        f_values[i] /= max_f;
    }*/

    float laplacef_values[6] =
    {
        laplacef(glm::vec3(vertices[0])),
        laplacef(glm::vec3(vertices[1])),
        laplacef(glm::vec3(vertices[2])),
        laplacef(glm::vec3(vertices[3])),
        laplacef(glm::vec3(vertices[4])),
        laplacef(glm::vec3(vertices[5])),
    };

    for (uint32_t i = 0; i < 6; ++i)
    {
        std::cout << laplacef_values[i] << std::endl;
    }

    float max_laplacef = *std::max_element(laplacef_values, laplacef_values + 5);
    float min_laplacef = *std::min_element(laplacef_values, laplacef_values + 5);
    for (uint32_t i = 0; i < 6; ++i)
    {
        laplacef_values[i] = (laplacef_values[i] + std::fabs(min_laplacef)) / (max_laplacef + std::fabs(min_laplacef));
    }

    uint32_t faces[15] = { 0, 1, 2, 0, 2, 3, 0, 3, 4, 0, 4, 5, 0, 5, 1 };
    float** L = new float* [6];
    for (uint32_t i = 0; i < 6; ++i)
    {
        L[i] = new float[6];
    }
    for (uint32_t i = 0; i < 6; ++i)
    {
        for (uint32_t j = 0; j < 6; ++j)
        {
            L[i][j] = 0.0f;
        }
    }
    build_graphlaplace(L, faces);

    float graphlaplacef_values[6] = { 0, };
    graphlaplacef(L, f_values, graphlaplacef_values);

    float max_graphlaplacef = *std::max_element(graphlaplacef_values, graphlaplacef_values + 5);
    float min_graphlaplacef = *std::min_element(graphlaplacef_values, graphlaplacef_values + 5);
    for (uint32_t i = 0; i < 6; ++i)
    {
        graphlaplacef_values[i] = (graphlaplacef_values[i] + std::fabs(min_graphlaplacef)) / (max_graphlaplacef+ std::fabs(min_graphlaplacef));
    }

    const uint32_t id0 = mesh.addVertex(vertices[0], glm::vec4(glm::vec3(graphlaplacef_values[0]),1), glm::vec3(0), glm::vec3(0, 0, 1));
    const uint32_t id1 = mesh.addVertex(vertices[1], glm::vec4(glm::vec3(graphlaplacef_values[1]),1), glm::vec3(0), glm::vec3(0, 0, 1));
    const uint32_t id2 = mesh.addVertex(vertices[2], glm::vec4(glm::vec3(graphlaplacef_values[2]),1), glm::vec3(0), glm::vec3(0, 0, 1));
    const uint32_t id3 = mesh.addVertex(vertices[3], glm::vec4(glm::vec3(graphlaplacef_values[3]),1), glm::vec3(0), glm::vec3(0, 0, 1));
    const uint32_t id4 = mesh.addVertex(vertices[4], glm::vec4(glm::vec3(graphlaplacef_values[4]),1), glm::vec3(0), glm::vec3(0, 0, 1));
    const uint32_t id5 = mesh.addVertex(vertices[5], glm::vec4(glm::vec3(graphlaplacef_values[5]),1), glm::vec3(0), glm::vec3(0, 0, 1));

    const uint32_t indices[15] =
    {
        id0, id1, id2, id0, id2, id3, id0, id3, id4, id0, id4, id5, id0, id5, id1
    };

    for (uint32_t i = 0; i < 5; ++i)
    {
        mesh.addTriangle(indices[3 * i], indices[3 * i + 1], indices[3 * i + 2]);
    }
    mesh.create();

    Shader basic = Shader("lib/OpenGL Renderer/src/Shader/GLShaders/basic.vert", "lib/OpenGL Renderer/src/Shader/GLShaders/basic.frag");
    
    while (window.isOpen())
    {
        GL::clear(0.8,0.5,0.1);

        basic.bind();
        basic.setMVP();
        basic.setInt("u_set", 1);
        mesh.render();

        window.spinOnce();
    }

    LOGGER::end();

    return 0;
}
