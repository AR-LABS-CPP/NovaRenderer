#pragma once

#include "Shader.h"

namespace Nova {
	class ShaderBuilder {
	public:
		ShaderBuilder();

		ShaderBuilder& withVertexShader(const std::string& path);
		ShaderBuilder& withFragmentShader(const std::string& path);
		ShaderBuilder& withGeometryShader(const std::string& path);
		ShaderBuilder& withComputeShader(const std::string& path);

		Shader buildShader();

	private:
		std::string vertexShaderPath;
		std::string fragmentShaderPath;
		std::string geometryShaderPath;
		std::string computeShaderPath;

		GLuint shaderProgram;
	};
}