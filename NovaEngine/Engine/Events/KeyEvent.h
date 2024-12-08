#pragma once

#include "Event.h"

namespace Nova {
	class KeyEvent : public Event {
	public:
		KeyEvent() : m_KeyCode(0) {}
		KeyEvent(int keycode)
			: m_KeyCode(keycode) {
		}

		inline int GetKeyCode() const {
			return m_KeyCode;
		}

		EVENT_CLASS_CATEGORY(EventCatKeyboard | EventCatInput);
	protected:
		int m_KeyCode;
	};

	class KeyPressedEvent : public KeyEvent {
	public:
		KeyPressedEvent(int keycode, int repeatCount)
			: KeyEvent(keycode), m_RepeatCount(repeatCount) {
		}

		inline int GetRepeatCount() const {
			return m_RepeatCount;
		}

		std::string ToString() const override {
			std::ostringstream oss;
			oss << "Key Pressed: " << GetKeyCode() << std::endl;
			return oss.str();
		}

		EVENT_CLASS_TYPE(KeyPressed);
	private:
		int m_RepeatCount;
	};

	class KeyReleasedEvent : public KeyEvent {
	public:
		KeyReleasedEvent(int keycode)
			: KeyEvent(keycode) { 
		}

		std::string ToString() const override {
			std::ostringstream oss;
			oss << "Key Released: " << GetKeyCode() << std::endl;
			return oss.str();
		}

		EVENT_CLASS_TYPE(KeyReleased);
	};

	class KeyStateEvent : public KeyEvent {
	public:
		KeyStateEvent(const bool* keys, GLfloat deltaTime) {
			std::copy(keys, keys + GLFW_KEY_LAST, m_Keys);
			this->deltaTime = deltaTime;
		}

		inline bool* getKeys() {
			return m_Keys;
		}

		inline GLfloat getDeltaTime() {
			return deltaTime;
		}

		std::string ToString() const override {
			std::ostringstream oss;
			oss << "KeyStateEvent: ";
			for (int i = 0; i < GLFW_KEY_LAST; ++i) {
				if (m_Keys[i]) {
					oss << "Key " << i << " pressed, ";
				}
			}
			return oss.str();
		}

		EVENT_CLASS_TYPE(KeyState);
	private:
		bool m_Keys[GLFW_KEY_LAST];
		GLfloat deltaTime;
	};
}