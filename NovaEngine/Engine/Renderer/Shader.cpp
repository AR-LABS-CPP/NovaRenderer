#include "pch.h"
#include "Shader.h"

namespace Nova {
	Shader::Shader() : shaderId(0) {}

	Shader::~Shader() {
		if (shaderId != 0) {
			glDeleteProgram(shaderId);
			shaderId = 0;
		}

		NOVA_INFO("A shader just got destroyed");
		NOVA_ASSERT(shaderId == 0, "Could not delete the shader");
	}

	// a loop is not necessary, there aren't many shaders out there
	void Shader::compileAndLink(const std::vector<std::string>& shaderPaths) {
		std::vector<GLuint> shaders;

		if(!shaderPaths[0].empty()) {
			std::string vertexShaderCode = loadShaderCodeFromDisk(shaderPaths[0]);
			
			GLuint shaderId = 0;
			compileShader(GL_VERTEX_SHADER, vertexShaderCode.c_str(), 1, shaderId);
			shaders.push_back(shaderId);
		}

		if (!shaderPaths[1].empty()) {
			std::string vertexShaderCode = loadShaderCodeFromDisk(shaderPaths[1]);

			GLuint shaderId = 0;
			compileShader(GL_FRAGMENT_SHADER, vertexShaderCode.c_str(), 1, shaderId);
			shaders.push_back(shaderId);
		}

		if (!shaderPaths[2].empty()) {
			std::string vertexShaderCode = loadShaderCodeFromDisk(shaderPaths[2]);

			GLuint shaderId = 0;
			compileShader(GL_GEOMETRY_SHADER, vertexShaderCode.c_str(), 1, shaderId);
			shaders.push_back(shaderId);
		}

		if (!shaderPaths[3].empty()) {
			std::string vertexShaderCode = loadShaderCodeFromDisk(shaderPaths[3]);

			GLuint shaderId = 0;
			compileShader(GL_FRAGMENT_SHADER, vertexShaderCode.c_str(), 1, shaderId);
			shaders.push_back(shaderId);
		}

		linkProgram(shaders);

		for (GLuint shader : shaders) {
			glDeleteShader(shader);
		}

		NOVA_INFO("Shaders compiled and linked");
		NOVA_ASSERT(shaders.size() > 0, "Shaders vector must be greater than 0");
	}
	
	void Shader::compileShader(
		int shaderType,
		const char* shaderCode,
		int shaderCount,
		GLuint& shaderIdHolder
	) {
		int success;
		char logInfo[512];

		switch (shaderType) {
		case GL_VERTEX_SHADER:
			shaderIdHolder = glCreateShader(GL_VERTEX_SHADER);
			break;

		case GL_FRAGMENT_SHADER:
			shaderIdHolder = glCreateShader(GL_FRAGMENT_SHADER);
			break;

		case GL_GEOMETRY_SHADER:
			shaderIdHolder = glCreateShader(GL_GEOMETRY_SHADER);
			break;

		case GL_COMPUTE_SHADER:
			shaderIdHolder = glCreateShader(GL_COMPUTE_SHADER);
			break;

		default:
			assert(false && "[-] unknown shader type encountered during compilation.");
		}

		glShaderSource(shaderIdHolder, shaderCount, &shaderCode, NULL);
		glCompileShader(shaderIdHolder);

		glGetShaderiv(shaderIdHolder, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(shaderIdHolder, 512, NULL, logInfo);
			std::string errorMessage = "[-] shader compilation failed: " + std::string(logInfo);
		}

		NOVA_INFO("Shader compiled");
		NOVA_ASSERT(shaderIdHolder != 0, "Shader id must not be zero");
	}

	void Shader::linkProgram(const std::vector<GLuint>& shaders) {
		NOVA_ASSERT(shaderId == 0, "Shader must be 0 before linking");
		NOVA_INFO("A program is being linked");

		shaderId = glCreateProgram();

		for (GLuint shader : shaders) {
			glAttachShader(shaderId, shader);
		}

		glLinkProgram(shaderId);

		int success;
		char infoLog[512];
		glGetProgramiv(shaderId, GL_LINK_STATUS, &success);

		if (!success) {
			glGetProgramInfoLog(shaderId, 512, nullptr, infoLog);
			NOVA_ERROR("Program linking failed due to:");
			NOVA_ERROR(infoLog);
		}

		NOVA_ASSERT(shaderId != 0, "Shader id must not be zero");
	}

	std::string Shader::loadShaderCodeFromDisk(std::string shaderPath) {
		NOVA_INFO("A shader is being loaded from disk");

		std::string shaderCode;
		std::ifstream shaderCodeFile;
		
		shaderCodeFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		
		try {
			shaderCodeFile.open(shaderPath);
			std::stringstream shaderStream;
		
			shaderStream << shaderCodeFile.rdbuf();
			shaderCodeFile.close();
		
			shaderCode = shaderStream.str();
		}
		catch (std::ifstream::failure ex) {
			NOVA_FATAL("failed to read shader file: " + std::string(ex.what()));
		}

		NOVA_INFO("A shader has been loaded from the disk");
		NOVA_ASSERT(shaderCode.size() != 0, "Shader code is of size zero");

		return shaderCode;
	}

	void Shader::useShader() {
		NOVA_ASSERT(shaderId != 0, "Shader id must not be zero");

		if (shaderId) {
			glUseProgram(shaderId);
		}
	}
	
	void Shader::setBool(const std::string& name, bool value) const {
		glUniform1i(glGetUniformLocation(shaderId, name.c_str()), (int)value);
	}

	void Shader::setInt(const std::string& name, int value) const {
		glUniform1i(glGetUniformLocation(shaderId, name.c_str()), value);
	}

	void Shader::setFloat(const std::string& name, float value) const {
		glUniform1f(glGetUniformLocation(shaderId, name.c_str()), value);
	}

	void Shader::setMat4(const std::string& name, glm::mat4 value) const {
		glUniformMatrix4fv(glGetUniformLocation(shaderId, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
	}

	void Shader::setVec3(const std::string& name, glm::vec3 vector) const {
		glUniform3fv(glGetUniformLocation(shaderId, name.c_str()), 1, glm::value_ptr(vector));
	}
}