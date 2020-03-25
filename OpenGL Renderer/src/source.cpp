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

	Shader basic = Shader::createObject("src/Shader/GLShaders/basic.vert",
										"src/Shader/GLShaders/basic.frag");

	Shader normal = Shader::createObject("src/Shader/GLShaders/Normal.vert",
										 "src/Shader/GLShaders/Normal.frag");

	Texture diffuse = Texture::createObject("res/crate_diffuse.png");
	Texture specular = Texture::createObject("res/crate_specular.png");

	Texture brickwall = Texture::createObject("res/brickwall.png");
	Texture brickwall_normal = Texture::createObject("res/brickwall_normal.png");

	Texture fabric = Texture::createObject("res/fabric.png");
	Texture fabric_normal = Texture::createObject("res/fabric_normal.png");

	normal.bind();
	normal.setVec4("lightcolor", glm::vec4(1, 1, 1, 1));

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

	Mesh mesh = MeshHelper::cuboidMesh(glm::vec4(1, 0, 0, 1), 10.0f, 0.2f, 10.0f, true);
	mesh.create();

	Mesh wall = MeshHelper::cuboidMesh(glm::vec4(0, 0, 0, 1), 10.0f, 10.0f, 0.2f, true);
	wall.create();

	Mesh light = MeshHelper::cubeMesh(glm::vec4(1, 1, 1, 1));
	light.create();

	Mesh crate = MeshHelper::cubeMesh(glm::vec4(0, 0, 0, 1));
	crate.create();

	FrameBuffer fbo = FrameBuffer::createObject(800, 800);

	fbo.unbind();

	double lastTime = glfwGetTime();
	int nbFrames = 0;

	glm::vec3 lightPos(0, 0, -7);

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
	materialmap.shininess = 256.0f*0.4;

	shader.setMaterial("material", material);
	shader.setMaterial("materialmap", materialmap);
	shader.setLight("light", licht);

	normal.bind();
	normal.setMaterial("materialmap", materialmap);
	normal.setLight("light", licht);

	glm::mat4 rotate = glm::rotate(glm::mat4(1), 0.01f, glm::vec3(1, 0, 0));

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

		basic.bind();
		basic.setMVP(glm::mat4(1), camera.getView(), camera.getProjection());
		basic.setInt("u_set", 1);

		normal.bind();
		

		//Wall
		brickwall.bind(0);
		brickwall_normal.bind(1);
		normal.setMVP(glm::translate(glm::mat4(1),
									 glm::vec3(0, 5.0f, -5.0f)),
									 camera.getView(), camera.getProjection());
		normal.setVec3("light.position", lightPos);
		wall.render(window, normal);


		//Plane
		fabric.bind(0);
		fabric_normal.bind(1);
		normal.bind();
		normal.setMat4("M", glm::mat4(1));
		normal.setMaterial("material", material);
		mesh.render(window, normal);


		//Crate
		shader.bind();
		shader.setMVP(glm::translate(glm::mat4(1), glm::vec3(1, 0.6, 0)),
									 camera.getView(),
									 camera.getProjection());
		shader.setBool("useMap", true);
		shader.setVec3("light.position", lightPos);
		shader.setVec3("viewPos", camera.getPosition());
		diffuse.bind(0);
		specular.bind(1);
		crate.render(window, shader);

		//Render light
		lightPos = rotate * glm::vec4(lightPos, 1);

		basic.bind();
		basic.setMat4("M", glm::translate(glm::mat4(1), lightPos));
		light.render(window, basic);


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
	Shader::destroyObject(basic);
	RenderWindow::destroyObject(window);
	Texture::destroyObject(diffuse);
	Texture::destroyObject(specular);
	Texture::destroyObject(brickwall);
	Texture::destroyObject(brickwall_normal);
	Texture::destroyObject(fabric);
	Texture::destroyObject(fabric_normal);
	Camera::destroyObject(camera);
	Mesh::destroyObject(mesh);
	Mesh::destroyObject(quad);
	Mesh::destroyObject(light);
	Mesh::destroyObject(crate);
	Mesh::destroyObject(wall);
	FrameBuffer::destroyObject(fbo);

	return 0;
}