#ifndef RENDERER_RENDER_WINDOW_H
#define RENDERER_RENDER_WINDOW_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>

#include <OpenGLObjects/VertexArray.h>
#include <Shader/Shader.h>

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
	static RenderWindow createObject(const unsigned int width, const unsigned int height, std::string title);

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
	*	\brief Renders the given vertex array object
	*	\param[in] vao The vertex buffer object
	*	\param[in] ibo The index buffer object
	*	\param[in] shader The shader used for this drawcall
	*/
	void render(VertexArray& vao, IndexBuffer& ibo, Shader& shader);

	/**
	*	\brief Clears the window
	*	\param[in] r = 0.0f The red channel
	*	\param[in] g = 0.0f The green channel
	*	\param[in] b = 0.0f The blue channel
	*	\param[in] a = 1.0f The alpha channel
	*/
	void clear(GLclampf r = 0.0f, GLclampf g = 0.0f, GLclampf b = 0.0f, GLclampf a = 1.0f);

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
	void setViewport(const unsigned int width, const unsigned int height);

	/**
	*	\brief Resets the viewport to the original window size
	*/
	void resetViewport();

	/**
	*	\brief Get the underlying GLFW window
	*	\return The GLFWwindow*
	*/
	inline GLFWwindow* getWindow(){ return _window; }

	/**
	*	\brief Get the width
	*	\return The width of the window
	*/
	inline unsigned int getWidth() const { return _width; }

	/**
	*	\brief Get the height
	*	\return The height of the window
	*/
	inline unsigned int getHeight() const { return _height; }

	/**
	*	\brief Get the aspect ratio
	*	\return The aspect ratio of the window
	*/
	inline float getAspectRatio() const { return _aspect_ratio; }
private:
	GLFWwindow* _window; /**<< The underlying GLFWwindow*/
	unsigned int _width; /**<< The width*/
	unsigned int _height; /**<< The height*/
	float _aspect_ratio; /**<< The apsect ratio*/
	bool _isOpen; /**<< Wether the window is open*/
};


#endif