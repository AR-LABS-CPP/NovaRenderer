#pragma once

#include "Event.h"

namespace Nova {
    class WindowResizeEvent : public Event {
    public:
        WindowResizeEvent(unsigned int width, unsigned int height)
            : m_Width(width), m_Height(height) {
        }

        unsigned int GetWidth() const { return m_Width; }
        unsigned int GetHeight() const { return m_Height; }

        std::string ToString() const override {
            std::ostringstream oss;
            oss << "Window Size: " << m_Width << ", " << m_Height << std::endl;
            return oss.str();
        }

        EVENT_CLASS_TYPE(WindowResize);
        EVENT_CLASS_CATEGORY(EventCatWindow | EventCatInput);
    private:
        unsigned int m_Width, m_Height;
    };

    class WindowFocusEvent : public Event {
    public:
        WindowFocusEvent(bool focused) : m_Focused(focused) {}

        bool IsFocused() const { return m_Focused; }

        std::string ToString() const override {
            std::ostringstream oss;
            oss << "Window Focused: " << m_Focused << std::endl;
            return oss.str();
        }

        EVENT_CLASS_TYPE(WindowFocus);
        EVENT_CLASS_CATEGORY(EventCatWindow | EventCatInput);
    private:
        bool m_Focused;
    };

    class WindowLostFocusEvent : public Event {
    public:
        WindowLostFocusEvent() {}

        std::string ToString() const override {
            std::ostringstream oss;
            oss << "Window Focus lost" << std::endl;
            return oss.str();
        }

        EVENT_CLASS_TYPE(WindowLostFocus);
        EVENT_CLASS_CATEGORY(EventCatWindow | EventCatInput);
    };

    class WindowMovedEvent : public Event {
    public:
        WindowMovedEvent(int x, int y) : m_X(x), m_Y(y) {}

        int GetX() const { return m_X; }
        int GetY() const { return m_Y; }

        std::string ToString() const override {
            std::ostringstream oss;
            oss << "Window New Position: " << m_X << ", " << m_Y << std::endl;
            return oss.str();
        }

        EVENT_CLASS_TYPE(WindowMoved);
        EVENT_CLASS_CATEGORY(EventCatWindow | EventCatInput);
    private:
        int m_X, m_Y;
    };
}
