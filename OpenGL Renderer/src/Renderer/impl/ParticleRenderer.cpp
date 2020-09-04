#include <Renderer/ParticleRenderer.h>

ParticleRenderer 
ParticleRenderer::createObject(const unsigned int num_particles, Texture texture)
{
	ParticleRenderer result;

	result._texture = texture;

	return result;
}

void 
destroyObject(ParticleRenderer& object)
{

}

void 
ParticleRenderer::update()
{

}

void 
ParticleRenderer::render()
{

}