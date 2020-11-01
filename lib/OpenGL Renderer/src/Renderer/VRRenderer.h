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

        void render();

        /**
         *  \brief Handles vr events 
         */
        void spinOnce();
    private:
        /**
         *  \brief Handles the event given by the vr context
         *  \param[in] event The event to handle
         */
        void handleEvents(const vr::VREvent_t& event);

        vr::IVRSystem* _vr_pointer = NULL;      /**<< The VR context */
        uint32_t _width = 0;                    /**<< Recommended Render target width */
        uint32_t _height = 0;                   /**<< Recommended Render target height */
        FrameBuffer _leftEyeTarget = {};           /**<< The texture for the left eye */
        FrameBuffer _rightEyeTarget = {};          /**<< The texture for the right eye */
};

#endif