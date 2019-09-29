#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <OpenGLObjects/VertexBuffer.h>
#include <OpenGLObjects/VertexBufferLayout.h>
#include <OpenGLObjects/IndexBuffer.h>
#include <OpenGLObjects/VertexArray.h>
#include <OpenGLObjects/Texture.h>
#include <Shader/Shader.h>

#include <IO/KeyManager.h>
#include <Renderer/RenderWindow.h>
#include <Renderer/Camera.h>


int main(void)
{
	RenderWindow window = RenderWindow::createObject(800, 800, "Render Window");
	KeyManager::instance()->setup(window.getWindow());
	Camera camera = Camera::createObject(window);

	Shader shader = Shader::createObject("C:/Users/DomenicZ/Documents/Visual Studio 2017/Projects/OpenGL Renderer/OpenGL Renderer/src/Shader/GLShaders/basic.vert",
								         "C:/Users/DomenicZ/Documents/Visual Studio 2017/Projects/OpenGL Renderer/OpenGL Renderer/src/Shader/GLShaders/basic.frag");

	Texture texture = Texture::createObject("res/sprite.png");
	shader.bind();
	shader.setVec4("u_color", glm::vec4(0.3, 0.1, 0.4, 1));
	shader.setInt("u_set", 0);
	shader.setInt("sprite", 0);

	float vertices[] = {
	-0.75f, -0.25f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
	-0.25f, -0.25f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f,
	-0.75f, 0.25f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	-0.25f, 0.25f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f
	};

	VertexBuffer vbo = VertexBuffer::createObject(vertices, 44);
	VertexBufferLayout layout;

	layout.add<float>(4);
	layout.add<float>(4);
	layout.add<float>(2);
	
	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 1
	};

	IndexBuffer ibo = IndexBuffer::createObject(indices, 6);

	float vertices2[] = {
	0.25f, -0.25f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
	0.75f, -0.25f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f,
	0.25f, 0.25f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
	0.75f, 0.25f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f
	};
	VertexBuffer vbo2 = VertexBuffer::createObject(vertices2, 32);
	VertexBufferLayout layout2;
	layout2.add<float>(4);
	layout2.add<float>(4);


	VertexArray vao = VertexArray::createObject();
	VertexArray vao2 = VertexArray::createObject();

	
	vao.addBuffer(vbo, layout, ibo);

	vao2.addBuffer(vbo2, layout2, ibo);

	/* Loop until the user closes the window */
	while (window.isOpen())
	{

		camera.processInput(0.005f);

		window.clear();

		shader.bind();
		shader.setInt("u_set", 0);
		shader.setMat4("MVP", camera.getProjection()*camera.getView(), GL_FALSE);
		window.render(vao, ibo, shader);

		vao2.bind();
		shader.setInt("u_set", 1);
		window.render(vao2, ibo, shader);

		window.spinOnce();

		if (KeyManager::instance()->isKeyDown(GLFW_KEY_ESCAPE))
		{
			window.close();
		}
	}

	VertexBuffer::destroyObject(vbo);
	VertexBuffer::destroyObject(vbo2);
	VertexArray::destroyObject(vao);
	VertexArray::destroyObject(vao2);
	IndexBuffer::destroyObject(ibo);
	Shader::destroyObject(shader);
	RenderWindow::destroyObject(window);

	return 0;
}