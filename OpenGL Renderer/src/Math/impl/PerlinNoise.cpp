#include <Math/PerlinNoise.h>
#include <ctime>
#include <Math/Functions.h>

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
	for (unsigned int x = 0; x < object.GRIDX; ++x) {
		delete[] object._gradients[x];
	}
	delete[] object._gradients;
}

float 
PerlinGenerator::generate(const float x, const float y)
{
	//Determine grid cell coordinates
	int x0 = static_cast<int>(x);
	int x1 = x0 + 1;
	int y0 = static_cast<int>(y);
	int y1 = y0 + 1;

	//Determine interpolation weights
	float sx = x - static_cast<float>(x0);
	float sy = y - static_cast<float>(y0);

	//Interpolate between grid point gradients
	float n0, n1, ix0, ix1;

	n0 = glm::dot(glm::vec2(x,y), glm::vec2(x0,y0));
	n1 = glm::dot(glm::vec2(x,y), glm::vec2(x1,y0));
	ix0 = Math::lerp(n0, n1, sx);

	n0 = glm::dot(glm::vec2(x, y), glm::vec2(x0, y1));
	n1 = glm::dot(glm::vec2(x, y), glm::vec2(x1, y1));
	ix1 = Math::lerp(n0, n1, sx);

	return Math::lerp(ix0, ix1, sy);

}