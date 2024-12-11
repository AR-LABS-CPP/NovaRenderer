#pragma once

#include "pch.h"
#include "Event.h"

/*
    Please note that I don't like smart pointers
    but I had to use them here cause of no other
    choice.
*/
namespace Nova {
    class EventQueue {
    public:
        using EventHandler = std::function<void(Event&)>;

        EventQueue(const EventQueue&) = delete;
        EventQueue& operator=(const EventQueue&) = delete;

        static EventQueue& getInstance() {
            static EventQueue instance;
            return instance;
        }

        template<typename T>
        void subscribe(const EventHandler& handler) {
            std::type_index typeIndex = std::type_index(typeid(T));
            mHandlers[typeIndex].push_back(handler);
        }

        void enqueue(std::unique_ptr<Event> event) {
            eventQueue.push(std::move(event));
        }

        void process() {
            while (!eventQueue.empty()) {
                auto& event = eventQueue.front();
                dispatch(*event);
                eventQueue.pop();
            }
        }

        ~EventQueue() = default;

    private:
        EventQueue() = default;

        std::queue<std::unique_ptr<Event>> eventQueue;
        std::unordered_map<std::type_index, std::vector<EventHandler>> mHandlers;

        void dispatch(Event& event) {
            std::type_index typeIndex = std::type_index(typeid(event));

            auto it = mHandlers.find(typeIndex);
            if (it != mHandlers.end()) {
                for (auto& handler : it->second) {
                    handler(event);
                }
            }
        }
    };
}