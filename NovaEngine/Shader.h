#pragma once

namespace Nova {
	class Shader {
	public:
		Shader();
		~Shader();

		void compileAndLink(const std::vector<std::string>& shaderPaths);

		void useShader();
		void setBool(const std::string& name, bool value) const;
			 
		void setInt(const std::string& name, int value) const;
		void setFloat(const std::string& name, float value) const;
		void setMat4(const std::string& name, glm::mat4 value) const;
		void setVec3(const std::string& name, glm::vec3 vector) const;
	private:
		GLuint shaderId;

		void compileShader(
			int shaderType,
			const char* shaderCode,
			int shaderCount,
			GLuint& shaderIdHolder
		);
		void linkProgram(const std::vector<GLuint>& shaders);
		
		std::string loadShaderCodeFromDisk(std::string shaderPath);
	};
}