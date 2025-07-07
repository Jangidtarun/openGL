#version 330 core

out vec4 frag_color;

in vec2 tex_coord;

uniform sampler2D texture1;

void main() {
	vec4 tex_color = texture(texture1, tex_coord);
	if (tex_color.a < 0.1)
		discard;
	frag_color = tex_color;
}
