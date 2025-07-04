#ifndef MESH_H
#define MESH_H

#include <glad/glad.h>

#include <glm/glm.hpp>

#include <string>
#include <vector>

#include "../shader/shader.h"

typedef struct {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texcoords;
} Vertex;


typedef struct {
	unsigned int id;
	std::string type;
	std::string path;
} Texture;


typedef struct {
	// mesh data
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;

	// render data
	unsigned int vao, vbo, ebo;
} Mesh;


Mesh init_mesh(std::vector<Vertex> vertices, 
		std::vector<unsigned int> indices,
		std::vector<Texture> textures);

void draw_mesh(Mesh *mesh, const unsigned int shader_program);
void setup_mesh(Mesh *mesh);

#endif
