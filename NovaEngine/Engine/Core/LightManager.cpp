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

		if (dirLight.isActive && dirLight.hasChanged) { 
			dirLight.directionalLight.setDirection(dirLight.direction);
			dirLight.directionalLight.applyLighting(attachedShader, 0);
			dirLight.resetChangeFlag();
		}
	}

	void LightManager::applyPointLights() {
		for (auto& pl : pointLights) {
			pl.second.pointLight.applyLighting(attachedShader, pl.first);
			pl.second.pointLight.setPosition(pl.second.position);
		}
	}

	void LightManager::applySpotLights() {
		for (auto& sl : spotLights) {
			sl.second.spotLight.applyLighting(attachedShader, sl.first);
			sl.second.spotLight.setPosition(sl.second.position);
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

	std::unordered_map<GLint, SpotLightStruct>& LightManager::getSpotLigts() {
		return spotLights;
	}
	
	std::unordered_map<GLint, PointLightStruct>& LightManager::getPointLights() {
		return pointLights;
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

		SpotLightStruct newSpotLight;
		newSpotLight.spotLight = SpotLight(
			glm::vec3(1.0),
			glm::vec3(1.0)
		);
		spotLights[nextSpotLightId++] = newSpotLight;

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

		PointLightStruct newPointLight;
		newPointLight.pointLight = PointLight(glm::vec3(1.0));
		pointLights[nextPointLightId++] = newPointLight;

		NOVA_INFO("Point light added, ID: " + (nextPointLightId - 1));
	}
	
	void LightManager::onPointLightRemoved(Event& event) {
		auto& pointLightRemovedEvent = static_cast<PointLightRemovedEvent&>(event);
	}
}