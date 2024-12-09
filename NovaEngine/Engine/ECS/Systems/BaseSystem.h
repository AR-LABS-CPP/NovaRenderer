#pragma once

#include "ECS/Managers/ComponentManager.h"

namespace Nova {
	class ISystem {
	public:
		virtual ~ISystem() = default;
		virtual void update(float deltaTime) = 0;
	};
}