#include "hzpch.h"
#include "Platform.h"

#include "Renderer.h"

#include "GLFW/glfw3.h"

namespace Hazel {

	float Platform::GetTime() const {
		switch (Renderer::GetAPI()) {
			case RendererAPI::API::None: HZ_CORE_ASSERT(false, "RendererAPI::None is not supported!"); return 0.0f;
			case RendererAPI::API::OpenGL: return (float)glfwGetTime();
		}
	}

}