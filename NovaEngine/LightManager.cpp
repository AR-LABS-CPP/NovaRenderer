#include "pch.h"
#include "LightManager.h"
#include "Common.h"

namespace Nova {
	LightManager::LightManager()
		: maxPointLights(MAX_POINT_LIGHTS), maxSpotLights(MAX_SPOT_LIGHTS) {}
	
	LightManager::~LightManager() {}

	void LightManager::applyDirectionalLight(Shader& shader, DirectionalLight& dirLight, glm::vec3 position) {
		dirLight.applyLighting(shader, 0);
		dirLight.setDirection(position);
	}

	void LightManager::applyPointLights(Shader& shader, std::vector<PointLight>& pointLights, glm::vec3& position) {
		size_t maxIdx = pointLights.size();

		if (pointLights.size() > MAX_POINT_LIGHTS) {
			maxIdx = MAX_POINT_LIGHTS;
		}

		for (size_t idx = 0; idx < maxIdx; idx++) {
			pointLights[idx].applyLighting(shader, static_cast<GLuint>(idx));
			pointLights[idx].setPosition(position);
		}
	}

	void LightManager::applySpotLights(Shader& shader, std::vector<SpotLight>& spotLights, glm::vec3 position, glm::vec3 direction) {
		size_t maxIdx = spotLights.size();

		if (spotLights.size() > MAX_SPOT_LIGHTS) {
			maxIdx = MAX_SPOT_LIGHTS;
		}

		for (size_t idx = 0; idx < maxIdx; idx++) {
			spotLights[idx].applyLighting(shader, static_cast<GLuint>(idx));
			spotLights[idx].setPosition(position);
			spotLights[idx].setDirection(direction);
		}
	}
}