#version 330 core

layout (location = 0) in vec3 pos_in;
layout (location = 1) in vec3 normal_in;
layout (location = 2) in vec2 tex_coord_in;

out vec2 tex_coord;
out vec3 result;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform vec3 light_pos;
uniform vec3 view_pos;
uniform vec3 light_color;

void main() {
    gl_Position = projection * view * model * vec4(pos_in, 1.0f);

	vec3 normal		= normalize(mat3(transpose(inverse(model))) * normal_in);
	vec3 frag_pos	= vec3(model * vec4(pos_in, 1.0f));

	float amb_strength	= 0.1f;
	float dif_strength	= 1.0f;
	float spe_strength	= 0.5f;
	float shininess		= 64.0f;

	vec3 light_dir	= normalize(light_pos - frag_pos);
	vec3 view_dir	= normalize(view_pos - frag_pos);
	vec3 reflection	= reflect(-light_dir, normal);

	vec3 ambient	= amb_strength * light_color;
	vec3 diffuse	= dif_strength * light_color * max(dot(light_dir, normal), 0.0f);
	vec3 specular	= spe_strength * light_color * pow(max(dot(view_dir, reflection), 0.0), shininess);

	result	= ambient + diffuse + specular;
    tex_coord	= tex_coord_in;
}
