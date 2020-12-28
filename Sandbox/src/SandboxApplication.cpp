#include <Mango.h>

#include "Platform/OpenGL/OpenGLShader.h"

#include "imgui/imgui.h"

#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>

class ExampleLayer : public Mango::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f)
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

		m_Shader = Mango::Shader::Create(vertexSrc, fragmentSrc);

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

		m_FlatColorShader = Mango::Shader::Create(flatColorShaderVertexSrc, flatColorShaderFragmentSrc);

		std::string textureShaderVertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec2 a_TexCoord;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Model;

			out vec2 v_TexCoord;

			void main()
			{
				v_TexCoord = a_TexCoord;
				gl_Position = u_ViewProjection * u_Model * vec4(a_Position, 1.0);
			}
		)";

		std::string textureShaderFragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec2 v_TexCoord;

			uniform sampler2D u_Texture;

			void main()
			{
				color = texture(u_Texture, v_TexCoord);
			}
		)";

		m_TextureShader = Mango::Shader::Create(textureShaderVertexSrc, textureShaderFragmentSrc);
		m_TextureShader = Mango::Shader::Create("assets/shaders/Texture.glsl");

		m_Texture = Mango::Texture2D::Create("assets/textures/Checkerboard.png");
		m_MangoLogoTexture = Mango::Texture2D::Create("assets/textures/Mango.png");
	
		m_TextureShader->Bind();
		std::dynamic_pointer_cast<Mango::OpenGLShader>(m_TextureShader)->UploadUniformInt("u_Texture", 0);
	}

	void OnUpdate(Mango::Timestep ts) override
	{
		MGO_TRACE("Delta time: {0}s ({1}ms): ", ts.GetSeconds(), ts.GetMilliseconds());

		// Update Camera
		{
			if (Mango::Input::IsKeyPressed(MGO_KEY_Q))
				m_CameraRotation += m_CameraRotationSpeed * ts;

			if (Mango::Input::IsKeyPressed(MGO_KEY_E))
				m_CameraRotation -= m_CameraRotationSpeed * ts;

			glm::vec3 delta(0);
			if (Mango::Input::IsKeyPressed(MGO_KEY_A) || Mango::Input::IsKeyPressed(MGO_KEY_LEFT))
				delta.x -= m_CameraMoveSpeed;

			if (Mango::Input::IsKeyPressed(MGO_KEY_D) || Mango::Input::IsKeyPressed(MGO_KEY_RIGHT))
				delta.x += m_CameraMoveSpeed;

			if (Mango::Input::IsKeyPressed(MGO_KEY_W) || Mango::Input::IsKeyPressed(MGO_KEY_UP))
				delta.y += m_CameraMoveSpeed;

			if (Mango::Input::IsKeyPressed(MGO_KEY_S) || Mango::Input::IsKeyPressed(MGO_KEY_DOWN))
				delta.y -= m_CameraMoveSpeed;

			glm::quat rotation = glm::angleAxis(glm::radians(m_CameraRotation), glm::vec3(0, 0, 1));
			m_CameraPosition += rotation * delta * ts;

			m_Camera.SetPosition(m_CameraPosition);
			m_Camera.SetRotation(m_CameraRotation);
		}

		Mango::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Mango::RenderCommand::Clear();

		Mango::Renderer::BeginScene(m_Camera);

		glm::mat4 scale = glm::scale(glm::mat4(1), glm::vec3(0.1f));

		//Mango::MaterialRef material = new Mango::Material(m_FlatColorShader);
		//Mango::MaterialInstanceRef primaryMaterial = new Mango::MaterialInstance(material);
		//primaryMaterial->Set("u_Color", m_PrimaryColor);
		//Mango::MaterialInstanceRef secondaryMaterial = new Mango::MaterialInstance(material);
		//secondaryMaterial->Set("u_Color", m_PrimaryColor);
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
		
		m_Texture->Bind();
		Mango::Renderer::Submit(m_TextureShader, m_SquareVA,  glm::scale(glm::mat4(1), glm::vec3(1.5f)));
		
		m_MangoLogoTexture->Bind();
		Mango::Renderer::Submit(m_TextureShader, m_SquareVA,  glm::scale(glm::mat4(1), glm::vec3(1.5f)));

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

	void OnEvent(Mango::Event& event) override
	{
		Mango::EventDispatcher dispatcher(event);
	}

private:
	Mango::Ref<Mango::Shader> m_Shader;
	Mango::Ref<Mango::VertexArray> m_VertexArray;

	Mango::Ref<Mango::Shader> m_FlatColorShader, m_TextureShader;
	Mango::Ref<Mango::VertexArray> m_SquareVA;

	Mango::Ref<Mango::Texture2D> m_Texture;
	Mango::Ref<Mango::Texture2D> m_MangoLogoTexture;

	Mango::OrthographicCamera m_Camera;

	glm::vec3 m_CameraPosition = glm::vec3(0);
	float m_CameraMoveSpeed = 5.0f;

	float m_CameraRotation = 0;
	float m_CameraRotationSpeed = 180.0f;

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