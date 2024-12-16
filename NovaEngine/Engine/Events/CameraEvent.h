#pragma once

#include "Event.h"

namespace Nova {
	class CameraFieldOfViewChangedEvent : public Event {
	public:
		CameraFieldOfViewChangedEvent() = default;
		CameraFieldOfViewChangedEvent(float fovValue)
			: fieldOfView(fovValue) {}

		std::string ToString() const {
			std::ostringstream oss;
			oss << "Field of view changed to: " << fieldOfView << std::endl;
			return oss.str();
		}

		float getFieldOfView() {
			return fieldOfView;
		}

		EVENT_CLASS_TYPE(FieldOfViewChanged);
		EVENT_CLASS_CATEGORY(EventCatGlobal);
	private:
		float fieldOfView;
	};
	
	class CameraNearClipChangedEvent : public Event {
	public:
		CameraNearClipChangedEvent() = default;
		CameraNearClipChangedEvent(float nearClipVal)
			: nearClip(nearClipVal) {}

		std::string ToString() const {
			std::ostringstream oss;
			oss << "Near clip changed to: " << nearClip << std::endl;
			return oss.str();
		}

		float getNearClip() {
			return nearClip;
		}

		EVENT_CLASS_TYPE(NearClipChanged);
		EVENT_CLASS_CATEGORY(EventCatGlobal);
	private:
		float nearClip;
	};
	
	class CameraFarClipChangedEvent : public Event {
	public:
		CameraFarClipChangedEvent() = default;
		CameraFarClipChangedEvent(long farClipVal)
			: farClip(farClipVal) {}

		std::string ToString() const {
			std::ostringstream oss;
			oss << "Far clip changed to: " << farClip << std::endl;
			return oss.str();
		}

		long getFarClip() {
			return farClip;
		}

		EVENT_CLASS_TYPE(FarClipChanged);
		EVENT_CLASS_CATEGORY(EventCatGlobal);
	private:
		long farClip;
	};

	class CameraMovementSpeedChangedEvent : public Event {
	public:
		CameraMovementSpeedChangedEvent() = default;
		CameraMovementSpeedChangedEvent(long movementSpeed)
			: movementSpeed(movementSpeed) {
		}

		std::string ToString() const {
			std::ostringstream oss;
			oss << "Movement speed changed to: " << movementSpeed << std::endl;
			return oss.str();
		}

		float getMovementSpeed() {
			return movementSpeed;
		}

		EVENT_CLASS_TYPE(FarClipChanged);
		EVENT_CLASS_CATEGORY(EventCatGlobal);
	private:
		float movementSpeed;
	};
}