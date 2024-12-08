#pragma once

namespace Nova {
	using EntityID = unsigned int;
	
	class Entity {
	public:
		
		Entity() : id(idCounter++) {}
		
		EntityID getID() const { return id; }
	private:
		static EntityID idCounter;
		EntityID id;
	};

	EntityID Entity::idCounter = 0;
}