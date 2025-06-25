#include "sphere.h"

SPHERE
create_sphere(const glm::vec3 pos, const float radius, const int sector_count, 
		const int stack_count) {
	SPHERE s;
	s.stack_count	= stack_count;
	s.sector_count	= sector_count;
	s.radius		= radius;
	s.pos			= pos;

	const float sector_step	= 2 * M_PI / (float) sector_count;
	const float stack_step	= M_PI / (float) stack_count;

	for (int i = 0; i <= stack_count; i++) {
		const float phi	= M_PI / 2 - (i * stack_step );
		const float xz	= radius * cosf(phi);
		const float y	= radius * sinf(phi);

		for (int j = 0; j <= sector_count; j++) {
			const float theta = j * sector_step;

			const float	x	= xz * cosf(theta);
			const float z	= xz * sinf(theta);

			s.vertices.push_back(pos.x + x);
			s.vertices.push_back(pos.y + y);
			s.vertices.push_back(pos.z + z);

			s.normals.push_back(x / radius);
			s.normals.push_back(y / radius);
			s.normals.push_back(z / radius);
		}
	}
	
	return s;
}


void
generate_indices(SPHERE *s) {
	int stack_count		= s->stack_count;
	int sector_count	= s->sector_count;

	for (int i = 0; i < stack_count; i++) {
		int k1 = i * (sector_count + 1);
		int k2 = (i + 1) * (sector_count + 1);
		for (int j = 0; j < sector_count; j++, k1++, k2++) {
			if(i != 0) {
				s->indices.push_back(k1);
				s->indices.push_back(k2);
				s->indices.push_back(k1 + 1);
			}

			if(i != (stack_count - 1)) {
				s->indices.push_back(k1 + 1);
				s->indices.push_back(k2);
				s->indices.push_back(k2 + 1);
			}
		}
	}
}

