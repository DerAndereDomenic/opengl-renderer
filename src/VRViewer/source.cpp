#include <iostream>
#include <Renderer/VRRenderer.h>
#include <DLogger/Logger.h>
#include <IO/KeyManager.h>
#include <Core/GLFunctions.h>
#include <Shader/ShaderManager.h>
#include <DataStructure/MeshHelper.h>
#include <glm/gtc/matrix_transform.hpp>

int main()
{
	LOGGER::setProject("VR Viewer", "1.0");
	LOGGER::start();

	RenderWindow dummy_window = RenderWindow::createObject(100, 100, "VR Renderer");
	VRRenderer renderer = VRRenderer::createObject();
	KeyManager::instance()->setup(dummy_window);
	GL::enableDebugOutput();

	ShaderManager::instance()->addShader("BasicVR");

	Mesh cube = MeshHelper::cubeMesh(glm::vec4(1));
	cube.create();

	bool running = true;

	while (running && dummy_window.isOpen())
	{
		renderer.getRenderTargetLeft().bind();
		GL::clear();
		ShaderManager::instance()->getShader("BasicVR").bind();
		ShaderManager::instance()->getShader("BasicVR").setMVP(glm::mat4(1), renderer.trackDevicePose(), renderer.projection(vr::Eye_Left));
		cube.render();

		renderer.getRenderTargetRight().bind();
		GL::clear();
		ShaderManager::instance()->getShader("BasicVR").bind();
		ShaderManager::instance()->getShader("BasicVR").setMVP(glm::mat4(1), renderer.trackDevicePose(), renderer.projection(vr::Eye_Right));
		cube.render();

		renderer.uploadToHMD();
		
		FrameBuffer::bindDefault();

		renderer.spinOnce();
		dummy_window.spinOnce();

		if (KeyManager::instance()->isKeyDown(GLFW_KEY_ESCAPE))
		{
			running = false;
			dummy_window.close();
		}
	}

	RenderWindow::destroyObject(dummy_window);
	VRRenderer::destroyObject(renderer);
	KeyManager::instance()->destroy();
	Mesh::destroyObject(cube);
	ShaderManager::destroyObject(*ShaderManager::instance());

	LOGGER::end();
	return 0;
}