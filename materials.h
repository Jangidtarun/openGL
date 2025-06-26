#ifndef MATERIALS_H
#define MATERIALS_H

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

typedef struct {
	glm::vec3	ambient;
	glm::vec3	diffuse;
	glm::vec3	specular;
	float		shininess;
} Material;

Material obsidian = {
	glm::vec3(0.053750,		0.050000, 	0.066250),
	glm::vec3(0.182750, 	0.170000, 	0.225250),
	glm::vec3(0.332741, 	0.328634, 	0.346435),
	0.3f
};

Material gold	= {
	glm::vec3(0.247250, 	0.1995, 	0.0745),
	glm::vec3(0.751640,		0.60648, 	0.22648),
	glm::vec3(0.628281, 	0.555802, 	0.366065),
	0.4f
};

#endif
