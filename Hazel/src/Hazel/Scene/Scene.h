#pragma once

#include <entt.hpp>

#include "Hazel/Core/Timestep.h"

namespace Hazel {

	class Entity; // Forward declaration

	class Scene {
		friend class Entity;
	public:
		Scene();
		~Scene();

		Entity CreateEntity(const std::string& name = "");

		void OnUpdate(Timestep ts);
	private:
		entt::registry m_Registry;
	};

}
