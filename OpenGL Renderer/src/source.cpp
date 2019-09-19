#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <OpenGLObjects/VertexBuffer.h>
#include <OpenGLObjects/VertexBufferLayout.h>
#include <OpenGLObjects/IndexBuffer.h>
#include <OpenGLObjects/VertexArray.h>
#include <Shader/Shader.h>


int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK)
		return -1;

	Shader shader = Shader::createObject("C:/Users/DomenicZ/Documents/Visual Studio 2017/Projects/OpenGL Renderer/OpenGL Renderer/src/Shader/GLShaders/basic.vert",
								         "C:/Users/DomenicZ/Documents/Visual Studio 2017/Projects/OpenGL Renderer/OpenGL Renderer/src/Shader/GLShaders/basic.frag");

	float vertices[] = {
	-0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
	0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f,
	-0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
	0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f
	};

	VertexBuffer vbo = VertexBuffer::createObject(vertices, 32);
	VertexBufferLayout layout;

	layout.add<float>(4);
	layout.add<float>(4);
	
	VertexArray vao = VertexArray::createObject();
	vao.addBuffer(vbo, layout);
	
	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 1
	};

	IndexBuffer ibo = IndexBuffer::createObject(indices, 6);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		vbo.bind();
		ibo.bind();
		shader.bind();

		vao.bind();
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawElements(GL_TRIANGLES, ibo.getCount(), GL_UNSIGNED_INT, (void*)0);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	VertexBuffer::destroyObject(vbo);
	IndexBuffer::destroyObject(ibo);
	Shader::destroyObject(shader);

	glfwTerminate();
	return 0;
}