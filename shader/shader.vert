#version 410

in vec3 position;
in vec3 normal;
in vec2 texCoord;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main(void)
{
    gl_Position =  projection * view * model * vec4(position, 1.0);
}
