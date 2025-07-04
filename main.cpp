#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "camera/camera.h"
#include "model/model.h"
#include "colors/colors.h"

// window settings
const unsigned int WINDOW_HEIGHT	= 750;
const unsigned int WINDOW_WIDTH		= 1000;
const float	ASPECT_RATIO			= (float) WINDOW_WIDTH / WINDOW_HEIGHT;
const char *WINDOW_TITLE			= "Lighting";

// res file paths
const std::string vshader_path	= "res/shaders/shader.vert";
const std::string fshader_path	= "res/shaders/shader.frag";
const std::string backpack_file_path	= "res/models/backpack/backpack.obj";

// camera
Camera cam;
bool mouse_first_in = true;
glm::vec2 mouse_last_loc(WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f);

// animation
float delta_time = 0.0f;
float last_frame = 0.0f;

// prototypes
void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void process_input(GLFWwindow *window);
void mouse_callback(GLFWwindow *window, double xpos_in, double ypos_in);
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);

int main() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow *window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, NULL, NULL);
	if (!window) {
		std::cout << "Failed to create GLFW window\n";
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to init GLAD\n";
		glfwDestroyWindow(window);
		glfwTerminate();
		return -2;
	}

	cam = create_camera();

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glEnable(GL_DEPTH_TEST);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	unsigned int vshader = compile_vertex_shader(vshader_path);
	unsigned int fshader = compile_fragment_shader(fshader_path);
	unsigned int shader_program	= create_shader_program(vshader, fshader);

	Model backpack = init_model(backpack_file_path);

	while (!glfwWindowShouldClose(window)) {
		glClearColor(COLOR_BLACK);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		process_input(window);

		float curr_frame = static_cast<float>(glfwGetTime());
		delta_time	= curr_frame - last_frame;
		last_frame	= curr_frame;

		// container shader program
		glUseProgram(shader_program);

		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 view	= get_view_matrix(&cam);
		glm::mat4 proj	= glm::perspective(glm::radians(cam.zoom),
				ASPECT_RATIO, 0.1f, 100.0f);

		uniset_vec3(shader_program, "view_pos", cam.position);
		uniset_mat4(shader_program, "model", model);
		uniset_mat4(shader_program, "view", view);
		uniset_mat4(shader_program, "projection", proj);

		draw_model(&backpack, shader_program);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteProgram(shader_program);
	glfwDestroyWindow(window);
	glfwTerminate();
}


void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
	glViewport(0, 0, width, height);
}


void process_input(GLFWwindow *window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
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


void mouse_callback(GLFWwindow *window, double xpos_in, double ypos_in) {
	float xpos = static_cast<float>(xpos_in);
	float ypos = static_cast<float>(ypos_in);

	if (mouse_first_in) {
		mouse_last_loc = glm::vec2(xpos, ypos);
		mouse_first_in = false;
	}

	float xoffset = xpos - mouse_last_loc.x;
	float yoffset = mouse_last_loc.y - ypos;

	mouse_last_loc = glm::vec2(xpos, ypos);

	get_cam_mouse_input(&cam, xoffset, yoffset);
}


void scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
	get_cam_mouse_scroll(&cam, static_cast<float>(yoffset));
}
