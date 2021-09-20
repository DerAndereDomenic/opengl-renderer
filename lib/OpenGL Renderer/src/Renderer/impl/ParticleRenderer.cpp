#include <Renderer/ParticleRenderer.h>
#include <ctime>
#include <Shader/ShaderManager.h>
#include <Core/GLFunctions.h>

Particle::Particle(const glm::vec3& position, const float& time_alive)
	:position(position)
{
	float angle = static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX)*3.14159f*2.0f;
	float r = powf(static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX), 0.5f);
	float x = r * cos(angle);
	float z = r * sin(angle);

	float y = sqrtf(fmax(0.0f, 1 - x * x - z * z));

	velocity = static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX) * glm::vec3(x, y, z);
	timeAlive = static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX)*time_alive;
}
 
ParticleRenderer::ParticleRenderer(const glm::vec3& position, const uint32_t& num_particles, const float& time_alive, const std::shared_ptr<Texture> texture)
{
	_texture = texture;
	_position = position;
	_timeAlive = time_alive;

	_attributes = new float[4 * num_particles];
	std::srand(std::time(nullptr));
	for (uint32_t i = 0; i < num_particles; ++i)
	{
		_particles.push_back(Particle(position, time_alive));
		_attributes[4 * i] = position.x;
		_attributes[4 * i + 1] = position.y;
		_attributes[4 * i + 2] = position.z;
		_attributes[4 * i + 3] = _particles[i].timeAlive;
	}

	_instanceArray = std::make_shared<VertexBuffer>(_attributes, num_particles * 4, GL_DYNAMIC_DRAW);
	VertexBufferLayout layout;
	layout.add(GL_FLOAT, 3);
	layout.add(GL_FLOAT, 1);
	_vao = std::make_shared<VertexArray>(GL_POINTS);
	_vao->addInstanceBuffer(_instanceArray, layout);

	ShaderManager::addShader("Particle", true);
}
 
ParticleRenderer::~ParticleRenderer()
{
	_particles.clear();
	delete[] _attributes;
}

void 
ParticleRenderer::update(const float& deltaTime)
{
	for (uint32_t i = 0; i < _particles.size(); ++i)
	{
		_particles[i].timeAlive -= deltaTime;
		_particles[i].position += deltaTime * _particles[i].velocity;
		if (_particles[i].timeAlive <= 0)
		{
			_particles[i] = Particle(_position, _timeAlive);
		}
		_attributes[4 * i] = _particles[i].position.x;
		_attributes[4 * i + 1] = _particles[i].position.y;
		_attributes[4 * i + 2] = _particles[i].position.z;
		_attributes[4 * i + 3] = _particles[i].timeAlive/_timeAlive;
	}

	_instanceArray->changeData(_attributes, 4 * _particles.size());
}

void 
ParticleRenderer::render(const Camera& camera)
{
	GL::disableDepthWriting();
	ShaderManager::getShader("Particle")->bind();
	ShaderManager::getShader("Particle")->setMVP(glm::mat4(1), camera.getView(), camera.getProjection());
	_texture->bind();
	_vao->renderInstanced(1, _particles.size());
	GL::enableDepthWriting();
}

void
ParticleRenderer::render(const glm::mat4& view, const glm::mat4& projection)
{
	GL::disableDepthWriting();
	ShaderManager::getShader("Particle")->bind();
	ShaderManager::getShader("Particle")->setMVP(glm::mat4(1), view, projection);
	_texture->bind();
	_vao->renderInstanced(1, _particles.size());
	GL::enableDepthWriting();
}