#pragma once

#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "Renderer/Shader.h"
#include "Events/LightEvent.h"
#include "Events/EventBus.h"
#include "Events/EventQueue.h"

namespace Nova {
	struct LightStructBase {
		bool hasChanged = false;

		template<typename T>
		bool setProperty(T& property, const T& newValue) {
			if (property != newValue) {
				property = newValue;
				hasChanged = true;

				return true;
			}

			return false;
		}

		void resetChangeFlag() {
			hasChanged = false;
		}
	};

	struct SpotLightStruct : public LightStructBase {
		SpotLight spotLight;
		glm::vec3 position;
		glm::vec3 direction;

		SpotLightStruct() {
			spotLight = SpotLight();
		}

		bool setPos(const glm::vec3& newPos) {
			return setProperty(position, newPos);
		}

		bool setDir(const glm::vec3& newDir) {
			return setProperty(direction, newDir);
		}
	};

	struct PointLightStruct : public LightStructBase {
		PointLight pointLight;
		glm::vec3 position;

		PointLightStruct() {
			pointLight = PointLight();
		}

		bool setPos(const glm::vec3& newPos) {
			return setProperty(position, newPos);
		}
	};

	struct DirectionalLightStruct : public LightStructBase {
		DirectionalLight directionalLight;
		glm::vec3 direction;

		DirectionalLightStruct() {
			directionalLight = DirectionalLight();
		}

		bool setDir(const glm::vec3& newDir) {
			return setProperty(direction, newDir);
		}
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
		
		void subscribeToEvents();
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