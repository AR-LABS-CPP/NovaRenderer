#pragma once

#include "Logging.h"

namespace Nova {
	class Engine {
	public:
		Engine() = default;
		~Engine();

		void initializeAndRun();
		void shutdown();
	private:
		Nova::LogManager logManager;
	};
}