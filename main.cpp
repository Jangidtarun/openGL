#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "camera/camera.h"
#include "model/model.h"

// window settings
const unsigned int WINDOW_HEIGHT	= 750;
const unsigned int WINDOW_WIDTH		= 1000;
const float	ASPECT_RATIO			= (float) WINDOW_WIDTH / WINDOW_HEIGHT;
const char *WINDOW_TITLE			= "Lighting";

// shader file paths
const char *vshader_path	= "res/shaders/shader.vert";
const char *fshader_path	= "res/shaders/shader.frag";

// camera
Camera cam;
bool mouse_first_in = true;
glm::vec2 mouse_last_loc(WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f);

// light source
SpotLight spot_light = create_spot_light(cam.position,
	cam.front,
	12.0f,
	14.0f,
	glm::vec3(0.0f, 1.0f, 0.0f),
	glm::vec3(0.1f),
	glm::vec3(1.0f),
	glm::vec3(1.0f));

PointLight point_light = create_point_light(glm::vec3(0.0f),
	glm::vec3(1.0f),
	glm::vec3(0.1f),
	glm::vec3(1.0f),
	glm::vec3(1.0f));

DirectionalLight dir_light = create_directional_light(glm::vec3(0.0f, 1.0f, 0.0f),
	glm::vec3(1.0, 0.702, 0.102),
	glm::vec3(0.1f),
	glm::vec3(1.0f),
	glm::vec3(1.0f));

const char *vshader_light_source_path	= "res/shaders/light_source.vert";
const char *fshader_light_source_path	= "res/shaders/light_source.frag";

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
	// cam.position	= glm::vec3(1.1f, 1.2f, 3.3f);
	// cam.up			= glm::normalize(glm::vec3(-0.086914f, 0.941746f, -0.3249f));
	// cam.front		= glm::normalize(glm::vec3(-0.167422f, -0.33530f, -0.9271f));

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glEnable(GL_DEPTH_TEST);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	unsigned int vshader	= compile_vertex_shader(vshader_path);
	unsigned int fshader	= compile_fragment_shader(fshader_path);
	unsigned int shader_program	= create_shader_program(vshader, fshader);

	Model backpack = init_model("res/models/backpack/backpack.obj");

	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.776, 0.494, 0.149, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		process_input(window);

		float curr_frame = static_cast<float>(glfwGetTime());
		delta_time	= curr_frame - last_frame;
		last_frame	= curr_frame;

		// container shader program
		glUseProgram(shader_program);

		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 view	= get_view_matrix(&cam);
		glm::mat4 proj	= glm::perspective(glm::radians(cam.zoom), ASPECT_RATIO, 0.1f, 100.0f);

		uniset_vec3(shader_program, "view_pos", cam.position);
		uniset_mat4(shader_program, "model", model);
		uniset_mat4(shader_program, "view", view);
		uniset_mat4(shader_program, "projection", proj);

		// set the material
		uniset_int(shader_program, "material.diffuse",	0);
		uniset_int(shader_program, "material.specular",	1);
		uniset_int(shader_program, "material.emission", 2);
		uniset_float(shader_program, "material.shininess",	gold.shininess);

		// set the light
		spot_light.position = cam.position;
		spot_light.direction = cam.front;

		point_light.position.z = 3 * sin(2 * glfwGetTime());

		set_spot_light_uniforms(shader_program, "spot_light", spot_light);
		set_point_light_uniforms(shader_program, "point_light", point_light);
		set_directional_light_uniforms(shader_program, "dir_light", dir_light);

		uniset_float(shader_program, "time", glfwGetTime());

		glBindVertexArray(vao);
		for (int i = 0; i < 10; i++) {
			model = glm::mat4(1.0f);
			model = glm::translate(model, cubePositions[i]);
			float angle = i * 2 * M_PI / 10;
			model = glm::rotate(model, angle, glm::vec3(0.0f, 0.0f, 1.0f));
			uniset_mat4(shader_program, "model", model);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		// light source shader program
		glUseProgram(shader_program_light_source);

		model = glm::mat4(1.0f);
		model = glm::translate(model, point_light.position);
		model = glm::scale(model, glm::vec3(0.2f));

		uniset_vec3(shader_program_light_source, "light_color", point_light.color);
		uniset_mat4(shader_program_light_source, "model", model);
		uniset_mat4(shader_program_light_source, "view", view);
		uniset_mat4(shader_program_light_source, "projection", proj);

		glBindVertexArray(light_vao);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteBuffers(1, &vbo);
	glDeleteVertexArrays(1, &vao);
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
