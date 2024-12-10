#pragma once

#include <typeinfo>

#define NOVA_DEFAULT_LOGGER_NAME "NovaLogger"
#define NOVA_PLATFORM_WINDOWS

#if defined(NOVA_PLATFORM_WINDOWS)
	#define NOVA_BREAK_DEBUG __debugbreak();
#elif defined(NOVA_PLATFORM_MAC)
	#define NOVA_BREAK_DEBUG __builtin_debugtrap();
#else
	#define NOVA_BREAK_DEBUG __builtin_trap();
#endif

#ifndef NOVA_CONFIG_RELEASE
	#define NOVA_LOG(level, ...) \
		if(spdlog::get(NOVA_DEFAULT_LOGGER_NAME)) \
			{ spdlog::get(NOVA_DEFAULT_LOGGER_NAME)->level("[{}] {}\n\tfile:{}\n\tline: {}", typeid(*this).name(), __VA_ARGS__); }

	#define NOVA_TRACE(...) NOVA_LOG(trace, __VA_ARGS__, __FILE__, __LINE__)
	
	#define NOVA_DEBUG(...) NOVA_LOG(debug, __VA__ARGS__, __FILE__, __LINE__)
	
	#define NOVA_INFO(...)	NOVA_LOG(info, __VA_ARGS__, __FILE__, __LINE__)
	
	#define NOVA_WARN(...)	NOVA_LOG(warn, __VA_ARGS__, __FILE__, __LINE__)
	
	#define NOVA_ERROR(...) NOVA_LOG(error, __VA_ARGS__, __FILE__, __LINE__)
	
	#define NOVA_FATAL(...) NOVA_LOG(critical, __VA_ARGS__, __FILE__, __LINE__)

	#define NOVA_ASSERT(x, msg) if ((x)) {} else { NOVA_FATAL("ASSERTION FAILED - {}\n\t{}\n\tin file: {}\n\ton line: {}", #x, msg, __FILE__, __LINE__); NOVA_BREAK_DEBUG }
#else
	#define NOVA_TRACE(...) (void)0
	#define NOVA_DEBUG(...) (void)0
	#define NOVA_INFO(...) (void)0
	#define NOVA_WARN(...) (void)0
	#define NOVA_ERROR(...) (void)0
	#define NOVA_FATAL(...) (void)0
#endif