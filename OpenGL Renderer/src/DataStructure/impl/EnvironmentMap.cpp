#include <DataStructure/EnvironmentMap.h>

EnvironmentMap 
EnvironmentMap::createObject(glm::vec3 position)
{
	EnvironmentMap result;
	result._camera = Camera::createObject(position, 90.0f, 1.0f, 0.1f, 100.0f);
	result._cube_map = Texture::createObject(1024, 1024, (void*)NULL, CUBEMAP);
	result._environment_map = FrameBuffer::createObject(1024, 1024);
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
EnvironmentMap::render(Scene scene, Skybox skybox, Shader shader)
{
	_environment_map.bind();
	glViewport(0, 0, 1024, 1024);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	for (unsigned int i = 0; i < 6; ++i)
	{
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, _cube_map.getID(), 0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		_camera.updateDirection(angles[i].pitch, angles[i].yaw);
		skybox.render(_camera);
		shader.bind();
		shader.setMVP(glm::mat4(1), _camera.getView(), _camera.getProjection());
		scene.render(shader);
	}
	_environment_map.unbind();
}