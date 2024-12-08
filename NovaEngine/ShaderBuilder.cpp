#include "pch.h"
#include "ShaderBuilder.h"

namespace Nova {
	ShaderBuilder::ShaderBuilder() : shaderProgram(0) {}

	ShaderBuilder& ShaderBuilder::withVertexShader(const std::string& path) {
		vertexShaderPath = path;
		return *this;
	}

	ShaderBuilder& ShaderBuilder::withFragmentShader(const std::string& path) {
		fragmentShaderPath = path;
		return *this;
	}

	ShaderBuilder& ShaderBuilder::withGeometryShader(const std::string& path) {
		geometryShaderPath = path;
		return *this;
	}

	ShaderBuilder& ShaderBuilder::withComputeShader(const std::string& path) {
		computeShaderPath = path;
		return *this;
	}

	Shader ShaderBuilder::buildShader() {
		// the order must remain like this
		std::vector<std::string> shaders = {
			vertexShaderPath,
			fragmentShaderPath,
			geometryShaderPath,
			computeShaderPath
		};

		Shader shaderProgram;
		shaderProgram.compileAndLink(shaders);

		return shaderProgram;
	}
}