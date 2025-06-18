<<<<<<< HEAD
#ifndef HELPER_H
#define HELPER_H

#include <stdio.h>
#include <stdlib.h>

const int INFO_LOG_SIZE = 512;

char *load_shader(const char *shader_path);
unsigned int compile_vertex_shader(const char *vertex_shader_code);
unsigned int compile_fragment_shader(const char *fragment_shader_code);
unsigned int create_shader_program(const unsigned int vert_shader, const unsigned int frag_shader);


unsigned int create_shader_program(const unsigned int vert_shader, const unsigned int frag_shader) {
    unsigned int shader_program = glCreateProgram();
    glAttachShader(shader_program, vert_shader);
    glAttachShader(shader_program, frag_shader);
    glLinkProgram(shader_program);

    int success;
    char infoLog[INFO_LOG_SIZE];

    glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shader_program, INFO_LOG_SIZE, NULL, infoLog);
        fprintf(stderr, "ERROR:SHADER:PROGRAM:LINKING:FAILED\n%s\n", infoLog);
    }

    return shader_program;
}


unsigned int compile_fragment_shader(const char *fragment_shader_code) {
    unsigned int fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_shader_code, NULL);
    glCompileShader(fragment_shader);

    int success;
    char infoLog[INFO_LOG_SIZE];

    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragment_shader, INFO_LOG_SIZE, NULL, infoLog);
        fprintf(stderr, "ERROR:SHADER:FRAGMENT:COMPILATION:FAILED\n%s\n", infoLog);
    }

    return fragment_shader;
}


unsigned int compile_vertex_shader(const char *vertex_shader_code) {
    unsigned int vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_shader_code, NULL);
    glCompileShader(vertex_shader);

    int success;
    char infoLog[INFO_LOG_SIZE];

    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertex_shader, INFO_LOG_SIZE, NULL, infoLog);
        fprintf(stderr, "ERROR:SHADER:VERTEX:COMPILATION:FAILED\n%s\n", infoLog);
    }

    return vertex_shader;
}


char *load_shader(const char *shader_path) {
    char *shader_code;

    FILE *shader_file = fopen(shader_path, "r");
    if (!shader_file) {
        fprintf(stderr, "ERROR:LOADING:SHADER:FAILED\n");
        return NULL;
    }

    // seek to end to determine file size
    fseek(shader_file, 0, SEEK_END);
    long file_size = ftell(shader_file);
    rewind(shader_file);

    // allocate buffer (+1 for null terminator)
    shader_code = (char *)malloc(file_size + 1);
    if (!shader_code) {
        fprintf(stderr, "ERROR:ALLOCATION:SHADER:BUFFER:FAILED\n");
        fclose(shader_file);
        return NULL;
    }

    // read file into buffer
    size_t read_size = fread(shader_code, 1, file_size, shader_file);
    shader_code[read_size] = '\0';

    fclose(shader_file);
    return shader_code;
}


#endif
=======
#ifndef _SHADER_H
#define _SHADER_H

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>


class Shader {
	public:
		unsigned int ID;

		Shader(const char *vertexPath, const char *fragmentPath) {
			std::string vertexCode;
			std::string fragmentCode;
			std::ifstream vShaderFile;
			std::ifstream fShaderFile;

			vShaderFile.exceptions (std::ifstream::failbit | 
					std::ifstream::badbit);
			fShaderFile.exceptions (std::ifstream::failbit | 
					std::ifstream::badbit);

			try {
				vShaderFile.open(vertexPath);
				fShaderFile.open(fragmentPath);

				std::stringstream vShaderStream, fShaderStream;
				vShaderStream << vShaderFile.rdbuf();
				fShaderStream << fShaderFile.rdbuf();

				vShaderFile.close();
				fShaderFile.close();

				vertexCode = vShaderStream.str();
				fragmentCode = fShaderStream.str();
			} catch (std::ifstream::failure &e) {
				std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ" << 
					std::endl;
			}

			const char *vShaderCode = vertexCode.c_str();
			const char *fShaderCode = fragmentCode.c_str();

			unsigned int vertex, fragment;
			int success;
			char infoLog[512];

			vertex = glCreateShader(GL_VERTEX_SHADER);
			glShaderSource(vertex, 1, &vShaderCode, NULL);
			glCompileShader(vertex);

			glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
			if (!success) {
				glGetShaderInfoLog(vertex, 512, NULL, infoLog);
				std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" <<
					infoLog << std::endl;
			}

			fragment = glCreateShader(GL_FRAGMENT_SHADER);
			glShaderSource(fragment, 1, &fShaderCode, NULL);
			glCompileShader(fragment);

			glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
			if (!success) {
				glGetShaderInfoLog(fragment, 512, NULL, infoLog);
				std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" <<
					infoLog << std::endl;
			}

			ID = glCreateProgram();
			glAttachShader(ID, vertex);
			glAttachShader(ID, fragment);
			glLinkProgram(ID);

			glGetProgramiv(ID, GL_LINK_STATUS, &success);
			if (!success) {
				glGetProgramInfoLog(ID, 512, NULL, infoLog);
				std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << 
					infoLog << std::endl;
			}

			glDeleteShader(vertex);
			glDeleteShader(fragment);
		}


		void use() {
			glUseProgram(ID);
		}

		void setBool(const std::string &name, bool value) const {
			glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
		}

		void setInt(const std::string &name, int value) const {
			glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
		}

		void setFloat(const std::string &name, float value) const {
			glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
		}
};

#endif
>>>>>>> origin/main
