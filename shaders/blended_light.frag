#version 330 core

in vec3 Color;
in vec2 UV;
in vec3 Normal;
in vec3 FragPos;
in vec4 FragPosLightSpace;

uniform sampler2D textureSampler;
uniform sampler2D shadowMap;
uniform float colorTexRatio; //0.0f = full color, 1.0f = full texture

//Light
uniform vec3  camPos;
uniform vec3  lightPos;
uniform vec3  lightColor;
uniform float ambientStrength;
uniform float diffuseStrength;
uniform float specularStrength;
uniform float shinyCoeff;

out vec4 outColor;

float trueColorTexRatio = clamp(colorTexRatio, 0.0f, 1.0f);


float ShadowCalc(vec4 fragPosLightSpace)
{
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    projCoords = projCoords * 0.5 + 0.5;
    float closestDepth = texture(shadowMap, projCoords.xy).r;
    float currentDepth = projCoords.z;

    return currentDepth > closestDepth  ? 1.0 : 0.0;
}


void main() {

	vec3 objColor = trueColorTexRatio *          texture(textureSampler, UV).rgb
	              + (1.0f - trueColorTexRatio) * Color;

	//Ambient
	vec3 ambient = ambientStrength * lightColor;

    //Diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0f);
    vec3 diffuse = diffuseStrength * diff * lightColor;

    //Specular
    vec3 viewDir = normalize(camPos - FragPos);
    vec3 reflectDir = normalize(reflect(-lightDir, norm));
    float spec = pow(max(dot(viewDir, reflectDir), 0.0f), shinyCoeff);
    vec3 specular = specularStrength * spec * lightColor;

    //Shadow
    float shadow = ShadowCalc(FragPosLightSpace);

    outColor = vec4((ambient + (1.0f - shadow) * (diffuse + specular)) * objColor, 1.0f);
}
