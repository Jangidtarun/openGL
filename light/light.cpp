#include "light.h"

PointLight
create_point_light(glm::vec3 position,
	glm::vec3 color,
	glm::vec3 ambient_intensity,
	glm::vec3 diffuse_intensity,
	glm::vec3 specular,
	float kc,
	float kl,
	float kq) {
	PointLight light;

	light.position			= position;
	light.color				= color;
	light.ambient_intensity	= ambient_intensity;
	light.diffuse_intensity	= diffuse_intensity;

	light.specular	= specular;
	light.diffuse	= light.color	* light.ambient_intensity;
	light.ambient	= light.diffuse	* light.diffuse_intensity;

	light.kc = kc;
	light.kl = kl;
	light.kq = kq;

	return light;
}


DirectionalLight
create_directional_light(glm::vec3 direction,
	glm::vec3 color,
	glm::vec3 ambient_intensity,
	glm::vec3 diffuse_intensity,
	glm::vec3 specular) {
	DirectionalLight light;

	light.direction			= direction;
	light.color				= color;
	light.ambient_intensity	= ambient_intensity;
	light.diffuse_intensity	= diffuse_intensity;

	light.specular	= specular;
	light.diffuse	= light.color	* light.ambient_intensity;
	light.ambient	= light.diffuse	* light.diffuse_intensity;

	return light;
}