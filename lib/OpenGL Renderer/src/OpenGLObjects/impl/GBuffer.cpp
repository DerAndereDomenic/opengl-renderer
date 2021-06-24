#include <OpenGLObjects/GBuffer.h>

GBuffer::GBuffer(const uint32_t& width, const uint32_t& height)
{
    _positionTexture = Texture::createObject(width, height, (float*)NULL, TEXTURE, GL_RGBA16F, GL_RGBA, GL_FLOAT);
    _normalTexture = Texture::createObject(width, height, (float*)NULL, TEXTURE, GL_RGBA16F, GL_RGBA, GL_FLOAT);
    _albedoSpecTexture = Texture::createObject(width, height, (uint8_t*)NULL, TEXTURE, GL_RGBA, GL_RGBA, GL_UNSIGNED_BYTE);

    _fbo = std::make_shared<FrameBuffer>(width, height);
    _fbo->attachColor(_positionTexture);
    _fbo->attachColor(_normalTexture);
    _fbo->attachColor(_albedoSpecTexture);
    _fbo->attachRenderBuffer();
    _fbo->verify();
}

void 
GBuffer::bind()
{
    _fbo->bind();
}

void 
GBuffer::bindTextures()
{
    _positionTexture.bind(0);
    _normalTexture.bind(1);
    _albedoSpecTexture.bind(2);
}
