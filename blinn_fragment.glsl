#version 330 core

//
// Created by jakub on 27.10.23.
//

in vec4 vColor;
in vec3 ex_worldPosition;
in vec3 ex_worldNormal;
in mat4 normalMatrix;

uniform vec3 lightPosition;
uniform vec4 lightColor;
uniform vec4 specularColor;
uniform float specularStrength;
uniform float diffuseStrength;
uniform vec3 cameraPosition;

out vec4 fragColor;

void main()
{
    vec3 norm = normalize(ex_worldNormal);
    vec3 lightDir = normalize(lightPosition - ex_worldPosition);
    vec3 viewDir = normalize(cameraPosition - ex_worldPosition);
    vec3 halfDir = normalize(lightDir + viewDir);
    float dot_product = max(dot(norm, lightDir), 0.0);
    float spec = pow(max(dot(norm, halfDir), 0.0), 32.0);
    vec4 specular = specularStrength * spec * specularColor;
    vec4 diffuse = dot_product * lightColor * diffuseStrength;
    vec4 ambient = vec4(0.09, 0.09, 0.09, 1.0);

    fragColor = (ambient + diffuse  + specular);
}
