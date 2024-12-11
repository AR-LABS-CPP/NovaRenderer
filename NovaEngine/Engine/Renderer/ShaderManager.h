#pragma once

#include "Vendor/nlohmann/json.hpp"
#include "Shader.h"

namespace Nova {
	enum class DefaultShaders {
		ObjectShader,
		GizmoShader,
		LightSourceShader,
		BackgroundShader
	};

	class ShaderManager {
	public:
		ShaderManager(const std::string& jsonPath) {
			std::ifstream input(jsonPath);
			shaderData = nlohmann::json::parse(input);
		}

		Shader& getShader(DefaultShaders shaderType);
	private:
		std::unordered_map<DefaultShaders, Shader> shaderCache;
		nlohmann::json shaderData;

		Shader loadShader(DefaultShaders shaderType);
	};
}