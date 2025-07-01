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

struct SpotLight {
	vec3	position;
	vec3	direction;
	float	cutoff;
	float	outer_cutoff;
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

uniform DirectionalLight dir_light;
uniform SpotLight spot_light;
uniform PointLight point_light;
uniform Material material;
uniform float time;


vec3 calculate_dir_light(DirectionalLight _light, vec3 _normal, vec3 _view_dir) {
	vec3 ambient	= _light.ambient * vec3(texture(material.diffuse, tex_coord));

	vec3 light_dir	= normalize(_light.direction);
	float diff		= max(dot(_normal, light_dir), 0.0);
	vec3 diffuse	= _light.diffuse * diff * vec3(texture(material.diffuse, tex_coord));

	vec3 reflect_dir	= reflect(-light_dir, _normal);
	float spec	= pow(max(dot(_view_dir, reflect_dir), 0.0), 128.0f * material.shininess);
	vec3 specular	= _light.specular * spec * vec3(texture(material.specular, tex_coord));

	return ambient + diffuse + specular;
}


vec3 calculate_spot_light(SpotLight _light, vec3 _normal, vec3 _frag_pos, vec3 _view_dir) {
	vec3 ambient	= _light.ambient * vec3(texture(material.diffuse, tex_coord));

	vec3 light_dir	= normalize(_light.position - _frag_pos);
	float diff		= max(dot(_normal, light_dir), 0.0);
	vec3 diffuse	= _light.diffuse * diff * vec3(texture(material.diffuse, tex_coord));

	vec3 reflect_dir	= reflect(-light_dir, _normal);
	float spec	= pow(max(dot(_view_dir, reflect_dir), 0.0), 128.0f * material.shininess);
	vec3 specular	= _light.specular * spec * vec3(texture(material.specular, tex_coord));

	float distance 	= length(_light.position - _frag_pos);
	float attenuation = 1.0 / (_light.kc + _light.kl * distance + _light.kq * distance * distance);
	float epsilon	= _light.cutoff - _light.outer_cutoff;
	float theta		= dot(light_dir, normalize(-_light.direction));
	float intensity	= clamp((theta - _light.outer_cutoff) / epsilon, 0.0, 1.0);

	return ambient + (diffuse + specular) * intensity * attenuation;
}

vec3 calculate_point_light(PointLight _light, vec3 _normal, vec3 _frag_pos, vec3 _view_dir) {
	vec3 ambient	= _light.ambient * vec3(texture(material.diffuse, tex_coord));

	vec3 light_dir	= normalize(_light.position - _frag_pos);
	float diff		= max(dot(_normal, light_dir), 0.0);
	vec3 diffuse	= _light.diffuse * diff * vec3(texture(material.diffuse, tex_coord));

	vec3 reflect_dir	= reflect(-light_dir, _normal);
	float spec	= pow(max(dot(_view_dir, reflect_dir), 0.0), 128.0f * material.shininess);
	vec3 specular	= _light.specular * spec * vec3(texture(material.specular, tex_coord));

	float distance 	= length(_light.position - _frag_pos);
	float attenuation = 1.0 / (_light.kc + _light.kl * distance + _light.kq * distance * distance);

	return ambient + (diffuse + specular) * attenuation;
}

void main() {
	vec3 emission = vec3(0.0f);
	if (texture(material.specular, tex_coord).r == 0.0) {
		emission = vec3(texture(material.emission, tex_coord)) * vec3(0.1f);
	}

	vec3 result = vec3(0.0f);
	result += calculate_spot_light(spot_light, normalize(normal), frag_pos, normalize(view_pos - frag_pos));
	result += calculate_point_light(point_light, normalize(normal), frag_pos, normalize(view_pos - frag_pos));
	result += calculate_dir_light(dir_light, normalize(normal), normalize(view_pos - frag_pos));

	frag_color	= vec4(result, 1.0);
}
