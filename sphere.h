#ifndef SPHERE_H
#define SPHERE_H

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>

// useful constants
const glm::vec3 ORIGIN	= glm::vec3(0.0f, 0.0f, 0.0f);

// defaults
const int SECTOR_COUNT	= 72;
const int STACK_COUNT	= 24;
const float RADIUS		= 1.0f;

typedef struct {
	// information to generate the sphere
	glm::vec3 pos;
	float radius;
	int stack_count;
	int sector_count;

	// generated information
	std::vector<float> vertices;
	std::vector<float> normals;
	std::vector<unsigned int> indices;
} SPHERE;

SPHERE 
create_sphere(const glm::vec3 pos = ORIGIN, 
		const float radius		= RADIUS,
		const int sector_count	= SECTOR_COUNT, 
		const int stack_count	= STACK_COUNT);

void generate_indices(SPHERE *s);

#endif
