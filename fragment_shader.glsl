// #version 330 core
#version 330 core

in vec3 vColor;
in vec3 ex_worldNormal;
in vec3 ex_worldPosition;
in mat4 normalMatrix;
in vec3 lightPosition;
in vec4 lightColor;
in vec4 specularColor;
in float specularStrength;
in float diffuseStrength;

out vec4 fragColor;

void main () {
	vec3 normal = normalize(ex_worldNormal);
	vec3 lightDirection = normalize(lightPosition - ex_worldPosition);
	vec3 reflectDirection = reflect(-lightDirection, normal);
	vec3 viewDirection = normalize(-ex_worldPosition);
	vec4 ambient = vec4(0.1, 0.1, 0.1, 1.0);
	float dot_product = max(dot(normal, lightDirection), 0.0);
	vec4 diffuse = dot_product * lightColor * diffuseStrength;
	float spec = pow(max(dot(reflectDirection, viewDirection), 0.0), 32);
	vec4 specular = specularStrength * spec * specularColor ;
	fragColor = (ambient + specular + diffuse) * vec4(vColor, 1.0f);
}
