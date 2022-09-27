#pragma once

#include <string>
#include "Hazel/Core/Core.h"
#include <glm/glm.hpp>

namespace Hazel {

	class Texture {
	public:
		virtual ~Texture() = default;

		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;

		virtual void SetData(void* data, uint32_t size) = 0;

		virtual void Bind(uint32_t slot = 0) const = 0;

		virtual bool operator==(const Texture& other) const = 0;
	};

	class Texture2D : public Texture {
	public:
		static Ref<Texture2D> Create(uint32_t width, uint32_t height);
		static Ref<Texture2D> Create(const std::string& path);
	};
	
	class SubTexture2D {
	public:
		SubTexture2D(const Ref<Texture2D>& texture, const glm::vec2& min, glm::vec2& max);

		const Ref<Texture2D> GetTexture() const { return m_Texture; };
		const glm::vec2* GetTexCoords() const { return m_TexCoords; }

		static Ref<SubTexture2D> CreateFromCoords(const Ref<Texture2D>& texture, const glm::vec2& coords, const glm::vec2& spriteSize);
	private:
		Ref<Texture2D> m_Texture;
		glm::vec2 m_TexCoords[4];
	};
}