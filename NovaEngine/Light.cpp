#include "pch.h"
#include "Light.h"

namespace Nova {
    Light::Light(const glm::vec3& col)
        : color(col) {}

    void Light::setColor(const glm::vec3& col) {
        color = col;
    }

    glm::vec3 Light::getColor() const {
        return color;
    }
}