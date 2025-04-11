#version 330 core

layout (location = 0) in vec3 vPositionIn;
layout (location = 1) in vec3 vColorIn;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec4 vColor;
out vec3 ex_worldNormal;
out vec3 ex_worldPosition;
out mat4 normalMatrix;

void main()
{
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(vPositionIn, 1.0);
    vColor = vec4(vColorIn, 1.0);
    mat4 normalMatrix = transpose(inverse(modelMatrix));
    ex_worldNormal = vec3(normalMatrix * vec4(vColorIn, 1.0));
    ex_worldPosition = vec3(modelMatrix * vec4(vPositionIn, 1.0));
}