#pragma once

#include "OrthographicCamera.h"

#include "Texture.h"

namespace Hazel {

	struct RendererPropsColor {
		const glm::vec3 Position;
		const glm::vec2 Size;
		const glm::vec4 Color;
	};

	struct RendererPropsTexture {
		const glm::vec3 Position;
		const glm::vec2 Size;
		const Ref<Texture2D> Texture;
		const float TilingFactor;
	};

	class Renderer2D {
	public:
		static void Init();
		static void Shutdown();
		static void Flush();

		static void BeginScene(const OrthographicCamera& camera);
		static void EndScene();
		
		static void DrawQuad(const RendererPropsColor& props);
		static void DrawQuad(const RendererPropsTexture& props);
	};

}