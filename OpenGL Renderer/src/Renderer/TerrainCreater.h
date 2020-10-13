#ifndef RENDERER_TERRAINCREATER_H
#define RENDERER_TERRAINCREATER_H

#include <OpenGLObjects/Texture.h>

namespace Terrain
{
	/**
	*	\brief Create a terrain texture
	*	\param[in] resx The resolution in x direction
	*	\param[in] resy The resolution in y direction
	*	\param[in] griddetail How many Perlin Noise cells should be used (must be <= 512)
	*	\return A texture containing the height values of the terrain
	*/
	Texture
	createTerrain(const uint32_t& resx, const uint32_t& resz, const uint32_t& griddetail);
}

#endif