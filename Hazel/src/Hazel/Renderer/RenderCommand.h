#pragma once

#include "RendererAPI.h"

namespace Hazel {

	class RenderCommand {
	public:
		static void Init() {
			m_RendererAPI->Init();
		}

		static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
			m_RendererAPI->SetViewport(x, y, width, height);
		}

		static void SetClearColor(const glm::vec4& color) {
			m_RendererAPI->SetClearColor(color);
		}

		static void Clear() {
			m_RendererAPI->Clear();
		}

		static void DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t count = 0) {
			m_RendererAPI->DrawIndexed(vertexArray, count);
		}
	private:
		static Scope<RendererAPI> m_RendererAPI;
	};

}