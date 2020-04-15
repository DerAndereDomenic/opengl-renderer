#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <OpenGLObjects/FrameBuffer.h>
#include <DataStructure/Mesh.h>
#include <DataStructure/MeshHelper.h>
#include <DataStructure/RenderObject.h>
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

	//---------------------------------------------------------------------------------//
	//                              SCENE SETUP                                        //
	//---------------------------------------------------------------------------------//
	Mesh crate = MeshHelper::cubeMesh(glm::vec4(0, 0, 0, 1));
	crate.create();

	Material mat_crate = Material::createObject("materialmap");
	mat_crate.texture_diffuse = Texture::createObject("res/crate_diffuse.png");
	mat_crate.texture_specular = Texture::createObject("res/crate_specular.png");
	mat_crate.useTextures = true;
	mat_crate.shininess = 0.4f * 128.0f;

	RenderObject obj_crate = RenderObject::createObject(crate, mat_crate, glm::translate(glm::mat4(1), glm::vec3(1, 0.5, 0)));

	Mesh wall = MeshHelper::cuboidMesh(glm::vec4(0, 0, 0, 1), 10.0f, 10.0f, 0.2f, true);
	wall.create();

	Material mat_brick = Material::createObject("materialmap");
	mat_brick.texture_diffuse = Texture::createObject("res/brickwall.png");
	mat_brick.texture_specular = mat_brick.texture_diffuse;
	mat_brick.texture_normal = Texture::createObject("res/brickwall_normal.png");
	mat_brick.useTextures = true;
	mat_brick.shininess = 0.4f * 128.0f;

	RenderObject obj_wall = RenderObject::createObject(wall, mat_brick, glm::translate(glm::mat4(1), glm::vec3(0, 5.0f, -5.0f)));

	//Mesh mesh = MeshHelper::cuboidMesh(glm::vec4(1, 0, 0, 1), 10.0f, 0.2f, 10.0f, true);
	//mesh.create();
	Mesh mesh = ObjLoader::loadObj("res/plane.obj", true);
	mesh.create();

	Material mat_fabric = Material::createObject("materialmap");
	mat_fabric.texture_diffuse = Texture::createObject("res/fabric.png");
	mat_fabric.texture_specular = mat_fabric.texture_diffuse;
	mat_fabric.texture_normal = Texture::createObject("res/fabric_normal.png");
	mat_fabric.useTextures = true;
	mat_fabric.shininess = 0.4f * 128.0f; 

	RenderObject obj_fabric = RenderObject::createObject(mesh, mat_fabric, glm::mat4(1));

	Mesh suzanne = ObjLoader::loadObj("res/suzanne_blender.obj");
	suzanne.create();

	Material mat_suzanne = Material::createObject("materialmap");
	mat_suzanne.ambient = glm::vec3(0.24725f, 0.1995f, 0.0745f);
	mat_suzanne.diffuse = glm::vec3(0.75164f, 0.60648f, 0.22648f);
	mat_suzanne.specular = glm::vec3(0.628281f, 0.555802f, 0.366065f);
	mat_suzanne.shininess = 0.4f * 16.0f;

	RenderObject obj_suzanne = RenderObject::createObject(suzanne, mat_suzanne, glm::translate(glm::mat4(1), glm::vec3(0, 7, 0)));

	Mesh light = MeshHelper::cubeMesh(glm::vec4(1, 1, 1, 1));
	light.create();

	glm::vec3 lightPos(0, 5, 15);
	//lightPos = glm::vec3(-2.0f, 4.0f, -1.0f);

	Light licht;
	licht.ambient = glm::vec3(0.1f, 0.1f, 0.1f);
	licht.diffuse = glm::vec3(1.0f, 1.0f, 1.0f);
	licht.specular = glm::vec3(1.0f, 1.0f, 1.0f);
	licht.position = lightPos;

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

	//---------------------------------------------------------------------------------//
	//                              RENDERING SETUP                                    //
	//---------------------------------------------------------------------------------//

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
		obj_wall.render(window, shadow);

		//Plane
		obj_fabric.render(window, shadow);

		//Crate
		obj_crate.render(window, shadow);

		//Suzanne
		obj_suzanne.render(window, shadow);

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
		
		//Light
		normal.bind();
		normal.setVec3("light.position", lightPos);
		normal.setVec3("viewPos", camera.getPosition());
		normal.setMat4("lightSpaceMatrix", lightSpaceMatrix);
		shadow_map.getTexture().bind(4);
		normal.setMVP(glm::mat4(1), camera.getView(), camera.getProjection());
		normal.setVec3("light.position", lightPos);

		//Wall
		obj_wall.render(window, normal);

		//Plane
		obj_fabric.render(window, normal);

		//Crate
		obj_crate.render(window, normal);

		//Suzanne
		obj_suzanne.render(window, normal);

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
	Material::destroyObject(mat_crate);
	Material::destroyObject(mat_brick);
	Material::destroyObject(mat_fabric);
	Material::destroyObject(mat_suzanne);
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