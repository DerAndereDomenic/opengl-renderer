#include <Renderer/VRRenderer.h>
#include <DLogger/Logger.h>
#include <string>

VRRenderer 
VRRenderer::createObject()
{
    VRRenderer result;

    vr::EVRInitError error = vr::VRInitError_None;
    result._vr_pointer = vr::VR_Init(&error, vr::VRApplication_Scene);
    if(error != vr::VRInitError_None)
    {
        result._vr_pointer = NULL;
        LOGGER::ERROR("Unable to init VR runtime: " + std::string(vr::VR_GetVRInitErrorAsEnglishDescription(error)) + "\n");
        exit(EXIT_FAILURE);
    }

    return result;
}

void 
VRRenderer::destroyObject(VRRenderer& object)
{
    if(object._vr_pointer != NULL)
    {
        vr::VR_Shutdown();
        object._vr_pointer = NULL;
    }
}

void 
VRRenderer::spinOnce()
{
    vr::VREvent_t event;
    if(_vr_pointer->PollNextEvent(&event, sizeof(event)))
    {
        handleEvents(event);
    }
}