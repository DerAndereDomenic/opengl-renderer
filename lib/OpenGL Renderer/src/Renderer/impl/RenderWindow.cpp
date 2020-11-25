#include <Renderer/RenderWindow.h>
#include <DLogger/Logger.h>
#include <Core/Platform.h>

RenderWindow 
RenderWindow::createObject(const uint32_t& width, const uint32_t& height, const std::string& title, Camera* camera)
{
	RenderWindow result;

	result._width = width;
	result._height = height;
	result._aspect_ratio = static_cast<float>(width) / static_cast<float>(height);
	result._camera = camera;

	if (!glfwInit())
	{
		LOGGER::ERROR("RENDERER::GLFWINIT::ERROR\n");
	}

	result._window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
	if (!result._window)
	{
		glfwTerminate();
		LOGGER::ERROR("RENDERER::WINDOW::ERROR\n");
	}

	glfwMakeContextCurrent(result._window);

	if (glewInit() != GLEW_OK)
	{
		LOGGER::ERROR("RENDERER::GLEWINIT::ERROR\n");
	}

	glfwSetInputMode(result._window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	result._isOpen = true;

	result._active_keys.insert(std::make_pair(GLFW_MOUSE_BUTTON_LEFT, false));

	result._textRenderer = TextRenderer::createObject(width, height);

#ifdef __OPENGLRENDERER_WINDOWS

	result._textRenderer.loadFont("C:/Windows/Fonts/consola.ttf", 16);

#elif __OPENGLRENDERER_UNIX

	result._textRenderer.loadFont("/usr/share/fonts/truetype/hack/Hack-Regular.ttf", 16);

#endif

	return result;
}

void 
RenderWindow::destroyObject(RenderWindow& window)
{
	window._width = 0;
	window._height = 0;
	window._aspect_ratio = 0.0f;
	window._isOpen = false;
	window._key_callbacks.clear();
	window._button_callbacks.clear();
	window._active_keys.clear();
	TextRenderer::destroyObject(window._textRenderer);
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
RenderWindow::resetViewport()
{
	glViewport(0, 0, _width, _height);
}

void 
RenderWindow::registerKeyCallback(const uint32_t& key, KeyPressFunction* callback)
{
	_key_callbacks.insert(std::make_pair(key, callback));
	_active_keys.insert(std::make_pair(key, false));
}

void 
RenderWindow::registerButtonCallback(const Button& button, KeyPressFunction* callback)
{
	_button_callbacks.insert(std::make_pair(button, callback));
}

void 
RenderWindow::spinOnce()
{
	glfwSwapBuffers(_window);
	glfwPollEvents();
	double currentTime = glfwGetTime();
	_deltaTime = currentTime - _lastTime;
	_lastTime = currentTime;

	double xpos, ypos;
	glfwGetCursorPos(_window, &xpos, &ypos);

	if (_camera != nullptr && _mode == ViewerMode::VIEWER)
	{
		_camera->processInput(_deltaTime, xpos, ypos);
	}

	for (typename std::unordered_multimap<uint32_t, KeyPressFunction*>::const_iterator it = _key_callbacks.begin(); it != _key_callbacks.end(); ++it)
	{
		typename std::unordered_map<uint32_t, bool>::iterator active = _active_keys.find(it->first);	//Lazy evaluation, iterator always exists because it was added when registering the callback
		if (!active->second && glfwGetKey(_window, it->first) == GLFW_PRESS)
		{
			it->second->onPress(it->first);
			active->second = true;
		}
		else if (active->second && glfwGetKey(_window, it->first) == GLFW_RELEASE)
		{
			active->second = false;
		}
	}
}

bool 
RenderWindow::updateSize()
{
	int32_t width_new;
	int32_t height_new;

	glfwGetFramebufferSize(_window, &width_new, &height_new);

	if (&width_new != NULL && &height_new != NULL)
	{
		if (width_new != _width || height_new != _height)
		{
			_width = width_new;
			_height = height_new;
			_aspect_ratio = static_cast<float>(_width) / static_cast<float>(_height);

			resetViewport();

			return true;
		}
	}
	return false;
}

bool 
RenderWindow::isOpen()
{
	return _isOpen && !glfwWindowShouldClose(_window);
}