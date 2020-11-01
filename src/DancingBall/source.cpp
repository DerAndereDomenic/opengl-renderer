#include <OpenGLRendererConfig.h>
#include <Core/GLFunctions.h>

#include <iostream>
#include <Renderer/RenderWindow.h>
#include <IO/KeyManager.h>
#include <Shader/ShaderManager.h>
#include <DataStructure/Mesh.h>
#include <IO/ObjLoader.h>
#include <DataStructure/Scene.h>
#include <glm/gtx/transform.hpp>
#include <DLogger/Logger.h>
#include <Core/GLFunctions.h>

Scene generateScene()
{
	std::vector<std::string> names;
	std::vector<Mesh> meshes;
	std::vector<Material> materials;
	std::vector<glm::mat4> models;

	names.push_back("Ball");
	meshes.push_back(ObjLoader::loadObj(RESOURCE_PATH + "sphere.obj")[0]);
	models.push_back(glm::mat4(1));
	Material ball_mat = Material::createObject("materialmap", PHONG);
	ball_mat.useTextures = false;
	ball_mat.diffuse = glm::vec4(1, 1, 0, 1);
	ball_mat.ambient = glm::vec4(1, 1, 0, 1);
	ball_mat.specular = glm::vec4(1, 1, 0, 1);
	ball_mat.shininess = 0.4f * 128.0f;
	materials.push_back(ball_mat);

	names.push_back("Plane");
	meshes.push_back(ObjLoader::loadObj(RESOURCE_PATH + "plane.obj")[0]);
	models.push_back(glm::scale(glm::translate(glm::mat4(1), glm::vec3(0, -1, 0)), glm::vec3(500, 500, 500)));
	Material plane_mat = Material::createObject("materialmap");
	plane_mat.useTextures = false;
	plane_mat.diffuse = glm::vec4(1, 0, 1, 1);
	plane_mat.ambient = glm::vec4(1, 0, 1, 1);
	plane_mat.specular = glm::vec4(1, 0, 1, 1);
	plane_mat.shininess = 0.4f * 128.0f;
	materials.push_back(plane_mat);

	Scene scene = Scene::createObject(names, meshes, materials, models);

	return scene;
}

int main()
{
	LOGGER::setProject("Dancing Ball", "1.0");
	LOGGER::start();

	unsigned int width = 1280, height = 720;

	RenderWindow window = RenderWindow::createObject(width, height, "Dancing Ball");
	KeyManager::instance()->setup(window);

	GL::enableDebugOutput();

	glm::vec3 camera_pos = 2.0f*glm::vec3(0, 1, 5);
	glm::mat4 view = glm::lookAt(camera_pos, glm::vec3(0,0,0), glm::vec3(0, 1, 0));
	glm::mat4 projection = glm::perspective(glm::radians(90.0f), static_cast<float>(width) / static_cast<float>(height), 0.01f, 100.0f);

	ShaderManager::instance()->addShader("Normal");
	
	Scene scene = generateScene();
	Light light = Light::createObject(glm::vec3(10, 10, 10), true, 2000, 2000, 0.1f, 500.0f);
	light.ambient = glm::vec3(0.1f);
	light.diffuse = glm::vec3(400.0f);
	light.specular = glm::vec3(400.0f);
	scene.addLight(&light);

	RenderObject& ball = scene.getObject("Ball");

	//SIMULATION-----------------------------------------------------------------------------------------------
	const unsigned int simulation_steps = 10000;
	float deltaTime = 0;
	const glm::vec3 GRAV_CONST(0, -9.81, 0);
	const float DAMPING = 1.15f;
	glm::vec3 v(0, 0, 1.0f);
	glm::vec3 p(0, 5, 0);
	ball.setModel(glm::translate(glm::mat4(1), p));

	double currentTime = 0;
	double lastTime = 0;

	bool firstFrame = true;

	while (window.isOpen())
	{
		currentTime = glfwGetTime();
		deltaTime = currentTime - lastTime;
		lastTime = currentTime;

		deltaTime /= static_cast<float>(simulation_steps);

		if (!firstFrame)
		{
			for (unsigned int i = 0; i < simulation_steps; ++i)
			{
				v += GRAV_CONST * deltaTime;
				p += v * deltaTime;

				if (p.y <= 0.0f)
				{
					p -= v * deltaTime;
					v.y = -v.y / DAMPING;
				}

			}
		}
		else
		{
			firstFrame = false;
		}
		



		view = glm::lookAt(camera_pos, p, glm::vec3(0, 1, 0));
		//if (glm::length(v) < 0.0001f)std::cout << p.y << std::endl;

		ball.setModel(glm::translate(glm::mat4(1), p));

		GL::clear();

		GL::setViewport(2000, 2000);

		scene.passLights2Shader(ShaderManager::instance()->getShader("Normal"));
		scene.updateShadowMaps();

		window.resetViewport();

		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		ShaderManager::instance()->getShader("Normal").bind();
		ShaderManager::instance()->getShader("Normal").setVec3("viewPos", camera_pos);
		ShaderManager::instance()->getShader("Normal").setMVP(glm::mat4(1), view, projection);

		scene.render(ShaderManager::instance()->getShader("Normal"));

		window.spinOnce();

		if (KeyManager::instance()->isKeyDown(GLFW_KEY_ESCAPE))
		{
			window.close();
		}
	}

	RenderWindow::destroyObject(window);
	KeyManager::instance()->destroy();
	Scene::destroyObject(scene);

	LOGGER::end();

	return 0;
}