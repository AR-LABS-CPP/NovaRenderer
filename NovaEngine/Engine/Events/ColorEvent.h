#pragma once

#include "Event.h"

namespace Nova {
	class BackgroundColorChangedEvent : public Event {};
	class AmbientColorChangedEvent : public Event {};
	class AlbedoColorChangedEvent : public Event {};
}