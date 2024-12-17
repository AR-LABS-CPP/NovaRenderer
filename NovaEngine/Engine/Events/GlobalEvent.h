#pragma once

#include "Event.h"

namespace Nova {
	class BackgroundColorChangedEvent : public Event {
	public:
		BackgroundColorChangedEvent() = default;
		BackgroundColorChangedEvent(
			ImVec4 bgColor
		) : xComp(bgColor.x), yComp(bgColor.y), zComp(bgColor.z), wComp(bgColor.w) {}

		std::string ToString() const {
			std::ostringstream oss;
			oss << "Background color changed: " << xComp << ", " << yComp << ", " << zComp << std::endl;
			return oss.str();
		}

		float getXComp() const { return xComp; }
		float getYComp() const { return yComp; }
		float getZComp() const { return zComp; }
		float getWComp() const { return wComp; }

		EVENT_CLASS_TYPE(BackgroundColorChanged);
		EVENT_CLASS_CATEGORY(EventCatGlobal);
	private:
		float xComp, yComp, zComp, wComp;
	};

	class ResetAllEvent : public Event {
	public:
		EVENT_CLASS_TYPE(ResetAll);
		EVENT_CLASS_CATEGORY(EventCatGlobal);
	};
}