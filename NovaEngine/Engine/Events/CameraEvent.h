#pragma once

#include "Event.h"

namespace Nova {
	class FieldOfViewChangedEvent : public Event {};
	class NearClipChangedEvent : public Event {};
	class FarClipChangedEvent : public Event {};
}