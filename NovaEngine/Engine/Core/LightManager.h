#pragma once

#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "Renderer/Shader.h"
#include "Events/LightEvent.h"
#include "Events/EventBus.h"

namespace Nova {
	struct SpotLightStruct {
		SpotLight spotLight;
		glm::vec3 position = glm::vec3(1.0);
		glm::vec3 direction = glm::vec3(1.0);
	};

	struct PointLightStruct {
		PointLight pointLight;
		glm::vec3 position = glm::vec3(1.0);
	};

	struct DirectionalLightStruct {
		DirectionalLight directionalLight;
		glm::vec3 direction = glm::vec3(1.0);
	};

	class LightManager {
	public:
		static GLint currNoOfPointLights;
		static GLint currNoOfSpotLights;
		static bool isDirectionalLightActive;

		LightManager(Shader& shader);
		~LightManager();

		void applyDirectionalLight();
		void applyPointLights();
		void applySpotLights();

		void applyAllLights();
	private:
		GLint maxPointLights;
		GLint maxSpotLights;
		Shader attachedShader;

		DirectionalLightStruct dirLight;
		std::unordered_map<GLint, SpotLightStruct> spotLights;
		std::unordered_map<GLint, PointLightStruct> pointLights;

		GLint nextSpotLightId = 1;
		GLint nextPointLightId = 1;

		void onDirectionalLightAdded(Event& event);
		void onDirectionalLightRemoved(Event& event);

		void onSpotLightAdded(Event& event);
		void onSpotLightRemoved(Event& event);

		void onPointLightAdded(Event& event);
		void onPointLightRemoved(Event& event);
	};
}