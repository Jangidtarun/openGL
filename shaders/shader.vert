#version 330 core

layout (location = 0) in vec3 pos_in;
layout (location = 1) in vec3 normal_in;
layout (location = 2) in vec2 tex_coord_in;

out vec2 tex_coord;
out vec3 normal;
out vec3 frag_pos;
out vec3 light_pos_;
	
uniform vec3 light_pos;
uniform vec3 view_pos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    gl_Position = projection * view * model * vec4(pos_in, 1.0f);
	normal		= mat3(transpose(inverse(view * model))) * normal_in;
	frag_pos	= vec3(view * model * vec4(pos_in, 1.0));
	light_pos_	= vec3(view * vec4(light_pos, 1.0));
    tex_coord	= tex_coord_in;
}
