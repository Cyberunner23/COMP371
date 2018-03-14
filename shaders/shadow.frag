#version 330 core

layout (location = 0) out vec4 outColor;

void main() {

    if (false)
    {
        outColor = vec4(vec3(gl_FragCoord.z), 1.0f);
    }

}
