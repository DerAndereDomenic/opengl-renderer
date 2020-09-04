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

	result._instanceArray = VertexBuffer::createObject(NULL, num_particles * 3, GL_DYNAMIC_DRAW);
	VertexBufferLayout layout;
	layout.add<float>(3);
	result._vao = VertexArray::createObject();
	result._vao.addInstanceBuffer(result._instanceArray, layout.getElements()[0]);

	std::srand(std::time(nullptr));
	for (unsigned int i = 0; i < num_particles; ++i)
	{
		result._particles.push_back(Particle(position));
	}

	return result;
}

void 
ParticleRenderer::destroyObject(ParticleRenderer& object)
{
	Texture::destroyObject(object._texture);
	object._particles.clear();
	VertexArray::destroyObject(object._vao);
	VertexBuffer::destroyObject(object._instanceArray);
}

void 
ParticleRenderer::update(float deltaTime)
{
	for (unsigned int i = 0; i < _particles.size(); ++i)
	{
		_particles[i].position += deltaTime * _particles[i].velocity;
		_particles[i].timeAlive += deltaTime;
	}
}

void 
ParticleRenderer::render()
{

}