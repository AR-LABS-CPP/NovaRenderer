#pragma once

#include "pch.h"
#include "ECS/Managers/ComponentManager.h"
#include "ECS/Systems/BaseSystem.h"

namespace Nova {
	class ECS {
	public:
		ECS() = default;

		void addSystem(std::unique_ptr<ISystem> system) {}

		void updateSystem(float deltaTime) {}

		template<typename T>
		void addComponentToEntity(EntityID entity, T component) {
			manager.addComponent(entity, component);
		}

		template<typename T>
		T* getComponentFromEntity(EntityID entity) {
			return manager.getComponent<T>(entity);
		}
	private:
		ComponentManager manager;
		std::vector<std::unique_ptr<ISystem>> systems;
	};
}