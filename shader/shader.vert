#version 410

in vec3 vPosition;
in vec3 vNormal;
in vec2 vTexCoord;

out vec3 fPosition;// Fragment position
out vec2 fTexCoord;// Fragment UV coordinate
out vec3 fNormal;// Fragment surface normal
out vec3 fViewDir;// Direction from main camera to fragment

uniform float iTime;
uniform vec3 mainCameraPos;
uniform mat4 mProjection;
uniform mat4 mView;
uniform mat4 mModel;

void main()
{
    fViewDir = normalize(vPosition - mainCameraPos);
    fNormal = vNormal;
    fTexCoord = vTexCoord;
    fPosition = vPosition;

    gl_Position = mProjection * mView * mModel * vec4(vPosition, 1.0);
}
