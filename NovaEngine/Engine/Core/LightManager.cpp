#include "pch.h"
#include "LightManager.h"

namespace Nova {
	GLint LightManager::currNoOfSpotLights = 0;
	GLint LightManager::currNoOfPointLights = 0;
	bool LightManager::isDirectionalLightActive = false;

	LightManager::LightManager(Shader& shader)
		: maxPointLights(MAX_POINT_LIGHTS), maxSpotLights(MAX_SPOT_LIGHTS) {
		subscribeToEvents();

		attachedShader = shader;
	}
	
	LightManager::~LightManager() {}

	void LightManager::applyDirectionalLight() {
		attachedShader.setBool("directionalLightActive", dirLight.isActive);

		if (isDirectionalLightActive) { 
			dirLight.directionalLight.applyLighting(attachedShader, 0);
		} 
	}

	void LightManager::applyPointLights() {
		attachedShader.setInt("nPointLights", currNoOfPointLights);

		if (currNoOfPointLights > 0) {
			for (auto& pl : pointLights) {
				pl.second.applyLighting(attachedShader, pl.first);
			}
		}
	}

	void LightManager::applySpotLights() {
		attachedShader.setInt("nSpotLights", currNoOfSpotLights);

		if (currNoOfSpotLights > 0) {
			for (auto& sl : spotLights) {
				sl.second.applyLighting(attachedShader, sl.first);
			}
		}
	}

	void LightManager::applyAllLights() {
		applyDirectionalLight();
		applyPointLights();
		applySpotLights();
	}

	void LightManager::subscribeToEvents() {
		evtQueue.subscribe<DirectionalLightAddedEvent>([this](Event& event) {
			onDirectionalLightAdded(event);
		});

		evtQueue.subscribe<DirectionalLightRemovedEvent>([this](Event& event) {
			onDirectionalLightRemoved(event);
		});

		evtQueue.subscribe<SpotLightAddedEvent>([this](Event& event) {
			onSpotLightAdded(event);
		});

		evtQueue.subscribe<SpotLightRemovedEvent>([this](Event& event) {});

		evtQueue.subscribe<PointLightAddedEvent>([this](Event& event) {
			onPointLightAdded(event);
		});

		evtQueue.subscribe<PointLightRemovedEvent>([this](Event& event) {});

		NOVA_INFO("LightManager subscribed to events");
	}

	std::unordered_map<GLint, SpotLight>& LightManager::getSpotLigts() {
		return spotLights;
	}
	
	std::unordered_map<GLint, PointLight>& LightManager::getPointLights() {
		return pointLights;
	}

	DirectionalLightStruct& LightManager::getDirectionalLight() {
		return dirLight;
	}

	void LightManager::onDirectionalLightAdded(Event& event) {
		auto& directionalLightAddedEvent = static_cast<DirectionalLightAddedEvent&>(event);

		if (dirLight.isActive) {
			NOVA_WARN("Directional light is already active");
			return;
		}

		dirLight.toggleActive();
		NOVA_INFO("Directional light is active");
	}
	
	void LightManager::onDirectionalLightRemoved(Event& event) {
		auto& directionalLightRemovedEvent = static_cast<DirectionalLightRemovedEvent&>(event);

		if (!dirLight.isActive) {
			NOVA_WARN("Directional light is not active");
			return;
		}

		dirLight.toggleActive();
		NOVA_INFO("Directional light deactivated");
	}

	void LightManager::onSpotLightAdded(Event& event) {
		auto& spotLightAddedEvent = static_cast<SpotLightAddedEvent&>(event);

		if(spotLights.size() == MAX_SPOT_LIGHTS) {
			NOVA_WARN("Reached maximum number of spot lights: " + std::to_string(MAX_SPOT_LIGHTS) + ", cannot add more");
			return;
		}

		SpotLight newSpotLight;
		spotLights[nextSpotLightId++] = newSpotLight;
		currNoOfSpotLights += 1;

		NOVA_INFO("Spot light added, ID: " + (nextSpotLightId - 1));
	}
	
	void LightManager::onSpotLightRemoved(Event& event) {
		auto& spotLightRemovedEvent = static_cast<SpotLightRemovedEvent&>(event);
	}

	void LightManager::onPointLightAdded(Event& event) {
		auto& pointLightAddedEvent = static_cast<PointLightAddedEvent&>(event);

		if (pointLights.size() == MAX_POINT_LIGHTS) {
			NOVA_WARN("Reached maximum number of point lights: " + std::to_string(MAX_SPOT_LIGHTS) + ", cannot add more");
			return;
		}

		PointLight newPointLight;
		pointLights[nextPointLightId++] = newPointLight;
		currNoOfPointLights += 1;

		NOVA_INFO("Point light added, ID: " + (nextPointLightId - 1));
	}
	
	void LightManager::onPointLightRemoved(Event& event) {
		auto& pointLightRemovedEvent = static_cast<PointLightRemovedEvent&>(event);
	}
}