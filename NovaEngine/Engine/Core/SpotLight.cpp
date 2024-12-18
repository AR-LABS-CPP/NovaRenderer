#include "pch.h"
#include "SpotLight.h"

namespace Nova {
    SpotLight::SpotLight(
        const glm::vec3& position,
        const glm::vec3& direction,
        const glm::vec3& color,
        const glm::vec3& ambient,
        const glm::vec3& diffuse,
        const glm::vec3& specular,
        float constant,
        float linear,
        float quadratic,
        float cutOff,
        float outerCutOff
    ) : position(position), direction(direction), constant(constant), linear(linear),
        quadratic(quadratic), cutOff(cutOff), outerCutOff(outerCutOff), ambient(ambient),
        diffuse(diffuse), specular(specular), color(color) {}

    void SpotLight::applyLighting(Shader& shader, GLuint index) const {
        std::string baseName = "spotLights[" + std::to_string(index) + "]";

        shader.setVec3(baseName + ".position", position);
        shader.setVec3(baseName + ".color", color);

        shader.setFloat(baseName + ".constant", constant);
        shader.setFloat(baseName + ".linear", linear);
        shader.setFloat(baseName + ".quadratic", quadratic);

        shader.setVec3(baseName + ".ambient", ambient);
        shader.setVec3(baseName + ".diffuse", diffuse);
        shader.setVec3(baseName + ".specular", specular);

        shader.setVec3(baseName + ".direction", direction);
        shader.setFloat(baseName + ".cutOff", cutOff);
        shader.setFloat(baseName + ".outerCutOff", outerCutOff);
    }
}