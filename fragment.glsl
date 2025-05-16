#version 330 core

out vec4 FragColor;
in vec3 ourColor;
in vec3 vposition;

void main() {
	FragColor = vec4(vposition, 1.0f);
}
