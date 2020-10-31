#ifndef __OPENGLRENDERER_CORE_GLFUNCTIONS_H
#define __OPENGLRENDERER_CORE_GLFUNCTIONS_H

#include <glew.h>
#include <cstdint>

namespace GL
{
    /**
	*	\brief Clears the window
	*	\param[in] r = 0.0f The red channel
	*	\param[in] g = 0.0f The green channel
	*	\param[in] b = 0.0f The blue channel
	*	\param[in] a = 1.0f The alpha channel
	*/
	void clear(const GLclampf& r = 0, const GLclampf& g = 0, const GLclampf& b = 0, const GLclampf& a = 1);

    /**
	*	\brief Sets the viewport
    *   \param[in] x The x location
    *   \param[in] y The y location
	*	\param[in] width The width of the viewport
	*	\param[in] height The height of the viewport
	*/
	void setViewport(const uint32_t& x, const uint32_t& y, const uint32_t& width, const uint32_t& height);

    /**
	*	\brief Sets the viewport (location = (0,0))
	*	\param[in] width The width of the viewport
	*	\param[in] height The height of the viewport
	*/
	void setViewport(const uint32_t& width, const uint32_t& height);

	/**
	*	\brief Enables depth testing
	*/
	void enableDepthWriting();

	/**
	*	\brief Disables depth testing
	*/
	void disableDepthWriting();
}

#endif