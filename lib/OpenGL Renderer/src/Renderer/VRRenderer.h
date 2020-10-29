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
        vr::IVRSystem* vr_pointer = NULL;
};

#endif