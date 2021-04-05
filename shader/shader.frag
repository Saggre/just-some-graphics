#version 410

uniform sampler2D myTextureSampler;

out vec4 color;

void main(void)
{
    color = texture(myTextureSampler, UV).rgb;
}
