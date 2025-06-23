#version 330 core

out vec4 frag_color;
in vec2 TexCoord;
uniform sampler2D texture1;
uniform vec3 light_color;

void main() {
	float ambient_strength	= 0.1;
	vec3 ambient	= ambient_strength * light_color;
    frag_color = texture(texture1, TexCoord) * vec4(ambient, 1.0f);
}
