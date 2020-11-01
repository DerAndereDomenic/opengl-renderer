#ifndef __OPENGLRENDERER_RENDERER_VRRENDERER_H
#define __OPENGLRENDERER_RENDERER_VRRENDERER_H

#include <openvr.h>
#include <OpenGLObjects/FrameBuffer.h>
#include <glm/glm.hpp>

class VRRenderer
{
    public:
        /**
         *  \brief Default constructor 
         */
        VRRenderer() = default;

        /**
         *  \brief Creates the VR invironment and returns the renderer
         *  \return The VR renderer
         */
        static VRRenderer createObject();

        /**
         *  \brief Destroys the renderer and closes the VR context
         *  \param[in] object The object to be destroyed
         */ 
        static void destroyObject(VRRenderer& object);

        /**
        *   \brief Uploads the internal framebuffer to the VR headset
        */
        void uploadToHMD();

        /**
         *  \brief Handles vr events 
         */
        void spinOnce();

        /**
        *   \brief Get the view matrix
        *   \return The view matrix of the HMD
        */
        glm::mat4 view();

        /**
        *   \brief Get the left eye projection matrix
        *   \return The left eye projection matrix
        */
        inline glm::mat4 leftProjection() { return _leftProjection; }

        /**
        *   \brief Get the right eye projection matrix
        *   \return The right eye projection matrix
        */
        inline glm::mat4 rightProjection() { return _rightProjection; }

        /**
        *   \brief Get the FrameBuffer for the left eye
        *   \return The FrameBuffer (Render target)
        */
        inline FrameBuffer getRenderTargetLeft() { return _renderTargetLeft; }

        /**
        *   \brief Get the FrameBuffer for the right eye
        *   \return The FrameBuffer (Render target)
        */
        inline FrameBuffer getRenderTargetRight() { return _renderTargetRight; }

        /**
        *   \brief Get the width
        *   \return The width
        */
        inline uint32_t getWidth() const { return _width; }

        /**
        *   \brief Get the height
        *   \return The height
        */
        inline uint32_t getHeight() const { return _height; }
    private:
        /**
         *  \brief Handles the event given by the vr context
         *  \param[in] event The event to handle
         */
        void handleEvents(const vr::VREvent_t& event);

        /**
        *   \brief Get the projection matrix of the specified eye
        *   \param[in] eye The eye
        *   \return The projection matrix
        */
        glm::mat4 projection(const vr::EVREye& eye);

        vr::IVRSystem* _vr_pointer = NULL;      /**<< The VR context */
        glm::mat4 _leftProjection;              /**<< The projection matrix of the left eye */
        glm::mat4 _rightProjection;             /**<< The projection matrix of the right eye */

        uint32_t _width = 0;                    /**<< Recommended Render target width */
        uint32_t _height = 0;                   /**<< Recommended Render target height */
        FrameBuffer _renderTargetLeft = {};     /**<< The render target for the left eye */
        FrameBuffer _renderTargetRight = {};    /**<< The render target for the right eye */
};

#endif