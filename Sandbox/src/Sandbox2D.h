//#pragma once
//
//#include "Hazel.h"
//
//class Sandbox2D : public Hazel::Layer {
//public:
//	Sandbox2D();
//	virtual ~Sandbox2D() = default;
//
//	virtual void OnAttach() override;
//	virtual void OnDetach() override;
//
//	virtual void OnUpdate(Hazel::Timestep ts) override;
//	virtual void OnImGuiRender() override;
//	virtual void OnEvent(Hazel::Event& e) override;
//private:
//	Hazel::OrthographicCameraController m_CameraController;
//
//	Hazel::Ref<Hazel::VertexArray> m_SquareVertexArray;
//	Hazel::Ref<Hazel::Shader> m_SquareShader;
//	Hazel::Ref<Hazel::Framebuffer> m_Framebuffer;
//
//	Hazel::Ref<Hazel::Texture2D> m_CheckerboardTexture;
//	Hazel::Ref<Hazel::Texture2D> m_SpriteSheet;
//	Hazel::Ref<Hazel::SubTexture2D> m_TextureStairs;
//
//	glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
//};
