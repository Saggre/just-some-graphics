#version 410

in vec3 position;
in vec3 normal;
in vec2 texCoord;
out vec2 uv;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main()
{
    gl_Position = projection * view * model * vec4(position, 1.0);
    uv = texCoord;
}
