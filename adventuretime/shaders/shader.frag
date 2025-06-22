#version 330 core

uniform float board_size;
in vec2 tex_coord;
out vec4 frag_color;

void main() {
	float x	= floor(tex_coord.x * board_size);
	float y = floor(tex_coord.y * board_size);
	float checker	= mod(x + y, 2.0);
	vec3 color		= mix(vec3(0.0f), vec3(1.0f), checker);
	frag_color		= vec4(color, 1.0f);
}

