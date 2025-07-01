#version 330 core

struct Material {
	sampler2D	diffuse;
	sampler2D	specular;
	sampler2D	emission;
	float		shininess;
};

struct PointLight {
	vec3	position;
	vec3	ambient;
	vec3	diffuse;
	vec3	specular;
};

struct DirectionalLight {
	vec3	direction;
	vec3	ambient;
	vec3	diffuse;
	vec3	specular;
};

out vec4 frag_color;

in vec2 tex_coord;
in vec3 normal;
in vec3 frag_pos;

uniform vec3 view_pos;

uniform	DirectionalLight light;
uniform Material material;

void main() {
	vec3 ambient	= light.ambient * vec3(texture(material.diffuse, tex_coord));

	vec3 norm		= normalize(normal);
	vec3 light_dir	= normalize(-light.direction);
	float diff		= max(dot(norm, light_dir), 0.0);
	vec3 diffuse	= light.diffuse * diff * vec3(texture(material.diffuse, tex_coord));

	vec3 view_dir	= normalize(view_pos - frag_pos);
	vec3 reflect_dir	= reflect(-light_dir, norm);
	float spec	= pow(max(dot(view_dir, reflect_dir), 0.0), 128.0f * material.shininess);
	vec3 specular	= light.specular * spec * vec3(texture(material.specular, tex_coord));

	vec3 emission = vec3(0.0f);
	if (texture(material.specular, tex_coord).r == 0.0) {
		emission	= vec3(texture(material.emission, tex_coord));
	}

	vec3 result	= ambient + diffuse + specular + emission;
	frag_color	= vec4(result, 1.0);
}
