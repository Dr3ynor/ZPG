#version 330 core

in vec3 ex_worldPosition;
in vec3 ex_worldNormal;

out vec4 fragColor;

struct PointLight {
	vec3 lightColor;
	vec3 position;
	float constant;
	float linear;
	float quadratic;
};

struct SpotLight {
	vec3 lightColor;
	vec3 position;
	vec3 direction;
	float constant;
	float linear;
	float quadratic;
	float angle;
};

struct SpotLightCamera {
	vec3 lightColor;
	float constant;
	float linear;
	float quadratic;
	float angle;
};

struct DirectionalLight {
	vec3 lightColor;
	vec3 direction;
};

uniform vec3 cameraPosition;
uniform vec3 cameraDirection;

uniform int numberOfPointLights;
uniform PointLight pointLights[5];

uniform int numberOfSpotLights;
uniform SpotLight spotLights[5];

uniform bool spotLightCamera_bool = false;
uniform SpotLightCamera spotLightCameraLight;

uniform bool directionalLight_bool = false;
uniform DirectionalLight directional;


float calculateDiffuse(vec3 lightVector)
{
	return max(dot(lightVector, ex_worldNormal), 0.0);
}

float calculateSpecular(vec3 lightVector, vec3 cameraVector)
{
	// Check if the light and normal vectors are pointing in the same direction
	if (dot(lightVector, ex_worldNormal) >= 0)
	{
		return pow(max(dot(reflect(-lightVector, ex_worldNormal), cameraVector), 0.0), 32);
	} else {
		// If the light and normal vectors are not aligned, there is no specular reflection
		return 0.0f;
	}
}

float calculateAttenuation(float distance, float constant, float linear, float quadratic)
{
	return 1.0 / (constant + linear * distance + quadratic * distance * distance);
}

vec4 calculatePointLight(PointLight pointLight, vec3 cameraVector)
{
	vec3 lightVector = normalize(pointLight.position - ex_worldPosition);

	float diffuse = calculateDiffuse(lightVector);
	float specular = calculateSpecular(lightVector, cameraVector);

	float distance = length(pointLight.position - ex_worldPosition);
	float attenuation = calculateAttenuation(distance, pointLight.constant, pointLight.linear, pointLight.quadratic);

	return attenuation * (diffuse * vec4(pointLight.lightColor, 1.0) + specular * vec4(1.0, 1.0, 1.0, 1.0));

}

vec4 calculateSpotLight(SpotLight spotLight, vec3 cameraVector)
{
	vec3 lightPosition = spotLight.position;
	vec3 lightVector = normalize(lightPosition - ex_worldPosition);

	float theta = dot(lightVector, normalize(spotLight.direction));

	// Check if the fragment is within the spotlight cone
	if (theta > spotLight.angle)
	{
		float diffuse = calculateDiffuse(lightVector);
		float specular = calculateSpecular(lightVector, cameraVector);
		float distance = length(spotLight.position - ex_worldPosition);
		float attenuation = calculateAttenuation(distance, spotLight.constant, spotLight.linear, spotLight.quadratic);

		return attenuation * (diffuse * vec4(spotLight.lightColor, 1.0) + specular * vec4(1.0, 1.0, 1.0, 1.0));
	}

	// If the fragment is outside the spotlight cone, return default
	return vec4(0.0);
}


vec4 calculateSpotLightCamera(SpotLightCamera spotLightCamera, vec3 cameraVector)
{
	vec3 lightPosition = cameraPosition;
	vec3 lightVector = normalize(lightPosition - ex_worldPosition);

	float theta = dot(lightVector, normalize(-cameraDirection));

	// Check if the fragment is within the spotlight cone
	if (theta > spotLightCamera.angle)
	{       
		float diffuse = calculateDiffuse(lightVector);
		float specular = calculateSpecular(lightVector, cameraVector);
		float distance = length(cameraPosition - ex_worldPosition);
		float attenuation = calculateAttenuation(distance, spotLightCamera.constant, spotLightCamera.linear, spotLightCamera.quadratic);

		return attenuation * (diffuse * vec4(spotLightCamera.lightColor, 1.0) + specular * vec4(1.0, 1.0, 1.0, 1.0));
	}

	// If the fragment is outside the spotlight camera cone, return default
	return vec4(0.0);
}

vec4 calculateDirectionalLight(DirectionalLight directionalLight, vec3 cameraVector)
{
	vec3 lightVector = normalize(directionalLight.direction);
	float diffuse = calculateDiffuse(lightVector);
	float specular = calculateSpecular(lightVector, cameraVector);

	return diffuse * vec4(directionalLight.lightColor, 1.0) + specular * vec4(1.0, 1.0, 1.0, 1.0);
}

void main() {
	vec4 pointResult = vec4(0.0, 0.0f, 0.0f, 1.0f);
	vec4 spotResult = vec4(0.0f, 0.0f, 0.0f, 1.0f);
	vec4 spotLightCamResult = vec4(0.0f, 0.0f, 0.0f, 1.0f);
	vec4 directionalLightResult = vec4(0.0f, 0.0f, 0.0f, 1.0f);
	
	vec3 cameraVector = normalize(cameraPosition - ex_worldPosition);
	

	for(int i = 0; i < numberOfPointLights; i++)
	{
		pointResult += calculatePointLight(pointLights[i], cameraVector);
	}

	for(int i = 0; i < numberOfSpotLights; i++)
	{
		spotResult += calculateSpotLight(spotLights[i], cameraVector);
	}
	
	if (spotLightCamera_bool)
	{
		spotLightCamResult = calculateSpotLightCamera(spotLightCameraLight, cameraVector);
	}

	if (directionalLight_bool)
	{
		directionalLightResult = calculateDirectionalLight(directional, cameraVector);
	}

	float ambient = 0.1f;

	fragColor = directionalLightResult + pointResult + spotResult + spotLightCamResult + ambient;
}
