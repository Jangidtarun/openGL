#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>

#include <stdio.h>
#include <stdlib.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>


const int INFO_LOG_SIZE = 512;

std::string load_shader(const std::string shader_path);
unsigned int compile_vertex_shader(const std::string vertex_shader_code);
unsigned int compile_fragment_shader(const std::string fragment_shader_code);
unsigned int create_shader_program(const unsigned int vert_shader, const unsigned int frag_shader);

void uniset_float(unsigned int shader_program, const std::string name, const float val);
void uniset_vec3(unsigned int shader_program, const std::string name, const glm::vec3 vec);
void uniset_mat4(unsigned int shader_program, const std::string name, const glm::mat4 mat);
void uniset_int(unsigned int shader_program, const std::string name, const int val);

#endif
