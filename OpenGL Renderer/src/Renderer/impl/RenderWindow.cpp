#include <Renderer/RenderWindow.h>
#include <Renderer/Camera.h>

RenderWindow 
RenderWindow::createObject(const uint32_t& width, const uint32_t& height, const std::string& title)
{
	RenderWindow result;

	result._width = width;
	result._height = height;
	result._aspect_ratio = static_cast<float>(width) / static_cast<float>(height);

	if (!glfwInit())
	{
		std::cerr << "RENDERER::GLFWINIT::ERROR" << std::endl;
	}

	result._window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
	if (!result._window)
	{
		glfwTerminate();
		std::cerr << "RENDERER::WINDOW::ERROR" << std::endl;
	}

	glfwMakeContextCurrent(result._window);

	if (glewInit() != GLEW_OK)
	{
		std::cerr << "RENDERER::GLEWINIT::ERROR" << std::endl;
	}

	glfwSetInputMode(result._window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	result._isOpen = true;

	return result;
}

void 
RenderWindow::destroyObject(RenderWindow& window)
{
	window._width = 0;
	window._height = 0;
	window._aspect_ratio = 0.0f;
	window._isOpen = false;
	if (window._window != nullptr)
	{
		window.close();
	}
}

void 
RenderWindow::close()
{
	_isOpen = false;
	glfwDestroyWindow(_window);
	_window = nullptr;
	glfwTerminate();
}

void
RenderWindow::setViewport(const uint32_t& width, const uint32_t& height)
{
	glViewport(0, 0, width, height);
}

void
RenderWindow::resetViewport()
{
	glViewport(0, 0, _width, _height);
}

void
RenderWindow::enableDepthWriting()
{
	glDepthMask(GL_TRUE);
}

void
RenderWindow::disableDepthWriting()
{
	glDepthMask(GL_FALSE);
}

void 
RenderWindow::clear(const GLclampf& r, const GLclampf& g, const GLclampf& b, const GLclampf& a)
{
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void 
RenderWindow::spinOnce()
{
	glfwSwapBuffers(_window);
	glfwPollEvents();
	double currentTime = glfwGetTime();
	_deltaTime = currentTime - _lastTime;
	_lastTime = currentTime;
}

void 
RenderWindow::updateCamera(Camera& camera)
{
	int32_t width_new;
	int32_t height_new;

	glfwGetWindowSize(_window, &width_new, &height_new);

	if (&width_new != NULL && &height_new != NULL)
	{
		if (width_new != _width || height_new != _height)
		{
			printf("Resized\n");
		}
	}
}

bool 
RenderWindow::isOpen()
{
	return !glfwWindowShouldClose(_window) && _isOpen;
}