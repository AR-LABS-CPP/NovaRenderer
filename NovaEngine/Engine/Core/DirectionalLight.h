#pragma once

#include "Light.h"

namespace Nova {
	class DirectionalLight : public Light {
	public:
		glm::vec3 direction;
		glm::vec3 ambient;
		glm::vec3 diffuse;
		glm::vec3 specular;
		glm::vec3 color;

		DirectionalLight(
			const glm::vec3& direction = glm::vec3(0.0),
			const glm::vec3& color = glm::vec3(1.0),
			const glm::vec3& ambient = glm::vec3(0.5),
			const glm::vec3& diffuse = glm::vec3(0.5),
			const glm::vec3& specular = glm::vec3(0.5)
		);

		void applyLighting(Shader& shader, GLuint index) const override;
		void setDirection(glm::vec3& newDirection);
	};
}