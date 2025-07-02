#include "mesh.h"


struct Mesh
init_mesh(std::vector<struct Vertex> vertices, 
		std::vector<unsigned int> indices,
		std::vector<struct Texture> textures)
{
	struct Mesh mesh;
	mesh.vertices = vertices;
	mesh.indices = indices;
	mesh.textures = textures;

	setup_mesh(&mesh);

	return mesh;
}


void draw_mesh(const struct Mesh &mesh, const unsigned int shader_program)
{
	unsigned int total_diffuse = 1;
	unsigned int total_specular = 1;
	for (int i = 0; i < mesh->textures.size(); i++) {
		glActiveTexture(GL_TEXTURE0 + i);
		std::string number;
		std::string name = mesh->textures[i].type;

		if (name == "texture_diffuse") {
			number = std::to_string(total_diffuse++);
		} else if (name == "texture_specular") {
			number = std::to_string(total_specular++);
		}

		uniset_int(shader_program, ("material." + name + number).c_str(), i);
		glBindTexture(GL_TEXTURE_2D, mesh->textures[i].id);
	}
	glActiveTexture(GL_TEXTURE0);

	// draw mesh
	glBindVertexArray(mesh->vao);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}


void setup_mesh(struct Mesh &mesh)
{
	glGenVertexArrays(1, &(mesh->vao));
	glGenBuffers(1, &(mesh->vbo));
	glGenBuffers(1, &(mesh->ebo));

	glBindVertexArray(mesh->vao);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vbo);

	glBufferData(GL_ARRAY_BUFFER, mesh->vertices.size() * sizeof(struct Vertex), 
			&(mesh->vertices[0]), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 
			mesh->indices.size() * sizeof(unsigned int), 
			&(mesh->indices[0]), GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(struct Vertex), 
			(void *)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(struct Vertex), 
			(void *)offsetof(struct Vertex, normal));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(struct Vertex), 
			(void *)offsetof(struct vertex, texcoords));

	glBindVertexArray(0);
}
