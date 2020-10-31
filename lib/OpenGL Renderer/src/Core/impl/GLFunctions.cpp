#include <Core/GLFunctions.h>

void 
GL::enableDebugOutput()
{
    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(detail::MessageCallback, 0);
}

void 
GL::clear(const GLclampf& r, const GLclampf& g, const GLclampf& b, const GLclampf& a)
{
    glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void 
GL::setViewport(const uint32_t& x, const uint32_t& y, const uint32_t& width, const uint32_t& height)
{
    glViewport(x, y, width, height);
}

void 
GL::setViewport(const uint32_t& width, const uint32_t& height)
{
    glViewport(0, 0, width, height);
}

void 
GL::enableDepthWriting()
{
    glDepthMask(GL_TRUE);
}

void 
GL::disableDepthWriting()
{
    glDepthMask(GL_FALSE);
}