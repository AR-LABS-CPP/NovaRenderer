#pragma once

#include "Structs/LightStructs.h"
#include "Renderer/Shader.h"
#include "Events/LightEvent.h"
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

		std::unordered_map<GLint, SpotLightStruct>& getSpotLigts();
		std::unordered_map<GLint, PointLightStruct>& getPointLights();
	private:
		GLint maxPointLights;
		GLint maxSpotLights;
		Shader attachedShader;

		DirectionalLightStruct dirLight;
		std::unordered_map<GLint, SpotLightStruct> spotLights;
		std::unordered_map<GLint, PointLightStruct> pointLights;

		GLint nextSpotLightId = 1;
		GLint nextPointLightId = 1;

		EventQueue& evtQueue = EventQueue::getInstance();

		void onDirectionalLightAdded(Event& event);
		void onDirectionalLightRemoved(Event& event);

		void onSpotLightAdded(Event& event);
		void onSpotLightRemoved(Event& event);

		void onPointLightAdded(Event& event);
		void onPointLightRemoved(Event& event);
	};
}