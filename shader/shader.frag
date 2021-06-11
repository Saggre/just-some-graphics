#version 410

uniform sampler2D myTextureSampler;
uniform vec3 mainCameraPos;

in vec2 fTexCoord;
in vec3 fNormal;
in vec3 fViewDir;

layout(location = 0) out vec4 fColor;

void main() {
    fColor = vec4(texture(myTextureSampler, fTexCoord).rgb, 1);
}
