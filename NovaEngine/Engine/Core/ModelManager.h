#pragma once

#include "pch.h"
#include "Model.h"
#include "Events/EventBus.h"

namespace Nova {
	class ModelManager {
	public:
		ModelManager() = default;
		~ModelManager() = default;

		void addModel(Model* model);
		Model* getModel(unsigned int modelId);
		bool removeModel(unsigned int modelId);
	private:
		std::unordered_map<unsigned int, Model*> models;
	};
}