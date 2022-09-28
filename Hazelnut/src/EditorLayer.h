#pragma once

#include "Hazel.h"

namespace Hazel {

	class EditorLayer : public Layer {
	public:
		EditorLayer();
		virtual ~EditorLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		virtual void OnUpdate(Timestep ts) override;
		virtual void OnImGuiRender() override;
		virtual void OnEvent(Event& e) override;
	private:
		OrthographicCameraController m_CameraController;

		Ref<Hazel::VertexArray> m_SquareVertexArray;
		Ref<Hazel::Shader> m_SquareShader;
		Ref<Hazel::Framebuffer> m_Framebuffer;

		Ref<Hazel::Texture2D> m_CheckerboardTexture;
		Ref<Hazel::Texture2D> m_SpriteSheet;
		Ref<Hazel::SubTexture2D> m_TextureStairs;

		bool m_ViewportFocused = false, m_ViewportHovered = false;
		glm::vec2 m_ViewportSize;

		glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
	};

}

