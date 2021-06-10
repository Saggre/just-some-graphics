
// Built file, do not edit manually

static const char *shader_frag = R""""(
#version 410

uniform sampler2D myTextureSampler;

in vec2 uv;
out vec4 color;

void main()
{
    color = vec4(texture(myTextureSampler, uv).rgb, 1);
    //color = vec4(1, 0, 1, 1);
}
)"""";

static const char *shader_vert = R""""(
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
)"""";

