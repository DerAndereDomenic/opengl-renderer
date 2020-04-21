#include <DataStructure/EnvironmentMap.h>

EnvironmentMap 
EnvironmentMap::createObject(glm::vec3 position)
{
	EnvironmentMap result;
	result._camera = Camera::createObject(position, 90.0f, 1.0f, 0.1f, 100.0f);
	result._cube_map = Texture::createObject(1000, 1000, CUBEMAP);
	result._environment_map = FrameBuffer::createObject(1000, 1000);
	result._environment_map.attachRenderBuffer();
	result._environment_map.unbind();
	return result;
}

void 
EnvironmentMap::destroyObject(EnvironmentMap& object)
{
	Camera::destroyObject(object._camera);
	Texture::destroyObject(object._cube_map);
	FrameBuffer::destroyObject(object._environment_map);
}

void 
EnvironmentMap::render(Scene scene, Shader shader)
{

}