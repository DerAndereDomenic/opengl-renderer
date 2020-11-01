#include <Core/GLFunctions.h>
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

    result._leftEyeTarget = FrameBuffer::createObject(result._width, result._height);
    result._leftEyeTarget.attachColor();
    result._leftEyeTarget.attachRenderBuffer();
    result._leftEyeTarget.verify();

    FrameBuffer::bindDefault();

    result._rightEyeTarget = FrameBuffer::createObject(result._width, result._height);
    result._rightEyeTarget.attachColor();
    result._rightEyeTarget.attachRenderBuffer();
    result._rightEyeTarget.verify();

    FrameBuffer::bindDefault();

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

    FrameBuffer::destroyObject(object._leftEyeTarget);
    FrameBuffer::destroyObject(object._rightEyeTarget);
}

void
VRRenderer::render()
{
    _leftEyeTarget.bind();
    GL::clear(1, 0, 0);

    _rightEyeTarget.bind();
    GL::clear(0, 1, 0);

    FrameBuffer::bindDefault();

    vr::TrackedDevicePose_t trackedDevicePose[vr::k_unMaxTrackedDeviceCount];
    vr::VRCompositor()->WaitGetPoses(trackedDevicePose, vr::k_unMaxTrackedDeviceCount, nullptr, 0);

    vr::Texture_t leftEyeTexture = { (void*)_leftEyeTarget.getTexture().getID(), vr::TextureType_OpenGL, vr::ColorSpace_Linear };
    vr::Texture_t rightEyeTexture = { (void*)_rightEyeTarget.getTexture().getID(), vr::TextureType_OpenGL, vr::ColorSpace_Linear };

    vr::VRCompositor()->Submit(vr::Eye_Left, &leftEyeTexture);
    vr::VRCompositor()->Submit(vr::Eye_Right, &rightEyeTexture);

    vr::VRCompositor()->PostPresentHandoff();
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