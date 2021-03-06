#ifndef __OPENGLRENDERER_RENDERER_PARTICLERENDERER_H
#define __OPENGLRENDERER_RENDERER_PARTICLERENDERER_H

#include <vector>
#include <OpenGLObjects/Texture.h>
#include <glm/glm.hpp>
#include <OpenGLObjects/VertexArray.h>
#include <Renderer/Camera.h>
#include <memory>

struct Particle
{
	glm::vec3 position;									/**<< The position of the particle in world space*/
	glm::vec3 velocity;									/**<< The velocity of the particle in world space*/

	float timeAlive = 0.0f;								/**<< The time this particle has to live*/

	/**
	*	\brief Creates a new particle
	*	\param[in] position The position of the particle in world space
	*	\param[in] time_alive The maximum time the particle should stay alive
	*/
	Particle(const glm::vec3& position, const float& time_alive);
};

class ParticleRenderer
{
	public:
		/**
		*	\brief Default constructor
		*/
		ParticleRenderer() = default;

		/**
		*	\brief Creates a ParticleRenderer
		*	\param[in] position The position of the emitter in world space
		*	\param[in] num_particles The number of particles alive at a time
		*	\param[in] time_alive The maximum time a particle should stay alive
		*	\param[in] texture The texture of an particle
		*/
		ParticleRenderer(const glm::vec3& position, const uint32_t& num_particles, const float& time_alive, const std::shared_ptr<Texture>& texture);

		/**
		*	\brief Destroys the object
		*/
		~ParticleRenderer();

		/**
		*	\brief Updates the particle system
		*	\param[in] deltaTime The time between two frames
		*/
		void update(const float& deltaTime);

		/**
		*	\brief Renders the particle system
		*	\param[in] camera The camera that is observing the particle system
		*	\note: This function disables depth writing for the draw call. The system should be rendered last in the scene
		*/
		void render(const Camera& camera);

		/**
		*	\brief Renders the particle system
		*	\param[in] view The view matrix
		*	\param[in] projection The projection matrix
		*	\note: This function disables depth writing for the draw call. The system should be rendered last in the scene
		*/
		void render(const glm::mat4& view, const glm::mat4& projection);
	private:
		std::shared_ptr<Texture> _texture;					/**<< The texture of a single particle*/
		std::vector<Particle> _particles;					/**<< The particles managed by this system*/
		std::shared_ptr<VertexArray> _vao;					/**<< The internal vao of the particle system*/
		std::shared_ptr<VertexBuffer> _instanceArray;		/**<< The data needed for each particle*/
		glm::vec3 _position;								/**<< The position of the emitter in world space*/
		float _timeAlive = 0.0f;							/**<< The maximum time a particle can stay alive*/
		float* _attributes = nullptr;						/**<< Internal buffer to update the vbo*/
};

#endif