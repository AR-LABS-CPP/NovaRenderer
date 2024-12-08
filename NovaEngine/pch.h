#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <set>
#include <memory>
#include <queue>
#include <map>
#include <unordered_map>
#include <string>
#include <functional>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imgui_internal.h"

#include "Common.h"
#include "Events/EventBus.h"

#ifdef NOVA_PLATFORM_WINDOWS
#endif // NOVA_PLATFORM_WINDOWS

#ifdef NOVA_PLATFORM_LINUX
#endif // NOVA_PLATFORM_LINUX

#ifdef NOVA_PLATFORM_MAC
#endif // NOVA_PLATFORM_MAC