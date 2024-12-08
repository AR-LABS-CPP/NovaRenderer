#pragma once

#include "Renderer/Shader.h"

namespace Nova {
	struct MeshVertex {
		glm::vec3 Position;
		glm::vec3 Normal;
		glm::vec2 TexCoords;
		glm::vec3 Tangent;
		glm::vec3 BiTangent;
	};

	struct MeshTexture {
		GLuint id;
		std::string type;
		std::string path;
	};

	class Mesh {
	public:
		std::vector<MeshVertex> vertices;
		std::vector<GLuint> indices;
		std::vector<MeshTexture> textures;

		Mesh(
			std::vector<MeshVertex> vertices,
			std::vector<GLuint> indices,
			std::vector<MeshTexture> textures
		);

		void drawMesh(const Shader& shader);
		void createFrameBuffer(int width, int height);
		void renderToFrameBuffer(const Shader& shader, int width, int height);
	private:
		GLuint VAO, VBO, EBO, FBO, RBO, Texture;

		void setupMesh();
	};
}