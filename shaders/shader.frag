#version 330 core

out vec4 frag_color;

in vec2 tex_coord;
in vec3 result;

uniform sampler2D texture1;

void main() {
	vec3 obj_color	= vec3(1.0, 0.5, 0.3);
	frag_color	= vec4(result * obj_color, 1.0);
    // frag_color = texture(texture1, tex_coord) * vec4(result, 1.0f);
}
