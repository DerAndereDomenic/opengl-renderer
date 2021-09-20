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
#include <DataStructure/EnvironmentMap.h>

int main()
{
	LOGGER::setProject("PBR", "1.0");
	LOGGER::start();

	uint32_t width = 1280, height = 720;

	Camera camera = Camera( static_cast<float>(width) / static_cast<float>(height), 0.01f, 500);
	RenderWindow window = RenderWindow(width, height, "PBR", &camera);

	GL::enableDebugOutput();

	WindowClose close_callback(&window);

	window.registerKeyCallback(GLFW_KEY_ESCAPE, &close_callback);

	ShaderManager::addShader("Normal");
	ShaderManager::addShader("Post");
	ShaderManager::addShader("Skybox");

	std::vector<std::string> names;
	std::vector<std::shared_ptr<Mesh>> meshes;
	std::vector<Material> material;
	std::vector<glm::mat4> models;

	names.push_back("Sphere");
	meshes = ObjLoader::loadObj("res/sphere.obj", true);
	Material sphere = Material("materialmap", GGX);
	sphere.useDiffuseTextures = true;
	sphere.useMetallicTextures = true;
	sphere.useNormalTextures = false;
	sphere.useRoughnessTextures = true;

	sphere.texture_diffuse = std::make_shared<Texture>("res/rustediron2_basecolor.png");
	sphere.texture_metallic = std::make_shared<Texture>("res/rustediron2_metallic.png");
	sphere.texture_normal = std::make_shared<Texture>("res/rustediron2_normal.png");
	sphere.texture_roughness = std::make_shared<Texture>("res/rustediron2_roughness.png");
	//sphere.ambient = glm::vec3(0.1 ,0 ,0);
	//sphere.diffuse = glm::vec3(1, 0, 0);
	//sphere.specular = glm::vec3(1, 0, 0);
	//sphere.roughness = 0.01f;
	//sphere.metallic = 0.5f;

	material.push_back(sphere);
	models.push_back(glm::mat4(1));
	

	Scene scene = Scene(names, meshes, material, models);

	Light light = Light(glm::vec3(10, 30, 10), false);
	light.ambient = glm::vec3(1.0f);
	light.diffuse = glm::vec3(1000.0f);
	light.specular = glm::vec3(1000.0f);

	scene.addLight(&light);

	FrameBuffer hdr(width, height);
	hdr.attachHDR();
	hdr.attachRenderBuffer();
	hdr.verify();

	FrameBuffer::bindDefault();

	std::shared_ptr<Mesh> screen_quad = MeshHelper::quadMesh(2.0f);
	screen_quad->create();

	std::vector<std::string> faces =
	{
		"right.jpg",
		"left.jpg",
		"top.jpg",
		"bottom.jpg",
		"front.jpg",
		"back.jpg"
	};

	std::shared_ptr<Texture> skybox = std::make_shared<Texture>("res/skybox/", faces);

	EnvironmentMap skybox_map(glm::vec3(0));
	skybox_map.setCubeMap(skybox);

	while (window.isOpen())
	{
		hdr.bind();

		GL::clear();

		skybox_map.renderSkybox(&camera, ShaderManager::getShader("Skybox"));

		ShaderManager::getShader("Normal")->bind();
		ShaderManager::getShader("Normal")->setMVP(glm::mat4(1), camera.getView(), camera.getProjection());
		ShaderManager::getShader("Normal")->setVec3("viewPos", camera.getPosition());

		scene.passLights2Shader(ShaderManager::getShader("Normal"));

		scene.render(ShaderManager::getShader("Normal"));

		hdr.bindDefault();
		
		GL::clear();

		ShaderManager::getShader("Post")->bind();
		ShaderManager::getShader("Post")->setFloat("exposure", 1.0f);

		hdr.getTexture()->bind();

		screen_quad->render();

		window.spinOnce();
	}

	LOGGER::end();

	return 0;
}
