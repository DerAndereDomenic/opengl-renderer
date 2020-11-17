#ifndef __OPENGLRENDERER_RENDERER_RENDER_WINDOW_H
#define __OPENGLRENDERER_RENDERER_RENDER_WINDOW_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>

#include <unordered_map>

#include <OpenGLObjects/VertexArray.h>
#include <Shader/Shader.h>
#include <GUI/KeyPressFunction.h>

#include <cstdint>

#include <Renderer/Camera.h>

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
	*	\return The given window
	*/
	static RenderWindow createObject(const uint32_t& width, const uint32_t& height, const std::string& title, Camera* camera = nullptr);

	/**
	*	\brief Destroys the given window
	*	\param[in] The window to be destroyed
	*/
	static void destroyObject(RenderWindow& window);

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
	*	\return If the window was resized
	*/
	bool updateSize();

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
	void registerCallback(const uint32_t& key, KeyPressFunction* callback);

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
private:
	GLFWwindow* _window = nullptr;												/**<< The underlying GLFWwindow*/
	uint32_t _width = 0;														/**<< The width*/
	uint32_t _height = 0;														/**<< The height*/
	float _aspect_ratio = 1.0f;													/**<< The apsect ratio*/
	bool _isOpen = false;														/**<< Wether the window is open*/
	double _deltaTime = 0;														/**<< The delta time between two frames*/
	double _lastTime = 0;														/**<< The time stamp of the last frame*/
	Camera* _camera = nullptr;													/**<< The camera */
	std::unordered_multimap<uint32_t, KeyPressFunction*> _callbacks = {};		/**< The key callbacks*/
};


#endif