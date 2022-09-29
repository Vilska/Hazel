#include "hzpch.h"
#include "Scene.h"

#include <glm/glm.hpp>

namespace Hazel {

	static void DoMath(const glm::mat4& transform) {}


	Scene::Scene() {

		struct TransformComponent {
			glm::mat4 Transform;

			TransformComponent() = default;
			TransformComponent(const TransformComponent&) = default;
			TransformComponent(const glm::mat4& transform)
				: Transform(transform) {}

			operator const glm::mat4& () { return Transform; }
		};

		TransformComponent transform;
		DoMath(transform);

		entt::entity entity = m_Registry.create();

		m_Registry.emplace<TransformComponent>(entity);

		m_Registry.remove<TransformComponent>(entity);

	}

	Scene::~Scene() {

	}

}