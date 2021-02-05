#include <Renderer/RenderWindow.h>
#include <IO/KeyManager.h>

int main()
{
	uint32_t width = 1280, height = 720;

	Camera camera = Camera::createObject(glm::vec3(0, 0, 0), 90.0f, width / height, 0.01f, 500);
	RenderWindow window = RenderWindow::createObject(width, height, "WaterScene", &camera);
	KeyManager::instance()->setup(window);

	while (window.isOpen())
	{
		window.spinOnce();
	}

	RenderWindow::destroyObject(window);
	Camera::destroyObject(camera);

	return 0;
}