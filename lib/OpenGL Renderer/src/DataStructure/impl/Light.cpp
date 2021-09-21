#include <DataStructure/Light.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <Shader/Shader.h>

 Light::Light(const glm::vec3& position, 
			  const bool& castShadows, 
			  const uint32_t& shadow_resx, 
			  const uint32_t& shadow_resy, 
			  const float& near, 
			  const float& far)
{
	this->position = position;
	this->castShadows = castShadows;

	if (castShadows)
	{
		shadow_map = std::make_shared<FrameBuffer>(shadow_resx, shadow_resy);
		shadow_map->attachDepthMap();
		shadow_map->disableColor();
		shadow_map->verify();
		shadow_map->unbind();

		lightProjection = glm::perspective(360.0f, static_cast<float>(shadow_resx) / static_cast<float>(shadow_resy), near, far);
		lightView = glm::lookAt(position, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		lightSpace = lightProjection * lightView;
	}
}

void 
Light::addToShader(std::shared_ptr<Shader> shader, const uint32_t& lightID)
{
	shader->bind();
	shader->setLight("lights_frag[" + std::to_string(lightID) + "]", *(this));
	shader->setMat4("lights_vert[" + std::to_string(lightID) + "].lightSpaceMatrix", lightSpace);
	if(castShadows)
		shader->setInt("lights_frag[" + std::to_string(lightID) + "].shadow_map", 9 + lightID);
	shader->setInt("lights_frag[" + std::to_string(lightID) + "].cast_shadow", castShadows ? 1:0);
}