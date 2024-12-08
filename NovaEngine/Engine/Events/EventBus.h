#pragma once
#include <vector>
#include <functional>
#include <unordered_map>
#include <typeindex>
#include <memory>
#include <mutex>
#include <iostream>
#include "Event.h"

namespace Nova {
    class EventBus {
    public:
        EventBus(const EventBus&) = delete;
        EventBus& operator=(const EventBus&) = delete;

        static EventBus& getInstance() {
            static EventBus instance;
            return instance;
        }

        using EventHandler = std::function<void(Event&)>;

        template<typename T>
        void subscribe(const EventHandler& handler) {
            std::type_index typeIndex = std::type_index(typeid(T));
            std::lock_guard<std::mutex> lock(m_Mutex);
            
            m_Handlers[typeIndex].push_back(handler);
        }

        void dispatch(Event& event) {
            std::type_index typeIndex = std::type_index(typeid(event));
            std::lock_guard<std::mutex> lock(m_Mutex);

            auto it = m_Handlers.find(typeIndex);
            if (it != m_Handlers.end()) {
                for (auto& handler : it->second) {
                    handler(event);
                }
            }
        }

    private:
        EventBus() = default;

        std::unordered_map<std::type_index, std::vector<EventHandler>> m_Handlers;
        std::mutex m_Mutex;
    };
}