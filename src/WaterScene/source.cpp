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

	Camera camera = Camera( width / height, 0.01f, 500);
	RenderWindow window = RenderWindow(width, height, "WaterScene", &camera);

	GL::enableDebugOutput();

	WindowClose close_callback(&window);

	window.registerKeyCallback(GLFW_KEY_ESCAPE, &close_callback);

	ShaderManager::addShader("Normal");
	ShaderManager::addShader("Water");

	std::shared_ptr<Mesh> water = MeshHelper::quadMesh(6);
	water->create();
	glm::mat4 rotate = glm::translate(glm::vec3(0,water_height,0)) * glm::rotate(-3.14159f / 2.0f, glm::vec3(1, 0, 0));

	std::vector<std::string> names;
	std::vector<std::shared_ptr<Mesh>> meshes;
	std::vector<Material> material;
	std::vector<glm::mat4> models;

	names.push_back("Terrain");
	meshes = ObjLoader::loadObj("res/terrain.obj");
	Material terrain = Material("materialmap", LAMBERT);
	terrain.ambient = glm::vec3(0.1, 0.1, 0.1);
	terrain.diffuse = glm::vec3(1, 1, 1);
	terrain.specular = glm::vec3(1, 1, 1);
	terrain.shininess = 0.4f * 128.0f;
	material.push_back(terrain);
	models.push_back(glm::mat4(1));

	names.push_back("Box");
	std::shared_ptr<Mesh> box_mesh = MeshHelper::cuboidMesh(glm::vec4(1), 1, 10, 1);
	meshes.push_back(box_mesh);
	Material box_material = Material("materialmap");
	box_material.ambient = glm::vec3(0.1, 0, 0);
	box_material.diffuse = glm::vec3(1, 0, 0);
	box_material.specular = glm::vec3(1, 0, 0);
	box_material.shininess = 0.4f * 128.0f;
	material.push_back(box_material);
	models.push_back(glm::translate(glm::vec3(-4,7,-4)));
	

	Scene scene = Scene(names, meshes, material, models);

	Light light = Light(glm::vec3(10, 30, 10), false);
	light.ambient = glm::vec3(1.0f);
	light.diffuse = glm::vec3(700.0f);
	light.specular = glm::vec3(700.0f);

	scene.addLight(&light);

	FrameBuffer reflection = FrameBuffer(width, height);
	reflection.attachColor();
	reflection.attachRenderBuffer();
	reflection.verify();

	FrameBuffer refraction = FrameBuffer(width, height);
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
		ShaderManager::getShader("Normal")->bind();
		ShaderManager::getShader("Normal")->setMVP(glm::mat4(1), camera.getView(), camera.getProjection());
		ShaderManager::getShader("Normal")->setVec3("viewPos", camera.getPosition());
		ShaderManager::getShader("Normal")->setVec4("plane", glm::vec4(0, -1, 0, -water_height));

		scene.passLights2Shader(ShaderManager::getShader("Normal"));
		scene.render(ShaderManager::getShader("Normal"));

		//Change camera
		camera.invertPitch();
		glm::vec3 position = camera.getPosition();
		camera.teleport(position - glm::vec3(0, 2*(position.y - water_height), 0));

		reflection.bind();
		GL::clear();
		ShaderManager::getShader("Normal")->setMVP(glm::mat4(1), camera.getView(), camera.getProjection());
		ShaderManager::getShader("Normal")->setVec3("viewPos", camera.getPosition());
		ShaderManager::getShader("Normal")->setVec4("plane", glm::vec4(0, 1, 0, water_height));

		scene.render(ShaderManager::getShader("Normal"));

		//Change camera back
		camera.invertPitch();
		camera.teleport(position);

		FrameBuffer::bindDefault();
		ShaderManager::getShader("Normal")->setMVP(glm::mat4(1), camera.getView(), camera.getProjection());
		ShaderManager::getShader("Normal")->setVec3("viewPos", camera.getPosition());
		ShaderManager::getShader("Normal")->setVec4("plane", glm::vec4(0, 1, 0, -100));

		scene.render(ShaderManager::getShader("Normal"));

		ShaderManager::getShader("Water")->bind();
		ShaderManager::getShader("Water")->setMVP(rotate, camera.getView(), camera.getProjection());
		ShaderManager::getShader("Water")->setVec3("viewPos", camera.getPosition());
		ShaderManager::getShader("Water")->setInt("reflection", 0);
		ShaderManager::getShader("Water")->setInt("refraction", 1);

		reflection.getTexture()->bind(0);
		refraction.getTexture()->bind(1);

		water->render();

		window.spinOnce();
	}

	LOGGER::end();

	return 0;
}
