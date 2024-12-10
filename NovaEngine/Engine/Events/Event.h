#pragma once

#include <string>
#include <sstream>

namespace Nova {
#define EVENT_CLASS_TYPE(type) \
        static EventType GetStaticType() { return EventType::type; } \
        virtual EventType GetEventType() const override { return GetStaticType(); } \
        virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) \
        virtual int GetCategoryFlags() const override { return category; }

#define BIT(x) (1 << x)

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
		KeyState,
		
		MouseBtnPressed,
		MouseBtnReleased,
		MouseMoved,
		MouseScrolled,

		ModelSelected,
		ModelLoaded,
		ModelUnloaded,
		ModelTranslated,
		ModelRotated,
		ModelScaled,
		ModelAddedToManager,
		ModelRemovedFromManager,
		ModelFetchedFromManager,

		DirectionalLightAdded,
		DirectionalLightRemoved,
		SpotLightAdded,
		SpotLightRemoved,
		PointLightAdded,
		PointLightRemoved,

		BackgroundColorChanged,
		AmbientColorChanged,
		AlbedoColorChanged,
		MetallicChanged,
		RoughnessChanged,

		FieldOfViewChanged,
		NearClipChanged,
		FarClipChanged
	};

	enum EventCategory {
		None = 0,
		EventCatEngine = BIT(1),
		EventCatInput = BIT(2),
		EventCatKeyboard = BIT(3),
		EventCatMouse = BIT(4),
		EventCatMouseButton = BIT(5),
		EventCatWindow = BIT(6),
		EventCatModel = BIT(7)
	};

	class Event {
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
}