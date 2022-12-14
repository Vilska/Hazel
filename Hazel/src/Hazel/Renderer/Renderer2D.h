#pragma once

#include "OrthographicCamera.h"

#include "Texture.h"

#include "Camera.h"
#include "EditorCamera.h"

#include "Hazel/Scene/Components.h"

namespace Hazel {

	struct RendererPropsColor {
		const glm::mat4 Transform;
		const glm::vec4 Color;
		int EntityID = -1;
	};

	struct RendererPropsTexture {
		const glm::mat4 Transform;
		const Ref<Texture2D> Texture;
		const float TilingFactor;
		int EntityID = -1;
	};

	struct RendererPropsSubTexture {
		const glm::mat4 Transform;
		const Ref<SubTexture2D> SubTexture;
		const float TilingFactor;
	};

	class Renderer2D {
	public:
		static void Init();
		static void Shutdown();
		static void Flush();

		static void BeginScene(const Camera& camera, const glm::mat4& transform);
		static void BeginScene(const EditorCamera& camera);
		static void BeginScene(const OrthographicCamera& camera);
		static void EndScene();
		
		static void DrawQuad(const RendererPropsColor& props);
		static void DrawQuad(const RendererPropsTexture& props);
		static void DrawQuad(const RendererPropsSubTexture& props);

		static void DrawSprite(const glm::mat4& transform, SpriteRendererComponent& src, int entityID);

		// Stats
		struct Statistics {
			uint32_t DrawCalls = 0;
			uint32_t QuadCount = 0;

			uint32_t GetTotalVertexCount() { return QuadCount * 4; }
			uint32_t GetTotalIndexCount() { return QuadCount * 6; }
		};

		static void ResetStats();
		static Statistics GetStats();
	private:
		static void StartNewBatch();
	};

}
