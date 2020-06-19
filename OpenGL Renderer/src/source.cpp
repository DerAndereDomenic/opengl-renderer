#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <OpenGLObjects/FrameBuffer.h>
#include <DataStructure/Mesh.h>
#include <DataStructure/MeshHelper.h>
#include <DataStructure/RenderObject.h>
#include <DataStructure/Skybox.h>
#include <DataStructure/Scene.h>
#include <Shader/Shader.h>

#include <IO/KeyManager.h>
#include <IO/ObjLoader.h>
#include <Renderer/RenderWindow.h>
#include <Renderer/Camera.h>
#include <DataStructure/EnvironmentMap.h>

#define LIGHTS 1


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

	std::vector<std::string> names;
	std::vector<Mesh> meshes;
	std::vector<Material> materials;
	std::vector<glm::mat4> models;

	names.push_back("Crate");

	Mesh crate = MeshHelper::cubeMesh(glm::vec4(0, 0, 0, 1));
	meshes.push_back(crate);

	Material mat_crate = Material::createObject("materialmap");
	mat_crate.texture_diffuse = Texture::createObject("res/crate_diffuse.png");
	mat_crate.texture_specular = Texture::createObject("res/crate_specular.png");
	mat_crate.useTextures = true;
	mat_crate.shininess = 0.4f * 128.0f;
	materials.push_back(mat_crate);

	models.push_back(glm::translate(glm::mat4(1), glm::vec3(1, 0.5, 0)));

	names.push_back("Table");

	Mesh table = ObjLoader::loadObj("res/table/simple-table.obj", true)[0];
	meshes.push_back(table);

	Material mat_table = Material::createObject("materialmap");
	mat_table.texture_diffuse = Texture::createObject("res/table/table_diffuse.png");
	mat_table.texture_specular = Texture::createObject("res/table/table_specular.png");
	mat_table.texture_normal = Texture::createObject("res/table/table_normal.png");
	mat_table.shininess = 128.0f * 0.4f;
	mat_table.useTextures = true;
	materials.push_back(mat_table);

	models.push_back(glm::translate(glm::mat4(1), glm::vec3(-3, 0, 2)));

	names.push_back("Wall");

	Mesh wall = MeshHelper::cuboidMesh(glm::vec4(0, 0, 0, 1), 10.0f, 10.0f, 0.2f, true);
	meshes.push_back(wall);

	Material mat_brick = Material::createObject("materialmap");
	mat_brick.texture_diffuse = Texture::createObject("res/brickwall.png");
	mat_brick.texture_specular = mat_brick.texture_diffuse;
	mat_brick.texture_normal = Texture::createObject("res/brickwall_normal.png");
	mat_brick.useTextures = true;
	mat_brick.shininess = 0.4f * 128.0f;
	materials.push_back(mat_brick);

	models.push_back(glm::translate(glm::mat4(1),glm::vec3(0, 5.0f, -5.0f)));

	names.push_back("Plane");

	Mesh mesh = MeshHelper::cuboidMesh(glm::vec4(1, 0, 0, 1), 10.0f, 0.2f, 10.0f, true);
	meshes.push_back(mesh);

	Material mat_fabric = Material::createObject("materialmap");
	mat_fabric.texture_diffuse = Texture::createObject("res/fabric.png");
	mat_fabric.texture_specular = mat_fabric.texture_diffuse;
	mat_fabric.texture_normal = Texture::createObject("res/fabric_normal.png");
	mat_fabric.useTextures = true;
	mat_fabric.shininess = 0.4f * 128.0f;
	materials.push_back(mat_fabric);

	models.push_back(glm::translate(glm::mat4(1), glm::vec3(0,-0.1,0)));

	names.push_back("suzanne");

	Mesh suzanne = ObjLoader::loadObj("res/suzanne_blender.obj")[0];
	meshes.push_back(suzanne);

	Material mat_suzanne = Material::createObject("materialmap");
	mat_suzanne.ambient = glm::vec3(0.24725f, 0.1995f, 0.0745f);
	mat_suzanne.diffuse = glm::vec3(0.75164f, 0.60648f, 0.22648f);
	mat_suzanne.specular = glm::vec3(0.628281f, 0.555802f, 0.366065f);
	mat_suzanne.shininess = 0.4f * 16.0f;
	materials.push_back(mat_suzanne);

	models.push_back(glm::translate(glm::mat4(1), glm::vec3(0, 7, 0)));

	//names.push_back("Sphere");

	Mesh sphere = ObjLoader::loadObj("res/sphere.obj")[0];
	sphere.create();
	//meshes.push_back(sphere);
	//materials.push_back(mat_sphere);

	//models.push_back(glm::translate(glm::mat4(1), glm::vec3(-2,3.0f, 0.0f)));

	names.push_back("BRDF Sphere");

	Mesh sphere_brdf = ObjLoader::loadObj("res/sphere.obj")[0];
	meshes.push_back(sphere_brdf);

	Material mat_brdf = Material::createObject("materialmap", MaterialType::GGX);
	mat_brdf.ambient = glm::vec3(0.1f, 0.1f, 0.1f);
	mat_brdf.diffuse = glm::vec3(1.0f, 1.0f, 1.0f);
	mat_brdf.specular = glm::vec3(1.0f, 1.0f, 1.0f);
	mat_brdf.shininess = 0.4f * 512.0f;

	materials.push_back(mat_brdf);

	models.push_back(glm::translate(glm::mat4(1), glm::vec3(0, 2, 6)));

	Mesh light = MeshHelper::cubeMesh(glm::vec4(1, 1, 1, 1));
	light.create();

	Material mat_lamp = Material::createObject("materialmap");
	mat_lamp.ambient = glm::vec3(10, 10, 10);
	mat_lamp.diffuse = glm::vec3(1, 1, 1);
	mat_lamp.specular = glm::vec3(1, 1, 1);
	mat_lamp.shininess = 128.0f * 0.4;

	RenderObject obj_light = RenderObject::createObject(light, mat_lamp, glm::translate(glm::mat4(1), glm::vec3(20, 0, 0)));

	Light l1;
	l1.ambient = glm::vec3(0.1f);//glm::vec3(0.1f, 0.0f, 0.0f);
	l1.diffuse = glm::vec3(1.0f);// glm::vec3(1.0f, 0.0f, 0.0f);
	l1.specular = glm::vec3(1.0f);//glm::vec3(1.0f, 0.0f, 0.0f);
	l1.position = glm::vec3(20,0,0);

	Light lights[LIGHTS] = { l1};

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

	Scene scene = Scene::createObject(names, meshes, materials, models);
	names.clear();
	meshes.clear();
	materials.clear();
	models.clear();

	//---------------------------------------------------------------------------------//
	//                              RENDERING SETUP                                    //
	//---------------------------------------------------------------------------------//

	Shader post = Shader::createObject("src/Shader/GLShaders/Post.vert",
		"src/Shader/GLShaders/Post.frag");

	Shader normal = Shader::createObject("src/Shader/GLShaders/Normal.vert",
		"src/Shader/GLShaders/Normal.frag");

	Shader shadow = Shader::createObject("src/Shader/GLShaders/Shadow.vert",
		"src/Shader/GLShaders/Shadow.frag");

	Shader cm = Shader::createObject("src/Shader/GLShaders/CubeMap.vert",
		"src/Shader/GLShaders/CubeMap.frag");

	Shader reflection = Shader::createObject("src/Shader/GLShaders/Reflection.vert",
		"src/Shader/GLShaders/Reflection.frag");

	FrameBuffer fbo = FrameBuffer::createObject(width, height);
	fbo.attachColor();
	fbo.attachColor();
	fbo.attachRenderBuffer();
	fbo.verify();
	fbo.unbind();

	EnvironmentMap map = EnvironmentMap::createObject(glm::vec3(0, 5, 0));

	glm::mat4 lightProjection = glm::perspective(360.0f, window.getAspectRatio(), near, far);
	
	for (unsigned int i = 0; i < LIGHTS; ++i)
	{
		lights[i].shadow_map = FrameBuffer::createObject(shadow_width, shadow_height);
		lights[i].shadow_map.attachDepthMap();
		lights[i].shadow_map.disableColor();
		lights[i].shadow_map.verify();
		lights[i].shadow_map.unbind();

		lights[i].lightView = glm::lookAt(lights[i].position, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		lights[i].lightSpace = lightProjection * lights[i].lightView;

	}

	double lastTime = glfwGetTime();
	int nbFrames = 0;

	post.bind();
	post.setInt("screenTexture", 0);
	post.setInt("lightTexture", 1);

	Skybox sky = Skybox::createObject(skybox);

	normal.bind();

	for (unsigned int i = 0; i < LIGHTS; ++i)
	{
		normal.setLight("lights_frag["+std::to_string(i)+"]", lights[i]);
		normal.setMat4("lights_vert["+ std::to_string(i) +"].lightSpaceMatrix", lights[i].lightSpace);
		normal.setInt("lights_frag["+ std::to_string(i) +"].shadow_map", 4+i);
	}
	

	glm::mat4 rotate = glm::rotate(glm::mat4(1), 3.14159f/4.0f, glm::vec3(0,0,1));

	lights[0].position = rotate * glm::vec4(lights[0].position, 1);
	obj_light.setModel(glm::translate(glm::mat4(1), lights[0].position));
	
	shadow.bind();
	shadow.setMat4("P", lightProjection);

	unsigned int frameID = 0;

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
		
		for (unsigned int i = 0; i < LIGHTS;++i) 
		{
			lights[i].shadow_map.bind();
			window.clear();
			lights[i].lightView = glm::lookAt(lights[i].position, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			lights[i].lightSpace = lightProjection * lights[i].lightView;

			//Wall
			shadow.bind();
			shadow.setMat4("V", lights[i].lightView);
			scene.render(shadow);
		}

		//----------------------------------------------------------------------------------------------
		window.resetViewport();
		//Render scene
		normal.bind();
		map.render(scene, sky, normal);

		window.resetViewport();
		fbo.bind();

		window.clear();
		glDrawBuffer(GL_COLOR_ATTACHMENT0);
		//Skybox
		//Use vertex data of the light block

		sky.render(camera);

		reflection.bind();
		reflection.setInt("cubemap", 0);
		reflection.setVec3("camera_position", camera.getPosition());
		map.getCubeMap().bind();
		reflection.setMVP(glm::translate(glm::mat4(1), glm::vec3(0, 5, 0)), camera.getView(), camera.getProjection());
		sphere.render();
		
		//Light
		normal.bind();
		normal.setVec3("viewPos", camera.getPosition());
		for (unsigned int i = 0; i < LIGHTS; ++i)
		{
			normal.setLight("lights_frag["+std::to_string(i)+"]", lights[i]);
			normal.setMat4("lights_vert["+std::to_string(i) + +"].lightSpaceMatrix", lights[i].lightSpace);
			lights[i].shadow_map.getTexture().bind(4+i);
		}
		normal.setMVP(glm::mat4(1), camera.getView(), camera.getProjection());
		
		scene.render(normal);

		//Render light
		unsigned int attachments[2] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1 };
		glDrawBuffers(2, attachments);

		obj_light.render(normal);


		//Render to quad
		fbo.unbind();
		window.clear();
		post.bind();
		fbo.getTexture(0).bind(0);
		fbo.getTexture(1).bind(1);
		quad.render();		

		window.spinOnce();

		frameID += 1;

		if (KeyManager::instance()->isKeyDown(GLFW_KEY_ESCAPE))
		{
			window.close();
		}
	}

	Shader::destroyObject(post);
	Shader::destroyObject(normal);
	Shader::destroyObject(shadow);
	Shader::destroyObject(reflection);
	Skybox::destroyObject(sky);
	RenderWindow::destroyObject(window);
	Camera::destroyObject(camera);
	Mesh::destroyObject(quad);
	RenderObject::destroyObject(obj_light);
	Scene::destroyObject(scene);
	FrameBuffer::destroyObject(fbo);
	FrameBuffer::destroyObject(lights[0].shadow_map);

	return 0;
}