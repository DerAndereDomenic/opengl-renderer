#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <OpenGLObjects/VertexBuffer.h>
#include <OpenGLObjects/VertexBufferLayout.h>


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

	float vertices[] = {
	-0.5f, -0.5f,
	0.5f, -0.5f,
	0.0f, 0.5f
	};

	VertexBuffer vbo = VertexBuffer::createObject(vertices, sizeof(float) * 6);
	VertexBufferLayout layout;

	layout.add<float>(2);
	unsigned int offset = 0;
	for (unsigned int i = 0; i < layout.getElements().size(); ++i)
	{
		BufferElement element = layout.getElements()[i];
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, element._count, element._type, element._normalized, layout.getVertexSize(), (const void*)offset);
		offset += element._count * BufferElement::getSizeOfType(element._type);
	}
	

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		vbo.bind();
		glDrawArrays(GL_TRIANGLES, 0, 3);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}