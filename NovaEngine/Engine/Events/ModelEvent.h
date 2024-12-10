#pragma once

#include "Event.h"

namespace Nova {
	class ModelSelectedEvent : public Event {
	public:
		ModelSelectedEvent() = default;
		ModelSelectedEvent(std::string& modelPath) : modelPath(modelPath) {
		}

		inline std::string& getModelPath() {
			return modelPath;
		}

		std::string ToString() const {
			std::ostringstream oss;
			oss << "Model selected, path: " << modelPath << std::endl;
			return oss.str();
		}

		EVENT_CLASS_TYPE(ModelSelected);
		EVENT_CLASS_CATEGORY(EventCatModel);
	private:
		std::string& modelPath;
	};
}