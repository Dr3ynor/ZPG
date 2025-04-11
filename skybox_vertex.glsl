#version 330 core

layout (location = 0) in vec3 vp;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec3 ex_worldPosition;

void main() {
    vec4 position = modelMatrix * vec4(vp, 1.0);
    
    ex_worldPosition = position.xyz / position.w;
    
    gl_Position = (projectionMatrix * mat4(mat3(viewMatrix)) * modelMatrix) * vec4(vp, 1.0);
    // gl_Position = (projectionMatrix * viewMatrix * modelMatrix) * vec4(vp, 1.0);
}