#pragma once

#include "Vendor/nlohmann/json.hpp"
#include "Shader.h"
#include "Log/Log.h"
#include "ShaderBuilder.h"
#include "Camera.h"

namespace Nova {
	enum class ShaderName {
		ObjectShader,
		GizmoShader,
		LightSourceShader,
		BackgroundShader
	};

	class ShaderManager {
	public:
		ShaderManager(const std::string& jsonPath);
		Shader getShader(ShaderName shaderName, Camera& cameraObj);
	private:
		std::unordered_map<ShaderName, Shader> shaderCache;
		nlohmann::json shaderData;

		Shader loadShader(ShaderName shaderName);
	};
}