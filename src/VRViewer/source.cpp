#include <iostream>
#include <Renderer/VRRenderer.h>
#include <DLogger/Logger.h>
#include <IO/KeyManager.h>
#include <Core/GLFunctions.h>

int main()
{
	LOGGER::setProject("VR Viewer", "1.0");
	LOGGER::start();

	RenderWindow dummy_window = RenderWindow::createObject(100, 100, "VR Renderer");
	VRRenderer renderer = VRRenderer::createObject();
	KeyManager::instance()->setup(dummy_window);
	GL::enableDebugOutput();

	bool running = true;

	while (running && dummy_window.isOpen())
	{

		renderer.render();

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

	LOGGER::end();
	return 0;
}