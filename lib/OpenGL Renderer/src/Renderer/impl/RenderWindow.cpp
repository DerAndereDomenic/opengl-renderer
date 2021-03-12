#include <OpenGLRendererConfig.h>
#include <Renderer/RenderWindow.h>
#include <DLogger/Logger.h>
#include <Core/Platform.h>
#include <IO/KeyManager.h>

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
	result._textRenderer.loadFont((RESOURCE_PATH + "Hack-Regular.ttf").c_str(), 16);
    
    KeyManager::instance()->setup(result);

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
RenderWindow::registerButtonCallback(Button* button, KeyPressFunction* callback)
{
	_button_callbacks.insert(std::make_pair(button, callback));
}

void 
RenderWindow::spinOnce()
{
	double xpos, ypos;
	glfwGetCursorPos(_window, &xpos, &ypos);

	if (_camera != nullptr && _mode == ViewerMode::VIEWER)
	{
		_camera->processInput(_deltaTime, xpos, ypos);
	}

	for (typename std::unordered_multimap<Button*, KeyPressFunction*, ButtonHash>::iterator it = _button_callbacks.begin(); it != _button_callbacks.end(); ++it)
	{
		ButtonMode mode = ButtonMode::IDLE;
		if (_mode == ViewerMode::EDIT)
		{
			if (it->first->inside(xpos, _height - ypos))
			{
				typename std::unordered_map<uint32_t, bool>::iterator active = _active_keys.find(GLFW_MOUSE_BUTTON_LEFT);

				mode = ButtonMode::HOVER;
				if (glfwGetMouseButton(_window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
				{
					if(!active->second)
					{
						it->second->onPress(0);
						active->second = true;
					}
					else
					{
						it->second->onHold(0);
						active->second = true;
					}
				}
				else if (active->second && glfwGetMouseButton(_window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
				{
					it->second->onRelease(0);
					active->second = false;
				}

				if(active->second)
				{
					mode = ButtonMode::CLICK;
				}
			}
		}

		it->first->render(_textRenderer, mode);
        
        if(_window == nullptr)
        {
            return;
        }
	}

	for (typename std::unordered_multimap<uint32_t, KeyPressFunction*>::const_iterator it = _key_callbacks.begin(); it != _key_callbacks.end(); ++it)
	{
		typename std::unordered_map<uint32_t, bool>::iterator active = _active_keys.find(it->first);	//Lazy evaluation, iterator always exists because it was added when registering the callback
		if (glfwGetKey(_window, it->first) == GLFW_PRESS)
		{
			if(!active->second)
			{
				it->second->onPress(it->first);
				active->second = true;
			}
			else
			{
				it->second->onHold(it->first);
				active->second = true;
			}
			
		}
		else if (active->second && glfwGetKey(_window, it->first) == GLFW_RELEASE)
		{
			it->second->onRelease(it->first);
			active->second = false;
		}
		
        if(_window == nullptr)
        {
            return;
        }
	}

	double currentTime = glfwGetTime();
	_deltaTime = currentTime - _lastTime;
	_lastTime = currentTime;
	glfwSwapBuffers(_window);
	glfwPollEvents();
}

void 
RenderWindow::updateSize(const uint32_t& width, const uint32_t& height)
{
	if (width != _width || height != _height)
	{
		_width = width;
		_height = height;
		_aspect_ratio = static_cast<float>(_width) / static_cast<float>(_height);

		glfwSetWindowSize(_window, width, height);

		resetViewport();
	}
}

bool 
RenderWindow::isOpen()
{
	return _isOpen && !glfwWindowShouldClose(_window);
}
