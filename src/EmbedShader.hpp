
// Built file, do not edit manually

static const char *shader_frag = R""""(
#version 410

in vec4 fPosition;
in vec4 fColor;
in vec4 fLightPosition;
in vec3 fNormal;

// output
out vec4 color;

void main(void)
{
    vec3 o =-normalize(fPosition.xyz);
    vec3 n = normalize(fNormal);
    vec3 r = reflect(o, n);
    vec3 l = normalize(fLightPosition.xyz-fPosition.xyz);

    float ambient = 0.1;
    float diffus = 0.7*max(0.0, dot(n, l));
    float specular = 0.6*pow(max(0.0, -dot(r, l)), 4.0);

    color = fColor * (ambient + diffus + specular);

    /*color = vec3(1,0,0);*/
}
)"""";

static const char *shader_vert = R""""(
#version 410

in vec3 position;
in vec3 normal;
in vec4 color;

uniform mat4 projection;
uniform mat4 view;

out vec4 fPosition;
out vec4 fColor;
out vec4 fLightPosition;
out vec3 fNormal;

void main(void)
{
    fPosition = view * vec4(position, 1.0);
    fLightPosition = view * vec4(0.0, 0.0, 1.0, 1.0);

    fColor = color;
    fNormal = vec3(view * vec4(normal, 0.0));

    gl_Position = projection * fPosition;
    /*gl_Position.x *= 1000.0f;*/
    /*gl_Position.y = 0.0;*/
}
)"""";

