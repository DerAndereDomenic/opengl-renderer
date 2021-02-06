#include <Renderer/RenderWindow.h>
#include <IO/KeyManager.h>
#include <Shader/ShaderManager.h>
#include <IO/ObjLoader.h>
#include <Core/GLFunctions.h>
#include <DataStructure/Scene.h>
#include <GUI/WindowClose.h>

int main()
{
	uint32_t width = 1280, height = 720;

	Camera camera = Camera::createObject( width / height, 0.01f, 500);
	RenderWindow window = RenderWindow::createObject(width, height, "WaterScene", &camera);
	KeyManager::instance()->setup(window);

	WindowClose close_callback(&window);

	window.registerKeyCallback(GLFW_KEY_ESCAPE, &close_callback);

	ShaderManager::instance()->addShader("Normal");

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

	while (window.isOpen())
	{
		GL::clear();
		ShaderManager::instance()->getShader("Normal").bind();
		ShaderManager::instance()->getShader("Normal").setMVP(glm::mat4(1), camera.getView(), camera.getProjection());
		ShaderManager::instance()->getShader("Normal").setVec3("viewPos", camera.getPosition());

		scene.passLights2Shader(ShaderManager::instance()->getShader("Normal"));
		scene.render(ShaderManager::instance()->getShader("Normal"));

		window.spinOnce();
	}

	RenderWindow::destroyObject(window);
	Camera::destroyObject(camera);
	Scene::destroyObject(scene);
	FrameBuffer::destroyObject(reflection);
	FrameBuffer::destroyObject(refraction);

	return 0;
}