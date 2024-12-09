#pragma once

#include "pch.h"
#include "ECS/Entities/Entity.h"
#include "ECS/Components/BaseComponent.h"

namespace Nova {
	class ComponentManager {
	public:
		template <typename T>
		void addComponent(EntityID entity, T component) {
			std::type_index type = typeid(T);
			components[type][entity] = std::make_unique<T>(std::move(component));
		}

		template<typename T>
		T* getComponent(EntityID entity) {
			std::type_index type = typeid(T);
			if (components[type].find(entity) != components[type].end()) {
				return static_cast<T*>(components[type][entity].get());
			}

			return nullptr;
		}

		template<typename T>
		std::vector<T*> getComponents() {
			std::type_index type = typeid(T);
			std::vector<T*> result;

			if (components.find(type) != components.end()) {
				for (auto& pair : components[type]) {
					result.push_back(static_cast<T*>(pair.second.get()));
				}
			}

			return result;
		}

		template<typename T>
		void removeComponent(EntityID entity) {
			std::type_index type = typeid(T);
			components[type].erase(entity);
		}

		template<typename... Components>
		std::vector<EntityID> getEntitiesWithComponents() {
			std::vector<EntityID> matchingEnts;

			for (const auto& [entity, _] : components[typeid(Components)...]) {
				bool hasAllComponents = (... && (components[typeid(Components)].count(entity) > 0));
				if (hasAllComponents) {
					matchingEnts.push_back(entity);
				}
			}

			return matchingEnts;
		}
	private:
		std::unordered_map<std::type_index, std::unordered_map<EntityID, std::unique_ptr<IComponent>>> components;
	};
}