#include <iostream>
#include <Renderer/VRRenderer.h>
#include <DLogger/Logger.h>
#include <IO/KeyManager.h>
#include <Core/GLFunctions.h>
#include <Shader/ShaderManager.h>
#include <DataStructure/MeshHelper.h>

int main()
{
	LOGGER::setProject("VR Viewer", "1.0");
	LOGGER::start();

	RenderWindow dummy_window = RenderWindow::createObject(100, 100, "VR Renderer");
	VRRenderer renderer = VRRenderer::createObject();
	KeyManager::instance()->setup(dummy_window);
	GL::enableDebugOutput();

	ShaderManager::instance()->addShader("BasicVR");

	Mesh quad = MeshHelper::quadMesh(2.0f);
	quad.create();

	bool running = true;

	while (running && dummy_window.isOpen())
	{
		renderer.getRenderTarget().bind();
		GL::clear();
		ShaderManager::instance()->getShader("BasicVR").bind();
		quad.render();

		renderer.render();
		
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
	Mesh::destroyObject(quad);
	ShaderManager::destroyObject(*ShaderManager::instance());

	LOGGER::end();
	return 0;
}