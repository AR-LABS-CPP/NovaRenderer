#pragma once

#include <string>

namespace Nova {
	enum class EventType {
		None = 0,
		WindowClose,
		WindowResize,
		WindowFocus,
		WindowLostFocus,
		WindowMoved,
		EngineTick,
		EngineUpdate,
		EngineRender,
		KeyPressed,
		KeyReleased,
		MouseBtnPressed,
		MouseBtnReleased,
		MouseMoved,
		MouseScrolled
	};

	enum EventCategory {
		None = 0,
		EventCatEngine = 1 << 0,
		EventCatInput = 1 << 1,
		EventCatKeyboard = 1 << 2,
		EventCatMouse = 1 << 3,
		EventCatMouseButton = 1 << 4,
		EventCatWindow = 1 << 5
	};

#define EVENT_CLASS_TYPE(type) \
    static EventType GetStaticType() { return EventType::type; } \
    virtual EventType GetEventType() const override { return GetStaticType(); } \
    virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) \
     virtual int GetCategoryFlags() const override { return category; }

	class Event {
		friend class EventDispatcher;

	public:
		virtual ~Event() = default;

		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;
		virtual std::string ToString() const { return GetName(); }

		inline bool IsInCategory(EventCategory category) {
			return GetCategoryFlags() & category;
		}
	protected:
		bool m_Handled = false;
	};

	/*class EventDispatcher {
		template<typename T>
		using EventFn = std::function<bool(T&)>;

	public:
		EventDispatcher(Event& event)
			: m_Event(event) {}

		template <typename T>
		bool Dispatch(EventFn<T> func) {
			if (m_Event.GetEventType() == T::GetStaticType()) {
				m_Event.m_Handled = func(*(T*)&m_Event);
				return true
			}

			return false;
		}

	private:
		Event& m_Event;
	};*/
}