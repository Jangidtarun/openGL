#ifndef MESH_H
#define MESH_H

#include <glm/glm.hpp>
#include <string>
#include <vector>

struct Vertex {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec3 texcoords;
};


struct Texture {
	unsigned int id;
	std::string type;
};


struct Mesh {
	// mesh data
	std::vector<struct Vector> vertices;
	std::vector<unsigned int> indices;
	std::vector<struct Texture> textures;

	// render data
	unsigned int vao, vbo, ebo;
};


struct Mesh
init_mesh(std::vector<struct Vertex> vertices, 
		std::vector<unsigned int> indices,
		std::vector<struct Texture> textures);

void draw_mesh(const struct Mesh &mesh, const unsigned int shader_program);

void setup_mesh(struct Mesh &mesh);

#endif
