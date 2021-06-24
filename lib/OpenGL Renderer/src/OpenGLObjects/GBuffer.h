#ifndef __OPENGLRENDERER_OPENGL_OBJECTS_GBUFFER_H
#define __OPENGLRENDERER_OPENGL_OBJECTS_GBUFFER_H

#include <OpenGLObjects/FrameBuffer.h>
#include <memory>

/**
*   \brief A class to model a GBuffer 
*/
class GBuffer
{
    public:
        /**
        *   \brief Default constructor 
        */
        GBuffer() = default;

        /**
        *   \brief Creates a GBuffer object
        *   \param[in] width The width
        *   \param[in] height The height
        */
        GBuffer(const uint32_t& width, const uint32_t& height);

        /**
        *   \brief Bind the underlying Framebuffer 
        */
        void bind();

        /**
        *   \brief Binds the internal textures
        *   \note Positions are binded to 0
        *         Normals are binded to 1
        *         Colors are binded to 2 
        */
        void bindTextures();

        /**
        *   \brief Get the underlying fbo
        *   \return The fbo 
        */
        inline std::shared_ptr<FrameBuffer> getFBO() {return _fbo;}

        /**
        *   \brief Get the underlying position buffer
        *   \return The position buffer 
        */
        inline  std::shared_ptr<Texture> getPositionBuffer() {return _positionTexture;}

        /**
        *   \brief Get the underlying normal buffer
        *   \return The normal buffer 
        */
        inline  std::shared_ptr<Texture> getNormalBuffer() {return _normalTexture;}

        /**
        *   \brief Get the underlying color buffer
        *   \return The color buffer 
        */
        inline  std::shared_ptr<Texture> getAlbedoSpecularBuffer() {return _albedoSpecTexture;}
    private:
        std::shared_ptr<FrameBuffer> _fbo;                          /**<< The Framebuffer */
        std::shared_ptr<Texture> _positionTexture;                   /**<< The position buffer */
        std::shared_ptr<Texture> _normalTexture;                     /**<< The normal buffer */
        std::shared_ptr<Texture> _albedoSpecTexture;                 /**<< The color buffer */
};

#endif