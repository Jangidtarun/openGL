#ifndef LIGHT_H
#define LIGHT_H

#include <glm/glm.hpp>
#include "../shader/shader.h"

#include <string>

// defaults
const glm::vec3 DEFAULT_POINT_LIGHT_POSITION	= glm::vec3(1.0f);
const glm::vec3 DEFAULT_LIGHT_COLOR		= glm::vec3(1.0f);
const glm::vec3 DEFAULT_LIGHT_AMB_INTEN	= glm::vec3(1.0f);
const glm::vec3 DEFAULT_LIGHT_DIF_INTEN	= glm::vec3(1.0f);
const glm::vec3 DEFAULT_LIGHT_SPE_INTEN = glm::vec3(1.0f);
const glm::vec3 DEFAULT_LIGHT_DIRECTION = glm::vec3(0.0f, -1.0f, 0.0f);
const float DEFAULT_SPOTLIGHT_CUTOFF_ANGLE = 12.0f;
const float DEFAULT_SPOTLIGHT_OUTER_CUTOFF_ANGLE = 17.0f;

// values for distance = 50
const float KC = 1.0f;
const float KL = 0.09f;
const float KQ = 0.032f;


typedef struct {
	// spatial information
	glm::vec3	position;

	// light information (required)
	glm::vec3	color;
	glm::vec3	ambient_intensity;
	glm::vec3	diffuse_intensity;
	glm::vec3	specular;

	// light information (generated)
	glm::vec3	ambient;
	glm::vec3	diffuse;

	// attenuation constants
	float	kc;
	float	kl;
	float	kq;
} PointLight;

typedef struct {
	// spatial information
	glm::vec3	position;
	glm::vec3	direction;
	float cutoff_angle;
	float outer_cutoff_angle;

	// light information (required)
	glm::vec3	color;
	glm::vec3	ambient_intensity;
	glm::vec3	diffuse_intensity;
	glm::vec3	specular;

	// light information (generated)
	glm::vec3	ambient;
	glm::vec3	diffuse;

	// attenuation constants
	float	kc;
	float	kl;
	float	kq;
} SpotLight;


typedef struct {
	// spatial information
	glm::vec3	direction;

	// light information (required)
	glm::vec3	color;
	glm::vec3	ambient_intensity;
	glm::vec3	diffuse_intensity;
	glm::vec3	specular;

	// light information (generated)
	glm::vec3	ambient;
	glm::vec3	diffuse;
} DirectionalLight;


PointLight
create_point_light(glm::vec3 position	= DEFAULT_POINT_LIGHT_POSITION,
	glm::vec3 color	= DEFAULT_LIGHT_COLOR,
	glm::vec3 ambient_intensity	= DEFAULT_LIGHT_AMB_INTEN,
	glm::vec3 diffuse_intensity	= DEFAULT_LIGHT_DIF_INTEN,
	glm::vec3 specular			= DEFAULT_LIGHT_SPE_INTEN,
	float kc = KC,
	float kl = KL,
	float kq = KQ);


SpotLight
create_spot_light(glm::vec3 position	= DEFAULT_POINT_LIGHT_POSITION,
	glm::vec3 direction	= DEFAULT_LIGHT_DIRECTION,
	float cutoff_angle = DEFAULT_SPOTLIGHT_CUTOFF_ANGLE,
	float outer_cutoff_angle = DEFAULT_SPOTLIGHT_OUTER_CUTOFF_ANGLE,
	glm::vec3 color	= DEFAULT_LIGHT_COLOR,
	glm::vec3 ambient_intensity	= DEFAULT_LIGHT_AMB_INTEN,
	glm::vec3 diffuse_intensity	= DEFAULT_LIGHT_DIF_INTEN,
	glm::vec3 specular			= DEFAULT_LIGHT_SPE_INTEN,
	float kc = KC,
	float kl = KL,
	float kq = KQ);


DirectionalLight
create_directional_light(glm::vec3 direction	= DEFAULT_LIGHT_DIRECTION,
	glm::vec3 color	= DEFAULT_LIGHT_COLOR,
	glm::vec3 ambient_intensity = DEFAULT_LIGHT_AMB_INTEN,
	glm::vec3 diffuse_intensity = DEFAULT_LIGHT_DIF_INTEN,
	glm::vec3 specular			= DEFAULT_LIGHT_SPE_INTEN);


void set_spot_light_uniforms(unsigned int shader_program,
	const std::string light_uniform_name,
	SpotLight &light);

void set_point_light_uniforms(unsigned int shader_program,
	const std::string light_uniform_name,
	PointLight &light);

void set_directional_light_uniforms(unsigned int shader_program,
	const std::string light_uniform_name,
	DirectionalLight &light);

#endif
