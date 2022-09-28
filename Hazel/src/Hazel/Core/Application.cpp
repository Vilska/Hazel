#include "hzpch.h"
#include "Application.h"

#include "Hazel/Renderer/Renderer.h"

#include "Input.h"

#include <GLFW/glfw3.h>

namespace Hazel {

	Application* Application::s_Instance = nullptr;

	// Main class, engines heart, declared in header file
	Application::Application(const std::string& name) {
		HZ_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window = Window::Create();
		m_Window->SetEventCallback(HZ_BIND_EVENT_FN(Application::OnEvent));

		Renderer::Init();

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);
	}

	Application::~Application() {
		Renderer::Shutdown();
	}

	void Application::PushLayer(Layer* layer) {
		m_LayerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* layer) {
		m_LayerStack.PushOverlay(layer);
	}

	void Application::Close() {
		m_Running = false;
	}

	void Application::OnEvent(Event& e) {
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(HZ_BIND_EVENT_FN(Application::OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(HZ_BIND_EVENT_FN(Application::OnWindowResize));

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();) {
			if (e.Handled) break;
			(*--it)->OnEvent(e);
		}
	}

	void Application::Run() {
		while (m_Running) {
			float time = m_Platform.GetTime();
			Timestep timestep = time - m_LastFrameTime;
			m_LastFrameTime = time;

			if (!m_Minimized) {
				for (Layer* layer : m_LayerStack) {
					layer->OnUpdate(timestep);
				}

				m_ImGuiLayer->Begin();
					for (Layer* layer : m_LayerStack) {
						layer->OnImGuiRender();
					}
				m_ImGuiLayer->End();
			}


			m_Window->OnUpdate();
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e) {
		m_Running = false;
		return m_Running;
	}

	bool Application::OnWindowResize(WindowResizeEvent& e) {
		if (e.GetWidth() == 0 || e.GetHeight() == 0) {
			m_Minimized = true;
			return false;
		}

		m_Minimized = false;
		Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());

		return false;
	}
}