#version 330 core

in vec3 ex_worldPosition;

uniform samplerCube textureSampler;

out vec4 fragColor;

void main() { 
    fragColor = texture(textureSampler, ex_worldPosition);
}