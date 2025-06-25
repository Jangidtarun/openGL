#version 330 core

out vec4 frag_color;

in vec3 normal;
in vec3 frag_pos;

uniform vec3 light_color;
uniform vec3 light_pos;
uniform vec3 view_pos;

void main() {
	const float ambient_strength	= 0.1;
	vec3 ambient					= ambient_strength * light_color;

	vec3 norm		= normalize(normal);
	vec3 light_dir	= normalize(light_pos - frag_pos);
	vec3 diffuse	= max(dot(norm, light_dir), 0.0) * light_color;

	const float specular_strength	= 0.5;
	const float shininess	= 32;
	vec3 view_dir			= normalize(view_pos - frag_pos);
	vec3 reflect_dir		= reflect(-light_dir, norm);
	float spec				= pow(max(dot(view_dir, reflect_dir), 0.0), shininess);
	vec3 specular			= specular_strength * spec * light_color;

	vec3 result	= ambient + diffuse + specular;

	vec3 obj_color	= vec3(1.0, 0.3, 0.3);
	frag_color		= vec4(result * obj_color, 1.0);
}
