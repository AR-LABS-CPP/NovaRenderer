#pragma once

#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "Renderer/Shader.h"

namespace Nova {
	class LightManager {
	public:
		static GLint currNoOfPointLights;
		static GLint currNoOfSpotLights;
		static bool isDirectionalLightActive;

		LightManager();
		~LightManager();

		void applyDirectionalLight(Shader& shader, DirectionalLight& dirLight, glm::vec3 direction);
		void applyPointLights(Shader& shader, std::vector<PointLight>& pointLights, glm::vec3& position);
		void applySpotLights(Shader& shader, std::vector<SpotLight>& spotLights, glm::vec3 position, glm::vec3 direction);
	private:
		GLint maxPointLights;
		GLint maxSpotLights;
	};
}