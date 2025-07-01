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
	light.ambient	= light.color	* light.ambient_intensity;
	light.diffuse	= light.color	* light.diffuse_intensity;

	light.kc = kc;
	light.kl = kl;
	light.kq = kq;

	return light;
}

SpotLight
create_spot_light(glm::vec3 position,
	glm::vec3 direction,
	float cutoff_angle,
	float outer_cutoff_angle,
	glm::vec3 color,
	glm::vec3 ambient_intensity,
	glm::vec3 diffuse_intensity,
	glm::vec3 specular,
	float kc,
	float kl,
	float kq) {
	SpotLight light;

	light.position			= position;
	light.direction			= direction;
	light.cutoff_angle		= cutoff_angle;
	light.outer_cutoff_angle		= outer_cutoff_angle;
	light.color				= color;
	light.ambient_intensity	= ambient_intensity;
	light.diffuse_intensity	= diffuse_intensity;

	light.specular	= specular;
	light.ambient	= light.color	* light.ambient_intensity;
	light.diffuse	= light.color	* light.diffuse_intensity;

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
	light.ambient	= light.color	* light.ambient_intensity;
	light.diffuse	= light.color	* light.diffuse_intensity;

	return light;
}

void set_spot_light_uniforms(unsigned int shader_program,
	const char *spotlight_uniform_name,
	SpotLight &light) {
	uniset_vec3(shader_program, stradd(spotlight_uniform_name, ".position"),	light.position);
	uniset_vec3(shader_program, stradd(spotlight_uniform_name, ".direction"),	light.direction);
	uniset_float(shader_program, stradd(spotlight_uniform_name, ".cutoff"),
	glm::cos(glm::radians(light.cutoff_angle)));
	uniset_float(shader_program, stradd(spotlight_uniform_name, ".outer_cutoff"),
	glm::cos(glm::radians(light.outer_cutoff_angle)));
	uniset_vec3(shader_program, stradd(spotlight_uniform_name, ".ambient"),	light.ambient);
	uniset_vec3(shader_program, stradd(spotlight_uniform_name, ".diffuse"),	light.diffuse);
	uniset_vec3(shader_program, stradd(spotlight_uniform_name, ".specular"),	light.specular);
	uniset_float(shader_program, stradd(spotlight_uniform_name, ".kc"), light.kc);
	uniset_float(shader_program, stradd(spotlight_uniform_name, ".kl"), light.kl);
	uniset_float(shader_program, stradd(spotlight_uniform_name, ".kq"), light.kq);
}

void set_point_light_uniforms(unsigned int shader_program,
	const char *pointlight_uniform_name,
	PointLight &light) {
	uniset_vec3(shader_program, stradd(pointlight_uniform_name, ".position"),	light.position);
	uniset_vec3(shader_program, stradd(pointlight_uniform_name, ".ambient"),	light.ambient);
	uniset_vec3(shader_program, stradd(pointlight_uniform_name, ".diffuse"),	light.diffuse);
	uniset_vec3(shader_program, stradd(pointlight_uniform_name, ".specular"),	light.specular);
	uniset_float(shader_program, stradd(pointlight_uniform_name, ".kc"), light.kc);
	uniset_float(shader_program, stradd(pointlight_uniform_name, ".kl"), light.kl);
	uniset_float(shader_program, stradd(pointlight_uniform_name, ".kq"), light.kq);
}

void set_directional_light_uniforms(unsigned int shader_program,
	const char *dirlight_uniform_name,
	DirectionalLight &light) {
	uniset_vec3(shader_program, stradd(dirlight_uniform_name, ".direction"),	light.direction);
	uniset_vec3(shader_program, stradd(dirlight_uniform_name, ".ambient"),	light.ambient);
	uniset_vec3(shader_program, stradd(dirlight_uniform_name, ".diffuse"),	light.diffuse);
	uniset_vec3(shader_program, stradd(dirlight_uniform_name, ".specular"),	light.specular);
}
