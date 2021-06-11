
// Built file, do not edit manually

static const char *shader_frag = R""""(
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
)"""";

static const char *shader_vert = R""""(
#version 410

in vec3 vPosition;
in vec3 vNormal;
in vec2 vTexCoord;

out vec2 fTexCoord;// Fragment UV coordinate
out vec3 fNormal;// Fragment surface normal
out vec3 fViewDir;// Direction from main camera to fragment

uniform vec3 mainCameraPos;
uniform mat4 mProjection;
uniform mat4 mView;
uniform mat4 mModel;
uniform mat4 mNormal;

void main()
{
    fNormal = vec3(mNormal * vec4(vNormal, 0.0));
    fViewDir = normalize(vPosition - mainCameraPos);
    fTexCoord = vTexCoord;

    gl_Position = mProjection * mView * mModel * vec4(vPosition, 1.0);
}
)"""";

