#pragma once

#include "Log/Log.h"
#include "Renderer/Shader.h"

namespace Nova {
	class Material {
	public:
		Material() = default;
		
		virtual void applyMaterial(Shader& shader, GLuint index) const = 0;
	private:
	};
}