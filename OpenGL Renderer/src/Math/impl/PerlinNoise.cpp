#include <Math/PerlinNoise.h>
#include <ctime>
#include <Math/Functions.h>
#include <iostream>
#include <random>

#define _USE_MATH_DEFINES
#include <math.h>

PerlinGenerator 
PerlinGenerator::createObject()
{
	PerlinGenerator rng;
	//std::srand(std::time(nullptr));
	std::random_device rd;
	std::mt19937 e2(rd());
	std::uniform_real_distribution<float> dist(0.0f, 2.0f*M_PI);
	rng._gradients = new glm::vec2*[rng.GRIDX];
	for (unsigned int x = 0; x < rng.GRIDX; ++x)
	{
		rng._gradients[x] = new glm::vec2[rng.GRIDY];
		for (unsigned int y = 0; y < rng.GRIDY; ++y)
		{
			float angle = dist(e2);
			float rx = cosf(angle);
			float ry = sinf(angle);
			rng._gradients[x][y] = glm::vec2(rx, ry);
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
PerlinGenerator::dot(int ix, int iy, float x, float y)
{
	float dx = x - static_cast<float>(ix);
	float dy = y - static_cast<float>(iy);

	return (dx * static_cast<float>(_gradients[ix][iy][0]) + dy * static_cast<float>(_gradients[ix][iy][1]));
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

	n0 = dot(x0,y0, x,y);
	n1 = dot(x1,y0, x,y);
	ix0 = Math::lerp(n0, n1, sx);

	n0 = dot(x0, y1, x, y);
	n1 = dot(x1, y1, x, y);
	ix1 = Math::lerp(n0, n1, sx);

	return Math::lerp(ix0, ix1, sy);

}