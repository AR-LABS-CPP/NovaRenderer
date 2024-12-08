#include "pch.h"
#include "DirectionalLight.h"

namespace Nova {
    DirectionalLight::DirectionalLight(
        const glm::vec3& direction,
        const glm::vec3& color,
        const glm::vec3& ambient,
        const glm::vec3& diffuse,
        const glm::vec3& specular
    ) : Light(color), direction(direction),
        ambient(ambient), diffuse(diffuse), specular(specular) {
    }

    void DirectionalLight::applyLighting(Shader& shader, GLuint index) const {
        shader.setVec3("directionalLight.direction", direction);
        shader.setVec3("directionalLight.color", getColor());
        shader.setVec3("directionalLight.ambient", ambient);
        shader.setVec3("directionalLight.diffuse", diffuse);
        shader.setVec3("directionalLight.specular", specular);
    }

    void DirectionalLight::setDirection(glm::vec3& newDirection) {
        direction = newDirection;
    }
}