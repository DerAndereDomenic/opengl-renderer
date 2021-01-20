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
#include <DataStructure/EnvironmentMap.h>
#include <Renderer/ParticleRenderer.h>
#include <Renderer/VRRenderer.h>


int main(void)
{
	LOGGER::setProject("VR Viewer", "1.0");
	LOGGER::start();

	const float scale = 0.2f;
	glm::mat4 scaling_matrix = glm::scale(glm::mat4(1), glm::vec3(scale));

	uint32_t width = 1280;
	uint32_t height = 720;

	uint32_t shadow_width = 2000;
	uint32_t shadow_height = 2000;

	float near = 0.1f;
	float far = 500.0f;

	RenderWindow window = RenderWindow::createObject(width, height, "Render Window");
	VRRenderer renderer = VRRenderer::createObject();

	GL::enableDebugOutput();
	KeyManager::instance()->setup(window);

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

	models.push_back(glm::translate(scaling_matrix, glm::vec3(1, 0.5, 0)));

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

	models.push_back(glm::translate(scaling_matrix, glm::vec3(-3, 0, 2)));

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

	models.push_back(glm::translate(scaling_matrix, glm::vec3(0, 5.0f, -5.0f)));

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

	models.push_back(glm::translate(scaling_matrix, glm::vec3(0, -0.1, 0)));

	names.push_back("suzanne");

	Mesh suzanne = ObjLoader::loadObj(RESOURCE_PATH + "suzanne_blender.obj")[0];
	meshes.push_back(suzanne);

	Material mat_suzanne = Material::createObject("materialmap");
	mat_suzanne.ambient = glm::vec3(0.24725f, 0.1995f, 0.0745f);
	mat_suzanne.diffuse = glm::vec3(0.75164f, 0.60648f, 0.22648f);
	mat_suzanne.specular = glm::vec3(0.628281f, 0.555802f, 0.366065f);
	mat_suzanne.shininess = 0.4f * 16.0f;
	materials.push_back(mat_suzanne);

	models.push_back(glm::translate(scaling_matrix, glm::vec3(0, 7, 0)));

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

	materials.push_back(mat_brdf);

	models.push_back(glm::translate(scaling_matrix, glm::vec3(0, 2, 6)));

	names.push_back("Mobius");

	Mesh mobius_mesh = ObjLoader::loadObj(RESOURCE_PATH + "mobius.obj")[0];
	meshes.push_back(mobius_mesh);

	Material mat_mobius = Material::createObject("materialmap", MaterialType::PHONG);
	mat_mobius.ambient = glm::vec3(0.05f, 0.05f, 0.1f);
	mat_mobius.diffuse = glm::vec3(0.7f, 0.7f, 1.0f);
	mat_mobius.specular = glm::vec3(0.7f, 0.7f, 1.0f);
	mat_mobius.shininess = 0.4f * 512.0f;

	materials.push_back(mat_mobius);

	models.push_back(glm::translate(scaling_matrix, glm::vec3(5, 2, 5)));

	Mesh light = MeshHelper::cubeMesh(glm::vec4(1, 1, 1, 1));
	light.create();

	Material mat_lamp = Material::createObject("materialmap");
	mat_lamp.ambient = glm::vec3(10, 10, 10);
	mat_lamp.diffuse = glm::vec3(1, 1, 1);
	mat_lamp.specular = glm::vec3(1, 1, 1);
	mat_lamp.shininess = 128.0f * 0.4f;

	RenderObject obj_light = RenderObject::createObject(light, mat_lamp, glm::translate(scaling_matrix, glm::vec3(20, 0, 0)));

	Light l1 = Light::createObject(glm::vec3(glm::rotate(glm::mat4(1), 3.14159f / 4.0f, glm::vec3(0, 0, 1)) * glm::vec4(20, 0, 0, 1))*scale, true, shadow_width, shadow_height, near, far);
	l1.ambient = glm::vec3(0.1f*scale*scale);
	l1.diffuse = glm::vec3(500.0f*scale * scale);
	l1.specular = glm::vec3(500.0f*scale * scale);

	Light l2 = Light::createObject(glm::vec3(0.0f, 0.2f, 0)*scale);
	l2.ambient = glm::vec3(0);
	l2.diffuse = glm::vec3(1.0f, 0.0f, 0.0f)*scale * scale;
	l2.specular = glm::vec3(1.0f, 0.0f, 0.0f)*scale * scale;

	Light l3 = Light::createObject(glm::vec3(-3, 0.2f, 2)*scale);
	l3.ambient = glm::vec3(0);
	l3.diffuse = glm::vec3(0.0f, 1.0f, 0.0f)*scale * scale;
	l3.specular = glm::vec3(0.0f, 1.0f, 0.0f)*scale * scale;

	Light l4 = Light::createObject(glm::vec3(0, 20, 20)*scale, true, shadow_width, shadow_height, near, far);
	l4.ambient = glm::vec3(0.1f*scale * scale);
	l4.diffuse = glm::vec3(500.0f*scale * scale);
	l4.specular = glm::vec3(500.0f*scale * scale);

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
	ShaderManager::instance()->addShader("Normal");
	ShaderManager::instance()->addShader("CubeMap");
	ShaderManager::instance()->addShader("Reflection");
	ShaderManager::instance()->addShader("VRScreen");

	ParticleRenderer particleRenderer = ParticleRenderer::createObject(glm::vec3(-1, 0, 0)*scale, 10000, 2, particleTexture);

	EnvironmentMap map = EnvironmentMap::createObject(glm::vec3(0, 5, 0)*scale);

	scene.passLights2Shader(ShaderManager::instance()->getShader("Normal"));
	obj_light.setModel(glm::translate(scaling_matrix, l1.position));

	Skybox sky = Skybox::createObject(skybox);

	uint32_t frameID = 0;

	Mesh screen_quad = MeshHelper::quadMesh(2);
	screen_quad.create();

	LOGGER::DEBUG("Finished rendering setup!\n");
	/* Loop until the user closes the window */
	while (window.isOpen())
	{
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

		GL::setViewport(renderer.getWidth(), renderer.getHeight());

		renderer.getRenderTargetLeft().bind();
		GL::clear();
		//Skybox
		//Use vertex data of the light block

		sky.render(renderer.leftView(), renderer.leftProjection());

		ShaderManager::instance()->getShader("Reflection").bind();
		ShaderManager::instance()->getShader("Reflection").setInt("cubemap", 0);
		ShaderManager::instance()->getShader("Reflection").setVec3("camera_position", renderer.positionLeft());
		map.getCubeMap().bind();
		ShaderManager::instance()->getShader("Reflection").setMVP(glm::translate(scaling_matrix, glm::vec3(0, 5, 0)), renderer.leftView(), renderer.leftProjection());
		sphere.render();

		//Light
		ShaderManager::instance()->getShader("Normal").bind();
		ShaderManager::instance()->getShader("Normal").setVec3("viewPos", renderer.positionRight());
		ShaderManager::instance()->getShader("Normal").setMVP(glm::mat4(1), renderer.leftView(), renderer.leftProjection());

		scene.render(ShaderManager::instance()->getShader("Normal"));

		//Render light

		obj_light.render(ShaderManager::instance()->getShader("Normal"));

		particleRenderer.update(window.DELTA_TIME());
		particleRenderer.render(renderer.leftView(), renderer.leftProjection());

		//RIGHT EYE--------------------------------------------------------------------------------------------------------

		renderer.getRenderTargetRight().bind();
		GL::clear();
		//Skybox
		//Use vertex data of the light block

		sky.render(renderer.rightView(), renderer.rightProjection());

		ShaderManager::instance()->getShader("Reflection").bind();
		ShaderManager::instance()->getShader("Reflection").setInt("cubemap", 0);
		ShaderManager::instance()->getShader("Reflection").setVec3("camera_position", renderer.positionRight());
		map.getCubeMap().bind();
		ShaderManager::instance()->getShader("Reflection").setMVP(glm::translate(scaling_matrix, glm::vec3(0, 5, 0)), renderer.rightView(), renderer.rightProjection());
		sphere.render();

		//Light
		ShaderManager::instance()->getShader("Normal").bind();
		ShaderManager::instance()->getShader("Normal").setVec3("viewPos", renderer.positionRight());
		ShaderManager::instance()->getShader("Normal").setMVP(glm::mat4(1), renderer.rightView(), renderer.rightProjection());

		scene.render(ShaderManager::instance()->getShader("Normal"));

		//Render light

		obj_light.render(ShaderManager::instance()->getShader("Normal"));

		//particleRenderer.update(window.DELTA_TIME());
		particleRenderer.render(renderer.rightView(), renderer.rightProjection());

		FrameBuffer::bindDefault();
		window.resetViewport();
		GL::clear();
		ShaderManager::instance()->getShader("VRScreen").bind();
		ShaderManager::instance()->getShader("VRScreen").setInt("leftEye", 0);
		ShaderManager::instance()->getShader("VRScreen").setInt("rightEye", 1);
		renderer.getRenderTargetLeft().getTexture().bind(0);
		renderer.getRenderTargetRight().getTexture().bind(1);
		screen_quad.render();

		window.spinOnce();
		renderer.uploadToHMD();

		++frameID;
	}

	ShaderManager::destroyObject(*ShaderManager::instance());
	Skybox::destroyObject(sky);
	RenderWindow::destroyObject(window);
	RenderObject::destroyObject(obj_light);
	Scene::destroyObject(scene);
	KeyManager::destroy();
	ParticleRenderer::destroyObject(particleRenderer);
	VRRenderer::destroyObject(renderer);
	Mesh::destroyObject(screen_quad);

	LOGGER::end();

	return 0;
}