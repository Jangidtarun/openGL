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

	float kc, kl, kq;
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

uniform PointLight light;
uniform Material material;
uniform float time;

void main() {
	float distance 	= length(light.position - frag_pos);
	float attenuation = 1.0 / (light.kc + light.kl * distance + light.kq * distance * distance);

	vec3 ambient	= light.ambient * vec3(texture(material.diffuse, tex_coord));

	vec3 norm		= normalize(normal);
	vec3 light_dir	= normalize(light.position - frag_pos);
	float diff		= max(dot(norm, light_dir), 0.0);
	vec3 diffuse	= light.diffuse * diff * vec3(texture(material.diffuse, tex_coord));

	vec3 view_dir	= normalize(view_pos - frag_pos);
	vec3 reflect_dir	= reflect(-light_dir, norm);
	float spec	= pow(max(dot(view_dir, reflect_dir), 0.0), 128.0f * material.shininess);
	vec3 specular	= light.specular * spec * vec3(texture(material.specular, tex_coord));

	vec3 emission = vec3(0.0f);
	if (texture(material.specular, tex_coord).r == 0.0) {
		emission = vec3(texture(material.emission, tex_coord)) * vec3(2.0f) * (sin(time) + 1.0f);
	}

	vec3 result	= ambient + (diffuse + specular) * attenuation + emission;
	frag_color	= vec4(result, 1.0);
}
