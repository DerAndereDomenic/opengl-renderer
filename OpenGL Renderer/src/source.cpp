#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <OpenGLObjects/FrameBuffer.h>
#include <DataStructure/Mesh.h>
#include <DataStructure/MeshHelper.h>
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

	Shader post = Shader::createObject("C:/Users/DomenicZ/Documents/Visual Studio 2017/Projects/OpenGL Renderer/OpenGL Renderer/src/Shader/GLShaders/Post.vert",
		                               "C:/Users/DomenicZ/Documents/Visual Studio 2017/Projects/OpenGL Renderer/OpenGL Renderer/src/Shader/GLShaders/Post.frag");

	Texture texture = Texture::createObject("res/sprite.png");
	shader.bind();
	shader.setVec4("u_color", glm::vec4(0.3, 0.1, 0.4, 1));
	shader.setInt("u_set", 0);
	shader.setInt("sprite", 0);

	Mesh quad = Mesh::createObject();

	unsigned int id1, id2, id3, id4;

	id1 = quad.addVertex(glm::vec4(-1, -1, 0, 1), glm::vec4(1), glm::vec2(0));
	id2 = quad.addVertex(glm::vec4(1, -1, 0, 1), glm::vec4(1), glm::vec2(1, 0));
	id3 = quad.addVertex(glm::vec4(1, 1, 0, 1), glm::vec4(1), glm::vec2(1, 1));
	id4 = quad.addVertex(glm::vec4(-1, 1, 0, 1), glm::vec4(1), glm::vec2(0, 1));

	quad.addTriangle(id1, id2, id3);
	quad.addTriangle(id1, id3, id4);

	quad.create();

	Mesh mesh = MeshHelper::cubeMesh(glm::vec4(1, 0, 0, 1));
	mesh.create();

	Mesh light = MeshHelper::cubeMesh(glm::vec4(1, 1, 1, 1));
	light.create();

	FrameBuffer fbo = FrameBuffer::createObject(800, 800);

	fbo.unbind();
	texture.bind();

	/* Loop until the user closes the window */
	while (window.isOpen())
	{

		camera.processInput(0.005f);

		fbo.bind();
		window.clear();
		shader.bind();
		texture.bind();
		shader.setInt("u_set", 1);
		shader.setMat4("P", camera.getProjection(), GL_FALSE);
		shader.setMat4("V", camera.getView(), GL_FALSE);
		shader.setMat4("M", glm::mat4(1), GL_FALSE);
		mesh.render(window, shader);
		shader.setMat4("M", glm::translate(glm::mat4(1), glm::vec3(-4, 3, 1)), GL_FALSE);
		light.render(window, shader);

		fbo.unbind();
		window.clear();
		post.bind();
		fbo.getTexture().bind();
		quad.render(window, post);

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

	return 0;
}