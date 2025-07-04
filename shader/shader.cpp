#include "shader.h"


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


unsigned int compile_fragment_shader(const char *fshader_path) {
	const char *fragment_shader_code = load_shader(fshader_path);
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


unsigned int compile_vertex_shader(const char *vshader_path) {
	const char *vertex_shader_code = load_shader(vshader_path);
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


std::string load_shader(const std::string shader_path) {
    std::string shader_code;
	std::ifstream shader_file;

	shader_file.exceptions (std::ifstream::failbit | std::ifstream::badbit);
	try {
		shader_file.open(shader_path);
		std::stringstream shader_stream;
		shader_stream << shader_file.rdbuf();
		shader_file.close();
		shader_code = shader_stream.str();
	} catch (std::ifstream::failure &e) {
		std::cout << "ERROR:SHADER:Failed to read file:\n" << 
			e.what() << std::endl;
	}

    return shader_code;
}


void uniset_float(unsigned int shader_program, const char *name, const float val) {
	glUniform1f(glGetUniformLocation(shader_program, name), val);
}


void uniset_vec3(unsigned int shader_program, const char *name, const glm::vec3 vec) {
	glUniform3fv(glGetUniformLocation(shader_program, name), 1, glm::value_ptr(vec));
}


void uniset_mat4(unsigned int shader_program, const char *name, const glm::mat4 mat) {
	glUniformMatrix4fv(glGetUniformLocation(shader_program, name), 1, GL_FALSE, glm::value_ptr(mat));
}


void uniset_int(unsigned int shader_program, const char *name, const int val) {
	glUniform1i(glGetUniformLocation(shader_program, name), val);
}
