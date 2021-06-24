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
        *   \return The completed GBuffer 
        */
        static GBuffer createObject(const uint32_t& width, const uint32_t& height);

        /**
        *   \brief Destroy the GBuffer
        *   \param[in] object The object to be destroyed 
        */
        static void destroyObject(GBuffer& object);

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
        inline Texture getPositionBuffer() {return _positionTexture;}

        /**
        *   \brief Get the underlying normal buffer
        *   \return The normal buffer 
        */
        inline Texture getNormalBuffer() {return _normalTexture;}

        /**
        *   \brief Get the underlying color buffer
        *   \return The color buffer 
        */
        inline Texture getAlbedoSpecularBuffer() {return _albedoSpecTexture;}
    private:
        std::shared_ptr<FrameBuffer> _fbo;          /**<< The Framebuffer */
        Texture _positionTexture;                   /**<< The position buffer */
        Texture _normalTexture;                     /**<< The normal buffer */
        Texture _albedoSpecTexture;                 /**<< The color buffer */
};

#endif