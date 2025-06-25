#version 330 core

layout (location = 0) in vec3 pos_in;
layout (location = 1) in vec3 normal_in;

out vec3 normal;
out vec3 frag_pos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 view_pos;

void main() {
    gl_Position = projection * view * model * vec4(pos_in, 1.0f);
	normal		= mat3(transpose(inverse(model))) * normal_in;
	frag_pos	= vec3(model * vec4(pos_in, 1.0));
}
