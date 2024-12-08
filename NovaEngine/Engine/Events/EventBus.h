#pragma once

#include <vector>
#include <functional>
#include <unordered_map>
#include <typeindex>
#include <iostream>
#include "Event.h"

namespace Nova {
	class EventBus {
	public:
		using EventHandler = std::function<void(Event&)>;

		template<typename T>
		void subscribe(const EventHandler& handler) {
			auto type = std::type_index(typeid(T));
			m_Handlers[type].push_back([handler](Event& event) {
				if (event.GetEventType() == T::GetStaticType()) {
					handler(event);
				}
			});
		}

		void dispatch(Event& event) {
			auto type = std::type_index(typeid(event));

			if (m_Handlers.find(type) != m_Handlers.end()) {
				for (auto& handler : m_Handlers[type]) {
					handler(event);
				}
			}
		}
	private:
		std::unordered_map<std::type_index, std::vector<EventHandler>> m_Handlers;
	};
}