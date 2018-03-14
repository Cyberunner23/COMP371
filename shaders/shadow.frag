#version 330 core

out vec4 outColor;

void main() {

    if (true)
    {
        outColor = vec4(vec3(gl_FragCoord.z), 1.0f);
    }

}
