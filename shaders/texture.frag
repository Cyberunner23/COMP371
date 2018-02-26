#version 330 core

in vec2 UV;
out vec3 outColor;

uniform sampler2D textureSampler;

void main() {
	outColor = texture(textureSampler, UV).rgb;
}
