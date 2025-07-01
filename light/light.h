#ifndef LIGHT_H
#define LIGHT_H

#include <glm/glm.hpp>

// defaults
const glm::vec3 DEFAULT_POINT_LIGHT_POSITION	= glm::vec3(1.0f);
const glm::vec3 DEFAULT_LIGHT_COLOR		= glm::vec3(1.0f);
const glm::vec3 DEFAULT_LIGHT_AMB_INTEN	= glm::vec3(1.0f);
const glm::vec3 DEFAULT_LIGHT_DIF_INTEN	= glm::vec3(0.5f);
const glm::vec3 DEFAULT_LIGHT_SPE_INTEN = glm::vec3(1.0f);
const glm::vec3 DEFAULT_LIGHT_DIRECTION = glm::vec3(0.0f, -1.0f, 0.0f);

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


DirectionalLight
create_directional_light(glm::vec3 direction	= DEFAULT_LIGHT_DIRECTION,
	glm::vec3 color	= DEFAULT_LIGHT_COLOR,
	glm::vec3 ambient_intensity = DEFAULT_LIGHT_AMB_INTEN,
	glm::vec3 diffuse_intensity = DEFAULT_LIGHT_DIF_INTEN,
	glm::vec3 specular			= DEFAULT_LIGHT_SPE_INTEN);

#endif
