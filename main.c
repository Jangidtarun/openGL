#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <cglm/cglm.h>
#include <cglm/types.h>

#include <stdio.h>
#include <math.h>

#include "texture.h"
#include "shader.h"
#include "error_codes.h"

#define INFO_LOG_SIZE 512

const unsigned int WINDOW_WIDTH = 800;
const unsigned int WINDOW_HEIGHT = 600;

const char *vertexShaderSource_path = "shaders/shader.vert";
const char *fragmentShaderSource_path = "shaders/shader.frag";
const char *texture1_path = "textures/img1.jpeg";
const char *texture2_path = "textures/img3.jpeg";

int init_opengl() {
	if (!glfwInit()) {
		fprintf(stderr, "Failed to initialize GLFW\n");
		return 0;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	return 1;
}

int main() {

	if (!init_opengl()) {
		return GLFW_INIT_FAILED;
	}

	GLFWwindow *window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (!window) {
		fprintf(stderr, "Failed to create GLFW window\n");
		glfwTerminate();
		return GLFW_WINDOW_CREATE_FAILED;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		fprintf(stderr, "Failed to initialize GLAD\n");
		return GLAD_INIT_FAILED;
	}

	glEnable(GL_DEPTH_TEST);

	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

	const char *vertexShaderSource = load_shader(vertexShaderSource_path);
	const char *fragmentShaderSource = load_shader(fragmentShaderSource_path);

	unsigned int vertexShader = compile_vertex_shader(vertexShaderSource);
	unsigned int fragmentShader = compile_fragment_shader(fragmentShaderSource);
	unsigned int shaderProgram = create_shader_program(vertexShader, fragmentShader);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	float vertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};

	unsigned int VBO;
	unsigned int VAO;

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), NULL);
	glEnableVertexAttribArray(0);

	// texture attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// textures
	unsigned int texture1;
	glGenTextures(1, &texture1);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture1);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	make_texture(texture1_path, JPG_TEX);

	unsigned int texture2;
	glGenTextures(1, &texture2);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture2);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	make_texture(texture2_path, JPG_TEX);

	glUseProgram(shaderProgram);

	glUniform1i(glGetUniformLocation(shaderProgram, "texture1"), 0);
	glUniform1i(glGetUniformLocation(shaderProgram, "texture2"), 1);

	unsigned int mixAmount_uniform_location = glGetUniformLocation(shaderProgram, "mixAmount");
	float mix_amount = 0.4;

	unsigned int model_uniform_location = glGetUniformLocation(shaderProgram, "model");
	unsigned int view_uniform_location = glGetUniformLocation(shaderProgram, "view");
	unsigned int projection_uniform_location = glGetUniformLocation(shaderProgram, "projection");

	mat4 model;


	mat4 projection;
	glm_mat4_identity(projection);
	glm_perspective(GLM_PI_4, (float)WINDOW_WIDTH / WINDOW_HEIGHT, 0.1f, 100.0f, projection);
	glUniformMatrix4fv(projection_uniform_location, 1, GL_FALSE, (const float *)projection);

	vec3 cubePositions[] = {
		{ 0.0f,  0.0f,   0.0f},
		{ 2.0f,  5.0f, -15.0f},
		{-1.5f, -2.2f,  -2.5f},
		{-3.8f, -2.0f, -12.3f},
		{ 2.4f, -0.4f,  -3.5f},
		{-1.7f,  3.0f,  -7.5f},
		{ 1.3f, -2.0f,  -2.5f},
		{ 1.5f,  2.0f,  -2.5f},
		{ 1.5f,  0.2f,  -1.5f},
		{-1.3f,  1.0f,  -1.5f}
	};

	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		for (int i = 0; i < 10; i++) {
			glm_mat4_identity(model);
			glm_translate(model, cubePositions[i]);
			float angle = GLM_PI_4f * i;
			glm_rotate(model, angle, (vec3){1.0f, 0.5f, 0.3f});
			glUniformMatrix4fv(model_uniform_location, 1, GL_FALSE, (const float *)model);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
			mix_amount += 0.01;
			if (mix_amount > 1.0) {
				mix_amount = 1.0;
			}
		} else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
			mix_amount -= 0.01;
			if (mix_amount < 0.0) {
				mix_amount = 0.0;
			}
		}

		mat4 view;
		const float radius = 10.0f;
		float camX = sin(glfwGetTime()) * radius;
		float camZ = cos(glfwGetTime()) * radius;
		glm_lookat((vec3){camX, 0.0f, camZ}, (vec3){0.0f, 0.0f, 0.0f}, (vec3){0.0f, 1.0f, 0.0f}, view);
		glUniformMatrix4fv(view_uniform_location, 1, GL_FALSE, (const float *)view);

		glUniform1f(mixAmount_uniform_location, mix_amount);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
