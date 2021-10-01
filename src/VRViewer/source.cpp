#include <Core/Platform.h>
#include <Core/GLFunctions.h>
#include <DLogger/Logger.h>

#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <OpenGLObjects/FrameBuffer.h>
#include <DataStructure/Mesh.h>
#include <DataStructure/MeshHelper.h>
#include <DataStructure/RenderObject.h>
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

	const float scale = 1.0f;
	glm::mat4 scaling_matrix = glm::scale(glm::mat4(1), glm::vec3(scale));

	uint32_t width = 1280;
	uint32_t height = 720;

	uint32_t shadow_width = 2000;
	uint32_t shadow_height = 2000;

	float near = 0.1f;
	float far = 500.0f;

	RenderWindow window(width, height, "Render Window");
	VRRenderer renderer;

	GL::enableDebugOutput();

	//---------------------------------------------------------------------------------//
	//                              SCENE SETUP                                        //
	//---------------------------------------------------------------------------------//
	LOGGER::DEBUG("Started scene setup!\n");
	std::vector<std::string> names;
	std::vector<std::shared_ptr<Mesh>> meshes;
	std::vector<Material> materials;
	std::vector<glm::mat4> models;

	names.push_back("Crate");

	std::shared_ptr<Mesh> crate = MeshHelper::cubeMesh(glm::vec4(0, 0, 0, 1));
	meshes.push_back(crate);

	Material mat_crate = Material("materialmap");
	mat_crate.texture_diffuse = std::make_shared<Texture>("res/crate_diffuse.png");
	mat_crate.texture_specular = std::make_shared<Texture>("res/crate_specular.png");
	mat_crate.useDiffuseTextures = true;
	mat_crate.useSpecularTextures = true;
	mat_crate.shininess = 0.4f * 128.0f;
	materials.push_back(mat_crate);

	models.push_back(glm::translate(scaling_matrix, glm::vec3(1, 0.5, 0)));

	names.push_back("Table");

	std::shared_ptr<Mesh> table = ObjLoader::loadObj("res/table/simple-table.obj", true)[0];
	meshes.push_back(table);

	Material mat_table = Material("materialmap");
	mat_table.texture_diffuse = std::make_shared<Texture>("res/table/table_diffuse.png");
	mat_table.texture_specular = std::make_shared<Texture>("res/table/table_specular.png");
	mat_table.texture_normal = std::make_shared<Texture>("res/table/table_normal.png");
	mat_table.shininess = 128.0f * 0.4f;
	mat_table.useDiffuseTextures = true;
	mat_table.useSpecularTextures = true;
	mat_table.useNormalTextures = true;
	materials.push_back(mat_table);

	models.push_back(glm::translate(scaling_matrix, glm::vec3(-3, 0, 2)));

	names.push_back("Wall");

	std::shared_ptr<Mesh> wall = MeshHelper::cuboidMesh(glm::vec4(0, 0, 0, 1), 10.0f, 10.0f, 0.2f, true);
	meshes.push_back(wall);

	Material mat_brick = Material("materialmap");
	mat_brick.texture_diffuse = std::make_shared<Texture>("res/brickwall.png");
	mat_brick.texture_specular = mat_brick.texture_diffuse;
	mat_brick.texture_normal = std::make_shared<Texture>("res/brickwall_normal.png");
	mat_brick.useDiffuseTextures = true;
	mat_brick.useSpecularTextures = true;
	mat_brick.useNormalTextures = true;
	mat_brick.shininess = 0.4f * 128.0f;
	materials.push_back(mat_brick);

	models.push_back(glm::translate(scaling_matrix, glm::vec3(0, 5.0f, -5.0f)));

	names.push_back("Plane");

	std::shared_ptr<Mesh> mesh = MeshHelper::cuboidMesh(glm::vec4(1, 0, 0, 1), 10.0f, 0.2f, 10.0f, true);
	meshes.push_back(mesh);

	Material mat_fabric = Material("materialmap");
	mat_fabric.texture_diffuse = std::make_shared<Texture>("res/fabric.png");
	mat_fabric.texture_specular = mat_fabric.texture_diffuse;
	mat_fabric.texture_normal = std::make_shared<Texture>("res/fabric_normal.png");
	mat_fabric.useDiffuseTextures = true;
	mat_fabric.useSpecularTextures = true;
	mat_fabric.useNormalTextures = true;
	mat_fabric.shininess = 0.4f * 128.0f;
	materials.push_back(mat_fabric);

	models.push_back(glm::translate(scaling_matrix, glm::vec3(0, -0.1, 0)));

	names.push_back("suzanne");

	std::shared_ptr<Mesh> suzanne = ObjLoader::loadObj("res/suzanne_blender.obj")[0];
	meshes.push_back(suzanne);

	Material mat_suzanne = Material("materialmap");
	mat_suzanne.ambient = glm::vec3(0.24725f, 0.1995f, 0.0745f);
	mat_suzanne.diffuse = glm::vec3(0.75164f, 0.60648f, 0.22648f);
	mat_suzanne.specular = glm::vec3(0.628281f, 0.555802f, 0.366065f);
	mat_suzanne.shininess = 0.4f * 16.0f;
	materials.push_back(mat_suzanne);

	models.push_back(glm::translate(scaling_matrix, glm::vec3(0, 7, 0)));

	names.push_back("Glass");

	std::shared_ptr<Mesh> sphere = ObjLoader::loadObj("res/sphere.obj")[0];
	meshes.push_back(sphere);

	Material mat_glass = Material("materialmap", GLASS);
	mat_glass.dynamic = false;
	mat_glass.environment = std::make_shared<EnvironmentMap>(glm::vec3(0, 5, 0));
	materials.push_back(mat_glass);

	models.push_back(glm::translate(glm::mat4(1), glm::vec3(0, 5, 0)));

	names.push_back("BRDF Sphere");

	std::shared_ptr<Mesh> sphere_brdf = ObjLoader::loadObj("res/sphere.obj")[0];
	meshes.push_back(sphere_brdf);

	Material mat_brdf = Material("materialmap", MaterialType::GGX);
	mat_brdf.ambient = glm::vec3(0.1f, 0.1f, 0.1f);
	mat_brdf.diffuse = glm::vec3(1.0f, 1.0f, 1.0f);
	mat_brdf.specular = glm::vec3(1.0f, 1.0f, 1.0f);
	mat_brdf.shininess = 0.4f * 512.0f;

	materials.push_back(mat_brdf);

	models.push_back(glm::translate(scaling_matrix, glm::vec3(0, 2, 6)));

	names.push_back("Mobius");

	std::shared_ptr<Mesh> mobius_mesh = ObjLoader::loadObj("res/mobius.obj")[0];
	meshes.push_back(mobius_mesh);

	Material mat_mobius = Material("materialmap", MaterialType::PHONG);
	mat_mobius.ambient = glm::vec3(0.05f, 0.05f, 0.1f);
	mat_mobius.diffuse = glm::vec3(0.7f, 0.7f, 1.0f);
	mat_mobius.specular = glm::vec3(0.7f, 0.7f, 1.0f);
	mat_mobius.shininess = 0.4f * 512.0f;

	materials.push_back(mat_mobius);

	models.push_back(glm::translate(scaling_matrix, glm::vec3(5, 2, 5)));

	std::shared_ptr<Mesh> light = MeshHelper::cubeMesh(glm::vec4(1, 1, 1, 1));
	light->create();

	Material mat_lamp = Material("materialmap");
	mat_lamp.ambient = glm::vec3(10, 10, 10);
	mat_lamp.diffuse = glm::vec3(1, 1, 1);
	mat_lamp.specular = glm::vec3(1, 1, 1);
	mat_lamp.shininess = 128.0f * 0.4f;

	std::shared_ptr<RenderObject> obj_light = std::make_shared<RenderObject>(light, mat_lamp, glm::translate(scaling_matrix, glm::vec3(20, 0, 0)));

	Light l1 = Light(glm::vec3(glm::rotate(glm::mat4(1), 3.14159f / 4.0f, glm::vec3(0, 0, 1)) * glm::vec4(20, 0, 0, 1))*scale, true, shadow_width, shadow_height, near, far);
	l1.ambient = glm::vec3(0.1f*scale*scale);
	l1.diffuse = glm::vec3(500.0f*scale * scale);
	l1.specular = glm::vec3(500.0f*scale * scale);

	Light l2 = Light(glm::vec3(0.0f, 0.2f, 0)*scale);
	l2.ambient = glm::vec3(0);
	l2.diffuse = glm::vec3(1.0f, 0.0f, 0.0f)*scale * scale;
	l2.specular = glm::vec3(1.0f, 0.0f, 0.0f)*scale * scale;

	Light l3 = Light(glm::vec3(-3, 0.2f, 2)*scale);
	l3.ambient = glm::vec3(0);
	l3.diffuse = glm::vec3(0.0f, 1.0f, 0.0f)*scale * scale;
	l3.specular = glm::vec3(0.0f, 1.0f, 0.0f)*scale * scale;

	Light l4 = Light(glm::vec3(0, 20, 20)*scale, true, shadow_width, shadow_height, near, far);
	l4.ambient = glm::vec3(0.1f*scale * scale);
	l4.diffuse = glm::vec3(500.0f*scale * scale);
	l4.specular = glm::vec3(500.0f*scale * scale);

	std::shared_ptr<Texture> particleTexture = std::make_shared<Texture>("res/smoke.png");

	std::vector<std::string> faces =
	{
		"right.jpg",
		"left.jpg",
		"top.jpg",
		"bottom.jpg",
		"front.jpg",
		"back.jpg"
	};

	std::shared_ptr<Texture> skybox_texture = std::make_shared<Texture>("res/skybox/", faces);

	Scene scene = Scene(names, meshes, materials, models);
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
	ShaderManager::addShader("Post");
	ShaderManager::addShader("Normal");
	ShaderManager::addShader("CubeMap");
	ShaderManager::addShader("Reflection");
	ShaderManager::addShader("VRScreen");
	ShaderManager::addShader("Skybox");

	ParticleRenderer particleRenderer = ParticleRenderer(glm::vec3(-1, 0, 0)*scale, 10000, 2, particleTexture);

	FrameBuffer fbo_left(renderer.getWidth(), renderer.getHeight());
	fbo_left.attachHDR();
	fbo_left.attachRenderBuffer();
	fbo_left.verify();

	FrameBuffer fbo_right(renderer.getWidth(), renderer.getHeight());
	fbo_right.attachHDR();
	fbo_right.attachRenderBuffer();
	fbo_right.verify();

	FrameBuffer::bindDefault();

	scene.passLights2Shader(ShaderManager::getShader("Normal"));
	obj_light->setModel(glm::translate(glm::mat4(1), l1.position));

	std::shared_ptr<EnvironmentMap> skybox_map = std::make_shared<EnvironmentMap>(glm::vec3(0));
	skybox_map->setCubeMap(skybox_texture);

	std::shared_ptr<Mesh> quad = MeshHelper::quadMesh(2.0f);

	quad->create();

	uint32_t frameID = 0;

	double currentTime;

	double endFrame;

	LOGGER::DEBUG("Finished rendering setup!\n");
	/* Loop until the user closes the window */
	while (window.isOpen())
	{
		GL::setViewport(shadow_width, shadow_height);
		scene.passLights2Shader(ShaderManager::getShader("Normal"));
		scene.updateShadowMaps();

		//----------------------------------------------------------------------------------------------
		window.resetViewport();
		std::shared_ptr<RenderObject> glass = scene.getObject("Glass");
		//Render scene
		if (frameID == 0)
		{
			ShaderManager::getShader("Normal")->bind();
			glass->getMaterial().environment->setSkybox(skybox_map);
			glass->getMaterial().environment->renderTo(&scene, ShaderManager::getShader("Normal"), ShaderManager::getShader("Skybox"));
		}

		GL::setViewport(renderer.getWidth(), renderer.getHeight());

		fbo_left.bind();
		GL::clear();
		//Skybox
		//Use vertex data of the light block
		skybox_map->renderAsSkybox(renderer.leftView(), renderer.leftProjection(), ShaderManager::getShader("Skybox"));

		ShaderManager::getShader("Reflection")->bind();
		ShaderManager::getShader("Reflection")->setInt("cubemap", 0);
		ShaderManager::getShader("Reflection")->setVec3("camera_position", renderer.position());
		glass->getMaterial().environment->getCubeMap()->bind();
		ShaderManager::getShader("Reflection")->setMVP(glm::translate(scaling_matrix, glm::vec3(0, 5, 0)), renderer.leftView(), renderer.leftProjection());
		sphere->render();
		glass->getMaterial().environment->getCubeMap()->unbind();

		//Light
		ShaderManager::getShader("Normal")->bind();
		ShaderManager::getShader("Normal")->setVec3("viewPos", renderer.position());
		ShaderManager::getShader("Normal")->setMVP(glm::mat4(1), renderer.leftView(), renderer.leftProjection());

		scene.render(ShaderManager::getShader("Normal"));

		//Render light

		obj_light->render(ShaderManager::getShader("Normal"));

		particleRenderer.update(window.DELTA_TIME());
		particleRenderer.render(renderer.leftView(), renderer.leftProjection());

		//RIGHT EYE--------------------------------------------------------------------------------------------------------

		fbo_right.bind();
		GL::clear();
		//Skybox
		//Use vertex data of the light block

		skybox_map->renderAsSkybox(renderer.rightView(), renderer.rightProjection(), ShaderManager::getShader("Skybox"));

		ShaderManager::getShader("Reflection")->bind();
		ShaderManager::getShader("Reflection")->setInt("cubemap", 0);
		ShaderManager::getShader("Reflection")->setVec3("camera_position", renderer.position());
		glass->getMaterial().environment->getCubeMap()->bind();
		ShaderManager::getShader("Reflection")->setMVP(glm::translate(scaling_matrix, glm::vec3(0, 5, 0)), renderer.rightView(), renderer.rightProjection());
		sphere->render();
		glass->getMaterial().environment->getCubeMap()->unbind();

		//Light
		ShaderManager::getShader("Normal")->bind();
		ShaderManager::getShader("Normal")->setVec3("viewPos", renderer.position());
		ShaderManager::getShader("Normal")->setMVP(glm::mat4(1), renderer.rightView(), renderer.rightProjection());

		scene.render(ShaderManager::getShader("Normal"));

		//Render light

		obj_light->render(ShaderManager::getShader("Normal"));

		//particleRenderer.update(window.DELTA_TIME());
		particleRenderer.render(renderer.rightView(), renderer.rightProjection());

		renderer.getRenderTargetLeft()->bind();
		GL::clear();
		ShaderManager::getShader("Post")->bind();
		ShaderManager::getShader("Post")->setFloat("exposure", 1.0f);
		ShaderManager::getShader("Post")->setInt("screenTexture", 0);
		fbo_left.getTexture()->bind();
		quad->render();

		renderer.getRenderTargetRight()->bind();
		GL::clear();
		ShaderManager::getShader("Post")->bind();
		ShaderManager::getShader("Post")->setFloat("exposure", 1.0f);
		ShaderManager::getShader("Post")->setInt("screenTexture", 0);
		fbo_right.getTexture()->bind();
		quad->render();
		

		FrameBuffer::bindDefault();
		window.resetViewport();
		GL::clear();
		ShaderManager::getShader("VRScreen")->bind();
		ShaderManager::getShader("VRScreen")->setInt("leftEye", 0);
		ShaderManager::getShader("VRScreen")->setInt("rightEye", 1);
		renderer.getRenderTargetLeft()->getTexture()->bind(0);
		renderer.getRenderTargetRight()->getTexture()->bind(1);
		quad->render();

		renderer.uploadToHMD();

		window.spinOnce();
		renderer.spinOnce();

		++frameID;
	}

	LOGGER::end();

	return 0;
}