#include <Core/GLFunctions.h>
#include <Renderer/VRRenderer.h>
#include <DLogger/Logger.h>
#include <string>
#include <iostream>

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

    result._renderTargetLeft = FrameBuffer::createObject(result._width, result._height);
    result._renderTargetLeft.attachColor(Texture::createObject(result._width, result._height, (void*)NULL, TEXTURE, GL_RGBA8, GL_RGBA));
    result._renderTargetLeft.attachRenderBuffer();
    result._renderTargetLeft.verify();

    result._renderTargetRight = FrameBuffer::createObject(result._width, result._height);
    result._renderTargetRight.attachColor(Texture::createObject(result._width, result._height, (void*)NULL, TEXTURE, GL_RGBA8, GL_RGBA));
    result._renderTargetRight.attachRenderBuffer();
    result._renderTargetRight.verify();

    GL::setViewport(result._width, result._height);

    FrameBuffer::bindDefault();

    result._leftProjection = result.projection(vr::Eye_Left);
    result._rightProjection = result.projection(vr::Eye_Right);

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

    FrameBuffer::destroyObject(object._renderTargetLeft);
    FrameBuffer::destroyObject(object._renderTargetRight);
}

void
VRRenderer::uploadToHMD()
{
    vr::TrackedDevicePose_t trackedDevicePose[vr::k_unMaxTrackedDeviceCount];
    vr::VRCompositor()->WaitGetPoses(trackedDevicePose, vr::k_unMaxTrackedDeviceCount, nullptr, 0);

    vr::Texture_t leftEyeTexture = { (void*)_renderTargetLeft.getTexture().getID(), vr::TextureType_OpenGL, vr::ColorSpace_Linear };
    vr::Texture_t rightEyeTexture = { (void*)_renderTargetRight.getTexture().getID(), vr::TextureType_OpenGL, vr::ColorSpace_Linear };

    vr::VRCompositor()->Submit(vr::Eye_Left, &leftEyeTexture);
    vr::VRCompositor()->Submit(vr::Eye_Right, &rightEyeTexture);

    vr::VRCompositor()->PostPresentHandoff();
}

glm::mat4 
VRRenderer::view(const Eye& eye)
{
    vr::TrackedDevicePose_t trackedDevicePose;
    _vr_pointer->GetDeviceToAbsoluteTrackingPose(vr::TrackingUniverseStanding, 0, &trackedDevicePose, 1);
    vr::HmdMatrix34_t e = _vr_pointer->GetEyeToHeadTransform((vr::EVREye)eye);
    glm::mat4 result = glm::mat4(1);
    glm::mat4 eye2head = glm::mat4(1);
    if (trackedDevicePose.bPoseIsValid)
    {
        for (int i = 0; i < 3; ++i)
        {
            for (int j = 0; j < 4; ++j)
            {
                result[j][i] = trackedDevicePose.mDeviceToAbsoluteTracking.m[i][j];
                eye2head[j][i] = e.m[i][j];
            }
        }
    }
    return glm::inverse(eye2head)*glm::inverse(result);
}

glm::mat4 
VRRenderer::leftView()
{
    return view(Eye::LEFT);
}

glm::mat4 
VRRenderer::rightView()
{
    return view(Eye::RIGHT);
}

glm::vec3 
VRRenderer::position()
{
    //glm::mat4 V = view(eye);
    //return -V[3];
    vr::TrackedDevicePose_t trackedDevicePose;
    _vr_pointer->GetDeviceToAbsoluteTrackingPose(vr::TrackingUniverseStanding, 0, &trackedDevicePose, 1);
    return glm::vec3(trackedDevicePose.mDeviceToAbsoluteTracking.m[0][3], trackedDevicePose.mDeviceToAbsoluteTracking.m[1][3], trackedDevicePose.mDeviceToAbsoluteTracking.m[2][3]);
}

glm::mat4
VRRenderer::projection(const vr::EVREye& eye)
{
    vr::HmdMatrix44_t projection = _vr_pointer->GetProjectionMatrix(eye, 0.1f, 10.0f);
    glm::mat4 result = glm::mat4(1);
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            result[i][j] = projection.m[j][i];
        }
    }

    return result;
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