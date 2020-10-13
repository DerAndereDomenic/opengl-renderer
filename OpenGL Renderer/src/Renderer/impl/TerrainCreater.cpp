#include <Renderer/TerrainCreater.h>
#include <Math/PerlinNoise.h>

Texture
Terrain::createTerrain(const uint32_t& resx, const uint32_t& resz, const uint32_t& griddetail)
{
	float* data = new float[resx * resz];
	PerlinGenerator rng = PerlinGenerator::createObject();

	float resolutionx = static_cast<float>(griddetail) / static_cast<float>(resx);
	float resolutiony = static_cast<float>(griddetail) / static_cast<float>(resz);

	uint32_t i = 0;
	for (uint32_t x = 0; x < resx; ++x)
	{
		for (uint32_t y = 0; y < resz; ++y)
		{
			data[i] = (rng.generate(x * resolutionx, y * resolutiony) + 1.0f) / 2.0f;
			++i;
		}
	}

	Texture result = Texture::createObject(resx, resz, data, TEXTURE, GL_RED, GL_RED, GL_FLOAT);
	delete[] data;
	PerlinGenerator::destroyObject(rng);
	return result;
}