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
	ShaderManager::addShader("CubeMapConvolution");
	ShaderManager::addShader("Prefilter");
	ShaderManager::addShader("LUDBRDF");

	std::vector<std::string> names;
	std::vector<std::shared_ptr<Mesh>> meshes;
	std::vector<Material> material;
	std::vector<glm::mat4> models;

	names.push_back("Sphere");
	meshes = ObjLoader::loadObj("res/sphere.obj", true);
	Material sphere = Material("materialmap", GGX);
	sphere.useDiffuseTextures = false;
	sphere.useMetallicTextures = false;
	sphere.useNormalTextures = false;
	sphere.useRoughnessTextures = false;
	sphere.useIrradianceTextures = true;

	//sphere.texture_diffuse = std::make_shared<Texture>("res/rustediron2_basecolor.png");
	//sphere.texture_metallic = std::make_shared<Texture>("res/rustediron2_metallic.png");
	//sphere.texture_normal = std::make_shared<Texture>("res/rustediron2_normal.png");
	//sphere.texture_roughness = std::make_shared<Texture>("res/rustediron2_roughness.png");
	sphere.texture_irradiance = std::make_shared<EnvironmentMap>(glm::vec3(0), 32, 32);
	sphere.ambient = glm::vec3(0.1 ,0.1 ,0.1);
	sphere.diffuse = glm::vec3(1, 1, 1);
	sphere.specular = glm::vec3(1, 1, 1);
	sphere.roughness = 1.0f;
	sphere.metallic = 0.5f;

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

	FrameBuffer capture_buffer(512, 512);
	capture_buffer.attachColor(sphere.LUD);
	capture_buffer.attachRenderBuffer();
	capture_buffer.verify();
	FrameBuffer::bindDefault();

	std::shared_ptr<Texture> skybox = std::make_shared<Texture>("res/skybox/", faces);

	std::shared_ptr<EnvironmentMap> skybox_map = std::make_shared<EnvironmentMap>(glm::vec3(0));
	skybox_map->setCubeMap(skybox);
	glDepthFunc(GL_LEQUAL);  
	std::shared_ptr<Texture> irradiance = Texture::createTexture(32, 32, (float*)NULL, CUBEMAP, GL_RGB16F, RGB, GL_FLOAT);
	sphere.texture_irradiance->setSkybox(skybox_map);
	sphere.texture_irradiance->setCubeMap(irradiance);
	sphere.texture_irradiance->renderTo(nullptr, ShaderManager::getShader("Normal"), ShaderManager::getShader("CubeMapConvolution"));
	
	std::shared_ptr<Texture> prefilter = Texture::createTexture(128, 128, (float*)NULL, CUBEMAP, GL_RGB16F, RGB, GL_FLOAT);
	EnvironmentMap prefilter_map(glm::vec3(0));
	prefilter_map.setCubeMap(prefilter);
	prefilter_map.setSkybox(skybox_map);
	prefilter_map.prefilter(ShaderManager::getShader("Prefilter"));

	GL::setViewport(512, 512);
	capture_buffer.bind();
	capture_buffer.clear();
	ShaderManager::getShader("LUDBRDF")->bind();

	screen_quad->render();

	FrameBuffer::bindDefault();

	while (window.isOpen())
	{
		GL::setViewport(width, height);
		hdr.bind();

		GL::clear();

		skybox_map->renderAsSkybox(&camera, ShaderManager::getShader("Skybox"));

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
