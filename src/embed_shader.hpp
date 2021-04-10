
// Built file, do not edit manually

static const char *shader_frag = R""""(
#version 410

//uniform sampler2D myTextureSampler;

out vec4 color;

void main(void)
{
    //color = texture(myTextureSampler, UV).rgb;
    color = vec4(1, 1, 1, 1);
}
)"""";

static const char *shader_vert = R""""(
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
)"""";

