#pragma once

#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "Renderer/Shader.h"
#include "Events/LightEvent.h"
#include "Events/EventBus.h"

namespace Nova {
	class LightManager {
	public:
		static GLint currNoOfPointLights;
		static GLint currNoOfSpotLights;
		static bool isDirectionalLightActive;

		LightManager(Shader& shader);
		~LightManager();

		void applyDirectionalLight(DirectionalLight& dirLight, glm::vec3 direction);
		void applyPointLights(std::vector<PointLight>& pointLights, glm::vec3& position);
		void applySpotLights(std::vector<SpotLight>& spotLights, glm::vec3 position, glm::vec3 direction);
	private:
		GLint maxPointLights;
		GLint maxSpotLights;
		Shader attachedShader;
	};
}