#ifndef __OPENGLRENDERER_RENDERER_VRRENDERER_H
#define __OPENGLRENDERER_RENDERER_VRRENDERER_H

#include <openvr.h>
#include <OpenGLObjects/FrameBuffer.h>

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

        void trackDevicePose();

        /**
        *   \brief Get the FrameBuffer used by this renderer
        *   \return The FrameBuffer (Render target)
        */
        inline FrameBuffer getRenderTarget() { return _renderTarget; }
    private:
        /**
         *  \brief Handles the event given by the vr context
         *  \param[in] event The event to handle
         */
        void handleEvents(const vr::VREvent_t& event);

        vr::IVRSystem* _vr_pointer = NULL;      /**<< The VR context */
        uint32_t _width = 0;                    /**<< Recommended Render target width */
        uint32_t _height = 0;                   /**<< Recommended Render target height */
        FrameBuffer _renderTarget = {};         /**<< The render target containing the textures */
};

#endif