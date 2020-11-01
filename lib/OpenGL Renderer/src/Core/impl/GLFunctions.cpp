#include <Core/GLFunctions.h>
#include <DLogger/Logger.h>

namespace detail
{
    void GLAPIENTRY
    MessageCallback(GLenum source,
                    GLenum type,
                    GLuint id,
                    GLenum severity,
                    GLsizei length,
                    const GLchar* message,
                    const void* userParam)
    {
        switch(severity)
        {
            case GL_DEBUG_SEVERITY_LOW:
            case GL_DEBUG_SEVERITY_MEDIUM:
            {
                if (id == 131218) return; //Some NVIDIA stuff going wrong -> disable this warning
                LOGGER::WARNING(std::string(message) + "\n");
            }
            break;
            case GL_DEBUG_SEVERITY_HIGH:
            {
                LOGGER::ERROR(std::string(message) + "\n");
            }
            break;
            default: break;
        }
    }
}

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