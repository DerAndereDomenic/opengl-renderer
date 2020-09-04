#include <Renderer/ParticleRenderer.h>
#include <ctime>

Particle::Particle(glm::vec3 position)
	:position(position)
{
	float angle = static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX)*3.14159f*2.0f;
	float r = sqrtf(static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX));
	float x = r * cos(angle);
	float y = r * sin(angle);

	float z = sqrtf(fmax(0.0f, 1 - x * x - y * y));

	velocity = static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX) * glm::vec3(x, y, z);
}

ParticleRenderer 
ParticleRenderer::createObject(glm::vec3 position, const unsigned int num_particles, Texture texture)
{
	ParticleRenderer result;

	result._texture = texture;

	std::srand(std::time(nullptr));
	for (unsigned int i = 0; i < num_particles; ++i)
	{
		result._particles.push_back(Particle(position));
	}

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