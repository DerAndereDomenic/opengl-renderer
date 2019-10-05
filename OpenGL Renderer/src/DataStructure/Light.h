#ifndef DATA_STRUCTURE_LIGHT_H
#define DATA_STRUCTURE_LIGHT_H

#include <glm/glm.hpp>

/**
*	\brief A struct to model light
*/
struct Light
{
	glm::vec3 position; /**<< The position of the light*/
	glm::vec3 ambient; /**<< The ambient strength of the light*/
	glm::vec3 diffuse; /**<< The diffuse strength of the light*/
	glm::vec3 specular; /**<< The specular strength of the light*/
};

#endif