#include <DataStructure/Light.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

Light 
Light::createObject(glm::vec3 position, unsigned int shadow_resx, unsigned int shadow_resy, float near, float far)
{
	Light result;

	result.shadow_map = FrameBuffer::createObject(shadow_resx, shadow_resy);
	result.shadow_map.attachDepthMap();
	result.shadow_map.disableColor();
	result.shadow_map.verify();
	result.shadow_map.unbind();

	result.lightProjection = glm::perspective(360.0f, static_cast<float>(shadow_resx) / static_cast<float>(shadow_resy), near, far);
	result.lightView = glm::lookAt(position, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	result.lightSpace = result.lightProjection * result.lightView;

	//ShaderManager::instance()->getShader("Normal").setLight("lights_frag[" + std::to_string(i) + "]", lights[i]);
	//ShaderManager::instance()->getShader("Normal").setMat4("lights_vert[" + std::to_string(i) + "].lightSpaceMatrix", lights[i].lightSpace);
	//ShaderManager::instance()->getShader("Normal").setInt("lights_frag[" + std::to_string(i) + "].shadow_map", 4 + i);

	return result;
}


void 
Light::destroyObject(Light& light)
{
	FrameBuffer::destroyObject(light.shadow_map);
}