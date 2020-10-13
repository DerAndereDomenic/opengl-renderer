#ifndef MATH_PERLIN_NOISE
#define MATH_PERLIN_NOISE

#include <glm/glm.hpp>

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
	static void destroyObject(PerlinGenerator& object);

	/**
	*	\brief Generates a random number
	*	\param[in] x The x-coordinate
	*	\param[in] y The y-coordinate
	*	\return The perlin random number
	*/
	float generate(const float x, const float y);
private:
	glm::vec2 **_gradients; /**<< The gradient vector field*/

	uint32_t GRIDX = 512; /**<< The x size of the grid*/
	uint32_t GRIDY = 512; /**<< The y size of the grid*/

	float dot(int ix, int iy, float x, float y);
};

#endif