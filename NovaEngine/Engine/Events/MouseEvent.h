#pragma once

#include "Event.h"

namespace Nova {
	class MouseMovedEvent : public Event {
	public:
		MouseMovedEvent(float x, float y)
			: m_MouseX(x), m_MouseY(y) {}
		
		inline float GetX() const {
			return m_MouseX;
		}

		inline float GetY() const {
			return m_MouseY;
		}

		std::string ToString() const override {}

		EVENT_CLASS_TYPE(MouseMoved);
		EVENT_CLASS_CATEGORY(EventCatMouse | EventCatInput);
	private:
		float m_MouseX, m_MouseY;
	};

	class MouseScrolledEvent : public Event {
	public:
		MouseScrolledEvent(float xOffset, float yOffset)
			: m_XOffset(xOffset), m_YOffset(yOffset) {}

		inline float GetXOffset() const {
			return m_XOffset;
		}

		inline float GetYOffset() const {
			return m_YOffset;
		}

		EVENT_CLASS_TYPE(MouseScrolled);
		EVENT_CLASS_CATEGORY(EventCatMouse | EventCatInput);
	private:
		float m_XOffset, m_YOffset;
	};
}