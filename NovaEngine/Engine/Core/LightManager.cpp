#include "pch.h"
#include "LightManager.h"

namespace Nova {
	GLint LightManager::currNoOfSpotLights = 0;
	GLint LightManager::currNoOfPointLights = 0;
	bool LightManager::isDirectionalLightActive = false;

	LightManager::LightManager(Shader& shader)
		: maxPointLights(MAX_POINT_LIGHTS), maxSpotLights(MAX_SPOT_LIGHTS) {
		attachedShader = shader;
	}
	
	LightManager::~LightManager() {}

	void LightManager::applyDirectionalLight(DirectionalLight& dirLight, glm::vec3 position) {
		dirLight.applyLighting(attachedShader, 0);
		dirLight.setDirection(position);
	}

	void LightManager::applyPointLights(std::vector<PointLight>& pointLights, glm::vec3& position) {
		size_t maxIdx = pointLights.size();

		if (pointLights.size() > MAX_POINT_LIGHTS) {
			maxIdx = MAX_POINT_LIGHTS;
		}

		for (size_t idx = 0; idx < maxIdx; idx++) {
			pointLights[idx].applyLighting(attachedShader, static_cast<GLuint>(idx));
			pointLights[idx].setPosition(position);
		}
	}

	void LightManager::applySpotLights(std::vector<SpotLight>& spotLights, glm::vec3 position, glm::vec3 direction) {
		size_t maxIdx = spotLights.size();

		if (spotLights.size() > MAX_SPOT_LIGHTS) {
			maxIdx = MAX_SPOT_LIGHTS;
		}

		for (size_t idx = 0; idx < maxIdx; idx++) {
			spotLights[idx].applyLighting(attachedShader, static_cast<GLuint>(idx));
			spotLights[idx].setPosition(position);
			spotLights[idx].setDirection(direction);
		}
	}
}