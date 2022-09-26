#include "hzpch.h"
#include "Renderer2D.h"

#include "VertexArray.h"
#include "Shader.h"
#include "RenderCommand.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Hazel {

	struct QuadVertex {
		glm::vec3 Position;
		glm::vec4 Color;
		glm::vec2 TexCoord;
	};

	struct Renderer2DProps {
		const uint32_t MaxQuads = 10000;
		const uint32_t MaxVertices = MaxQuads * 4;
		const uint32_t MaxIndices = MaxQuads * 6;

		Ref<VertexArray> QuadVertexArray;
		Ref<VertexBuffer> QuadVertexBuffer;
		Ref<Shader> TextureShader;
		Ref<Texture2D> WhiteTexture;

		uint32_t QuadIndexCount = 0;
		QuadVertex* QuadVertexBufferBase = nullptr;
		QuadVertex* QuadVertexBufferPtr = nullptr;
	};

	static Renderer2DProps s_Data;

	void Renderer2D::Init() {
		s_Data.QuadVertexArray = VertexArray::Create();

		s_Data.QuadVertexBuffer = VertexBuffer::Create(s_Data.MaxVertices * sizeof(QuadVertex));
		s_Data.QuadVertexBuffer->SetLayout({
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float4, "a_Color" },
			{ ShaderDataType::Float2, "a_TexCoord" }
		});
		s_Data.QuadVertexArray->AddVertexBuffer(s_Data.QuadVertexBuffer);

		s_Data.QuadVertexBufferBase = new QuadVertex[s_Data.MaxVertices];

		uint32_t* quadIndices = new uint32_t[s_Data.MaxIndices];

		uint32_t offset = 0;
		for (uint32_t i = 0; i < s_Data.MaxIndices; i += 6) {
			quadIndices[i + 0] = offset + 0;
			quadIndices[i + 1] = offset + 1;
			quadIndices[i + 2] = offset + 2;

			quadIndices[i + 3] = offset + 2;
			quadIndices[i + 4] = offset + 3;
			quadIndices[i + 5] = offset + 0;

			offset += 4;
		}

		Ref<IndexBuffer> quadIndexBuffer = IndexBuffer::Create(quadIndices, s_Data.MaxIndices);
		s_Data.QuadVertexArray->SetIndexBuffer(quadIndexBuffer);
		delete[] quadIndices;

		s_Data.WhiteTexture = Texture2D::Create(1, 1);
		uint32_t whiteTextureData = 0xffffffff;
		s_Data.WhiteTexture->SetData(&whiteTextureData, sizeof(whiteTextureData));

		s_Data.TextureShader = Shader::Create("assets/shaders/Texture.glsl");
		s_Data.TextureShader->Bind();
		s_Data.TextureShader->SetInt("u_Texture", 0);
	}

	void Renderer2D::Shutdown() {
	}

	void Renderer2D::BeginScene(const OrthographicCamera& camera) {
		s_Data.TextureShader->Bind();
		s_Data.TextureShader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());

		s_Data.QuadIndexCount = 0;
		s_Data.QuadVertexBufferPtr = s_Data.QuadVertexBufferBase;
	}

	void Renderer2D::EndScene() {
		uint32_t dataSize = (uint8_t*)s_Data.QuadVertexBufferPtr - (uint8_t*)s_Data.QuadVertexBufferBase;
		s_Data.QuadVertexBuffer->SetData(s_Data.QuadVertexBufferBase, dataSize);

		Flush();
	}

	void Renderer2D::Flush() {
		RenderCommand::DrawIndexed(s_Data.QuadVertexArray, s_Data.QuadIndexCount);
	}

	void Renderer2D::DrawQuad(const RendererPropsColor& props) {

		s_Data.QuadVertexBufferPtr->Position = props.Position;
		s_Data.QuadVertexBufferPtr->Color = props.Color;
		s_Data.QuadVertexBufferPtr->TexCoord = {0.0f, 0.0f};
		s_Data.QuadVertexBufferPtr++;

		s_Data.QuadVertexBufferPtr->Position = { props.Position.x + props.Size.x, props.Position.y, 0.0f};
		s_Data.QuadVertexBufferPtr->Color = props.Color;
		s_Data.QuadVertexBufferPtr->TexCoord = { 1.0f, 0.0f };
		s_Data.QuadVertexBufferPtr++;

		s_Data.QuadVertexBufferPtr->Position = { props.Position.x + props.Size.x, props.Position.y + props.Size.y, 0.0f };
		s_Data.QuadVertexBufferPtr->Color = props.Color;
		s_Data.QuadVertexBufferPtr->TexCoord = { 1.0f, 1.0f };
		s_Data.QuadVertexBufferPtr++;

		s_Data.QuadVertexBufferPtr->Position = { props.Position.x, props.Position.y + props.Size.y, 0.0f };
		s_Data.QuadVertexBufferPtr->Color = props.Color;
		s_Data.QuadVertexBufferPtr->TexCoord = { 0.0f, 1.0f };
		s_Data.QuadVertexBufferPtr++;

		s_Data.QuadIndexCount += 6;

		//s_Data.WhiteTexture->Bind();

		//glm::mat4 transform = glm::translate(glm::mat4(1.0f), props.Position) * glm::scale(glm::mat4(1.0f), {props.Size.x, props.Size.y, 1.0f});
		//s_Data.TextureShader->SetMat4("u_Transform", transform);

		//s_Data.QuadVertexArray->Bind();
		//RenderCommand::DrawIndexed(s_Data.QuadVertexArray);
	}

	//void Renderer2D::DrawQuad(const RendererPropsTexture& props) {
	//	s_Data.TextureShader->SetFloat4("u_Color", glm::vec4(1.0f));
	//	s_Data.TextureShader->SetFloat("u_TilingFactor", props.Tiling);
	//	props.Texture->Bind();

	//	glm::mat4 transform = glm::translate(glm::mat4(1.0f), props.Position) * glm::scale(glm::mat4(1.0f), { props.Size.x, props.Size.y, 1.0f });
	//	s_Data.TextureShader->SetMat4("u_Transform", transform);

	//	s_Data.QuadVertexArray->Bind();
	//	RenderCommand::DrawIndexed(s_Data.QuadVertexArray);
	//}
}
