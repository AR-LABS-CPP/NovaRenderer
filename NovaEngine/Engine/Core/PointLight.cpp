#include "pch.h"
#include "PointLight.h"

namespace Nova {
    PointLight::PointLight(
        const glm::vec3& position,
        const glm::vec3& color,
        const glm::vec3& ambient,
        const glm::vec3& diffuse,
        const glm::vec3& specular,
        float constant,
        float linear,
        float quadratic
    ) : color(color), constant(constant), linear(linear), quadratic(quadratic),
        ambient(ambient), diffuse(diffuse), specular(specular), position(position) {}

    void PointLight::applyLighting(Shader& shader, GLuint index) const {
        std::string baseName = "pointLights[" + std::to_string(index) + "]";

        shader.setVec3(baseName + ".position", position);
        shader.setVec3(baseName + ".color", color);
        shader.setVec3(baseName + ".ambient", ambient);
        shader.setVec3(baseName + ".diffuse", diffuse);
        shader.setVec3(baseName + ".specular", specular);
        shader.setFloat(baseName + ".constant", constant);
        shader.setFloat(baseName + ".linear", linear);
        shader.setFloat(baseName + ".quadratic", quadratic);
    }

    void PointLight::setPosition(glm::vec3& newPosition) {
        position = newPosition;
    }
}