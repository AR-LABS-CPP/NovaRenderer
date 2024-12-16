#pragma once

#include "Light.h"
#include "Renderer/Shader.h"

namespace Nova {
    class PointLight : public Light {
    public:
        float constant;
        float linear;
        float quadratic;
        glm::vec3 ambient;
        glm::vec3 diffuse;
        glm::vec3 specular;
        glm::vec3 position;
        glm::vec3 color;

        PointLight(
            const glm::vec3& position = glm::vec3(1.0f),
            const glm::vec3& color = glm::vec3(1.0f),
            const glm::vec3& ambient = glm::vec3(0.5),
            const glm::vec3& diffuse = glm::vec3(0.5),
            const glm::vec3& specular = glm::vec3(0.5),
            float constant = 1.0,
            float linear = 0.09,
            float quadratic = 0.032
        );

        void applyLighting(Shader& shader, GLuint index) const override;
        void setPosition(glm::vec3& newPosition);
    };
}