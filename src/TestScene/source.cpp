#include <OpenGLRendererConfig.h>
#include <Core/Platform.h>
#include <Core/GLFunctions.h>
#include <DLogger/Logger.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <OpenGLObjects/FrameBuffer.h>
#include <DataStructure/Mesh.h>
#include <DataStructure/MeshHelper.h>
#include <DataStructure/RenderObject.h>
#include <DataStructure/Skybox.h>
#include <DataStructure/Scene.h>
#include <Shader/ShaderManager.h>
#include <IO/KeyManager.h>
#include <IO/ObjLoader.h>
#include <Renderer/RenderWindow.h>
#include <Renderer/Camera.h>
#include <DataStructure/EnvironmentMap.h>
#include <Renderer/TextRenderer.h>
#include <Renderer/ParticleRenderer.h>
#include <GUI/DebugControl.h>
#include <GUI/ExposureControl.h>
#include <GUI/WindowClose.h>
#include <GUI/ModeControl.h>
#include <GUI/Button.h>

#include <iomanip>
#include <sstream>


int main(void)
{
	LOGGER::setProject("OpenGL Renderer", std::to_string(OpenGLRenderer_VERSION_MAJOR) + "." + std::to_string(OpenGLRenderer_VERSION_MINOR));
	LOGGER::start();


	uint32_t width = 1280;
	uint32_t height = 720;

	uint32_t shadow_width = 2000;
	uint32_t shadow_height = 2000;

	float near = 0.1f;
	float far = 500.0f;

	Camera camera = Camera::createObject(static_cast<float>(width)/static_cast<float>(height), near, far);
	RenderWindow window = RenderWindow::createObject(width, height, "Render Window", &camera);

	GL::enableDebugOutput();
	KeyManager::instance()->setup(window);

	std::stringstream stream;

	//---------------------------------------------------------------------------------//
	//                              CALLBACKS   /    UI                                //
	//---------------------------------------------------------------------------------//
	WindowClose close_callback(&window);
	DebugControl debug_callback;
	ExposureControl exposure_callback;
	ModeControl mode_callback(&window);

	Button debugButton(0, window.getHeight() - 16, 100, 16);
	Button closeButton(116, window.getHeight() - 16, 100, 16);

	debugButton.setText("Debug");
	closeButton.setText("Close");

	window.registerKeyCallback(GLFW_KEY_ESCAPE, &close_callback);
	window.registerKeyCallback(GLFW_KEY_H, &debug_callback);
	window.registerKeyCallback(GLFW_KEY_KP_ADD, &exposure_callback);
	window.registerKeyCallback(GLFW_KEY_KP_SUBTRACT, &exposure_callback);
	window.registerKeyCallback(GLFW_KEY_LEFT_ALT, &mode_callback);
	
	window.registerButtonCallback(debugButton, &debug_callback);
	window.registerButtonCallback(closeButton, &close_callback);

	//---------------------------------------------------------------------------------//
	//                              SCENE SETUP                                        //
	//---------------------------------------------------------------------------------//
	LOGGER::DEBUG("Started scene setup!\n");
	std::vector<std::string> names;
	std::vector<Mesh> meshes;
	std::vector<Material> materials;
	std::vector<glm::mat4> models;

	names.push_back("Crate");

	Mesh crate = MeshHelper::cubeMesh(glm::vec4(0, 0, 0, 1));
	meshes.push_back(crate);

	Material mat_crate = Material::createObject("materialmap");
	mat_crate.texture_diffuse = Texture::createObject(RESOURCE_PATH + "crate_diffuse.png");
	mat_crate.texture_specular = Texture::createObject(RESOURCE_PATH + "crate_specular.png");
	mat_crate.useTextures = true;
	mat_crate.shininess = 0.4f * 128.0f;
	materials.push_back(mat_crate);

	models.push_back(glm::translate(glm::mat4(1), glm::vec3(1, 0.5, 0)));

	names.push_back("Table");

	Mesh table = ObjLoader::loadObj(RESOURCE_PATH + "table/simple-table.obj", true)[0];
	meshes.push_back(table);

	Material mat_table = Material::createObject("materialmap");
	mat_table.texture_diffuse = Texture::createObject(RESOURCE_PATH + "table/table_diffuse.png");
	mat_table.texture_specular = Texture::createObject(RESOURCE_PATH + "table/table_specular.png");
	mat_table.texture_normal = Texture::createObject(RESOURCE_PATH + "table/table_normal.png");
	mat_table.shininess = 128.0f * 0.4f;
	mat_table.useTextures = true;
	materials.push_back(mat_table);

	models.push_back(glm::translate(glm::mat4(1), glm::vec3(-3, 0, 2)));

	names.push_back("Wall");

	Mesh wall = MeshHelper::cuboidMesh(glm::vec4(0, 0, 0, 1), 10.0f, 10.0f, 0.2f, true);
	meshes.push_back(wall);

	Material mat_brick = Material::createObject("materialmap");
	mat_brick.texture_diffuse = Texture::createObject(RESOURCE_PATH + "brickwall.png");
	mat_brick.texture_specular = mat_brick.texture_diffuse;
	mat_brick.texture_normal = Texture::createObject(RESOURCE_PATH + "brickwall_normal.png");
	mat_brick.useTextures = true;
	mat_brick.shininess = 0.4f * 128.0f;
	materials.push_back(mat_brick);

	models.push_back(glm::translate(glm::mat4(1),glm::vec3(0, 5.0f, -5.0f)));

	names.push_back("Plane");

	Mesh mesh = MeshHelper::cuboidMesh(glm::vec4(1, 0, 0, 1), 10.0f, 0.2f, 10.0f, true);
	meshes.push_back(mesh);

	Material mat_fabric = Material::createObject("materialmap");
	mat_fabric.texture_diffuse = Texture::createObject(RESOURCE_PATH + "fabric.png");
	mat_fabric.texture_specular = mat_fabric.texture_diffuse;
	mat_fabric.texture_normal = Texture::createObject(RESOURCE_PATH + "fabric_normal.png");
	mat_fabric.useTextures = true;
	mat_fabric.shininess = 0.4f * 128.0f;
	materials.push_back(mat_fabric);

	models.push_back(glm::translate(glm::mat4(1), glm::vec3(0,-0.1,0)));

	names.push_back("suzanne");

	Mesh suzanne = ObjLoader::loadObj(RESOURCE_PATH + "suzanne_blender.obj")[0];
	meshes.push_back(suzanne);

	Material mat_suzanne = Material::createObject("materialmap");
	mat_suzanne.ambient = glm::vec3(0.24725f, 0.1995f, 0.0745f);
	mat_suzanne.diffuse = glm::vec3(0.75164f, 0.60648f, 0.22648f);
	mat_suzanne.specular = glm::vec3(0.628281f, 0.555802f, 0.366065f);
	mat_suzanne.shininess = 0.4f * 16.0f;
	materials.push_back(mat_suzanne);

	models.push_back(glm::translate(glm::mat4(1), glm::vec3(0, 7, 0)));

	Mesh sphere = ObjLoader::loadObj(RESOURCE_PATH + "sphere.obj")[0];
	sphere.create();

	names.push_back("BRDF Sphere");

	Mesh sphere_brdf = ObjLoader::loadObj(RESOURCE_PATH + "sphere.obj")[0];
	meshes.push_back(sphere_brdf);

	Material mat_brdf = Material::createObject("materialmap", MaterialType::GGX);
	mat_brdf.ambient = glm::vec3(0.1f, 0.1f, 0.1f);
	mat_brdf.diffuse = glm::vec3(1.0f, 1.0f, 1.0f);
	mat_brdf.specular = glm::vec3(1.0f, 1.0f, 1.0f);
	mat_brdf.shininess = 0.4f * 512.0f;
	mat_brdf.roughness = 0.4f;

	materials.push_back(mat_brdf);

	models.push_back(glm::translate(glm::mat4(1), glm::vec3(0, 2, 6)));

	names.push_back("Mobius");

	Mesh mobius_mesh = ObjLoader::loadObj(RESOURCE_PATH + "mobius.obj")[0];
	meshes.push_back(mobius_mesh);

	Material mat_mobius = Material::createObject("materialmap", MaterialType::PHONG);
	mat_mobius.ambient = glm::vec3(0.05f, 0.05f, 0.1f);
	mat_mobius.diffuse = glm::vec3(0.7f, 0.7f, 1.0f);
	mat_mobius.specular = glm::vec3(0.7f, 0.7f, 1.0f);
	mat_mobius.shininess = 0.4f * 512.0f;

	materials.push_back(mat_mobius);

	models.push_back(glm::translate(glm::mat4(1), glm::vec3(5, 2, 5)));

	Mesh light = MeshHelper::cubeMesh(glm::vec4(1, 1, 1, 1));
	light.create();

	Material mat_lamp = Material::createObject("materialmap");
	mat_lamp.ambient = glm::vec3(10, 10, 10);
	mat_lamp.diffuse = glm::vec3(1, 1, 1);
	mat_lamp.specular = glm::vec3(1, 1, 1);
	mat_lamp.shininess = 128.0f * 0.4f;

	RenderObject obj_light = RenderObject::createObject(light, mat_lamp, glm::translate(glm::mat4(1), glm::vec3(20, 0, 0)));

	Light l1 = Light::createObject(glm::rotate(glm::mat4(1), 3.14159f / 4.0f, glm::vec3(0, 0, 1)) * glm::vec4(20,0,0,1), true, shadow_width, shadow_height, near, far);
	l1.ambient = glm::vec3(0.1f);
	l1.diffuse = glm::vec3(500.0f );
	l1.specular = glm::vec3(500.0f);

	Light l2 = Light::createObject(glm::vec3(0.0f, 0.2f, 0));
	l2.ambient = glm::vec3(0);
	l2.diffuse = glm::vec3(1.0f, 0.0f, 0.0f);
	l2.specular = glm::vec3(1.0f, 0.0f, 0.0f);

	Light l3 = Light::createObject(glm::vec3(-3, 0.2f, 2));
	l3.ambient = glm::vec3(0);
	l3.diffuse = glm::vec3(0.0f, 1.0f, 0.0f);
	l3.specular = glm::vec3(0.0f, 1.0f, 0.0f);

	Light l4 = Light::createObject(glm::vec3(0, 20, 20), true, shadow_width, shadow_height, near, far);
	l4.ambient = glm::vec3(0.1f);
	l4.diffuse = glm::vec3(500.0f);
	l4.specular = glm::vec3(500.0f);

	Texture particleTexture = Texture::createObject(RESOURCE_PATH + "smoke.png");

	std::vector<std::string> faces =
	{
		"right.jpg",
		"left.jpg",
		"top.jpg",
		"bottom.jpg",
		"front.jpg",
		"back.jpg"
	};

	Texture skybox = Texture::createObject(RESOURCE_PATH + "skybox/", faces);

	Mesh quad = MeshHelper::quadMesh(2.0f);

	quad.create();

	Scene scene = Scene::createObject(names, meshes, materials, models);
	names.clear();
	meshes.clear();
	materials.clear();
	models.clear();

	scene.addLight(&l1);
	scene.addLight(&l2);
	scene.addLight(&l3);
	scene.addLight(&l4);

	LOGGER::DEBUG("Finished scene setup!\n");
	//---------------------------------------------------------------------------------//
	//                              RENDERING SETUP                                    //
	//---------------------------------------------------------------------------------//
	LOGGER::DEBUG("Start Renderer setup!\n");
	ShaderManager::instance()->addShader("Post");
	ShaderManager::instance()->addShader("Normal");
	ShaderManager::instance()->addShader("CubeMap");
	ShaderManager::instance()->addShader("Reflection");
	ShaderManager::instance()->addShader("Volume");
	ShaderManager::instance()->addShader("DisplayNormal", true);
	ShaderManager::instance()->addShader("DisplayVertices", true);
	ShaderManager::instance()->addShader("DisplayEdges", true);

	TextRenderer textRenderer = window.getTextRenderer();

	ParticleRenderer particleRenderer = ParticleRenderer::createObject(glm::vec3(-1, 0, 0), 10000, 2, particleTexture);

	FrameBuffer fbo = FrameBuffer::createObject(window.getWidth(), window.getHeight());
	fbo.attachHDR();
	fbo.attachRenderBuffer();
	fbo.verify();
	fbo.unbind();

	EnvironmentMap map = EnvironmentMap::createObject(glm::vec3(0, 5, 0));

	scene.passLights2Shader(ShaderManager::instance()->getShader("Normal"));
	obj_light.setModel(glm::translate(glm::mat4(1), l1.position));

	ShaderManager::instance()->getShader("Post").bind();
	ShaderManager::instance()->getShader("Post").setInt("screenTexture", 0);
	ShaderManager::instance()->getShader("Post").setInt("lightTexture", 1);

	Skybox sky = Skybox::createObject(skybox);

	uint32_t res = 512;
	float halfres = static_cast<float>(res) / 2.0f;
	float* vol_data = new float[res * res * res];
	for (uint32_t i = 0; i < res * res * res; ++i)
	{
		int32_t x = i % res - res/2;
		int32_t y = (i / res)% res - res/2;
		int32_t z = i / (res * res) - res/2;
		float _x = 2.0f * static_cast<float>(x) / static_cast<float>(res);
		float _y = 2.0f * static_cast<float>(y) / static_cast<float>(res);
		float _z = 2.0f * static_cast<float>(z) / static_cast<float>(res);
		float norm = sqrtf(_x * _x + _y * _y + _z * _z);
		if (norm > 1.0f) vol_data[i] = 0;
		else
		{
			vol_data[i] = 0.01f;
		}
	}
	Texture vol_tex = Texture::createObject(res, res, res, vol_data, GL_RED, GL_RED, GL_FLOAT);

	delete[] vol_data;

	uint32_t frameID = 0;

	double currentTime;

	double endFrame;

	LOGGER::DEBUG("Finished rendering setup!\n");
	/* Loop until the user closes the window */
	while (window.isOpen())
	{
		currentTime = glfwGetTime();

		GL::setViewport(shadow_width, shadow_height);
		scene.passLights2Shader(ShaderManager::instance()->getShader("Normal"));
		scene.updateShadowMaps();

		//----------------------------------------------------------------------------------------------
		window.resetViewport();
		//Render scene
		if (frameID == 0)
		{
			ShaderManager::instance()->getShader("Normal").bind();
			map.render(scene, sky, ShaderManager::instance()->getShader("Normal"));
		}

		window.resetViewport();
		fbo.bind();

		fbo.clear();
		//Skybox
		//Use vertex data of the light block

		sky.render(camera);

		ShaderManager::instance()->getShader("Reflection").bind();
		ShaderManager::instance()->getShader("Reflection").setInt("cubemap", 0);
		ShaderManager::instance()->getShader("Reflection").setVec3("camera_position", camera.getPosition());
		map.getCubeMap().bind();
		ShaderManager::instance()->getShader("Reflection").setMVP(glm::translate(glm::mat4(1), glm::vec3(0, 5, 0)), camera.getView(), camera.getProjection());
		sphere.render();
		
		//Light
		ShaderManager::instance()->getShader("Normal").bind();
		ShaderManager::instance()->getShader("Normal").setVec3("viewPos", camera.getPosition());
		ShaderManager::instance()->getShader("Normal").setMVP(glm::mat4(1), camera.getView(), camera.getProjection());
		
		scene.render(ShaderManager::instance()->getShader("Normal"));

		if (debug_callback.getDebug())
		{
			ShaderManager::instance()->getShader("DisplayNormal").bind();
			ShaderManager::instance()->getShader("DisplayNormal").setMVP(glm::mat4(1), camera.getView(), camera.getProjection());

			scene.render(ShaderManager::instance()->getShader("DisplayNormal"));

			glPointSize(5);

			ShaderManager::instance()->getShader("DisplayVertices").bind();
			ShaderManager::instance()->getShader("DisplayVertices").setMVP(glm::mat4(1), camera.getView(), camera.getProjection());

			scene.render(ShaderManager::instance()->getShader("DisplayVertices"));

			glLineWidth(5);

			ShaderManager::instance()->getShader("DisplayEdges").bind();
			ShaderManager::instance()->getShader("DisplayEdges").setMVP(glm::mat4(1), camera.getView(), camera.getProjection());

			scene.render(ShaderManager::instance()->getShader("DisplayEdges"));
		}

		//Render light

		obj_light.render(ShaderManager::instance()->getShader("Normal"));

		ShaderManager::instance()->getShader("Volume").bind();
		ShaderManager::instance()->getShader("Volume").setMVP(glm::translate(glm::mat4(1), glm::vec3(20, 0, -20)), camera.getView(), camera.getProjection());
		ShaderManager::instance()->getShader("Volume").setVec3("lightPos", l1.position);
		ShaderManager::instance()->getShader("Volume").setVec3("viewPos", camera.getPosition());
		vol_tex.bind();
		light.render();
		


		particleRenderer.update(window.DELTA_TIME());
		particleRenderer.render(camera);


		//Render to quad
		fbo.unbind();
		GL::clear();
		ShaderManager::instance()->getShader("Post").bind();
		ShaderManager::instance()->getShader("Post").setFloat("exposure", exposure_callback.getExposure());
		fbo.getTexture(0).bind(0);
		//lights[0].shadow_map.getTexture().bind();
		quad.render();
		
		stream << "X: " << std::fixed << std::setprecision(2) << camera.getPosition().x;
		textRenderer.render(stream.str(), window.getWidth()-100, window.getHeight()-16, 1, glm::vec3(1, 1, 1));
		stream.str("");

		stream << "Y: " << std::fixed << std::setprecision(2) << camera.getPosition().y;
		textRenderer.render(stream.str(), window.getWidth() - 100, window.getHeight() - 32, 1, glm::vec3(1, 1, 1));
		stream.str("");

		stream << "Z: " << std::fixed << std::setprecision(2) << camera.getPosition().z;
		textRenderer.render(stream.str(), window.getWidth() - 100, window.getHeight() - 48, 1, glm::vec3(1, 1, 1));
		stream.str("");

		endFrame = glfwGetTime();

		stream << "Render time: " << std::fixed << std::setprecision(5) << (endFrame - currentTime) << "ms FPS: " << std::fixed << std::setprecision(1) << 1.0f / (endFrame - currentTime) << "; Display FPS: " << std::fixed << std::setprecision(1) << 1.0f/window.DELTA_TIME();
		textRenderer.render(stream.str(), 16, 16, 1, glm::vec3(0, 1, 0));
		stream.str("");

		window.spinOnce();

		++frameID;
	}

	ShaderManager::destroyObject(*ShaderManager::instance());
	Skybox::destroyObject(sky);
	RenderWindow::destroyObject(window);
	Camera::destroyObject(camera);
	Mesh::destroyObject(quad);
	RenderObject::destroyObject(obj_light);
	Scene::destroyObject(scene);
	FrameBuffer::destroyObject(fbo);
	KeyManager::destroy();
	ParticleRenderer::destroyObject(particleRenderer);
	Texture::destroyObject(vol_tex);

	LOGGER::end();

	return 0;
}