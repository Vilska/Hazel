#include "Sandbox2D.h"
#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Platform/OpenGL/OpenGLShader.h"

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f) {}

void Sandbox2D::OnAttach() {
	m_SquareVertexArray = Hazel::VertexArray::Create();

	float squareVertices[5 * 4] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.5f,  0.5f, 0.0f,
		-0.5f,  0.5f, 0.0f
	};

	Hazel::Ref<Hazel::VertexBuffer> squareVertexBuffer;
	squareVertexBuffer.reset(Hazel::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
	squareVertexBuffer->SetLayout({
		{ Hazel::ShaderDataType::Float3, "a_Position" }
		});
	m_SquareVertexArray->AddVertexBuffer(squareVertexBuffer);

	uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };

	Hazel::Ref<Hazel::IndexBuffer> squareIndexBuffer;
	squareIndexBuffer.reset(Hazel::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
	m_SquareVertexArray->SetIndexBuffer(squareIndexBuffer);

	m_SquareShader = Hazel::Shader::Create("assets/shaders/FlatColor.glsl");
}

void Sandbox2D::OnDetach() {

}

void Sandbox2D::OnUpdate(Hazel::Timestep ts) {
	m_CameraController.OnUpdate(ts);

	// Render
	Hazel::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
	Hazel::RenderCommand::Clear();

	Hazel::Renderer::BeginScene(m_CameraController.GetCamera());

	std::dynamic_pointer_cast<Hazel::OpenGLShader>(m_SquareShader)->Bind();
	std::dynamic_pointer_cast<Hazel::OpenGLShader>(m_SquareShader)->UploadUniformFloat4("u_Color", m_SquareColor);

	Hazel::Renderer::Submit(m_SquareShader, m_SquareVertexArray, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

	Hazel::Renderer::EndScene();
}

void Sandbox2D::OnImGuiRender() {
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}

void Sandbox2D::OnEvent(Hazel::Event& e) {
	m_CameraController.OnEvent(e);
}