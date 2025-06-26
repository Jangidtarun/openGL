#ifndef SHADER_H
#define SHADER_H

#include <stdio.h>
#include <stdlib.h>

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>


const int INFO_LOG_SIZE = 512;

char *load_shader(const char *shader_path);
unsigned int compile_vertex_shader(const char *vertex_shader_code);
unsigned int compile_fragment_shader(const char *fragment_shader_code);
unsigned int create_shader_program(const unsigned int vert_shader, const unsigned int frag_shader);

void uniset_float(unsigned int shader_program, const char *name, const float val);
void uniset_vec3(unsigned int shader_program, const char *name, const glm::vec3 vec);
void uniset_mat4(unsigned int shader_program, const char *name, const glm::mat4 mat);

#endif
