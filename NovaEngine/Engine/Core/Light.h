#pragma once

#include "Renderer/Shader.h"

namespace Nova {
	class Light {
	public:
		Light(const glm::vec3& col);

		virtual ~Light() {}
		virtual void applyLighting(Shader& shader, GLuint index) const = 0;

		void setColor(const glm::vec3& col);
		glm::vec3 getColor() const;
	private:
		glm::vec3 color;
	};
}