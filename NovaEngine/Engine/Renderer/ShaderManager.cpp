#include "pch.h"
#include "ShaderManager.h"

namespace Nova {
	ShaderManager::ShaderManager(const std::string& jsonPath) {
		std::ifstream input(jsonPath);
		NOVA_ASSERT(input.is_open(), "Shader config file must be present in the project");
		shaderData = nlohmann::json::parse(input);
	}

	Shader& ShaderManager::getShader(ShaderName shaderName) {
		if (shaderCache.find(shaderName) != shaderCache.end()) {
			return shaderCache[shaderName];
		}
		else {
			Shader loadedShader = loadShader(shaderName);
			shaderCache[shaderName] = loadedShader;
			return shaderCache[shaderName];
		}
	}

	Shader ShaderManager::loadShader(ShaderName shaderName) {
		std::string shaderKey;

		switch (shaderName) {
		case ShaderName::ObjectShader:
			shaderKey = "ObjectShader";
			break;
		case ShaderName::GizmoShader:
			shaderKey = "GizmoShader";
			break;
		case ShaderName::LightSourceShader:
			shaderKey = "LightSourceShader";
			break;
		case ShaderName::BackgroundShader:
			shaderKey = "BackgroundShader";
			break;
		default:
			throw std::invalid_argument("Unknown shader type.");
		}

		NOVA_ASSERT(shaderData.contains(shaderKey), "Shader config file must contain " + shaderKey + "'s paths");
		std::string vertexPath = shaderData[shaderKey]["vertex"].get<std::string>();
		std::string fragmentPath = shaderData[shaderKey]["fragment"].get<std::string>();

		return ShaderBuilder()
			.withVertexShader(vertexPath)
			.withFragmentShader(fragmentPath)
			.buildShader();
	}
}
