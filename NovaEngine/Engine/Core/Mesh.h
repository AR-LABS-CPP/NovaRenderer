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

	struct BoundingBox {
		glm::vec3 minExtent;
		glm::vec3 maxExtent;
	};

	class Mesh {
	public:
		std::vector<MeshVertex> vertices;
		std::vector<GLuint> indices;
		std::vector<MeshTexture> textures;
		BoundingBox boundingBox;

		Mesh(
			std::vector<MeshVertex> vertices,
			std::vector<GLuint> indices,
			std::vector<MeshTexture> textures,
			BoundingBox boundingBox
		);

		void drawMesh(const Shader& shader);
		void createFrameBuffer(int width, int height);
		void renderToFrameBuffer(const Shader& shader, int width, int height);
	private:
		GLuint VAO, VBO, EBO, FBO, RBO, Texture;

		void setupMesh();
	};
}