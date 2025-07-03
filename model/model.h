#ifndef MODEL_H
#define MODEL_H

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../texture/texture.h"
#include "../mesh/mesh.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <iostream>
#include <vector>
#include <string>


typedef struct {
	std::vector<Mesh> meshes;
	std::string directory;
	std::vector<Texture> textures_loaded;
} Model;

Model init_model(const char *path);
void draw_model(Model *model, const unsigned int shader_program);

void load_model(Model *model, const std::string path);
void process_node(Model *model, aiNode *node, const aiScene *scene);
Mesh process_mesh(Model *model, aiMesh *mesh, const aiScene *scene);
std::vector<Texture> load_material_textures(Model *model, aiMaterial *material, 
		aiTextureType type, std::string type_name);

#endif
