#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 vertexColor;
layout (location = 2) in vec2 vertexUV;
layout (location = 3) in vec3 vertexNormal;

uniform mat4 MVP;
uniform mat4 MM; //Model Matrix
uniform mat4 ShadowMVP;

out vec3 Color;
out vec2 UV;
out vec3 Normal;
out vec3 FragPos;
out vec4 FragPosShadow;

void main() {
	gl_Position = MVP * vec4(position, 1.0);
	FragPosShadow = ShadowMVP * vec4(position, 1.0f);
	Color = vertexColor;
	UV = vertexUV;
	Normal = vec3(MM * vec4(vertexNormal, 0.0f));
	FragPos = vec3(MM * vec4(position, 1.0f));
}
