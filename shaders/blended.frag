#version 330 core

in vec3 Color;
in vec2 UV;

uniform sampler2D textureSampler;
uniform float colorTexRatio; //0.0f = full color, 1.0f = full texture

out vec3 outColor;

float trueColorTexRatio = clamp(colorTexRatio, 0.0f, 1.0f);

void main() {
	outColor = trueColorTexRatio *          texture(textureSampler, UV).rgb
	         + (1.0f - trueColorTexRatio) * Color;
}
