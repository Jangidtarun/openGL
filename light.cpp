#include "light.h"

LIGHT
create_light(glm::vec3 position, glm::vec3 light_color, glm::vec3 ambient_intensity, 
		glm::vec3 diffuse_intensity, glm::vec3 specular) {
	LIGHT light;

	light.position			= position;
	light.light_color		= light_color;
	light.ambient_intensity	= ambient_intensity;
	light.diffuse_intensity	= diffuse_intensity;

	light.specular	= specular;
	light.diffuse	= light.light_color	* light.ambient_intensity;
	light.ambient	= light.diffuse		* light.diffuse_intensity;

	return light;
}
