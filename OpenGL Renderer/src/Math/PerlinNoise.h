#ifndef MATH_PERLIN_NOISE
#define MATH_PERLIN_NOISE

#include <glm/glm.hpp>
#define GRIDX 512
#define GRIDY 512

class PerlinGenerator
{
public:
	/**
	*	\brief Creates an Perlin number generator
	*/
	PerlinGenerator() = default;

	/**
	*	\brief Creates an Perlin number generator and initializes the gradient grid
	*	\return The RNG
	*/
	static PerlinGenerator createObject();

	/**
	*	\brief Destroys the Perlin RNG
	*	\param[in] object The object to be destroyed
	*/
	static void destroyObject(PerlingGenerator& object);

	/**
	*	\brief Generates a random number
	*	\param[in] x The x-coordinate
	*	\param[in] y The y-coordinate
	*	\return The perlin random number
	*/
	float generate(const float x, const float y);
private:
	glm::vec2 gradients[GRIDX][GRIDY]; /**<< The gradient vector field*/
};

#endif