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
	unsigned int width = 1280;
	unsigned int height = 720;

	unsigned int shadow_width = 10000;
	unsigned int shadow_height = 10000;

	float near = 0.1f;
	float far = 500.0f;

	RenderWindow window = RenderWindow::createObject(width, height, "Render Window");
	KeyManager::instance()->setup(window);
	Camera camera = Camera::createObject(window, near, far);

	Shader post = Shader::createObject("src/Shader/GLShaders/Post.vert",
		                               "src/Shader/GLShaders/Post.frag");

	Shader basic = Shader::createObject("src/Shader/GLShaders/basic.vert",
										"src/Shader/GLShaders/basic.frag");

	Shader normal = Shader::createObject("src/Shader/GLShaders/Normal.vert",
										 "src/Shader/GLShaders/Normal.frag");

	Shader skybox_shader = Shader::createObject("src/Shader/GLShaders/Skybox.vert",
										 "src/Shader/GLShaders/Skybox.frag");

	Shader shadow = Shader::createObject("src/Shader/GLShaders/Shadow.vert",
										 "src/Shader/GLShaders/Shadow.frag");

	Texture diffuse = Texture::createObject("res/crate_diffuse.png");
	Texture specular = Texture::createObject("res/crate_specular.png");

	Texture brickwall = Texture::createObject("res/brickwall.png");
	Texture brickwall_normal = Texture::createObject("res/brickwall_normal.png");

	Texture fabric = Texture::createObject("res/fabric.png");
	Texture fabric_normal = Texture::createObject("res/fabric_normal.png");

	std::vector<std::string> faces =
	{
		"right.jpg",
		"left.jpg",
		"top.jpg",
		"bottom.jpg",
		"front.jpg",
		"back.jpg"
	};

	Texture skybox = Texture::createObject("res/skybox/", faces);

	Mesh quad = Mesh::createObject();

	unsigned int id1, id2, id3, id4;

	id1 = quad.addVertex(glm::vec3(-1, -1, 0), glm::vec4(1), glm::vec2(0), glm::vec3(0,0,1));
	id2 = quad.addVertex(glm::vec3(1, -1, 0), glm::vec4(1), glm::vec2(1, 0), glm::vec3(0, 0, 1));
	id3 = quad.addVertex(glm::vec3(1, 1, 0), glm::vec4(1), glm::vec2(1, 1), glm::vec3(0, 0, 1));
	id4 = quad.addVertex(glm::vec3(-1, 1, 0), glm::vec4(1), glm::vec2(0, 1), glm::vec3(0, 0, 1));

	quad.addTriangle(id1, id2, id3);
	quad.addTriangle(id1, id3, id4);

	quad.create();

	//Mesh mesh = MeshHelper::cuboidMesh(glm::vec4(1, 0, 0, 1), 10.0f, 0.2f, 10.0f, true);
	//mesh.create();
	Mesh mesh = ObjLoader::loadObj("res/plane.obj", true);
	mesh.create();

	Mesh wall = MeshHelper::cuboidMesh(glm::vec4(0, 0, 0, 1), 10.0f, 10.0f, 0.2f, true);
	wall.create();

	Mesh light = MeshHelper::cubeMesh(glm::vec4(1, 1, 1, 1));
	light.create();

	Mesh crate = MeshHelper::cubeMesh(glm::vec4(0, 0, 0, 1));
	crate.create();

	Mesh suzanne = ObjLoader::loadObj("res/suzanne_blender.obj");
	suzanne.create();

	FrameBuffer fbo = FrameBuffer::createObject(width, height);
	fbo.attachColor();
	fbo.attachColor();
	fbo.attachRenderBuffer();
	fbo.verify();
	fbo.unbind();

	FrameBuffer shadow_map = FrameBuffer::createObject(shadow_width, shadow_height);
	shadow_map.attachDepthMap();
	shadow_map.disableColor();
	shadow_map.verify();
	shadow_map.unbind();

	double lastTime = glfwGetTime();
	int nbFrames = 0;

	glm::vec3 lightPos(0, 5, 15);
	//lightPos = glm::vec3(-2.0f, 4.0f, -1.0f);
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
	materialmap.normal = 2;
	materialmap.height = 3;
	materialmap.shininess = 256.0f*0.4;

	glm::mat4 lightProjection = glm::perspective(360.0f, window.getAspectRatio(), near, far);

	//glm::mat4 lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, 1.0f, 50.0f);
	glm::mat4 lightView = glm::lookAt(lightPos, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	//glm::mat4 lightView = glm::lookAt(glm::vec3(-2.0f, 4.0f, -1.0f),
	//	glm::vec3(0.0f, 0.0f, 0.0f),
	//	glm::vec3(0.0f, 1.0f, 0.0f));

	glm::mat4 lightSpaceMatrix = lightProjection * lightView;

	post.bind();
	post.setInt("screenTexture", 0);
	post.setInt("lightTexture", 1);

	skybox_shader.bind();
	skybox_shader.setInt("skybox", 0);

	normal.bind();
	normal.setMaterial("materialmap", materialmap);
	normal.setMaterial("material", material);
	normal.setLight("light", licht);
	normal.setMat4("lightSpaceMatrix", lightSpaceMatrix);
	normal.setInt("shadowMap", 4);

	glm::mat4 rotate = glm::rotate(glm::mat4(1), 0.001f, glm::vec3(0, 1, 0));
	
	shadow.bind();
	shadow.setMat4("P", lightProjection);
	shadow.setMat4("V", lightView);

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

		window.setViewport(shadow_width, shadow_height);
		shadow_map.bind();
		window.clear();
		lightView = glm::lookAt(lightPos, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		lightSpaceMatrix = lightProjection * lightView;

		//Wall
		shadow.bind();
		shadow.setMat4("V", lightView);
		shadow.setMat4("M", glm::translate(glm::mat4(1), glm::vec3(0, 5.0f, -5.0f)));
		wall.render(window, shadow);

		//Plane
		shadow.setMat4("M", glm::mat4(1));
		mesh.render(window, shadow);

		//Crate
		shadow.setMat4("M", glm::translate(glm::mat4(1), glm::vec3(1, 0.5, 0)));
		crate.render(window, shadow);

		//Suzanne
		shadow.setMat4("M", glm::translate(glm::mat4(1), glm::vec3(0, 7, 0)));
		suzanne.render(window, shadow);

		//----------------------------------------------------------------------------------------------
		window.resetViewport();
		//Render scene
		fbo.bind();
		window.clear();
		glDrawBuffer(GL_COLOR_ATTACHMENT0);

		//Skybox
		//Use vertex data of the light block
		window.disableDepthWriting();
		skybox_shader.bind();
		skybox.bind(0);
		skybox_shader.setMVP(glm::mat4(1),
							 glm::mat4(glm::mat3(camera.getView())),
							 camera.getProjection());
		light.render(window, skybox_shader);
		window.enableDepthWriting();
		
		//Wall
		normal.bind();
		normal.setBool("useMap", true);
		normal.setMat4("lightSpaceMatrix", lightSpaceMatrix);
		brickwall.bind(0);
		brickwall.bind(1);
		brickwall_normal.bind(2);
		shadow_map.getTexture().bind(4);
		normal.setMVP(glm::translate(glm::mat4(1),
									 glm::vec3(0, 5.0f, -5.0f)),
									 camera.getView(), camera.getProjection());
		normal.setVec3("light.position", lightPos);
		wall.render(window, normal);

		//Plane
		fabric.bind(0);
		fabric.bind(1);
		fabric_normal.bind(2);
		normal.setMat4("M", glm::mat4(1));
		mesh.render(window, normal);

		//Crate
		fabric_normal.unbind(2);
		diffuse.bind(0);
		specular.bind(1);
		normal.setMat4("M", glm::translate(glm::mat4(1), glm::vec3(1, 0.5, 0)));
		normal.setVec3("light.position", lightPos);
		normal.setVec3("viewPos", camera.getPosition());
		crate.render(window, normal);

		//Suzanne
		normal.setBool("useMap", false);
		normal.setMat4("M", glm::translate(glm::mat4(1), glm::vec3(0, 7, 0)));
		suzanne.render(window, normal);

		//Render light
		lightPos = rotate * glm::vec4(lightPos, 1);
		unsigned int attachments[2] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1 };
		glDrawBuffers(2, attachments);

		basic.bind();
		basic.setMVP(glm::translate(glm::mat4(1), lightPos), camera.getView(), camera.getProjection());
		basic.setInt("u_set", 1);
		light.render(window, basic);

		//Render to quad
		fbo.unbind();
		window.clear();
		post.bind();
		fbo.getTexture(0).bind(0);
		fbo.getTexture(1).bind(1);
		quad.render(window, post);		

		window.spinOnce();

		if (KeyManager::instance()->isKeyDown(GLFW_KEY_ESCAPE))
		{
			window.close();
		}
	}

	Shader::destroyObject(post);
	Shader::destroyObject(basic);
	Shader::destroyObject(normal);
	Shader::destroyObject(shadow);
	Shader::destroyObject(skybox_shader);
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
	Mesh::destroyObject(suzanne);
	FrameBuffer::destroyObject(fbo);
	FrameBuffer::destroyObject(shadow_map);

	return 0;
}