#include <OpenGLObjects/GBuffer.h>

GBuffer 
GBuffer::createObject(const uint32_t& width, const uint32_t& height)
{
    GBuffer result;

    result._positionTexture = Texture::createObject(width, height, (float*)NULL, TEXTURE, GL_RGBA16F, GL_RGBA, GL_FLOAT);
    result._normalTexture = Texture::createObject(width, height, (float*)NULL, TEXTURE, GL_RGBA16F, GL_RGBA, GL_FLOAT);
    result._albedoSpecTexture = Texture::createObject(width, height, (uint8_t*)NULL, TEXTURE, GL_RGBA, GL_RGBA, GL_UNSIGNED_BYTE);

    result._fbo = FrameBuffer::createObject(width, height);
    result._fbo.attachColor(result._positionTexture);
    result._fbo.attachColor(result._normalTexture);
    result._fbo.attachColor(result._albedoSpecTexture);
    result._fbo.attachRenderBuffer();
    result._fbo.verify();

    return result;
}

void 
GBuffer::destroyObject(GBuffer& object)
{

}

void 
GBuffer::bind()
{

}

void 
GBuffer::bindTextures()
{

}
