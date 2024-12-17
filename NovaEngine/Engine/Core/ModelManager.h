#pragma once

#include "pch.h"
#include "Model.h"
#include "Events/EventQueue.h"
#include "Events/GlobalEvent.h"

namespace Nova {
	class ModelManager {
	public:
		ModelManager();
		~ModelManager() = default;

		void addModel(Model model);
		Model getModel(unsigned int modelId);
		std::vector<Model> getAllModels();
		bool removeModel(unsigned int modelId);

		void subscribeToEvents();
	private:
		std::unordered_map<unsigned int, Model> models;

		EventQueue& eventQueue = EventQueue::getInstance();
	};
}