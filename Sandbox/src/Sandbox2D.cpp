#include "Sandbox2D.h"
#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f) {}

void Sandbox2D::OnAttach() {

}

void Sandbox2D::OnDetach() {

}

void Sandbox2D::OnUpdate(Hazel::Timestep ts) {
	m_CameraController.OnUpdate(ts);

	// Render
	Hazel::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
	Hazel::RenderCommand::Clear();

	Hazel::Renderer2D::BeginScene(m_CameraController.GetCamera());

	//std::dynamic_pointer_cast<Hazel::OpenGLShader>(m_SquareShader)->Bind();
	//std::dynamic_pointer_cast<Hazel::OpenGLShader>(m_SquareShader)->UploadUniformFloat4("u_Color", m_SquareColor);
	//Hazel::Renderer::Submit(m_SquareShader, m_SquareVertexArray, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

	Hazel::Renderer2D::DrawQuad({ 0.0f, 0.0f }, { 1.0f, 1.0f }, { 0.8f, 0.2f, 0.3f, 1.0f });
	Hazel::Renderer2D::DrawQuad({ 0.5f, 0.5f }, { 1.0f, 1.0f }, { 0.4f, 0.6f, 0.8f, 1.0f });
	Hazel::Renderer2D::EndScene();
}

void Sandbox2D::OnImGuiRender() {
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}

void Sandbox2D::OnEvent(Hazel::Event& e) {
	m_CameraController.OnEvent(e);
}