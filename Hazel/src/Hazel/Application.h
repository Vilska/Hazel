#pragma once

#include "Core.h"

namespace Hazel {

	class HAZEL_API Application { // HAZEL_API = export (Core.h)

	public:
		Application();
		virtual ~Application();

		void Run();
	};

	// To be defined in Client
	Application* CreateApplication();

}

