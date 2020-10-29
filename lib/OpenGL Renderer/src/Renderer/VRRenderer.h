#ifndef __OPENGLRENDERER_RENDERER_VRRENDERER_H
#define __OPENGLRENDERER_RENDERER_VRRENDERER_H

#include <openvr.h>

class VRRenderer
{
    public:
        VRRenderer() = default;

        static VRRenderer createObject();

        static void destroyObject(VRRenderer& object);

        void spinOnce();
    private:
        void handleEvents(const vr::VREvent_t& event);

        vr::IVRSystem* _vr_pointer = NULL;
};

#endif