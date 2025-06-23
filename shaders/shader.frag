#version 330 core

out vec4 frag_color;

in vec2 tex_coord;
in vec3 normal;
in vec3 frag_pos;

uniform sampler2D texture1;
uniform vec3 light_color;
uniform vec3 light_pos;

void main() {
	float ambient_strength	= 0.1;
	vec3 ambient	= ambient_strength * light_color;

	vec3 norm	= normalize(normal);
	vec3 light_dir	= normalize(light_pos - frag_pos);
	vec3 diffuse	= max(dot(norm, light_dir), 0.0) * light_color;

	vec3 result	= ambient + diffuse;

    frag_color = texture(texture1, tex_coord) * vec4(result, 1.0f);
}
