#pragma once

namespace Nova {
	class LogManager {
	public:
		LogManager() = default;
		~LogManager() = default;

		void initialize();
		void shutdown();
	private:
	};
}