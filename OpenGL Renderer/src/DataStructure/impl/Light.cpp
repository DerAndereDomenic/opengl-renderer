#include <DataStructure/Light.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <Shader/Shader.h>

Light 
Light::createObject(const glm::vec3& position, 
					const bool& castShadows, 
					const uint32_t& shadow_resx, 
					const uint32_t& shadow_resy, 
					const float& near, 
					const float& far)
{
	Light result;

	result.position = position;
	result.castShadows = castShadows;

	if (castShadows)
	{
		result.shadow_map = FrameBuffer::createObject(shadow_resx, shadow_resy);
		result.shadow_map.attachDepthMap();
		result.shadow_map.disableColor();
		result.shadow_map.verify();
		result.shadow_map.unbind();

		result.lightProjection = glm::perspective(360.0f, static_cast<float>(shadow_resx) / static_cast<float>(shadow_resy), near, far);
		result.lightView = glm::lookAt(position, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		result.lightSpace = result.lightProjection * result.lightView;
	}
	return result;
}

void 
Light::destroyObject(Light& light)
{
	FrameBuffer::destroyObject(light.shadow_map);
}

void 
Light::addToShader(Shader& shader, const uint32_t& lightID)
{
	shader.bind();
	shader.setLight("lights_frag[" + std::to_string(lightID) + "]", *(this));
	shader.setMat4("lights_vert[" + std::to_string(lightID) + "].lightSpaceMatrix", lightSpace);
	shader.setInt("lights_frag[" + std::to_string(lightID) + "].shadow_map", 4 + lightID);
}