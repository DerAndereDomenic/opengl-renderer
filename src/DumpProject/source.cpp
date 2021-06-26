#include <OpenGLRendererConfig.h>
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
	LOGGER::setProject("OpenGL Renderer", std::to_string(OpenGLRenderer_VERSION_MAJOR) + "." + std::to_string(OpenGLRenderer_VERSION_MINOR));
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

	Model model(RESOURCE_PATH + "cornell_box.gltf");
	Light light = Light(glm::vec3(0, 9.5, 0));
	light.ambient = glm::vec3(0.1f);
	light.diffuse = glm::vec3(500.0f );
	light.specular = glm::vec3(500.0f);

	std::shared_ptr<Mesh> quad = MeshHelper::quadMesh(2.0f);

	quad->create();

	LOGGER::DEBUG("Finished scene setup!\n");
	//---------------------------------------------------------------------------------//
	//                              RENDERING SETUP                                    //
	//---------------------------------------------------------------------------------//
	LOGGER::DEBUG("Start Renderer setup!\n");
	ShaderManager::instance()->addShader("Post");
	ShaderManager::instance()->addShader("Normal");

	std::shared_ptr<TextRenderer> textRenderer = window.getTextRenderer();

	std::shared_ptr<FrameBuffer> fbo = std::make_shared<FrameBuffer>(window.getWidth(), window.getHeight());
	fbo->attachHDR();
	fbo->attachRenderBuffer();
	fbo->verify();
	fbo->unbind();

	EnvironmentMap map = EnvironmentMap(glm::vec3(0, 5, 0));

	ShaderManager::instance()->getShader("Post")->bind();
	ShaderManager::instance()->getShader("Post")->setInt("screenTexture", 0);
	ShaderManager::instance()->getShader("Post")->setInt("lightTexture", 1);

	uint32_t frameID = 0;

	double currentTime;

	double endFrame;

	LOGGER::DEBUG("Finished rendering setup!\n");
	/* Loop until the user closes the window */
	while (window.isOpen())
	{
		currentTime = glfwGetTime();

		//----------------------------------------------------------------------------------------------
		window.resetViewport();

		window.resetViewport();
		fbo->bind();

		fbo->clear();
		
		ShaderManager::instance()->getShader("Normal")->bind();
		ShaderManager::instance()->getShader("Normal")->setVec3("viewPos", camera.getPosition());
		ShaderManager::instance()->getShader("Normal")->setMVP(glm::mat4(1), camera.getView(), camera.getProjection());
		light.addToShader(ShaderManager::instance()->getShader("Normal"), 0);
		model.render(ShaderManager::instance()->getShader("Normal"));

		//Render to quad
		fbo->unbind();
		GL::clear();
		ShaderManager::instance()->getShader("Post")->bind();
		ShaderManager::instance()->getShader("Post")->setFloat("exposure", exposure_callback.getExposure());
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

	ShaderManager::destroyObject(*ShaderManager::instance());
	KeyManager::destroy();

	LOGGER::end();

	return 0;
}
