#include "model.h"

Model init_model(const std::string path) {
	Model m;
	load_model(&m, path);
	return m;
}

void draw_model(Model *model, const unsigned int shader_program) {
	for (unsigned int i = 0; i < model->meshes.size(); i++) {
		draw_mesh(&(model->meshes[i]), shader_program);
	}
}

void load_model(Model *model, const std::string path) {
	Assimp::Importer importer;
	const aiScene *scene = importer.ReadFile(path, 
			aiProcess_Triangulate | aiProcess_FlipUVs);

	if ((!scene || scene->mFlags) && (AI_SCENE_FLAGS_INCOMPLETE || 
			!scene->mRootNode)) {
		std::cout << "Error:ASSIMP:" << importer.GetErrorString() << std::endl;
		return;
	}

	model->directory = path.substr(0, path.find_last_of('/'));
	process_node(model, scene->mRootNode, scene);
}

void process_node(Model *model, aiNode *node, const aiScene *scene) {
	for (unsigned int i = 0; i < node->mNumMeshes; i++) {
		aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
		model->meshes.push_back(process_mesh(model, mesh, scene));
	}

	for (unsigned int i = 0; i < node->mNumChildren; i++) {
		process_node(model, node->mChildren[i], scene);
	}
}

Mesh process_mesh(Model *model, aiMesh *mesh, const aiScene *scene) {
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;

	for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
		Vertex vertex;

		// process vertex data
		glm::vec3 vector;
		vector.x = mesh->mVertices[i].x;
		vector.y = mesh->mVertices[i].y;
		vector.z = mesh->mVertices[i].z;
		vertex.position = vector;

		if (mesh->HasNormals()) {
			vector.x = mesh->mNormals[i].x;
			vector.y = mesh->mNormals[i].y;
			vector.z = mesh->mNormals[i].z;
			vertex.normal = vector;
		}

		if (mesh->mTextureCoords[0]) {
			glm::vec2 vec;
			vec.x = mesh->mTextureCoords[0][i].x;
			vec.y = mesh->mTextureCoords[0][i].y;
			vertex.texcoords = vec;
		} else {
			vertex.texcoords = glm::vec2(0.0f);
		}

		vertices.push_back(vertex);
	}

	// process indices data
	for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
		aiFace face = mesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; j++) {
			indices.push_back(face.mIndices[j]);
		}
	}
	
	// process texture / material data
	if (mesh->mMaterialIndex >= 0) {
		aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
		std::vector<Texture> diffuse_maps = load_material_textures(model, 
				material, aiTextureType_DIFFUSE, "texture_diffuse");
		textures.insert(textures.end(), diffuse_maps.begin(), 
				diffuse_maps.end());
		std::vector<Texture> specular_maps = load_material_textures(model, 
				material, aiTextureType_SPECULAR, "texture_specular");
		textures.insert(textures.end(), specular_maps.begin(), 
				specular_maps.end());
	}

	Mesh m = init_mesh(vertices, indices, textures);
	return m;
}
	
	
std::vector<Texture> load_material_textures(Model *model, aiMaterial *material, 
		aiTextureType type, std::string type_name) {
	std::vector<Texture> textures;
	for (unsigned int i = 0; i < material->GetTextureCount(type); i++) {
		aiString str;
		material->GetTexture(type, i , &str);

		bool skip = false;
		for (unsigned int j = 0; j < model->textures_loaded.size(); j++) {
			if (std::strcmp(model->textures_loaded[j].path.data(), 
						str.C_Str()) == 0) {
				textures.push_back(model->textures_loaded[j]);
				skip = true;
				break;
			}
		}

		if (!skip) {
			Texture texture;
			texture.id = make_texture(str.C_Str(), model->directory);
			texture.type = type_name;
			texture.path = str.C_Str();
			textures.push_back(texture);
			model->textures_loaded.push_back(texture);
		}
	}
	return textures;
}
