#version 410

uniform sampler2D myTextureSampler;

in vec2 uv;
out vec4 color;

void main()
{
    color = vec4(texture(myTextureSampler, uv).rgb, 1);
    //color = vec4(1, 0, 1, 1);
}
