#include <Math/PerlinNoise.h>
#include <ctime>

PerlinGenerator 
PerlinGenerator::createObject()
{
	PerlinGenerator rng;
	std::srand(std::time(nullptr));

	rng._gradients = new glm::vec2*[rng.GRIDX];
	for (unsigned int x = 0; x < rng.GRIDX; ++x)
	{
		rng._gradients[x] = new glm::vec2[rng.GRIDY];
		for (unsigned int y = 0; y < rng.GRIDY; ++y)
		{
			rng._gradients[x][y] = glm::vec2(std::rand(), std::rand());
			rng._gradients[x][y] /= rng._gradients[x][y].length;
		}
	}
	return rng;
}

void 
PerlinGenerator::destroyObject(PerlinGenerator& object)
{

}

float 
PerlinGenerator::generate(const float x, const float y)
{

}