#version 330 core

layout (location = 0) in vec3 vp;
layout (location = 1) in vec3 vc;
layout (location = 2) in vec2 vt;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec3 ex_worldPosition;
out vec3 ex_worldNormal;
out vec2 vTexture;

void main() {    
    vec4 position = modelMatrix * vec4(vp, 1.0);
    ex_worldPosition = position.xyz / position.w;
    ex_worldNormal = normalize(transpose(inverse(mat3(modelMatrix))) * vc);
    gl_Position = (projectionMatrix * viewMatrix * modelMatrix) * vec4(vp, 1.0);
    vTexture = vt;
}