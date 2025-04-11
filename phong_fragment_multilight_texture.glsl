#version 330 core

// Input variables from vertex shader
in vec3 ex_worldPosition;
in vec3 ex_worldNormal;
in vec2 vTexture;

// Output variable to fragment shader
out vec4 fragColor;

// Structure for Point Light
struct PointLight {
	vec3 lightColor;
	vec3 position;
	float constant;
	float linear;
	float quadratic;
};

// Structure for Spot Light
struct SpotLight {
	vec3 lightColor;
	vec3 position;
	vec3 direction;
	float constant;
	float linear;
	float quadratic;
	float angle;
};

// Structure for Spot Camera Light
struct SpotLightCamera {
	vec3 lightColor;
	float constant;
	float linear;
	float quadratic;
	float angle;
};

// Structure for Directional Light
struct DirectionalLight {
	vec3 lightColor;
	vec3 direction;
};

// Uniform variables from the application
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

uniform sampler2D textureSampler;

// Function to calculate the diffuse reflection component
float calculateDiffuse(vec3 lightVector) {
    // Compute the dot product between the normalized light vector and the surface normal
    // The max function is used to ensure the result is clamped to a minimum of 0
    return max(dot(lightVector, ex_worldNormal), 0.0);
}

// Function to calculate the specular reflection component
float calculateSpecular(vec3 lightVector, vec3 cameraVector) {
    // Check if the light and normal vectors are pointing in the same direction
    if (dot(lightVector, ex_worldNormal) >= 0) {
        // Compute the reflection vector and then the dot product with the camera vector
        // The result is raised to the power of 32 to simulate a shiny, focused highlight
        return pow(max(dot(reflect(-lightVector, ex_worldNormal), cameraVector), 0.0), 16);
    } else {
        // If the light and normal vectors are not aligned, there is no specular reflection
        return 0.0f;
    }
}

// Function to calculate light attenuation based on distance
float calculateAttenuation(float distance, float constant, float linear, float quadratic) {
    // Compute attenuation using the specified quadratic, linear, and constant factors
    // A small constant term is added to avoid division by zero
    return 1.0 / (constant + linear * distance + quadratic * distance * distance + 0.001);
}

// Function to calculate the contribution of a point light
vec4 calculatePointLight(PointLight pointLight, vec3 cameraVector) {
    // Normalize the vector pointing from the fragment to the point light position
    vec3 lightVector = normalize(pointLight.position - ex_worldPosition);

    // Calculate the diffuse and specular contributions
    float diffuse = calculateDiffuse(lightVector);
    float specular = calculateSpecular(lightVector, cameraVector);

    // Calculate the distance between the fragment and the point light
    float distance = length(pointLight.position - ex_worldPosition);

    // Calculate the attenuation factor based on distance
    float attenuation = calculateAttenuation(distance, pointLight.constant, pointLight.linear, pointLight.quadratic);

    // Combine the diffuse and specular components, apply attenuation, and return the result
    return attenuation * (diffuse * vec4(pointLight.lightColor, 1.0) + specular * vec4(1.0, 1.0, 1.0, 1.0));
}

// Function to calculate the contribution of a spot light
vec4 calculateSpotLight(SpotLight spotLight, vec3 cameraVector) {
    // Calculate the vector from the fragment to the spot light position
    vec3 lightVector = normalize(spotLight.position - ex_worldPosition);

    // Calculate the cosine of the angle between the light direction and the light vector
    float theta = dot(lightVector, normalize(spotLight.direction));

    // Check if the fragment is within the spotlight cone
    if (theta > spotLight.angle) {
        // Calculate the diffuse and specular contributions
        float diffuse = calculateDiffuse(lightVector);
        float specular = calculateSpecular(lightVector, cameraVector);

        // Calculate the distance between the fragment and the spot light
        float distance = length(spotLight.position - ex_worldPosition);

        // Calculate the attenuation factor based on distance
        float attenuation = calculateAttenuation(distance, spotLight.constant, spotLight.linear, spotLight.quadratic);

        // Combine the diffuse and specular components, apply attenuation, and return the result
        return attenuation * (diffuse * vec4(spotLight.lightColor, 1.0) + specular * vec4(1.0, 1.0, 1.0, 1.0));
    }

    // If outside the spotlight cone, return a default value
    return texture(textureSampler, vTexture) * vec4(0.0);
}

// Function to calculate the contribution of a spotlight with camera properties
vec4 calculateSpotLightCamera(SpotLightCamera spotLightCamera, vec3 cameraVector) {
    // Calculate the vector from the fragment to the spotlight camera position
    vec3 lightVector = normalize(cameraPosition - ex_worldPosition);

    // Calculate the cosine of the angle between the light direction and the light vector
    float theta = dot(lightVector, normalize(-cameraDirection));

    // Check if the fragment is within the spotlight cone
    if (theta > spotLightCamera.angle) {
        // Calculate the diffuse and specular contributions
        float diffuse = calculateDiffuse(lightVector);
        float specular = calculateSpecular(lightVector, cameraVector);

        // Calculate the distance between the fragment and the spotlight camera
        float distance = length(cameraPosition - ex_worldPosition);

        // Calculate the attenuation factor based on distance
        float attenuation = calculateAttenuation(distance, spotLightCamera.constant, spotLightCamera.linear, spotLightCamera.quadratic);

        // Combine the diffuse and specular components, apply attenuation, and return the result
        return attenuation * (diffuse * vec4(spotLightCamera.lightColor, 1.0) + specular * vec4(1.0, 1.0, 1.0, 1.0));
    }

    // If outside the spotlight camera cone, return a default value
    return texture(textureSampler, vTexture) * vec4(0.0);
}


// Function to calculate the contribution of a directional light
vec4 calculateDirectionalLight(DirectionalLight directionalLight, vec3 cameraVector) {
    // Normalize the direction vector of the directional light
    vec3 lightVector = normalize(directionalLight.direction);

    // Calculate the diffuse and specular contributions
    float diffuse = calculateDiffuse(lightVector);
    // float specular = calculateSpecular(lightVector, cameraVector);

    // Combine the diffuse and specular components and return the result
    return diffuse * vec4(directionalLight.lightColor, 1.0); //+ specular * vec4(1.0, 1.0, 1.0, 1.0);
}

// Main function where the final color is computed
void main() {
    // Initialize variables to accumulate lighting contributions
    vec4 pointResult = vec4(0.0, 0.0f, 0.0f, 1.0f);
    vec4 spotResult = vec4(0.0f, 0.0f, 0.0f, 1.0f);
    vec4 spotLightCamResult = vec4(0.0f, 0.0f, 0.0f, 1.0f);
    vec4 directionalLightResult = vec4(0.0f, 0.0f, 0.0f, 1.0f);

    // Calculate the normalized vector from the fragment to the camera position
    vec3 cameraVector = normalize(cameraPosition - ex_worldPosition);

    // Calculate contributions from Point Lights
    for (int i = 0; i < numberOfPointLights; i++) {
        pointResult += calculatePointLight(pointLights[i], cameraVector);
    }

    // Calculate contributions from Spot Lights
    for (int i = 0; i < numberOfSpotLights; i++) {
        spotResult += calculateSpotLight(spotLights[i], cameraVector);
    }

    // Calculate contribution from Spot Light with Camera properties if enabled
    if (spotLightCamera_bool) {
        spotLightCamResult = calculateSpotLightCamera(spotLightCameraLight, cameraVector);
    }

    // Calculate contribution from Directional Light if enabled
    if (directionalLight_bool) {
        directionalLightResult = calculateDirectionalLight(directional, cameraVector);
    }

    // Ambient lighting intensity
    float ambient = 0.1f;

    // Combine all lighting contributions with texture color
    fragColor = texture(textureSampler, vTexture) * (directionalLightResult + pointResult + spotResult + spotLightCamResult + ambient);
}