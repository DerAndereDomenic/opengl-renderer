#ifndef DATA_STRUCTURE_TUMPOSE_H
#define DATA_STRUCTURE_TUMPOSE_H

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

struct TUMPose
{
	glm::vec3 _translation; /**< The translation vector of the camera pose*/
	glm::fquat _rotation;	/**< The rotation of the camera pose as quaternion*/
};

#endif