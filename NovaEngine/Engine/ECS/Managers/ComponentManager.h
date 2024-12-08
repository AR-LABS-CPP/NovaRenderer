#pragma once

#include "pch.h"
#include "ECS/Entities/Entity.h"
#include "Components/BaseComponent.h"

namespace Nova {
	class ComponentManager {
	public:
		template <typename T>
		void addComponent(EntityID entity, T component) {
			std::type_index type = typeid(T);
			components[type][entity] = std::make_unique<T>(std::move(component));
		}

		template <typename T>
		T* getComponent(EntityID entity) {
			std::type_index type = typeid(T);
			if (components[type].find(entity) != components[type].end()) {
				return static_cast<T*>(components[type][entity].get());
			}

			return nullptr;
		}

		template<typename T>
		void removeComponent(EntityID entity) {
			std::type_index type = typeid(T);
			components[type].erase(entity);
		}
	private:
		std::unordered_map<std::type_index, std::unordered_map<EntityID, std::unique_ptr<IComponent>>> components;
	};
}