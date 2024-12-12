#pragma once

#include "Light.h"
#include "Renderer/Shader.h"

namespace Nova {
    class SpotLight : public Light {
    public:
        glm::vec3 position;
        glm::vec3 direction;
        glm::vec3 ambient;
        glm::vec3 diffuse;
        glm::vec3 specular;
        glm::vec3 color;
        float constant;
        float linear;
        float quadratic;
        float cutOff;
        float outerCutOff;

        SpotLight(
            const glm::vec3& position = glm::vec3(1.0f),
            const glm::vec3& direction = glm::vec3(1.0f),
            const glm::vec3& color = glm::vec3(1.0f),
            const glm::vec3& ambient = glm::vec3(0.5),
            const glm::vec3& diffuse = glm::vec3(0.5),
            const glm::vec3& specular = glm::vec3(0.5),
            float constant = 1.0f,
            float linear = 0.09f,
            float quadratic = 0.032f,
            float cutOff = glm::cos(glm::radians(15.5f)),
            float outerCutOff = glm::cos(glm::radians(17.5f))
        );

        void applyLighting(Shader& shader, GLuint index) const override;
    };
}