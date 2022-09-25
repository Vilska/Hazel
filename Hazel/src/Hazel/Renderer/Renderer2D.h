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
		float Tiling;
	};

	class Renderer2D {
	public:
		static void Init();
		static void Shutdown();

		static void BeginScene(const OrthographicCamera& camera);
		static void EndScene();
		
		//static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color); Is this really needed?
		static void DrawQuad(const RendererPropsColor& props);
		//static void DrawQuad(const RendererPropsTexture& props); Is this really needed?
		static void DrawQuad(const RendererPropsTexture& props);
	};

}