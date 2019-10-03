#ifndef OPENGL_OBJECTS_FRAMEBUFFER_H
#define OPENGL_OBJECTS_FRAMEBUFFER_H

#include <OpenGLObjects/RenderBuffer.h>
#include <OpenGLObjects/Texture.h>

/**
*	\brief A class to model a frame buffer object
*/
class FrameBuffer
{
public:
	/**
	*	\brief Create an empty frame buffer object
	*/
	FrameBuffer() = default;

	/**
	*	\brief Create a frame buffer object
	*	\param[in] width The width of the buffer
	*	\param[in] height The height of the buffer
	*	\return The render buffer object
	*/
	static FrameBuffer createObject(unsigned int width, unsigned int height);

	/**
	*	\brief Destroy the render buffer object
	*	\param[in] object The object to be destroyed
	*/
	static void destroyObject(FrameBuffer& object);

	/**
	*	\brief Binds the render buffer object
	*/
	void bind();

	/**
	*	\brief Unbinds the render buffer object (bind = 0)
	*/
	void unbind();
private:
	unsigned int _ID; /**<< The internal OpenGL handle for the fbo*/
	Texture _render_texture; /**<< The Color texture of this fbo*/
	RenderBuffer _depth_stencil; /**<< The depth and stencil buffer of this fbo*/
};

#endif