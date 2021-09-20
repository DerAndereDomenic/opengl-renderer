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

std::shared_ptr<Scene> generateScene()
{
	std::vector<std::string> names;
	std::vector<std::shared_ptr<Mesh>> meshes;
	std::vector<Material> materials;
	std::vector<glm::mat4> models;

	names.push_back("Ball");
	meshes.push_back(ObjLoader::loadObj("res/sphere.obj")[0]);
	models.push_back(glm::mat4(1));
	Material ball_mat = Material("materialmap", PHONG);
	ball_mat.diffuse = glm::vec4(1, 1, 0, 1);
	ball_mat.ambient = glm::vec4(1, 1, 0, 1);
	ball_mat.specular = glm::vec4(1, 1, 0, 1);
	ball_mat.shininess = 0.4f * 128.0f;
	materials.push_back(ball_mat);

	names.push_back("Plane");
	meshes.push_back(ObjLoader::loadObj("res/plane.obj")[0]);
	models.push_back(glm::scale(glm::translate(glm::mat4(1), glm::vec3(0, -1, 0)), glm::vec3(500, 500, 500)));
	Material plane_mat = Material("materialmap");
	plane_mat.diffuse = glm::vec4(1, 0, 1, 1);
	plane_mat.ambient = glm::vec4(1, 0, 1, 1);
	plane_mat.specular = glm::vec4(1, 0, 1, 1);
	plane_mat.shininess = 0.4f * 128.0f;
	materials.push_back(plane_mat);

	Scene scene = Scene(names, meshes, materials, models);

	return std::make_shared<Scene>(scene);
}

int main()
{
	LOGGER::setProject("Dancing Ball", "1.0");
	LOGGER::start();

	unsigned int width = 1280, height = 720;

	RenderWindow window = RenderWindow(width, height, "Dancing Ball");

	GL::enableDebugOutput();

	glm::vec3 camera_pos = 2.0f*glm::vec3(0, 1, 5);
	glm::mat4 view = glm::lookAt(camera_pos, glm::vec3(0,0,0), glm::vec3(0, 1, 0));
	glm::mat4 projection = glm::perspective(glm::radians(90.0f), static_cast<float>(width) / static_cast<float>(height), 0.01f, 100.0f);

	ShaderManager::addShader("Normal");
	
	std::shared_ptr<Scene> scene = generateScene();
	Light light = Light(glm::vec3(10, 10, 10), true, 2000, 2000, 0.1f, 500.0f);
	light.ambient = glm::vec3(0.1f);
	light.diffuse = glm::vec3(400.0f);
	light.specular = glm::vec3(400.0f);
	scene->addLight(&light);

	std::shared_ptr<RenderObject> ball = scene->getObject("Ball");

	//SIMULATION-----------------------------------------------------------------------------------------------
	const unsigned int simulation_steps = 10000;
	float deltaTime = 0;
	const glm::vec3 GRAV_CONST(0, -9.81, 0);
	const float DAMPING = 1.15f;
	glm::vec3 v(0, 0, 1.0f);
	glm::vec3 p(0, 5, 0);
	ball->setModel(glm::translate(glm::mat4(1), p));

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

		ball->setModel(glm::translate(glm::mat4(1), p));

		GL::clear();

		GL::setViewport(2000, 2000);

		scene->passLights2Shader(ShaderManager::getShader("Normal"));
		scene->updateShadowMaps();

		window.resetViewport();

		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		ShaderManager::getShader("Normal")->bind();
		ShaderManager::getShader("Normal")->setVec3("viewPos", camera_pos);
		ShaderManager::getShader("Normal")->setMVP(glm::mat4(1), view, projection);

		scene->render(ShaderManager::getShader("Normal"));

		window.spinOnce();

		if (KeyManager::isKeyDown(GLFW_KEY_ESCAPE))
		{
			window.close();
		}
	}

	LOGGER::end();

	return 0;
}
