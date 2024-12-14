#pragma once

#include "Core/SpotLight.h"
#include "Core/PointLight.h"
#include "Core/DirectionalLight.h"
#include <glm/glm.hpp>
#include <iostream>

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
			position = glm::vec3(1.0);
			direction = glm::vec3(1.0);
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
			position = glm::vec3(1.0);
		}

		bool setPos(const glm::vec3& newPos) {
			return setProperty(position, newPos);
		}
	};

	struct DirectionalLightStruct : public LightStructBase {
		DirectionalLight directionalLight;
		glm::vec3 direction;
		bool isActive;

		DirectionalLightStruct() {
			directionalLight = DirectionalLight();
			direction = glm::vec3(1.0);
			isActive = false;
		}

		bool setDir(const glm::vec3& newDir) {
			return setProperty(direction, newDir);
		}

		bool toggleActive() {
			return setProperty(isActive, isActive ? false : true);
		}
	};
}