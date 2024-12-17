#pragma once

#include "Structs/LightStructs.h"
#include "Renderer/Shader.h"
#include "Events/LightEvent.h"
#include "Events/GlobalEvent.h"
#include "Events/EventBus.h"
#include "Events/EventQueue.h"

namespace Nova {
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
		void subscribeToEvents();
		void clearAllLights();

		std::unordered_map<GLint, SpotLight>& getSpotLigts();
		std::unordered_map<GLint, PointLight>& getPointLights();

		DirectionalLightStruct& getDirectionalLight();
	private:
		GLint maxPointLights;
		GLint maxSpotLights;
		Shader attachedShader;

		DirectionalLightStruct dirLight;
		std::unordered_map<GLint, SpotLight> spotLights;
		std::unordered_map<GLint, PointLight> pointLights;

		
		GLint nextSpotLightId = 0;
		GLint nextPointLightId = 0;

		EventQueue& evtQueue = EventQueue::getInstance();

		void onDirectionalLightAdded(Event& event);
		void onDirectionalLightRemoved(Event& event);

		void onSpotLightAdded(Event& event);
		void onSpotLightRemoved(Event& event);

		void onPointLightAdded(Event& event);
		void onPointLightRemoved(Event& event);
	};
}