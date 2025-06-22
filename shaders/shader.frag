#version 330 core

out vec4 frag_color;
in vec2 TexCoord;
uniform sampler2D texture1;
uniform vec3 light_color;

void main() {
    frag_color = texture(texture1, TexCoord) * vec4(light_color, 1.0f);
}
