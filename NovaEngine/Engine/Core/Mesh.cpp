#include "pch.h"
#include "Mesh.h"

namespace Nova {
	Mesh::Mesh(
		std::vector<MeshVertex> vertices,
		std::vector<GLuint> indices,
		std::vector<MeshTexture> textures
	) {
		this->vertices = vertices;
		this->indices = indices;
		this->textures = textures;

		setupMesh();
	}

	void Mesh::drawMesh(const Shader& shader) {
		GLuint diffuseNr = 1;
		GLuint specularNr = 1;
		GLuint normalNr = 1;

		if (textures.size() > 0) {
			shader.setBool("hasTexture", true);

			for (unsigned int idx = 0; idx < textures.size(); idx++) {
				glActiveTexture(GL_TEXTURE0 + idx);

				std::string number;
				std::string name = textures[idx].type;

				if (name == "texture_diffuse") {
					number = std::to_string(diffuseNr++);
				}
				else if (name == "texture_specular") {
					number = std::to_string(specularNr++);
				}
				else if (name == "texture_normal") {
					number = std::to_string(normalNr++);
				}

				shader.setInt((name + number).c_str(), idx);
				glBindTexture(GL_TEXTURE_2D, textures[idx].id);
			}
		}
		else {
			shader.setBool("hasTexture", false);
		}

		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(indices.size()), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		glActiveTexture(GL_TEXTURE0);
	}

	void Mesh::setupMesh() {
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);

		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);

		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(MeshVertex), &vertices[0], GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(MeshVertex), (void*)0);

		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(MeshVertex), (void*)offsetof(MeshVertex, Normal));

		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(MeshVertex), (void*)offsetof(MeshVertex, TexCoords));

		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(MeshVertex), (void*)offsetof(MeshVertex, Tangent));

		glEnableVertexAttribArray(4);
		glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(MeshVertex), (void*)offsetof(MeshVertex, BiTangent));

		glBindVertexArray(0);
	}

	void Mesh::createFrameBuffer(
		int width,
		int height
	) {
		glGenFramebuffers(1, &FBO);
		glBindFramebuffer(GL_FRAMEBUFFER, FBO);

		glGenTextures(1, &Texture);
		glBindTexture(GL_TEXTURE_2D, Texture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, Texture, 0);
		
		glGenRenderbuffers(1, &RBO);
		glBindRenderbuffer(GL_RENDERBUFFER, RBO);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, RBO);

		NOVA_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE, "Framebuffer must be complete");

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void Mesh::renderToFrameBuffer(
		const Shader& shader,
		int width,
		int height
	) {
		NOVA_ASSERT(width != 0 && height != 0, "width or height cannot be zero");
		
		if (FBO == 0) {
			createFrameBuffer(width, height);
		}

		NOVA_ASSERT(this->FBO != 0, "frame buffer object must not be zero");

		drawMesh(shader);
	}
}