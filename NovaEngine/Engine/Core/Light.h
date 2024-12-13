#pragma once

#include "Renderer/Shader.h"

namespace Nova {
	class Light {
	public:
		Light() = default;

		virtual ~Light() {}
		virtual void applyLighting(Shader& shader, GLuint index) const = 0;
	};
}