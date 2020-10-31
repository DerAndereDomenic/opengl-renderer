#include <Core/GLFunctions.h>


void 
GL::clear(const GLclampf& r = 0, const GLclampf& g = 0, const GLclampf& b = 0, const GLclampf& a = 1)
{
    glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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