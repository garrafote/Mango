#include <Mango.h>

#include "Platform/OpenGL/OpenGLShader.h"

#include "imgui/imgui.h"

#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>

class ExampleLayer : public Mango::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_CameraController(1280.0f / 720.0f, true)
	{
		m_VertexArray = Mango::VertexArray::Create();

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f,   0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f,   0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f,   0.8f, 0.8f, 0.2f, 1.0f,
		};

		Mango::Ref<Mango::VertexBuffer> vertexBuffer;
		vertexBuffer = Mango::VertexBuffer::Create(vertices, sizeof(vertices));
		Mango::BufferLayout layout = {
			{ Mango::ShaderDataType::Float3, "a_Position" },
			{ Mango::ShaderDataType::Float4, "a_Color" },
			//{ ShaderDataType::Float3, "a_Normal" },
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		unsigned int indices[3]{ 0, 1, 2 };
		Mango::Ref<Mango::IndexBuffer> indexBuffer;
		indexBuffer = Mango::IndexBuffer::Create(indices, 3);
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVA = Mango::VertexArray::Create();

		float squareVertices[5 * 7] = {
			// position        | UV
			-0.5f, -0.5f, 0.0f,  0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f,  1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f,  1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f,  0.0f, 1.0f,
		};

		Mango::Ref<Mango::VertexBuffer> squareVB;
		squareVB = Mango::VertexBuffer::Create(squareVertices, sizeof(squareVertices));
		squareVB->SetLayout({
			{ Mango::ShaderDataType::Float3, "a_Position" },
			{ Mango::ShaderDataType::Float2, "a_TexCoord" },
		});
		m_SquareVA->AddVertexBuffer(squareVB);

		unsigned int squareIndices[6]{ 0, 1, 2, 2, 3, 0 };
		Mango::Ref<Mango::IndexBuffer> squareIB;
		squareIB = Mango::IndexBuffer::Create(squareIndices, 6);
		m_SquareVA->SetIndexBuffer(squareIB);

		std::string vertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Model;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * u_Model * vec4(a_Position, 1.0);
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			in vec4 v_Color;

			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;
			}
		)";

		m_Shader = Mango::Shader::Create("VertexPosColor", vertexSrc, fragmentSrc);

		std::string flatColorShaderVertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Model;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_Model * vec4(a_Position, 1.0);
			}
		)";

		std::string flatColorShaderFragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec3 v_Position;

			uniform vec3 u_Color;

			void main()
			{
				color = vec4(u_Color, 1.0);
			}
		)";

		m_FlatColorShader = Mango::Shader::Create("FlatColor", flatColorShaderVertexSrc, flatColorShaderFragmentSrc);

		auto textureShader = m_ShaderLibrary.Load("assets/shaders/Texture.glsl");

		m_Texture = Mango::Texture2D::Create("assets/textures/Checkerboard.png");
		m_MangoLogoTexture = Mango::Texture2D::Create("assets/textures/Mango.png");
	
		textureShader->Bind();
		std::dynamic_pointer_cast<Mango::OpenGLShader>(textureShader)->UploadUniformInt("u_Texture", 0);
	}

	void OnUpdate(Mango::Timestep ts) override
	{
		// Update
		m_CameraController.OnUpdate(ts);

		// Render
		Mango::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Mango::RenderCommand::Clear();

		Mango::Renderer::BeginScene(m_CameraController.GetCamera());

		glm::mat4 scale = glm::scale(glm::mat4(1), glm::vec3(0.1f));

		m_FlatColorShader->Bind();
		std::dynamic_pointer_cast<Mango::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat3("u_Color", m_SquareColor);
		
		for (int x = 0; x < 20; x++)
		{
			for (int y = 0; y < 20; y++)
			{
				glm::vec3 pos(x * 1.1f, y * 1.1f, 0.0f);
				glm::mat4 transform = glm::translate(scale, pos);
				Mango::Renderer::Submit(m_FlatColorShader, m_SquareVA, transform);
			}
		}
		
		auto textureShader = m_ShaderLibrary.Get("Texture");

		m_Texture->Bind();
		Mango::Renderer::Submit(textureShader, m_SquareVA,  glm::scale(glm::mat4(1), glm::vec3(1.5f)));
		
		m_MangoLogoTexture->Bind();
		Mango::Renderer::Submit(textureShader, m_SquareVA,  glm::scale(glm::mat4(1), glm::vec3(1.5f)));

		// Triangle
		// Mango::Renderer::Submit(m_Shader, m_VertexArray);

		Mango::Renderer::EndScene();
	}

	void OnImGuiRender() override
	{
		ImGui::Begin("Properties");
		ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
		ImGui::End();
	}

	void OnEvent(Mango::Event& e) override
	{
		m_CameraController.OnEvent(e);
	}

private:
	Mango::ShaderLibrary m_ShaderLibrary;

	Mango::Ref<Mango::Shader> m_Shader;
	Mango::Ref<Mango::VertexArray> m_VertexArray;

	Mango::Ref<Mango::Shader> m_FlatColorShader;
	Mango::Ref<Mango::VertexArray> m_SquareVA;

	Mango::Ref<Mango::Texture2D> m_Texture;
	Mango::Ref<Mango::Texture2D> m_MangoLogoTexture;

	Mango::OrthographicCameraController m_CameraController;

	// Properties
	glm::vec3 m_SquareColor = { 0.8f, 0.2f, 0.3f };
};

class Sandbox : public Mango::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{

	}
};

Mango::Application* Mango::CreateApplication()
{
	return new Sandbox();
}