#include "pch.h"
#include "Model.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace Nova {
	Model::Model() : modelId(-1) {}
	Model::Model(std::string& path, unsigned int id) {
		modelId = id;
		loadModel(path);
	}

	void Model::drawModel(const Shader& shader, int width, int height) {
		for (unsigned int idx = 0; idx < meshes.size(); idx++) {
			meshes[idx].drawMesh(shader);
		}
	}

	void Model::loadModel(std::string& path) {
		Assimp::Importer import;
		const aiScene* scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenSmoothNormals);

		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
			std::cout << "[-] assimp load model failed: " << import.GetErrorString() << std::endl;
			return;
		}

		directory = path.substr(0, path.find_last_of("/"));

		processNode(scene->mRootNode, scene);
	}

	void Model::processNode(aiNode* node, const aiScene* scene, glm::mat4 parentTransform) {
		glm::mat4 nodeTransform = parentTransform * glm::transpose(glm::make_mat4(&node->mTransformation.a1));
		
		for (unsigned int idx = 0; idx < node->mNumMeshes; idx++) {
			aiMesh* mesh = scene->mMeshes[node->mMeshes[idx]];
			meshes.push_back(processMesh(mesh, scene, nodeTransform));
		}

		for (unsigned int idx = 0; idx < node->mNumChildren; idx++) {
			processNode(node->mChildren[idx], scene, nodeTransform);
		}
	}

	Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene, const glm::mat4& transform) {
		std::vector<MeshVertex> vertices;
		std::vector<GLuint> indices;
		std::vector<MeshTexture> textures;

		for (unsigned int idx = 0; idx < mesh->mNumVertices; idx++) {
			MeshVertex vertex;
			glm::vec4 position;
			glm::vec3 vector;

			position = transform * glm::vec4(mesh->mVertices[idx].x, mesh->mVertices[idx].y, mesh->mVertices[idx].z, 1.0f);
			vertex.Position = glm::vec3(position);

			if (mesh->HasNormals()) {
				vector.x = mesh->mNormals[idx].x;
				vector.y = mesh->mNormals[idx].y;
				vector.z = mesh->mNormals[idx].z;
				vertex.Normal = vector;
			
				if (mesh->HasTangentsAndBitangents()) {
					vector.x = mesh->mTangents[idx].x;
					vector.y = mesh->mTangents[idx].y;
					vector.z = mesh->mTangents[idx].z;
					vertex.Tangent = vector;

					vector.x = mesh->mBitangents[idx].x;
					vector.y = mesh->mBitangents[idx].y;
					vector.z = mesh->mBitangents[idx].z;
					vertex.BiTangent = vector;
				}
			}
			else {
				vertex.TexCoords = glm::vec2(0.0f, 0.0f);
			}

			// if there are any texture coordinates available?
			if (mesh->mTextureCoords[0]) {
				glm::vec2 vec;
				vec.x = mesh->mTextureCoords[0][idx].x;
				vec.y = mesh->mTextureCoords[0][idx].y;
				vertex.TexCoords = vec;	
			}
			else {
				vertex.TexCoords = glm::vec2(0.0f, 0.0f);
			}

			vertices.push_back(vertex);
		}

		for (unsigned int idx = 0; idx < mesh->mNumFaces; idx++) {
			aiFace face = mesh->mFaces[idx];

			for (unsigned int innerIdx = 0; innerIdx < face.mNumIndices; innerIdx++) {
				indices.push_back(face.mIndices[innerIdx]);
			}
		}

		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
		std::vector<MeshTexture> diffuseMaps = loadMaterialTextures(
			material,
			aiTextureType_DIFFUSE,
			"texture_diffuse"
		);

		textures.insert(
			textures.end(),
			diffuseMaps.begin(),
			diffuseMaps.end()
		);

		std::vector<MeshTexture> specularMaps = loadMaterialTextures(
			material,
			aiTextureType_SPECULAR,
			"texture_specular"
		);

		textures.insert(
			textures.end(),
			specularMaps.begin(),
			specularMaps.end()
		);

		std::vector<MeshTexture> normalMaps = loadMaterialTextures(
			material,
			aiTextureType_HEIGHT,
			"texture_normal"
		);

		textures.insert(
			textures.end(),
			normalMaps.begin(),
			normalMaps.end()
		);

		std::vector<MeshTexture> heightMaps = loadMaterialTextures(
			material,
			aiTextureType_AMBIENT,
			"texture_height"
		);

		textures.insert(
			textures.end(),
			heightMaps.begin(),
			heightMaps.end()
		);

		return Mesh(vertices, indices, textures);
	}

	std::string Model::getLocalDirectory(std::string& directory) {
		std::string localDirectory = directory;

		size_t lastSlash = localDirectory.find_last_of("\\/");
		if (lastSlash != std::string::npos) {
			localDirectory = localDirectory.substr(0, lastSlash);
		}

		return localDirectory;
	}

	unsigned int Model::textureFromFile(
		std::string path,
		std::string& directory,
		bool gamma
	) {
		std::string localDirectory = getLocalDirectory(directory);
		std::string filename = path;
		filename = localDirectory + '\\' + filename;

		unsigned int textureID;
		glGenTextures(1, &textureID);

		int width, height, nrComponents;

		stbi_set_flip_vertically_on_load(1);

		unsigned char* data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
		if (data)
		{
			GLenum format;

			switch (nrComponents) {
				case 1:
					format = GL_RED;
					break;

				case 3:
					format = GL_RGB;
					break;

				case 4:
					format = GL_RGBA;
					break;

				default:
					format = GL_RGB;
					break;
			}

			glBindTexture(GL_TEXTURE_2D, textureID);
			glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			stbi_image_free(data);
		}
		else
		{
			NOVA_WARN("Texture failed to load at path: " + path + "; Reason: " + stbi_failure_reason());
			stbi_image_free(data);
		}

		stbi_set_flip_vertically_on_load(0);

		return textureID;
	}

	std::vector<MeshTexture> Model::loadMaterialTextures(
		aiMaterial* mat,
		aiTextureType type,
		std::string typeName
	) {
		std::vector<MeshTexture> textures;

		for (unsigned int idx = 0; idx < mat->GetTextureCount(type); idx++) {
			aiString str;
			mat->GetTexture(type, idx, &str);
			std::string texturePath = str.C_Str();

			if (textures_loaded.find(texturePath) != textures_loaded.end()) {
				textures.push_back(textures_loaded[texturePath]);
			}
			else {
				MeshTexture texture;
				texture.id = textureFromFile(texturePath, directory);
				texture.type = typeName;
				texture.path = texturePath;
				textures.push_back(texture);
				textures_loaded[texturePath] = texture;
			}
		}

		return textures;
	}
}