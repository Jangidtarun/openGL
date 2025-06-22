#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "../shader.h"

const unsigned int WIN_WIDTH	= 600;
const unsigned int WIN_HEIGHT	= 600;
const char *WIN_TITLE = "3D World";

const char *vshader_path	= "shaders/shader.vert";
const char *fshader_path	= "shaders/shader.frag";


// prototypes
void process_input(GLFWwindow *window);
void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
	glViewport(0, 0, width, height);
}


int main() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow *window = glfwCreateWindow(WIN_WIDTH, WIN_HEIGHT, WIN_TITLE, nullptr, nullptr);
	if (!window) {
		std::cout << "Failed to crate window\n";
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initiate GLAD\n";
		return -1;
	}

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	unsigned int vshader = compile_vertex_shader(vshader_path);
	unsigned int fshader = compile_fragment_shader(fshader_path);
	unsigned int shader_program = create_shader_program(vshader, fshader);

	float vertices[] = {
		-0.5f,  0.5f, 0.0f, 0.0f,  1.0f,
		 0.5f,  0.5f, 0.0f, 1.0f,  1.0f,
		 0.5f, -0.5f, 0.0f, 1.0f,  0.0f,
		-0.5f, -0.5f, 0.0f, 0.0f,  0.0f
	};

	unsigned int indices[] = {
		0, 1, 2,
		0, 2, 3
	};


	unsigned int VAO, VBO;
	unsigned int EBO;

	// generate and bind vbo
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// generate and bind vao
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// generate and bind ebo
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// location = 0 (position attribute)
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glUseProgram(shader_program);

	unsigned int board_size_uniloc = glGetUniformLocation(shader_program, "board_size");
	glUniform1f(board_size_uniloc, 8.0f);

	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.1f, 0.7f, 0.8f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		process_input(window);

		// glDrawArrays(GL_TRIANGLES, 0, 4);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
		
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
}


void process_input(GLFWwindow *window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}
