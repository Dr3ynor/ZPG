#version 330 core

//
// Created by jakub on 27.10.23.
//

layout (location = 0) in vec3 vp;
layout (location = 1) in vec3 vc;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec4 vColor;
out vec3 ex_worldPosition;
out vec3 ex_worldNormal;
out mat4 normalMatrix;

void main() {
    vColor = vec4(vc, 1.0);
    
    ex_worldPosition = vec3(modelMatrix * vec4(vp,1.0f));
    mat4 normalMatrix = transpose(inverse(modelMatrix));
    ex_worldNormal = vec3(normalMatrix * vec4(vc, 1.0f));
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(vp, 1.0);
}