#ifndef RENDERER_PARTICLERENDERER_H
#define RENDERER_PARTICLERENDERER_H

#include <vector>
#include <OpenGLObjects/Texture.h>
#include <glm/glm.hpp>
#include <OpenGLObjects/VertexArray.h>
#include <Renderer/Camera.h>

struct Particle
{
	glm::vec3 position;
	glm::vec3 velocity;

	float timeAlive = 0.0f;

	Particle(glm::vec3 position, float time_alive);
};

class ParticleRenderer
{
	public:
		ParticleRenderer() = default;

		static ParticleRenderer createObject(glm::vec3 position, const unsigned int num_particles, float time_alive, Texture texture);

		static void destroyObject(ParticleRenderer& object);

		void update(float deltaTime);

		void render(Camera& camera);
	private:
		Texture _texture;
		std::vector<Particle> _particles;
		VertexArray _vao;
		VertexBuffer _instanceArray;
		glm::vec3 _position;
		float _timeAlive;
		float* _positions;
};

#endif