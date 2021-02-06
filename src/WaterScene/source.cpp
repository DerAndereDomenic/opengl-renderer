#include <Renderer/RenderWindow.h>
#include <IO/KeyManager.h>
#include <Shader/ShaderManager.h>
#include <IO/ObjLoader.h>
#include <Core/GLFunctions.h>
#include <DataStructure/Scene.h>
#include <GUI/WindowClose.h>
#include <DLogger/Logger.h>
#include <DataStructure/MeshHelper.h>
#include <glm/gtx/transform.hpp>

int main()
{
	LOGGER::setProject("WaterScene", "1.0");
	LOGGER::start();

	uint32_t width = 1280, height = 720;
	float water_height = 4;

	Camera camera = Camera::createObject( width / height, 0.01f, 500);
	RenderWindow window = RenderWindow::createObject(width, height, "WaterScene", &camera);
	KeyManager::instance()->setup(window);

	GL::enableDebugOutput();

	WindowClose close_callback(&window);

	window.registerKeyCallback(GLFW_KEY_ESCAPE, &close_callback);

	ShaderManager::instance()->addShader("Normal");
	ShaderManager::instance()->addShader("Water");

	Mesh water = MeshHelper::quadMesh(6);
	water.create();
	glm::mat4 rotate = glm::translate(glm::vec3(0,water_height,0)) * glm::rotate(-3.14159f / 2.0f, glm::vec3(1, 0, 0));

	std::vector<std::string> names;
	std::vector<Mesh> meshes;
	std::vector<Material> material;
	std::vector<glm::mat4> models;

	names.push_back("Terrain");
	meshes = ObjLoader::loadObj(RESOURCE_PATH + "terrain.obj");
	Material terrain = Material::createObject("materialmap", LAMBERT);
	terrain.ambient = glm::vec3(0.1, 0.1, 0.1);
	terrain.diffuse = glm::vec3(1, 1, 1);
	terrain.specular = glm::vec3(1, 1, 1);
	terrain.shininess = 0.4f * 128.0f;
	terrain.useTextures = false;
	material.push_back(terrain);
	models.push_back(glm::mat4(1));

	names.push_back("Box");
	Mesh box_mesh = MeshHelper::cuboidMesh(glm::vec4(1), 1, 10, 1);
	meshes.push_back(box_mesh);
	Material box_material = Material::createObject("materialmap");
	box_material.ambient = glm::vec3(0.1, 0, 0);
	box_material.diffuse = glm::vec3(1, 0, 0);
	box_material.specular = glm::vec3(1, 0, 0);
	box_material.shininess = 0.4f * 128.0f;
	box_material.useTextures = false;
	material.push_back(box_material);
	models.push_back(glm::translate(glm::vec3(-4,7,-4)));
	

	Scene scene = Scene::createObject(names, meshes, material, models);

	Light light = Light::createObject(glm::vec3(10, 30, 10), false);
	light.ambient = glm::vec3(1.0f);
	light.diffuse = glm::vec3(700.0f);
	light.specular = glm::vec3(700.0f);

	scene.addLight(&light);

	FrameBuffer reflection = FrameBuffer::createObject(width, height);
	reflection.attachColor();
	reflection.attachRenderBuffer();
	reflection.verify();

	FrameBuffer refraction = FrameBuffer::createObject(width, height);
	refraction.attachColor();
	refraction.attachRenderBuffer();
	refraction.verify();

	FrameBuffer::bindDefault();
	GL::enableClipping(0);
	while (window.isOpen())
	{
		GL::clear();

		refraction.bind();
		GL::clear();
		ShaderManager::instance()->getShader("Normal").bind();
		ShaderManager::instance()->getShader("Normal").setMVP(glm::mat4(1), camera.getView(), camera.getProjection());
		ShaderManager::instance()->getShader("Normal").setVec3("viewPos", camera.getPosition());
		ShaderManager::instance()->getShader("Normal").setVec4("plane", glm::vec4(0, -1, 0, -water_height));

		scene.passLights2Shader(ShaderManager::instance()->getShader("Normal"));
		scene.render(ShaderManager::instance()->getShader("Normal"));

		//Change camera
		camera.invertPitch();
		glm::vec3 position = camera.getPosition();
		camera.teleport(position - glm::vec3(0, 2*(position.y - water_height), 0));

		reflection.bind();
		GL::clear();
		ShaderManager::instance()->getShader("Normal").setMVP(glm::mat4(1), camera.getView(), camera.getProjection());
		ShaderManager::instance()->getShader("Normal").setVec3("viewPos", camera.getPosition());
		ShaderManager::instance()->getShader("Normal").setVec4("plane", glm::vec4(0, 1, 0, water_height));

		scene.render(ShaderManager::instance()->getShader("Normal"));

		//Change camera back
		camera.invertPitch();
		camera.teleport(position);

		FrameBuffer::bindDefault();
		ShaderManager::instance()->getShader("Normal").setMVP(glm::mat4(1), camera.getView(), camera.getProjection());
		ShaderManager::instance()->getShader("Normal").setVec3("viewPos", camera.getPosition());
		ShaderManager::instance()->getShader("Normal").setVec4("plane", glm::vec4(0, 1, 0, -100));

		scene.render(ShaderManager::instance()->getShader("Normal"));

		ShaderManager::instance()->getShader("Water").bind();
		ShaderManager::instance()->getShader("Water").setMVP(rotate, camera.getView(), camera.getProjection());
		ShaderManager::instance()->getShader("Water").setInt("reflection", 0);
		ShaderManager::instance()->getShader("Water").setInt("refraction", 1);

		reflection.getTexture().bind(0);
		refraction.getTexture().bind(1);

		water.render();

		window.spinOnce();
	}

	RenderWindow::destroyObject(window);
	Camera::destroyObject(camera);
	Scene::destroyObject(scene);
	FrameBuffer::destroyObject(reflection);
	FrameBuffer::destroyObject(refraction);
	ShaderManager::destroyObject(*ShaderManager::instance());
	Mesh::destroyObject(water);

	LOGGER::end();

	return 0;
}