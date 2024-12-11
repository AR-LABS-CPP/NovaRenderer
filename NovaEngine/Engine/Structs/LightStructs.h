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

		SpotLightStruct() = default;

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

		PointLightStruct() = default;

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
		}

		bool setDir(const glm::vec3& newDir) {
			return setProperty(direction, newDir);
		}

		bool toggleActive() {
			std::cout << isActive << std::endl;
			return setProperty(isActive, isActive ? false : true);
		}
	};
}