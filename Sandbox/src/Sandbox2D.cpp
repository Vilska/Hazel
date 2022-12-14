//#include "Sandbox2D.h"
//#include "imgui/imgui.h"
//
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>
//
//#include <chrono>
//
//#include <chrono>
//
//Sandbox2D::Sandbox2D()
//	: Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f) {}
//
//void Sandbox2D::OnAttach() {
//	m_CheckerboardTexture = Hazel::Texture2D::Create("assets/textures/Checkerboard.png");
//}
//
//void Sandbox2D::OnDetach() {
//
//}
//
//void Sandbox2D::OnUpdate(Hazel::Timestep ts) {
//	HZ_PROFILE_FUNCTION();
//	
//	m_CameraController.OnUpdate(ts);
//
//	Hazel::Renderer2D::ResetStats();
//	Hazel::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
//	Hazel::RenderCommand::Clear();
//
//	Hazel::Renderer2D::BeginScene(m_CameraController.GetCamera());
//	Hazel::Renderer2D::DrawQuad({ { -1.0f, 0.0f, 0.0f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f } });
//	Hazel::Renderer2D::DrawQuad({ { 0.5f, -0.5f, 0.0f }, {0.5f, 0.75f}, {0.2f, 0.3f, 0.8f, 1.0f} });
//	Hazel::Renderer2D::DrawQuad({ { -5.0f, -5.0f, -0.1f }, { 10.0f, 10.0f }, m_CheckerboardTexture, 10.0f});
//
//	for (float y = -5.0f; y < 5.0f; y += 0.5f) {
//		for (float x = -5.0f; x < 5.0f; x += 0.5f) {
//			glm::vec4 color = { (x + 5.0f) / 10.0f, 0.4f, (y + 5.0f) / 10.0f, 1.0f };
//			Hazel::Renderer2D::DrawQuad({ { x, y, 1.0f }, { 0.45f, 0.45f }, color });
//		}
//	}
//
//	Hazel::Renderer2D::EndScene();
//}
//
//void Sandbox2D::OnImGuiRender() {
//	HZ_PROFILE_FUNCTION();
//
//	ImGui::Begin("Settings");
//
//	auto stats = Hazel::Renderer2D::GetStats();
//	ImGui::Text("Renderer2D Stats:");
//	ImGui::Text("Draw Calls: %d", stats.DrawCalls);
//	ImGui::Text("Quads: %d", stats.QuadCount);
//	ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
//	ImGui::Text("Indices: %d", stats.GetTotalIndexCount());
//
//	ImGui::End();
//}
//
//void Sandbox2D::OnEvent(Hazel::Event& e) {
//	m_CameraController.OnEvent(e);
//}