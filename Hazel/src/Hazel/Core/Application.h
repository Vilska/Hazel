#pragma once

#include "Core.h"

#include "Window.h"
#include "LayerStack.h"
#include "Hazel/Events/Event.h"
#include "Hazel/Events/ApplicationEvent.h"

#include "Hazel/ImGui/ImGuiLayer.h"

#include "Hazel/Core/Timestep.h"

#include "Hazel/Renderer/Platform.h"

namespace Hazel {

	// Declaration for Application class
	class Application {
	public:
		Application(const std::string& name = "Hazel Engine");
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		Window& GetWindow() { return *m_Window; }

		void Close();

		ImGuiLayer* GetImGuiLayer() { return m_ImGuiLayer; };

		static Application& Get() { return *s_Instance; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
	private:
		Ref<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		bool m_Minimized = false;
		LayerStack m_LayerStack;
		float m_LastFrameTime = 0.0f;
		Platform m_Platform;

		static Application* s_Instance;
	};

	// To be defined in Client
	Application* CreateApplication();

}