#include <Renderer/TerrainCreater.h>
#include <Math/PerlinNoise.h>

Texture
Terrain::createTerrain(unsigned int resx, unsigned int resz, unsigned int griddetail)
{
	float* data = new float[resx * resz];
	PerlinGenerator rng = PerlinGenerator::createObject();

	float resolutionx = static_cast<float>(griddetail) / static_cast<float>(resx);
	float resolutiony = static_cast<float>(griddetail) / static_cast<float>(resz);

	unsigned int i = 0;
	for (unsigned int x = 0; x < resx; ++x)
	{
		for (unsigned int y = 0; y < resz; ++y)
		{
			data[i] = (rng.generate(x * resolutionx, y * resolutiony) + 1.0f) / 2.0f;
			++i;
		}
	}

	Texture result = Texture::createObject(data, resx, resz);
	delete data;
	PerlinGenerator::destroyObject(rng);
	return result;
}