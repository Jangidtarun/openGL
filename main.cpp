#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

#include "camera.h"
#include "texture.h"
#include "shader.h"
#include "error_codes.h"

// settings
const unsigned int WINDOW_WIDTH		= 800;
const unsigned int WINDOW_HEIGHT	= 600;

// camera
CAMERA cam;
bool first_mouse	= true;
float mouse_last_x	= WINDOW_WIDTH / 2.0f;
float mouse_last_y	= WINDOW_HEIGHT / 2.0f;

// timing
float delta_time = 0.0f;
float last_frame = 0.0f;

// filepath constants
const char *vertexShaderSource_path = "shaders/shader.vert";
const char *fragmentShaderSource_path = "shaders/shader.frag";
const char *texture1_path = "textures/img1.jpeg";
const char *texture2_path = "textures/img3.jpeg";

// prototypes
void processInput(GLFWwindow *window);
void mouse_callback(GLFWwindow *window, double xpos, double ypos);
void mouse_scroll_callback(GLFWwindow *window, double xoffset, double yoffset);
GLFWwindow *create_window(const unsigned int width, const unsigned int height, const char *title);
void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void enable_glfw_params();
bool init_opengl();


int main() {

	if (!init_opengl()) {
		return GLFW_INIT_FAILED;
	}

	GLFWwindow *window = create_window(WINDOW_WIDTH, WINDOW_HEIGHT, "LearnOpenGL");
	if (!window) {
		return GLFW_WINDOW_CREATE_FAILED;
	}

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD\n";
		return GLAD_INIT_FAILED;
	}

	cam = create_camera();

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	enable_glfw_params();

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

	glm::vec3 cubePositions[] = {
		glm::vec3( 0.0f,  0.0f,   0.0f),
		glm::vec3( 2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f,  -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3( 2.4f, -0.4f,  -3.5f),
		glm::vec3(-1.7f,  3.0f,  -7.5f),
		glm::vec3( 1.3f, -2.0f,  -2.5f),
		glm::vec3( 1.5f,  2.0f,  -2.5f),
		glm::vec3( 1.5f,  0.2f,  -1.5f),
		glm::vec3(-1.3f,  1.0f,  -1.5f)
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

	// texture 1
	unsigned int texture1;
	glGenTextures(1, &texture1);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture1);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	make_texture(texture1_path, JPG_TEX);

	// texture 2
	unsigned int texture2;
	glGenTextures(1, &texture2);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture2);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	make_texture(texture2_path, JPG_TEX);

	// tell OPENGL for each sample to which texutre unit it belongs to (only has to be done once)
	glUseProgram(shaderProgram);
	glUniform1i(glGetUniformLocation(shaderProgram, "texture1"), 0);
	glUniform1i(glGetUniformLocation(shaderProgram, "texture2"), 1);

	unsigned int mixAmount_uniform_location = glGetUniformLocation(shaderProgram, "mixAmount");
	float mix_amount = 0.4;
	glUniform1f(mixAmount_uniform_location, mix_amount);

	unsigned int model_uniform_location = glGetUniformLocation(shaderProgram, "model");
	unsigned int view_uniform_location = glGetUniformLocation(shaderProgram, "view");
	unsigned int projection_uniform_location = glGetUniformLocation(shaderProgram, "projection");

	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.1f, 0.7f, 0.9f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		processInput(window);

		float current_frame = static_cast<float>(glfwGetTime());
		delta_time = current_frame - last_frame;
		last_frame = current_frame;

		glm::mat4 projection = glm::perspective(glm::radians(cam.zoom), 
				(float) WINDOW_WIDTH / WINDOW_HEIGHT, 0.1f, 100.0f);
		glUniformMatrix4fv(projection_uniform_location, 1, GL_FALSE, glm::value_ptr(projection));

		glm::mat4 view = get_view_matrix(&cam);
		glUniformMatrix4fv(view_uniform_location, 1, GL_FALSE, glm::value_ptr(view));

		for (int i = 0; i < 10; i++) {
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, cubePositions[i]);
			float angle = 20.0f * i;
			model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			glUniformMatrix4fv(model_uniform_location, 1, GL_FALSE, glm::value_ptr(model));

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

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


void mouse_scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
	get_cam_mouse_scroll(&cam, static_cast<float>(yoffset));
}


void mouse_callback(GLFWwindow *window, double xpos_in, double ypos_in) {
	float xpos = static_cast<float>(xpos_in);
	float ypos = static_cast<float>(ypos_in);
	
	if (first_mouse) {
		mouse_last_x = xpos;
		mouse_last_y = ypos;
		first_mouse = false;
	}

	float xoffset = xpos - mouse_last_x;
	float yoffset = mouse_last_y - ypos;

	mouse_last_x = xpos;
	mouse_last_y = ypos;

	get_cam_mouse_input(&cam, xoffset, yoffset);
}


void processInput(GLFWwindow *window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, 1);
	}

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		get_cam_keyboard_input(&cam, FORWARD, delta_time);
	} else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		get_cam_keyboard_input(&cam, BACKWARD, delta_time);
	} else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		get_cam_keyboard_input(&cam, LEFT, delta_time);
	} else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		get_cam_keyboard_input(&cam, RIGHT, delta_time);
	}
}


GLFWwindow *create_window(const unsigned int width, const unsigned int heigt, const char *title) {
	GLFWwindow *window = glfwCreateWindow(width, heigt, title, nullptr, nullptr);
	if (!window) {
		std::cout << "Failed to create GLFW window\n";
		glfwTerminate();
	} else {
		glfwMakeContextCurrent(window);
		glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
		glfwSetCursorPosCallback(window, mouse_callback);
		glfwSetScrollCallback(window, mouse_scroll_callback);
	}

	return window;
}


void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
	glViewport(0, 0, width, height);
}


bool init_opengl() {
	if (!glfwInit()) {
		std::cout << "Failed to initialize GLFW\n";
		return GL_FALSE;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	return GL_TRUE;
}


void enable_glfw_params() {
	glEnable(GL_DEPTH_TEST);
}
