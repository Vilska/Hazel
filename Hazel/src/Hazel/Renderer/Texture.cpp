#include "hzpch.h"
#include "Texture.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGlTexture.h"

namespace Hazel {

	Ref<Texture2D> Texture2D::Create(uint32_t width, uint32_t height) {
		switch (Renderer::GetAPI()) {
		case RendererAPI::API::None: HZ_CORE_ASSERT(false, "RendererAPI::None is not supported!"); return nullptr;
		case RendererAPI::API::OpenGL: return std::make_shared<OpenGLTexture2D>(width, height);
		}

		HZ_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	Ref<Texture2D> Texture2D::Create(const std::string& path) {
		switch (Renderer::GetAPI()) {
			case RendererAPI::API::None: HZ_CORE_ASSERT(false, "RendererAPI::None is not supported!"); return nullptr;
			case RendererAPI::API::OpenGL: return std::make_shared<OpenGLTexture2D>(path);
		}

		HZ_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
	
	SubTexture2D::SubTexture2D(const Ref<Texture2D>& texture, const glm::vec2& min, glm::vec2& max)
		: m_Texture(texture) {
		m_TexCoords[0] = { min.x, min.y };
		m_TexCoords[1] = { max.x, min.y };
		m_TexCoords[2] = { max.x, max.y };
		m_TexCoords[3] = { min.x, max.y };
	}

	Ref<SubTexture2D> SubTexture2D::CreateFromCoords(const Ref<Texture2D>& texture, const glm::vec2& coords, const glm::vec2& spriteSize) {
		glm::vec2 min = { coords.x / texture->GetWidth(), coords.y / texture->GetHeight() };
		glm::vec2 max = { (coords.x + spriteSize.x) / texture->GetWidth(), (coords.y + spriteSize.y) / texture->GetHeight() };
		return CreateRef<SubTexture2D>(texture, min, max);
	}
}