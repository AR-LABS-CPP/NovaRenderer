#pragma once

#include "Event.h"

namespace Nova {
    class WindowCloseEvent : public Event {
    public:
        WindowCloseEvent() {}

        std::string ToString() const override {
            return "WindowCloseEvent";
        }

        EVENT_CLASS_TYPE(WindowClose)
    };

    class WindowResizeEvent : public Event {
    public:
        WindowResizeEvent(unsigned int width, unsigned int height)
            : m_Width(width), m_Height(height) {
        }

        unsigned int GetWidth() const { return m_Width; }
        unsigned int GetHeight() const { return m_Height; }

        std::string ToString() const override {}

        EVENT_CLASS_TYPE(WindowResize)

    private:
        unsigned int m_Width, m_Height;
    };

    class WindowFocusEvent : public Event {
    public:
        WindowFocusEvent(bool focused) : m_Focused(focused) {}

        bool IsFocused() const { return m_Focused; }

        std::string ToString() const override {
            return m_Focused ? "WindowFocusEvent: Focused" : "WindowFocusEvent: Lost Focus";
        }

        EVENT_CLASS_TYPE(WindowFocus)

    private:
        bool m_Focused;
    };

    class WindowLostFocusEvent : public Event {
    public:
        WindowLostFocusEvent() {}

        std::string ToString() const override {
            return "WindowLostFocusEvent";
        }

        EVENT_CLASS_TYPE(WindowLostFocus)
    };

    class WindowMovedEvent : public Event {
    public:
        WindowMovedEvent(int x, int y) : m_X(x), m_Y(y) {}

        int GetX() const { return m_X; }
        int GetY() const { return m_Y; }

        std::string ToString() const override {}

        EVENT_CLASS_TYPE(WindowMoved)

    private:
        int m_X, m_Y;
    };
}
