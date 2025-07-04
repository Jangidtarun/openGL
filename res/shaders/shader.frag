#version 330 core

out vec4 frag_color;

in vec3 frag_pos;
in vec3 normal;
in vec2 tex_coord;

struct PointLight {
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float kc;
	float kl;
	float kq;
};

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;
uniform vec3 view_pos;
uniform PointLight plight;

vec3 calculate_point_light(PointLight _light, vec3 _normal, vec3 _frag_pos, 
		vec3 _view_dir) {
	vec3 ambient	= _light.ambient * vec3(texture(texture_diffuse1, 
				tex_coord));

	vec3 light_dir	= normalize(_light.position - _frag_pos);
	float diff		= max(dot(_normal, light_dir), 0.0);
	vec3 diffuse	= _light.diffuse * diff * vec3(texture(texture_diffuse1, 
				tex_coord));

	vec3 reflect_dir	= reflect(-light_dir, _normal);
	float spec	= pow(max(dot(_view_dir, reflect_dir), 0.0), 128.0f * 32);
	vec3 specular	= _light.specular * spec * vec3(texture(texture_specular1, 
				tex_coord));

	float distance 	= length(_light.position - _frag_pos);
	float attenuation = 1.0 / (_light.kc + _light.kl * distance + 
			_light.kq * distance * distance);

	return ambient + (diffuse + specular) * attenuation;
}

void main() {
	vec3 result = calculate_point_light(plight, normalize(normal), 
			frag_pos, normalize(view_pos - frag_pos));
	frag_color = vec4(result, 1.0f);
}
