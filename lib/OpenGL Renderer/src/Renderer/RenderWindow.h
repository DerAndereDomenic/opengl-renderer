#ifndef __OPENGLRENDERER_RENDERER_RENDER_WINDOW_H
#define __OPENGLRENDERER_RENDERER_RENDER_WINDOW_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>

#include <unordered_map>

#include <OpenGLObjects/VertexArray.h>
#include <Shader/Shader.h>
#include <Renderer/TextRenderer.h>
#include <GUI/KeyPressFunction.h>
#include <GUI/Button.h>

#include <cstdint>

#include <Renderer/Camera.h>

/**
*	\brief The mode of the window
*/
enum class ViewerMode
{
	VIEWER = 0,		/**<< Standard first person camera*/
	EDIT = 1		/**<< Free cursor */
};

/**
*	\brief A class to model a render window
*/
class RenderWindow
{
public:
	/**
	*	\brief Create an empty render window
	*/
	RenderWindow() = default;

	/**
	*	\brief Create a render window
	*	\param[in] width The width of the window
	*	\param[in] height The height of the window
	*	\param[in] title The title of the window
	*	\param[in] camera A camera
	*/
	RenderWindow(const uint32_t& width, const uint32_t& height, const std::string& title, Camera* camera = nullptr);

	/**
	*	\brief Destroys the given window
	*/
	~RenderWindow();

	/**
	*	\brief Closes the window
	*/
	void close();

	/**
	*	\brief Swap buffers and polls GLFW events
	*/
	void spinOnce();

	/**
	*	\brief Updates the size of the window if resized
	*	\param[in] width The new width
	*	\param[in] height The new height
	*/
	void updateSize(const uint32_t& width, const uint32_t& height);

	/**
	*	\brief Checks if the window is open
	*	\return Wether the window is open or not
	*/
	bool isOpen();

	/**
	*	\brief Resets the viewport to the original window size
	*/
	void resetViewport();

	/**
	*	\brief Register a key press callback
	*	\param[in] key The key to register the callback on
	*	\param[in] callback The callback to register
	*/
	void registerKeyCallback(const uint32_t& key, KeyPressFunction* callback);

	/**
	*	\brief Register a button callback
	*	\param[in] The button to register
	*	\param[in] The function of the button to implement
	*/
	void registerButtonCallback(Button* button, KeyPressFunction* callback);

	/**
	*	\brief Get the underlying GLFW window
	*	\return The GLFWwindow*
	*/
	inline GLFWwindow* getWindow(){ return _window; }

	/**
	*	\brief Get the width
	*	\return The width of the window
	*/
	inline uint32_t getWidth() const { return _width; }

	/**
	*	\brief Get the height
	*	\return The height of the window
	*/
	inline uint32_t getHeight() const { return _height; }

	/**
	*	\brief Get the aspect ratio
	*	\return The aspect ratio of the window
	*/
	inline float getAspectRatio() const { return _aspect_ratio; }

	/**
	*	\brief Get the delta time between two frames
	*	\return The delta time between two frames
	*/
	inline double DELTA_TIME() const { return _deltaTime; }

	/**
	*	\brief Get the default Text Renderer
	*	\return The Text Renderer
	*/
	inline std::shared_ptr<TextRenderer> getTextRenderer() { return _textRenderer; }

	/**
	*	\brief Set the mode of the viewer
	*	\param[in] mode The new mode
	*/
	inline void setMode(const ViewerMode& mode) { _mode = mode; }

	/**
	*	\brief Get the mode of the viewer
	*	\return The current mode
	*/
	inline ViewerMode getMode() { return _mode; }
private:
	GLFWwindow* _window = nullptr;															/**<< The underlying GLFWwindow*/
	uint32_t _width = 0;																	/**<< The width*/
	uint32_t _height = 0;																	/**<< The height*/
	float _aspect_ratio = 1.0f;																/**<< The apsect ratio*/
	bool _isOpen = false;																	/**<< Wether the window is open*/
	double _deltaTime = 0;																	/**<< The delta time between two frames*/
	double _lastTime = 0;																	/**<< The time stamp of the last frame*/
	Camera* _camera = nullptr;																/**<< The camera */
	std::unordered_multimap<uint32_t, KeyPressFunction*> _key_callbacks = {};				/**<< The key callbacks*/
	std::unordered_multimap<Button*, KeyPressFunction*, ButtonHash> _button_callbacks = {};	/**<< The button callbacks*/
	std::unordered_multimap<uint32_t, bool> _active_keys = {};								/**<< List of active keys*/
	ViewerMode _mode = ViewerMode::VIEWER;													/**<< The mode of the viewer*/
	std::shared_ptr<TextRenderer> _textRenderer = {};										/**<< The default text renderer*/
};


#endif