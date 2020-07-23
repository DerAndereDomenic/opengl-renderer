#include "../Functions.h"
#include <glm/gtx/transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/matrix_inverse.hpp>

TUMPose
Math::View2TUMPose(glm::mat4 view)
{
	glm::mat4 view_rot = glm::rotate(glm::radians(180.0f), glm::vec3(1.0f, 0.0f, 0.0f)) * view;
	glm::mat4 view_inv = glm::affineInverse(view_rot);

	glm::fquat q = glm::toQuat(view_inv);

	TUMPose pose;
	pose._translation = glm::vec3(view_inv[3][0], view_inv[3][1], view_inv[3][2]);
	pose._rotation = q;

	return pose;
}