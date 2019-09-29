#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <OpenGLObjects/VertexBuffer.h>
#include <OpenGLObjects/VertexBufferLayout.h>
#include <OpenGLObjects/IndexBuffer.h>
#include <OpenGLObjects/VertexArray.h>
#include <OpenGLObjects/Texture.h>
#include <DataStructure/Mesh.h>
#include <Shader/Shader.h>

#include <IO/KeyManager.h>
#include <Renderer/RenderWindow.h>
#include <Renderer/Camera.h>


int main(void)
{
	RenderWindow window = RenderWindow::createObject(800, 800, "Render Window");
	KeyManager::instance()->setup(window);
	Camera camera = Camera::createObject(window);

	Shader shader = Shader::createObject("C:/Users/DomenicZ/Documents/Visual Studio 2017/Projects/OpenGL Renderer/OpenGL Renderer/src/Shader/GLShaders/basic.vert",
								         "C:/Users/DomenicZ/Documents/Visual Studio 2017/Projects/OpenGL Renderer/OpenGL Renderer/src/Shader/GLShaders/basic.frag");

	Texture texture = Texture::createObject("res/sprite.png");
	shader.bind();
	shader.setVec4("u_color", glm::vec4(0.3, 0.1, 0.4, 1));
	shader.setInt("u_set", 0);
	shader.setInt("sprite", 0);

	Mesh mesh = Mesh::createObject();

	unsigned int id1 = mesh.addVertex(glm::vec4(-0.75f, -0.25f, 0.0f, 1.0f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f));
	unsigned int id2 = mesh.addVertex(glm::vec4(-0.25f, -0.25f, 0.0f, 1.0f), glm::vec4(0.0f, 1.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f));
	unsigned int id3 = mesh.addVertex(glm::vec4(-0.75f, 0.25f, 0.0f, 1.0f), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f));
	unsigned int id4 = mesh.addVertex(glm::vec4(-0.25f, 0.25f, 0.0f, 1.0f), glm::vec4(1.0f, 1.0f, 0.0f, 1.0f), glm::vec2(1.0f, 1.0f));

	mesh.addTriangle(id1, id2, id3);
	mesh.addTriangle(id3, id4, id2);

	mesh.create();

	Mesh mesh2 = Mesh::createObject();

	id1 = mesh2.addVertex(glm::vec4(0.25f, -0.25f, 0.0f, 1.0f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f));
	id2 = mesh2.addVertex(glm::vec4(0.75f, -0.25f, 0.0f, 1.0f), glm::vec4(0.0f, 1.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f));
	id3 = mesh2.addVertex(glm::vec4(0.25f, 0.25f, 0.0f, 1.0f), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f) , glm::vec2(0.0f, 1.0f));
	id4 = mesh2.addVertex(glm::vec4(0.75f, 0.25f, 0.0f, 1.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f));

	mesh2.addTriangle(id1, id2, id3);
	mesh2.addTriangle(id3, id4, id2);

	mesh2.create();

	/* Loop until the user closes the window */
	while (window.isOpen())
	{

		camera.processInput(0.005f);

		window.clear();

		shader.bind();
		shader.setInt("u_set", 0);
		shader.setMat4("MVP", camera.getProjection()*camera.getView(), GL_FALSE);
		mesh.render(window, shader);

		shader.setInt("u_set", 1);
		mesh2.render(window, shader);

		window.spinOnce();

		if (KeyManager::instance()->isKeyDown(GLFW_KEY_ESCAPE))
		{
			window.close();
		}
	}

	Shader::destroyObject(shader);
	RenderWindow::destroyObject(window);
	Texture::destroyObject(texture);
	Camera::destroyObject(camera);
	Mesh::destroyObject(mesh);
	Mesh::destroyObject(mesh2);

	return 0;
}