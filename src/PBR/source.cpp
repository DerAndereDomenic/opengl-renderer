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
	ShaderManager::addShader("LUTBRDF");
	ShaderManager::addShader("ERtoCube");

	std::vector<std::string> names;
	std::vector<std::shared_ptr<Mesh>> meshes;
	std::vector<Material> material;
	std::vector<glm::mat4> models;

	names.push_back("Sphere");
	meshes = ObjLoader::loadObj("res/uv_sphere.obj", true);
	Material sphere = Material("materialmap", GGX);
	sphere.useDiffuseTextures = true;
	sphere.useMetallicTextures = true;
	sphere.useNormalTextures = true;
	sphere.useRoughnessTextures = true;
	sphere.useIBLTextures = true;

	sphere.texture_diffuse = std::make_shared<Texture>("res/rustediron2_basecolor.png");
	sphere.texture_metallic = std::make_shared<Texture>("res/rustediron2_metallic.png");
	sphere.texture_normal = std::make_shared<Texture>("res/rustediron2_normal.png");
	sphere.texture_roughness = std::make_shared<Texture>("res/rustediron2_roughness.png");
	//sphere.ambient = glm::vec3(0.1 ,0.1 ,0.1);
	//sphere.diffuse = glm::vec3(1, 1, 1);
	//sphere.specular = glm::vec3(1, 1, 1);
	//sphere.roughness = 1.0f;
	//sphere.metallic = 0.0f;

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
	capture_buffer.attachColor(sphere.LUT);
	capture_buffer.attachRenderBuffer();
	capture_buffer.verify();
	FrameBuffer::bindDefault();

	glDepthFunc(GL_LEQUAL);  

	std::shared_ptr<Texture> hdr_equirect = std::make_shared<Texture>("res/main_building.hdr", true);
	std::shared_ptr<Texture> hdr_cubemap = Texture::createTexture(512, 512, (float*)nullptr, CUBEMAP, GL_RGBA16F, GL_RGBA, GL_FLOAT);
	std::shared_ptr<EnvironmentMap> dummy_cm = std::make_shared<EnvironmentMap>(glm::vec3(0));
	dummy_cm->setCubeMap(hdr_equirect);

	std::shared_ptr<EnvironmentMap> skybox_map = std::make_shared<EnvironmentMap>(glm::vec3(0));
	skybox_map->setCubeMap(hdr_cubemap);
	skybox_map->setSkybox(dummy_cm);
	skybox_map->renderTo(nullptr, ShaderManager::getShader("Normal"), ShaderManager::getShader("ERtoCube"));

	EnvironmentMap irradiance_map(glm::vec3(0));
	irradiance_map.setSkybox(skybox_map);
	irradiance_map.setCubeMap(sphere.texture_irradiance);
	irradiance_map.renderTo(nullptr, ShaderManager::getShader("Normal"), ShaderManager::getShader("CubeMapConvolution"));
	
	EnvironmentMap prefilter_map(glm::vec3(0));
	prefilter_map.setSkybox(skybox_map);
	prefilter_map.setCubeMap(sphere.texture_prefilter);
	prefilter_map.prefilter(ShaderManager::getShader("Prefilter"));

	GL::setViewport(512, 512);
	capture_buffer.bind();
	capture_buffer.clear();
	ShaderManager::getShader("LUTBRDF")->bind();

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
