#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader/shader.h"
#include "camera/camera.h"
#include "texture/texture.h"
#include "materials/materials.h"
#include "light/light.h"

// window settings
const unsigned int WINDOW_HEIGHT	= 750;
const unsigned int WINDOW_WIDTH		= 1000;
const float	ASPECT_RATIO			= (float) WINDOW_WIDTH / WINDOW_HEIGHT;
const char *WINDOW_TITLE			= "Lighting";

// shader file paths
const char *vshader_path	= "res/shaders/shader.vert";
const char *fshader_path	= "res/shaders/shader.frag";

// texture file paths
const char *diffuse_map_texture		= "res/textures/container2.png";
const char *specular_map_texture	= "res/textures/container2_specular.png";
const char *emission_map_texture	= "res/textures/matrix.jpg";

// camera
Camera cam;
bool mouse_first_in = true;
glm::vec2 mouse_last_loc(WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f);

// light source
SpotLight light = create_spot_light(cam.position,
	cam.front,
	12.0f,
	14.0f,
	glm::vec3(1.0f),
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

	unsigned int vshader_light_source	= compile_vertex_shader(vshader_light_source_path);
	unsigned int fshader_light_source	= compile_fragment_shader(fshader_light_source_path);
	unsigned int shader_program_light_source = create_shader_program(vshader_light_source, fshader_light_source);

	unsigned int diffuse_map;
	glGenTextures(1, &diffuse_map);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, diffuse_map);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_REPEAT);

	make_texture(diffuse_map_texture, PNG_TEX);

	unsigned int specular_map;
	glGenTextures(1, &specular_map);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, specular_map);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_REPEAT);

	make_texture(specular_map_texture, PNG_TEX);

	unsigned int emission_map;
	glGenTextures(1, &emission_map);

	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, emission_map);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_REPEAT);

	make_texture(emission_map_texture, JPG_TEX);

	float vertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f, 1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f, 0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f, 1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f, 0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f, 1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f, 1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f
	};

	glm::vec3 cubePositions[10];
	for (int i = 0; i < 10; i++) {
		float angle = i * (2 * M_PI / 10);
		float r = 2.0f;
		cubePositions[i] = glm::vec3(r * cos(angle), r * sin(angle), -2.0f);
	}


	unsigned int vao;
	unsigned int vbo;
	unsigned int light_vao;

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// layout (location = 0) position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);

	// layout (location = 1) normal
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// layout (location = 2) texture
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glGenVertexArrays(1, &light_vao);
	glBindVertexArray(light_vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	// layout (location = 0) position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);


	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.1, 0.1, 0.1, 1.0);
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
		light.position = cam.position;
		light.direction = cam.front;
		uniset_vec3(shader_program, "light.position",	light.position);
		uniset_vec3(shader_program, "light.direction",	light.direction);
		uniset_float(shader_program, "light.cutoff", glm::cos(glm::radians(light.cutoff_angle)));
		uniset_float(shader_program, "light.outer_cutoff", glm::cos(glm::radians(light.outer_cutoff_angle)));
		uniset_vec3(shader_program, "light.ambient",	light.ambient);
		uniset_vec3(shader_program, "light.diffuse",	light.diffuse);
		uniset_vec3(shader_program, "light.specular",	light.specular);
		uniset_float(shader_program, "light.kc", light.kc);
		uniset_float(shader_program, "light.kl", light.kl);
		uniset_float(shader_program, "light.kq", light.kq);

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
		// glUseProgram(shader_program_light_source);

		// model = glm::mat4(1.0f);
		// model = glm::translate(model, light.position);
		// model = glm::scale(model, glm::vec3(0.2f));

		// uniset_vec3(shader_program_light_source, "light_color", light.color);
		// uniset_mat4(shader_program_light_source, "model", model);
		// uniset_mat4(shader_program_light_source, "view", view);
		// uniset_mat4(shader_program_light_source, "projection", proj);

		// glBindVertexArray(light_vao);
		// glDrawArrays(GL_TRIANGLES, 0, 36);

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
