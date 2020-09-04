#include <Renderer/ParticleRenderer.h>

Particle::Particle(glm::vec3 position)
	:position(position)
{

}

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