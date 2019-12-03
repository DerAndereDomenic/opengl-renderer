#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <OpenGLObjects/FrameBuffer.h>
#include <DataStructure/Mesh.h>
#include <DataStructure/MeshHelper.h>
#include <Shader/Shader.h>

#include <IO/KeyManager.h>
#include <IO/ObjLoader.h>
#include <Renderer/RenderWindow.h>
#include <Renderer/Camera.h>


int main(void)
{
	RenderWindow window = RenderWindow::createObject(800, 800, "Render Window");
	KeyManager::instance()->setup(window);
	Camera camera = Camera::createObject(window);

	Shader shader = Shader::createObject("src/Shader/GLShaders/Lightning.vert",
								         "src/Shader/GLShaders/Lightning.frag");

	Shader post = Shader::createObject("src/Shader/GLShaders/Post.vert",
		                               "src/Shader/GLShaders/Post.frag");

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

	Mesh crate = MeshHelper::cubeMesh(glm::vec4(0, 0, 0, 1));
	crate.create();

	Mesh sphere = ObjLoader::loadObj("res/sphere.obj");
	sphere.create();

	Mesh suzanne = ObjLoader::loadObj("res/suzanne_blender.obj");
	suzanne.create();

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

	Material material_sphere;
	material_sphere.ambient = glm::vec3(0.25, 0.25, 0.25);
	material_sphere.diffuse = glm::vec3(0.4, 0.4, 0.4);
	material_sphere.specular = glm::vec3(0.774597, 0.774597, 0.774597);
	material_sphere.shininess = 128.0f*0.6;

	Material diffuse_blue;
	diffuse_blue.ambient = glm::vec3(0, 0, 0.2);
	diffuse_blue.diffuse = glm::vec3(0, 0, 0.8);
	diffuse_blue.specular = glm::vec3(0, 0, 0);
	diffuse_blue.shininess = 1;

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
	shader.setMaterial("materialmap", materialmap);
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
		shader.setBool("useMap", false);
		//Plane
		shader.setMaterial("material", material);
		mesh.render(window, shader);
		//Sphere
		shader.setMaterial("material", material_sphere);
		shader.setMat4("M", glm::translate(glm::mat4(1), glm::vec3(-0.5, 2.0, -1.0)), GL_FALSE);
		sphere.render(window, shader);
		//Suzanne
		shader.setMaterial("material", diffuse_blue);
		shader.setMat4("M", glm::translate(glm::mat4(1), glm::vec3(3, 3, 3)), GL_FALSE);
		suzanne.render(window, shader);
		//Crate
		shader.setMat4("M", glm::translate(glm::mat4(1), glm::vec3(1, 0.6, 0)), GL_FALSE);
		shader.setBool("useMap", true);
		diffuse.bind(0);
		specular.bind(1);
		crate.render(window, shader);

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
	Mesh::destroyObject(crate);
	Mesh::destroyObject(sphere);
	FrameBuffer::destroyObject(fbo);

	return 0;
}