#include <Core/Platform.h>
#include <Core/GLFunctions.h>
#include <DLogger/Logger.h>

#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <OpenGLObjects/FrameBuffer.h>
#include <DataStructure/Mesh.h>
#include <DataStructure/MeshHelper.h>
#include <DataStructure/RenderObject.h>
#include <DataStructure/Skybox.h>
#include <DataStructure/Scene.h>
#include <DataStructure/Model.h>
#include <Shader/ShaderManager.h>
#include <IO/KeyManager.h>
#include <IO/ObjLoader.h>
#include <Renderer/RenderWindow.h>
#include <Renderer/Camera.h>
#include <DataStructure/EnvironmentMap.h>
#include <Renderer/TextRenderer.h>
#include <Renderer/ParticleRenderer.h>
#include <GUI/DebugControl.h>
#include <GUI/ExposureControl.h>
#include <GUI/WindowClose.h>
#include <GUI/ModeControl.h>
#include <GUI/Button.h>

#include <iomanip>
#include <sstream>


int main(void)
{
	LOGGER::setProject("OpenGL Renderer", "1.0");
	LOGGER::start();


	uint32_t width = 1280;
	uint32_t height = 720;

	uint32_t shadow_width = 2000;
	uint32_t shadow_height = 2000;

	float near = 0.1f;
	float far = 500.0f;

	Camera camera = Camera(static_cast<float>(width)/static_cast<float>(height), near, far);
	RenderWindow window = RenderWindow(width, height, "Render Window", &camera);

	GL::enableDebugOutput();

	std::stringstream stream;

	//---------------------------------------------------------------------------------//
	//                              CALLBACKS   /    UI                                //
	//---------------------------------------------------------------------------------//
	WindowClose close_callback(&window);
	ExposureControl exposure_callback;
	ModeControl mode_callback(&window);

	Button debugButton(0, window.getHeight() - 16, 100, 16);
	Button closeButton(116, window.getHeight() - 16, 100, 16);

	debugButton.setText("Debug");
	closeButton.setText("Close");

	window.registerKeyCallback(GLFW_KEY_ESCAPE, &close_callback);
	window.registerKeyCallback(GLFW_KEY_KP_ADD, &exposure_callback);
	window.registerKeyCallback(GLFW_KEY_KP_SUBTRACT, &exposure_callback);
	window.registerKeyCallback(GLFW_KEY_LEFT_ALT, &mode_callback);
	
	window.registerButtonCallback(&closeButton, &close_callback);

	//---------------------------------------------------------------------------------//
	//                              SCENE SETUP                                        //
	//---------------------------------------------------------------------------------//
	LOGGER::DEBUG("Started scene setup!\n");

	std::vector<std::string> names;
	std::vector<std::shared_ptr<Model>> models;

	Model model("res/Sponza/Sponza.gltf", glm::mat4(1), true);

	Light light = Light(glm::vec3(5.0f, 15.0f, 0), true, shadow_width, shadow_height, 0.01f, 500.0f);
	light.ambient = glm::vec3(0.1f);
	light.diffuse = glm::vec3(500.0f );
	light.specular = glm::vec3(500.0f);

	names.push_back("Sponza");
	models.push_back(std::make_shared<Model>(model));

	Scene scene(names, models);
	scene.addLight(&light);

	names.clear();
	models.clear();

	std::shared_ptr<Mesh> quad = MeshHelper::quadMesh(2.0f);

	quad->create();

	LOGGER::DEBUG("Finished scene setup!\n");
	//---------------------------------------------------------------------------------//
	//                              RENDERING SETUP                                    //
	//---------------------------------------------------------------------------------//
	LOGGER::DEBUG("Start Renderer setup!\n");
	ShaderManager::addShader("Post");
	ShaderManager::addShader("Normal");

	std::shared_ptr<TextRenderer> textRenderer = window.getTextRenderer();

	std::shared_ptr<FrameBuffer> fbo = std::make_shared<FrameBuffer>(window.getWidth(), window.getHeight());
	fbo->attachHDR();
	fbo->attachRenderBuffer();
	fbo->verify();
	fbo->unbind();

	EnvironmentMap map = EnvironmentMap(glm::vec3(0, 5, 0));

	ShaderManager::getShader("Post")->bind();
	ShaderManager::getShader("Post")->setInt("screenTexture", 0);
	ShaderManager::getShader("Post")->setInt("lightTexture", 1);

	uint32_t frameID = 0;

	double currentTime;

	double endFrame;

	LOGGER::DEBUG("Finished rendering setup!\n");
	/* Loop until the user closes the window */
	while (window.isOpen())
	{
		currentTime = glfwGetTime();

		//----------------------------------------------------------------------------------------------
		GL::setViewport(shadow_width, shadow_height);
		scene.passLights2Shader(ShaderManager::getShader("Normal"));
		scene.updateShadowMaps();

		window.resetViewport();
		fbo->bind();

		fbo->clear();
		
		ShaderManager::getShader("Normal")->bind();
		ShaderManager::getShader("Normal")->setVec3("viewPos", camera.getPosition());
		ShaderManager::getShader("Normal")->setMVP(glm::mat4(1), camera.getView(), camera.getProjection());
		scene.render(ShaderManager::getShader("Normal"));

		//Render to quad
		fbo->unbind();
		GL::clear();
		ShaderManager::getShader("Post")->bind();
		ShaderManager::getShader("Post")->setFloat("exposure", exposure_callback.getExposure());
		fbo->getTexture(0)->bind(0);
		//lights[0].shadow_map.getTexture().bind();
		quad->render();
		
		stream << "X: " << std::fixed << std::setprecision(2) << camera.getPosition().x;
		textRenderer->render(stream.str(), window.getWidth()-100, window.getHeight()-16, 1, glm::vec3(1, 1, 1));
		stream.str("");

		stream << "Y: " << std::fixed << std::setprecision(2) << camera.getPosition().y;
		textRenderer->render(stream.str(), window.getWidth() - 100, window.getHeight() - 32, 1, glm::vec3(1, 1, 1));
		stream.str("");

		stream << "Z: " << std::fixed << std::setprecision(2) << camera.getPosition().z;
		textRenderer->render(stream.str(), window.getWidth() - 100, window.getHeight() - 48, 1, glm::vec3(1, 1, 1));
		stream.str("");

		endFrame = glfwGetTime();

		stream << "Render time: " << std::fixed << std::setprecision(5) << (endFrame - currentTime) << "ms FPS: " << std::fixed << std::setprecision(1) << 1.0f / (endFrame - currentTime) << "; Display FPS: " << std::fixed << std::setprecision(1) << 1.0f/window.DELTA_TIME();
		textRenderer->render(stream.str(), 16, 16, 1, glm::vec3(0, 1, 0));
		stream.str("");

		window.spinOnce();

		++frameID;
	}

	LOGGER::end();

	return 0;
}
