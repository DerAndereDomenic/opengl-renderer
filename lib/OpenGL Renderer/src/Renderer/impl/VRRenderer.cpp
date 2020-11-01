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

    result._vr_pointer->GetRecommendedRenderTargetSize(&result._width, &result._height);

    result._leftEyeTexture = Texture::createObject(result._width, result._height, (void*)nullptr);
    result._rightEyeTexture = Texture::createObject(result._width, result._height, (void*)nullptr);

    LOGGER::INFO("Initialized VR with recommended Render target size: " + std::to_string(result._width) + ", " + std::to_string(result._height) + "\n");

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
    object._width = 0;
    object._height = 0;

    Texture::destroyObject(object._leftEyeTexture);
    Texture::destroyObject(object._rightEyeTexture);
}

void 
VRRenderer::handleEvents(const vr::VREvent_t& event)
{
    switch(event.eventType)
    {
        //default:
            //LOGGER::DEBUG("Event (OpenVR) Event: " + std::to_string(event.eventType) + "\n");
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