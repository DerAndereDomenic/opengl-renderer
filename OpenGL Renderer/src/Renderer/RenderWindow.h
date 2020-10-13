#ifndef RENDERER_RENDER_WINDOW_H
#define RENDERER_RENDER_WINDOW_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>

#include <OpenGLObjects/VertexArray.h>
#include <Shader/Shader.h>

#include <cstdint>

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
	*	\return The given window
	*/
	static RenderWindow createObject(const uint32_t& width, const uint32_t& height, const std::string& title);

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
	*	\brief Clears the window
	*	\param[in] r = 0.0f The red channel
	*	\param[in] g = 0.0f The green channel
	*	\param[in] b = 0.0f The blue channel
	*	\param[in] a = 1.0f The alpha channel
	*/
	void clear(const GLclampf& r = 0, const GLclampf& g = 0, const GLclampf& b = 0, const GLclampf& a = 1);

	/**
	*	\brief Swap buffers and polls GLFW events
	*/
	void spinOnce();

	/**
	*	\brief Checks if the window is open
	*	\return Wether the window is open or not
	*/
	bool isOpen();

	/**
	*	\brief Sets the viewport (location = (0,0))
	*	\param[in] width The width of the viewport
	*	\param[in] height The height of the viewport
	*/
	void setViewport(const uint32_t& width, const uint32_t& height);

	/**
	*	\brief Resets the viewport to the original window size
	*/
	void resetViewport();

	/**
	*	\brief Enables depth testing
	*/
	void enableDepthWriting();

	/**
	*	\brief Disables depth testing
	*/
	void disableDepthWriting();

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
	GLFWwindow* _window;			/**<< The underlying GLFWwindow*/
	uint32_t _width = 0.0f;		/**<< The width*/
	uint32_t _height = 0.0f;	/**<< The height*/
	float _aspect_ratio = 1.0f;		/**<< The apsect ratio*/
	bool _isOpen = false;			/**<< Wether the window is open*/
	double _deltaTime = 0;			/**<< The delta time between two frames*/
	double _lastTime = 0;			/**<< The time stamp of the last frame*/
};


#endif