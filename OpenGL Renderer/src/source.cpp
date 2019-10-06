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

	Shader shader = Shader::createObject("C:/Users/DomenicZ/Documents/Visual Studio 2017/Projects/OpenGL Renderer/OpenGL Renderer/src/Shader/GLShaders/Lightning.vert",
								         "C:/Users/DomenicZ/Documents/Visual Studio 2017/Projects/OpenGL Renderer/OpenGL Renderer/src/Shader/GLShaders/Lightning.frag");

	Shader post = Shader::createObject("C:/Users/DomenicZ/Documents/Visual Studio 2017/Projects/OpenGL Renderer/OpenGL Renderer/src/Shader/GLShaders/Post.vert",
		                               "C:/Users/DomenicZ/Documents/Visual Studio 2017/Projects/OpenGL Renderer/OpenGL Renderer/src/Shader/GLShaders/Post.frag");

	Texture diffuse = Texture::createObject("res/crate_diffuse.png");
	Texture specular = Texture::createObject("res/crate_specular.png");

	shader.bind();
	shader.setVec4("lightcolor", glm::vec4(1, 1, 1, 1));

	Mesh quad = Mesh::createObject();

	unsigned int id1, id2, id3, id4;

	id1 = quad.addVertex(glm::vec3(-1, -1, 0), glm::vec4(1), glm::vec2(0), glm::vec3(0,0,1));
	id2 = quad.addVertex(glm::vec3(1, -1, 0), glm::vec4(1), glm::vec2(1, 0), glm::vec3(0, 0, 1));
	id3 = quad.addVertex(glm::vec3(1, 1, 0), glm::vec4(1), glm::vec2(1, 1), glm::vec3(0, 0, 1));
	id4 = quad.addVertex(glm::vec3(-1, 1, 0), glm::vec4(1), glm::vec2(0, 1), glm::vec3(0, 0, 1));

	quad.addTriangle(id1, id2, id3);
	quad.addTriangle(id1, id3, id4);

	quad.create();

	Mesh mesh = MeshHelper::cuboidMesh(glm::vec4(1, 0, 0, 1), 10.0f, 0.2f, 10.0f);
	mesh.create();

	Mesh light = MeshHelper::cubeMesh(glm::vec4(1, 1, 1, 1));
	light.create();

	FrameBuffer fbo = FrameBuffer::createObject(800, 800);

	fbo.unbind();

	double lastTime = glfwGetTime();
	int nbFrames = 0;

	glm::mat4 rot = glm::rotate(glm::mat4(1), 0.001f, glm::vec3(1, 0, 0));
	glm::vec3 lightPos(0, 0, -5);

	Material material;
	material.ambient = glm::vec3(0.24725f, 0.1995f, 0.0745f);
	material.diffuse = glm::vec3(0.75164f, 0.60648f, 0.22648f);
	material.specular = glm::vec3(0.628281f, 0.555802f, 0.366065f);
	material.shininess =  128.0f*0.4f;

	Light licht;
	licht.ambient = glm::vec3(0.1f, 0.1f, 0.1f);
	licht.diffuse = glm::vec3(1.0f, 1.0f, 1.0f);
	licht.specular = glm::vec3(1.0f, 1.0f, 1.0f);
	licht.position =  lightPos;

	MaterialMap materialmap;
	materialmap.diffuse = 0;
	materialmap.specular = 1;
	materialmap.shininess = 128.0f*0.4;

	shader.setMaterial("material", material);
	shader.setLight("light", licht);

	/* Loop until the user closes the window */
	while (window.isOpen())
	{

		double currentTime = glfwGetTime();
		nbFrames++;
		if (currentTime - lastTime >= 1.0)
		{
			printf("%f fps\n", double(nbFrames));
			nbFrames = 0;
			lastTime += 1.0;
		}

		camera.processInput(0.005f);

		//Render scene
		fbo.bind();
		window.clear();
		shader.bind();
		shader.setMat4("P", camera.getProjection(), GL_FALSE);
		shader.setMat4("V", camera.getView(), GL_FALSE);
		shader.setMat4("M", glm::mat4(1), GL_FALSE);
		shader.setInt("isLight", false);
		mesh.render(window, shader);

		//Render light
		lightPos = rot * glm::vec4(lightPos, 1);
		shader.setMat4("M", glm::translate(glm::mat4(1), lightPos), GL_FALSE);
		shader.setVec3("light.position", lightPos);
		shader.setVec3("viewPos", camera.getPosition());
		shader.setInt("isLight", true);
		light.render(window, shader);


		//Render to quad
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
	Shader::destroyObject(post);
	RenderWindow::destroyObject(window);
	Texture::destroyObject(diffuse);
	Texture::destroyObject(specular);
	Camera::destroyObject(camera);
	Mesh::destroyObject(mesh);
	Mesh::destroyObject(quad);
	Mesh::destroyObject(light);
	FrameBuffer::destroyObject(fbo);

	return 0;
}