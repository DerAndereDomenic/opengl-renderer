#ifndef OPENGL_OBJECTS_FRAMEBUFFER_H
#define OPENGL_OBJECTS_FRAMEBUFFER_H

#include <OpenGLObjects/RenderBuffer.h>
#include <OpenGLObjects/Texture.h>
#include <vector>

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
	static FrameBuffer createObject(uint32_t width, uint32_t height);

	/**
	*	\brief Destroy the render buffer object
	*	\param[in] object The object to be destroyed
	*/
	static void destroyObject(FrameBuffer& object);

	/**
	*	\brief Attaches a color texture to the Framebuffer
	*/
	void attachColor();

	/**
	*	\brief Attaches a color texture to the Framebuffer
	*	\param[in] color_buffer The texture that should be added
	*/
	void attachColor(Texture color_buffer);

	/**
	*	\brief Attaches a hdr texture (floating point texture) to the Framebuffer
	*/
	void attachHDR();

	/**
	*	\brief Attach a depth map to the Framebuffer
	*/
	void attachDepthMap();

	/**
	*	\brief Disable color attachement
	*/
	void disableColor();

	/**
	*	\brief Attaches a Depth/Stencil Renderbuffer to the Framebuffer
	*/
	void attachRenderBuffer();

	/**
	*	\brief Verify if the Framebuffer is complete
	*	\return true if all necessary attachments are given
	*/
	bool verify();

	/**
	*	\brief Binds the render buffer object
	*/
	void bind() const;

	/**
	*	\brief Unbinds the render buffer object (bind = 0)
	*/
	void unbind() const;

	/**
	*	\brief Unbind the buffer (bind default)
	*	\note: Does the same as unbind but isn't tied to an object
	*/
	static void bindDefault();

	/**
	*	\brief Clears the window
	*	\param[in] r = 0.0f The red channel
	*	\param[in] g = 0.0f The green channel
	*	\param[in] b = 0.0f The blue channel
	*	\param[in] a = 1.0f The alpha channel
	*/
	void clear(GLclampf r = 0, GLclampf g = 0, GLclampf b = 0, GLclampf a = 1);

	/**
	*	\brief The color attachment of the fbo
	*	\param[in] index The index of the color attachment
	*	\return The Texture for the Color attachment
	*/
	inline Texture getTexture(const uint32_t index = 0) { return _render_textures[index]; }
private:
	uint32_t _ID; /**<< The internal OpenGL handle for the fbo*/
	std::vector<Texture> _render_textures; /**<< The Color textures of this fbo*/
	RenderBuffer _depth_stencil; /**<< The depth and stencil buffer of this fbo*/

	uint32_t _width; /**<< The width of the Framebuffer*/
	uint32_t _height; /**<< The height of the Framebuffer*/
};

#endif