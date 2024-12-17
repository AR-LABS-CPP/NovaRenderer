#version 460 core

out vec4 FragColor;

#define NR_POINT_LIGHTS 40
#define NR_SPOT_LIGHTS 40

struct Material {
    float shininess;
};

struct DirectionalLight {
    vec3 color;
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight {
    vec3 position;
    vec3 color;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    
    float constant;
    float linear;
    float quadratic;
};

struct SpotLight {
    vec3 position;
    vec3 direction;
    vec3 color;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float cutOff;
    float outerCutOff;

    float constant;
    float linear;
    float quadratic;
};

in vec2 TexCoords;
in vec3 Normal;
in vec3 Tangent;
in vec3 BiTangent;
in mat3 TBNMatrix;
in vec3 FragPos;
in vec4 FragPosLightSpace;

uniform sampler2D diffuseTexture;
uniform sampler2D shadowMap;

uniform Material material;

uniform vec3 viewerPos;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;
uniform sampler2D texture_normal1;

uniform DirectionalLight directionalLight;
uniform PointLight pointLights[NR_POINT_LIGHTS];
uniform SpotLight spotLights[NR_SPOT_LIGHTS];

uniform int nPointLights;
uniform int nSpotLights;
uniform int directionalLightActive;

uniform bool hasTexture;

vec3 calculateDirectionalLight(
    DirectionalLight directionaLight,
    vec3 normal,
    vec3 viewerDir
);

vec3 calculatePointLight(
    PointLight light,
    vec3 normal,
    vec3 fragPos,
    vec3 viewerDir
);

vec3 calculateSpotLight(
    SpotLight light,
    vec3 normal,
    vec3 fragPos,
    vec3 viewerDir
);

float calculateShadow(
    vec4 fragPosLightSpace
);

void main() {
    vec3 norm = Normal;
    vec3 viewDir = normalize(viewerPos - FragPos);

    vec3 result = vec3(0.0);

    if(directionalLightActive == 1) {
        result += calculateDirectionalLight(directionalLight, norm, viewDir);
    }

    if(nSpotLights > 0) {
        for(int idx = 0; idx < nSpotLights; idx++) {
            result += calculateSpotLight(spotLights[idx], FragPos, viewDir, norm);
        }
    }

    if(nPointLights > 0) {
        for(int idx = 0; idx < nPointLights; idx++) {
            result += calculatePointLight(pointLights[idx], FragPos, viewDir, norm);
        }
    }

    result = pow(result, vec3(1.0 / 2.2));
    FragColor = vec4(result, 1.0);
}

vec3 calculateDirectionalLight(
    DirectionalLight directionalLight,
    vec3 normal,
    vec3 viewerDir
) {
    vec3 color = texture(diffuseTexture, TexCoords).rgb;

    vec3 lightDir = normalize(directionalLight.direction - FragPos);

    // Default colors in case of no textures
    vec3 baseDiffuseColor = directionalLight.diffuse;
    vec3 baseSpecularColor = directionalLight.specular;

    // Sample textures once
    vec3 textureDiffuse = hasTexture ? vec3(texture(texture_diffuse1, TexCoords)) : baseDiffuseColor;
    vec3 textureSpecular = hasTexture ? vec3(texture(texture_specular1, TexCoords)) : baseSpecularColor;

    // Diffuse
    float diff = max(dot(lightDir, normal), 0.0);

    // Specular
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewerDir, reflectDir), 0.0), 16);

    // Ambient
    vec3 ambient = directionalLight.ambient * textureDiffuse * directionalLight.color;
    vec3 diffuse = directionalLight.diffuse * diff * textureDiffuse;
    vec3 specular = directionalLight.specular * spec * textureSpecular;

    // Shadow
    // float shadow = calculateShadow(FragPosLightSpace);

    // Combine components
    // vec3 result = (ambient + (1.0 - shadow) * (diffuse + specular)) * color;
    vec3 result = ambient + diffuse + specular;

    return result;
}

vec3 calculatePointLight(
    PointLight light,
    vec3 fragPos,
    vec3 viewerDir,
    vec3 normal
) {
    vec3 lightDir = normalize(light.position - fragPos);

    // Default colors in case of no textures
    vec3 baseDiffuseColor = light.diffuse;
    vec3 baseSpecularColor = light.specular;

    vec3 textureDiffuse = hasTexture ? vec3(texture(texture_diffuse1, TexCoords)) : baseDiffuseColor;
    vec3 textureSpecular = hasTexture ? vec3(texture(texture_specular1, TexCoords)) : baseSpecularColor;

    // Diffuse
    float diff = max(dot(normal, lightDir), 0.0);

    // Specular
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewerDir, reflectDir), 0.0), 16);

    // Attenuation
    float dist = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * dist + 
        light.quadratic * (dist * dist));

    // Ambient
    vec3 ambient = light.ambient * light.color * textureDiffuse;
    vec3 diffuse = light.diffuse * diff * textureDiffuse;
    vec3 specular = light.specular * spec * textureSpecular;

    // Apply attenuation
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;

    // Final combination
    vec3 result = (ambient + diffuse + specular);

    return result;
}

vec3 calculateSpotLight(
    SpotLight light,
    vec3 fragPos,
    vec3 viewerDir,
    vec3 normal
) { 
    vec3 lightDir = normalize(light.position - fragPos);

    // Default colors in case of no textures
    vec3 baseDiffuseColor = light.diffuse;
    vec3 baseSpecularColor = light.specular;

    vec3 textureDiffuse = hasTexture ? vec3(texture(texture_diffuse1, TexCoords)) : baseDiffuseColor;
    vec3 textureSpecular = hasTexture ? vec3(texture(texture_specular1, TexCoords)) : baseSpecularColor;

    // Diffuse
    float diff = max(dot(normal, lightDir), 0.0);

    // Specular
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewerDir, reflectDir), 0.0), 16);

    // Attenuation
    float dist = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * dist + 
        light.quadratic * (dist * dist));

    // Spotlight Intensity
    float theta = dot(lightDir, normalize(-light.direction));
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);

    // Ambient
    vec3 ambient = light.ambient * light.color * textureDiffuse;
    vec3 diffuse = light.diffuse * diff * textureDiffuse;
    vec3 specular = light.specular * spec * textureSpecular;

    // Apply attenuation and spotlight intensity
    ambient *= attenuation * intensity;
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;

    // Final combination
    vec3 result = (ambient + diffuse + specular);

    return result;
}

float calculateShadow(vec4 fragPosLightSpace) {
    // Transform clip space coordinates to normalized device coordinates (NDC)
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    projCoords = projCoords * 0.5 + 0.5;  // Transform to [0, 1] range

    // Get the closest depth value from the shadow map
    float closestDepth = texture(shadowMap, projCoords.xy).r;

    // Current fragment depth
    float currentDepth = projCoords.z;

    // Add a bias to prevent shadow acne
    float bias = max(0.005 * (1.0 - dot(Normal, vec3(0.0, 0.0, -1.0))), 0.005);

    // Check if the current fragment is in shadow
    float shadow = currentDepth - bias > closestDepth ? 1.0 : 0.0;

    // If fragment is outside the light frustum, don't apply shadow
    if (projCoords.z > 1.0)
        shadow = 0.0;

    return shadow;
}