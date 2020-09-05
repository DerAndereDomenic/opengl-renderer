#include <Renderer/ParticleRenderer.h>
#include <ctime>
#include <Shader/ShaderManager.h>

Particle::Particle(glm::vec3 position, float time_alive)
	:position(position)
{
	float angle = static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX)*3.14159f*2.0f;
	float r = sqrtf(static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX));
	float x = r * cos(angle);
	float z = r * sin(angle);

	float y = sqrtf(fmax(0.0f, 1 - x * x - z * z));

	velocity = static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX) * glm::vec3(x, y, z);
	timeAlive = static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX);
}

ParticleRenderer 
ParticleRenderer::createObject(glm::vec3 position, const unsigned int num_particles, float time_alive, Texture texture)
{
	ParticleRenderer result;

	result._texture = texture;
	result._position = position;
	result._timeAlive = time_alive;

	result._attributes = new float[3 * num_particles];
	std::srand(std::time(nullptr));
	for (unsigned int i = 0; i < num_particles; ++i)
	{
		result._particles.push_back(Particle(position, time_alive));
		result._attributes[3 * i] = position.x;
		result._attributes[3 * i + 1] = position.y;
		result._attributes[3 * i + 2] = position.z;
	}

	result._instanceArray = VertexBuffer::createObject(result._attributes, num_particles * 3, GL_DYNAMIC_DRAW);
	VertexBufferLayout layout;
	layout.add<float>(3);
	result._vao = VertexArray::createObject();
	result._vao.addInstanceBuffer(result._instanceArray, layout);

	ShaderManager::instance()->addShader("Particle", true);

	return result;
}

void 
ParticleRenderer::destroyObject(ParticleRenderer& object)
{
	Texture::destroyObject(object._texture);
	object._particles.clear();
	VertexArray::destroyObject(object._vao);
	VertexBuffer::destroyObject(object._instanceArray);
	delete[] object._attributes;
}

void 
ParticleRenderer::update(float deltaTime)
{
	for (unsigned int i = 0; i < _particles.size(); ++i)
	{
		_particles[i].timeAlive -= deltaTime;
		_particles[i].position += deltaTime * _particles[i].velocity;
		if (_particles[i].timeAlive <= 0)
		{
			_particles[i] = Particle(_position, _timeAlive);
		}
		_attributes[3 * i] = _particles[i].position.x;
		_attributes[3 * i + 1] = _particles[i].position.y;
		_attributes[3 * i + 2] = _particles[i].position.z;
	}

	_instanceArray.changeData(_attributes, 3 * _particles.size());
}

void 
ParticleRenderer::render(Camera& camera)
{
	glDepthMask(GL_FALSE);
	ShaderManager::instance()->getShader("Particle").bind();
	ShaderManager::instance()->getShader("Particle").setMVP(glm::mat4(1), camera.getView(), camera.getProjection());
	_texture.bind();
	_vao.bind();
	glDrawArraysInstanced(GL_POINTS, 0, 1, _particles.size());
	glDepthMask(GL_TRUE);
}