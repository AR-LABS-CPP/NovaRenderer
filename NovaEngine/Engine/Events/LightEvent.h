#pragma once

#include "Event.h"

namespace Nova {
	class LightEvent : public Event {
	public:
		LightEvent() = default;
		LightEvent(unsigned int lightId)
			: lightId(lightId) {}

		inline unsigned int getLightId() {
			return lightId;
		}

		EVENT_CLASS_CATEGORY(EventCatLight);
	private:
		unsigned int lightId;
	};

	class DirectionalLightAddedEvent : public LightEvent {
	public:
		DirectionalLightAddedEvent() = default;

		EVENT_CLASS_TYPE(DirectionalLightAdded);
	};

	class DirectionalLightRemovedEvent : public LightEvent {
	public:
		DirectionalLightRemovedEvent() = default;

		EVENT_CLASS_TYPE(DirectionalLightRemoved);
	};

	class PointLightAddedEvent : public LightEvent {
	public:
		PointLightAddedEvent() = default;

		EVENT_CLASS_TYPE(PointLightAdded);
	};
	
	class PointLightRemovedEvent : public LightEvent {
	public:
		PointLightRemovedEvent() = default;
		PointLightRemovedEvent(unsigned int pointLightId)
			: LightEvent(pointLightId) {}

		EVENT_CLASS_TYPE(PointLightRemoved);
	};
	
	class SpotLightAddedEvent : public LightEvent {
	public:
		SpotLightAddedEvent() = default;

		EVENT_CLASS_TYPE(SpotLightAdded);
	};
	
	class SpotLightRemovedEvent : public LightEvent {
	public:
		SpotLightRemovedEvent() = default;
		SpotLightRemovedEvent(unsigned int spotLightId)
			: LightEvent(spotLightId) {}

		EVENT_CLASS_TYPE(SpotLightRemoved);
	};
}