#version 330 core
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
in vec3 FragPos;

uniform Material material;

uniform vec3 viewerPos;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;

uniform DirectionalLight directionalLight;
uniform PointLight pointLights[NR_POINT_LIGHTS];
uniform SpotLight spotLights[NR_SPOT_LIGHTS];

uniform int nPointLights;
uniform int nSpotLights;

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

float materialShininess = 2;

void main() {
    
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewerPos - FragPos);

    // apply directional, point and spot lights
    vec3 result = calculateDirectionalLight(directionalLight, norm, viewDir);

    for(int idx = 0; idx < min(nPointLights, NR_POINT_LIGHTS); idx++) {
        result += calculatePointLight(pointLights[idx], norm, FragPos, viewDir);
    }

    for(int idx = 0; idx < min(nSpotLights, NR_SPOT_LIGHTS); idx++) {
        result += calculateSpotLight(spotLights[idx], norm, FragPos, viewDir);
    }

    FragColor = vec4(result, 1.0);
}

vec3 calculateDirectionalLight(
    DirectionalLight directionalLight,
    vec3 normal,
    vec3 viewerDir
) {
    vec3 lightDir = normalize(-directionalLight.direction);

    // Sample textures once
    vec3 textureDiffuse = vec3(texture(texture_diffuse1, TexCoords));
    if (textureDiffuse == vec3(0.0)) textureDiffuse = vec3(1.0);

    vec3 textureSpecular = vec3(texture(texture_specular1, TexCoords));
    if (textureSpecular == vec3(0.0)) textureSpecular = vec3(1.0);

    // Diffuse
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = directionalLight.diffuse * diff;

    // Specular
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewerDir, reflectDir), 0.0), materialShininess);
    vec3 specular = directionalLight.specular * spec;

    // Ambient
    vec3 ambient = directionalLight.ambient * directionalLight.color;

    // Combine components
    vec3 result = (ambient + diffuse) * textureDiffuse + specular * textureSpecular;

    return result;
}

vec3 calculatePointLight(
    PointLight light,
    vec3 normal,
    vec3 fragPos,
    vec3 viewerDir
) {
    vec3 lightDir = normalize(light.position - fragPos);

    vec3 textureDiffuse = vec3(texture(texture_diffuse1, TexCoords));
    if (textureDiffuse == vec3(0.0)) textureDiffuse = vec3(1.0);

    vec3 textureSpecular = vec3(texture(texture_specular1, TexCoords));
    if (textureSpecular == vec3(0.0)) textureSpecular = vec3(1.0);

    // Diffuse
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff;

    // Specular
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewerDir, reflectDir), 0.0), materialShininess);
    vec3 specular = light.specular * spec;

    // Attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + 
        light.quadratic * (distance * distance));

    // Ambient
    vec3 ambient = light.ambient * light.color;

    // Apply attenuation
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;

    // Final combination
    vec3 result = (ambient + diffuse) * textureDiffuse + specular * textureSpecular;

    return result;
}

vec3 calculateSpotLight(
    SpotLight light,
    vec3 normal,
    vec3 fragPos,
    vec3 viewerDir
) {
    vec3 lightDir = normalize(light.position - fragPos);

    vec3 textureDiffuse = vec3(texture(texture_diffuse1, TexCoords));
    if (textureDiffuse == vec3(0.0)) textureDiffuse = vec3(1.0);

    vec3 textureSpecular = vec3(texture(texture_specular1, TexCoords));
    if (textureSpecular == vec3(0.0)) textureSpecular = vec3(1.0);

    // Diffuse
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff;

    // Specular
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewerDir, reflectDir), 0.0), materialShininess);
    vec3 specular = light.specular * spec;

    // Attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + 
        light.quadratic * (distance * distance));

    // Spotlight Intensity
    float theta = dot(lightDir, normalize(-light.direction));
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);

    // Ambient
    vec3 ambient = light.ambient * light.color;

    // Apply attenuation and spotlight intensity
    ambient *= attenuation * intensity;
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;

    // Final combination
    vec3 result = (ambient + diffuse) * textureDiffuse + specular * textureSpecular;

    return result;
}