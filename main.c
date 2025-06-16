#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

#define INFO_LOG_SIZE 512
#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 600


const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main() {\n"
    "   gl_Position = vec4(aPos, 1.0);\n"
    "}\0";


const char *fragmentShaderSource = "#version 330 core\n"
	"out vec4 fragColor;\n"
	"void main() {\n"
	"	fragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
	"}\0";


int main() {
	if (!glfwInit()) {
		fprintf(stderr, "Failed to initialize GLFW\n");
		return -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow *window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Win1", NULL, NULL);
	if (!window) {
		fprintf(stderr, "Failed to create GLFW window\n");
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		fprintf(stderr, "Failed to initialize GLAD\n");
		return -1;
	}

	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

	float vertices[] = {
		0.0f,  0.5f, 0.0f, // Top vertex
		-0.5f, -0.5f, 0.0f, // Bottom left vertex
		0.5f, -0.5f, 0.0f  // Bottom right vertex
	};

	GLuint VBO;
	GLuint VAO;

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	GLuint vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);

	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	int success;
	char infoLog[INFO_LOG_SIZE];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

	if (!success) {
		glGetShaderInfoLog(vertexShader, INFO_LOG_SIZE, NULL, infoLog);
		fprintf(stderr, "ERROR:SHADER:VERTEX:COMPILATION FAILED\n%s\n", infoLog);
	}

	GLuint fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

	if (!success) {
		glGetShaderInfoLog(fragmentShader, INFO_LOG_SIZE, NULL, infoLog);
		fprintf(stderr, "ERROR:SHADER:FRAGMENT:COMPILATION FAILED\n%s\n", infoLog);
	}

	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, INFO_LOG_SIZE, NULL, infoLog);
		fprintf(stderr, "ERROR:PROGRAM:SHADER:LINKING FAILED\n%s\n", infoLog);
	}

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), NULL);
	glEnableVertexAttribArray(0);

	glUseProgram(shaderProgram);

	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.2f, 0.3f, 0.3f, 0.2f);
		glClear(GL_COLOR_BUFFER_BIT);

		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
