#ifndef RENDERER_PARTICLERENDERER_H
#define RENDERER_PARTICLERENDERER_H

#include <vector>
#include <OpenGLObjects/Texture.h>
#include <glm/glm.hpp>
#include <OpenGLObjects/VertexArray.h>

struct Particle
{
	glm::vec3 position;
	glm::vec3 velocity;

	float timeAlive = 0.0f;

	Particle(glm::vec3 position);
};

class ParticleRenderer
{
	public:
		ParticleRenderer() = default;

		static ParticleRenderer createObject(glm::vec3 position, const unsigned int num_particles, Texture texture);

		static void destroyObject(ParticleRenderer& object);

		void update(float deltaTime);

		void render();
	private:
		Texture _texture;
		std::vector<Particle> _particles;
		VertexArray _vao;
		VertexBuffer _instanceArray;
		float* _positions;
};

#endif