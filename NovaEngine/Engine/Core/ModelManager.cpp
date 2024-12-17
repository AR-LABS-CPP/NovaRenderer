#include "pch.h"
#include "ModelManager.h"

namespace Nova {
	ModelManager::ModelManager() {
		subscribeToEvents();
	}

	void ModelManager::addModel(Model model) {
		if (models.find(model.modelId) != models.end()) {
			NOVA_WARN("Model is already added, ID: " + model.modelId);
			return;
		}

		models[model.modelId] = model;
		NOVA_ASSERT(models.find(model.modelId) != models.end(), "Model could not be added");
	}

	Model ModelManager::getModel(unsigned int modelId) {
		NOVA_ASSERT(modelId > 0, "Must provide a valid model id");

		if (models.find(modelId) != models.end()) {
			return models[modelId];
		}

		NOVA_WARN("Model could not be found, ID: " + modelId);

		return Model();
	}

	std::vector<Model> ModelManager::getAllModels() {
		std::vector<Model> result;

		for (auto& it : models) {
			result.push_back(it.second);
		}

		return result;
	}

	bool ModelManager::removeModel(unsigned int modelId) {
		if (models.find(modelId) == models.end()) {
			NOVA_WARN("Model does not exist, ID: " + modelId);
			return true;
		}

		models.erase(modelId);
		NOVA_ASSERT(models.find(modelId) == models.end(), "Model could not be removed");
		
		return true;
	}

	void ModelManager::subscribeToEvents() {
		eventQueue.subscribe<ResetAllEvent>([this](Event& event) {
			models.clear();
		});
	}
}