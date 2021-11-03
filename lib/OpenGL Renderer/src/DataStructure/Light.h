#ifndef __OPENGLRENDERER_DATASTRUCTURE_LIGHT_H
#define __OPENGLRENDERER_DATASTRUCTURE_LIGHT_H

#include <glm/glm.hpp>
#include <OpenGLObjects/FrameBuffer.h>
#include <memory>
class Shader;

/**
*	\brief A struct to model light
*/
class Light
{
	public:
		/**
		*	\brief Default constructor
		*/
		Light() = default;

		/**
		*	\brief Creates a light object
		*	\param[in] position The position of the light source
		*	\param[in] castShadows If this lightsource should cast shadows
		*	\param[in] shadow_resx The x resolution of the shadow map
		*	\param[in] shadow_resy The y resolution of the shadow map
		*	\param[in] near The near plane
		*	\param[in] far The far plane
		*/
		Light(const glm::vec3& position, 
			  const bool& castShadows = false, 
			  const uint32_t& shadow_resx = 0, 
			  const uint32_t& shadow_resy = 0, 
			  const float& near = 0, 
			  const float& far = 0);


		/**
		*	\brief Adds the light to the specified shader
		*	\param[in] shader The shader where the light should be added
		*	\param[in] lightID The ID of the light (i.e. the position in the light array used by the shader)
		*/
		void addToShader(const std::shared_ptr<Shader>& shader, const uint32_t& lightID);

		//Member variables
		glm::vec3 position;								/**<< The position of the light*/
		glm::vec3 ambient;								/**<< The ambient strength of the light*/
		glm::vec3 diffuse;								/**<< The diffuse strength of the light*/
		glm::vec3 specular;								/**<< The specular strength of the light*/

		std::shared_ptr<FrameBuffer> shadow_map;		/**<< The shadowmap generated by this lightsource*/
		glm::mat4 lightSpace;							/**<< The light space matrix of this lightsource*/
		glm::mat4 lightView;							/**<< The view matrix from this lightsource's perspective*/
		glm::mat4 lightProjection;						/**<< The light projection matrix*/
		
		bool castShadows;								/**<< If the light source casts shadows*/
};

#endif