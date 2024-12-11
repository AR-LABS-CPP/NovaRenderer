#pragma once

#include <filesystem>
#include "Renderer/Shader.h"
#include "Mesh.h"

namespace Nova {
	class Model {
	public:
		std::vector<Mesh> meshes;
		std::string directory;
		std::unordered_map<std::string, MeshTexture> textures_loaded;
		unsigned int modelId;

		Model();
		Model(std::string& path, unsigned int id);

		void drawModel(const Shader& shader, int width, int height);
	private:
		void loadModel(std::string& path);
		void processNode(aiNode* node, const aiScene* scene, glm::mat4 parentTransform = glm::mat4(1.0f));

		unsigned int textureFromFile(
			std::string path,
			std::string& directory,
			bool gamma = false
		);

		Mesh processMesh(aiMesh* mesh, const aiScene* scene, const glm::mat4& transform);

		std::vector<MeshTexture> loadMaterialTextures(
			aiMaterial* mat,
			aiTextureType type,
			std::string typeName
		);
		
		std::string fallbackTexturePath = std::filesystem::current_path().string();
		std::string getLocalDirectory(std::string& directory);
	};
}