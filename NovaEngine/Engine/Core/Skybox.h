#pragma once

#include "Log/Log.h"
#include "Renderer/Shader.h"

namespace Nova {
	class Skybox {
	public:
		Skybox(std::vector<std::string>& faces);
		~Skybox();

		void renderSkyBox();
	private:
		static float skyboxVertices[];

		GLuint skyboxId, skyboxVAO, skyboxVBO;
		int width, height, nrChannels;
		unsigned char* data;

		void initAndBind();
		void loadAndBindTextures(std::vector<std::string>& faces);
	};
}