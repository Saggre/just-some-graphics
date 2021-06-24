#version 410
#define M_PI 3.1415926535897932384626433832795

uniform float iTime;
uniform sampler2D myTextureSampler;
uniform vec3 mainCameraPos;

in vec3 fPosition;
in vec2 fTexCoord;
in vec3 fNormal;
in vec3 fViewDir;

layout(location = 0) out vec4 fColor;

vec3 clamp01(vec3 x) {
    return clamp(x, 0, 1);
}

void main() {
    vec3 lightPos = vec3(0, 10, 0);
    vec3 lightDir = normalize(lightPos - fPosition);
    vec3 halfwayDir = normalize(lightDir + fViewDir);

    float shininess = 4.0;
    vec3 lightColor = vec3(1, 1, 1);
    float spec = pow(max(dot(fNormal, halfwayDir), 0.0), shininess);
    vec3 specular = lightColor * spec;

    fColor = vec4(clamp01(texture(myTextureSampler, fTexCoord).rgb + specular), 1);
    // fColor = vec4(specular, 1);
    // fColor = vec4(fNormal, 1);
}
