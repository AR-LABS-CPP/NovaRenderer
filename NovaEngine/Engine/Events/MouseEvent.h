#pragma once

#include "Event.h"

namespace Nova {
	class MouseMovedEvent : public Event {
	public:
		MouseMovedEvent(float x, float y, bool* keys)
			: m_MouseX(x), m_MouseY(y) {
			std::copy(keys, keys + GLFW_KEY_LAST, m_Keys);
		}
		
		inline float GetX() const {
			return m_MouseX;
		}

		inline float GetY() const {
			return m_MouseY;
		}

		inline bool* getKeys() {
			return m_Keys;
		}

		std::string ToString() const override {
			std::ostringstream oss;
			oss << "Mouse Coords (moved): " << m_MouseX << ", " << m_MouseY << std::endl;
			return oss.str();
		}

		EVENT_CLASS_TYPE(MouseMoved);
		EVENT_CLASS_CATEGORY(EventCatMouse | EventCatInput);
	private:
		float m_MouseX, m_MouseY;
		bool m_Keys[GLFW_KEY_LAST];
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

		std::string ToString() const override {
			std::ostringstream oss;
			oss << "Mouse Coords (offset): " << m_XOffset << ", " << m_YOffset << std::endl;
			return oss.str();
		}

		EVENT_CLASS_TYPE(MouseScrolled);
		EVENT_CLASS_CATEGORY(EventCatMouse | EventCatInput);
	private:
		float m_XOffset, m_YOffset;
	};
}