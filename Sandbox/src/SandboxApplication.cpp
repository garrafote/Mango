#include <Mango.h>

#include <glm/gtx/quaternion.hpp>
#include "imgui/imgui.h"

class ExampleLayer : public Mango::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f)
	{
		m_VertexArray.reset(Mango::VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f,   0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f,   0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f,   0.8f, 0.8f, 0.2f, 1.0f,
		};

		std::shared_ptr<Mango::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Mango::VertexBuffer::Create(vertices, sizeof(vertices)));
		Mango::BufferLayout layout = {
			{ Mango::ShaderDataType::Float3, "a_Position" },
			{ Mango::ShaderDataType::Float4, "a_Color" },
			//{ ShaderDataType::Float3, "a_Normal" },
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		unsigned int indices[3]{ 0, 1, 2 };
		std::shared_ptr<Mango::IndexBuffer> indexBuffer;
		indexBuffer.reset(Mango::IndexBuffer::Create(indices, 3));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVA.reset(Mango::VertexArray::Create());

		float squareVertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f,
		};

		std::shared_ptr<Mango::VertexBuffer> squareVB;
		squareVB.reset(Mango::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareVB->SetLayout({
			{ Mango::ShaderDataType::Float3, "a_Position" },
			});
		m_SquareVA->AddVertexBuffer(squareVB);

		unsigned int squareIndices[6]{ 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<Mango::IndexBuffer> squareIB;
		squareIB.reset(Mango::IndexBuffer::Create(squareIndices, 6));
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

		m_Shader.reset(Mango::Shader::Create(vertexSrc, fragmentSrc));

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

			uniform vec4 u_Color;

			void main()
			{
				color = u_Color;
			}
		)";

		m_FlatColorShader.reset(Mango::Shader::Create(flatColorShaderVertexSrc, flatColorShaderFragmentSrc));


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

		for (int x = 0; x < 20; x++)
		{
			for (int y = 0; y < 20; y++)
			{
				glm::vec3 pos(x * 1.1f, y * 1.1f, 0.0f);
				glm::mat4 transform = glm::translate(scale, pos);
				if ((x + y) % 2 == 0)
					m_FlatColorShader->UploadUniform("u_Color", m_PrimaryColor);
				else
					m_FlatColorShader->UploadUniform("u_Color", m_SecondaryColor);
				Mango::Renderer::Submit(m_FlatColorShader, m_SquareVA, transform);
			}
		}

		Mango::Renderer::Submit(m_Shader, m_VertexArray);

		Mango::Renderer::EndScene();
	}

	void OnImGuiRender() override
	{
		ImGui::Begin("Properties");

		ImGui::PushItemWidth(77);
		ImGuiColorEditFlags colorPickerFlags = ImGuiColorEditFlags_NoInputs;
		ImGui::ColorPicker4("Primary Color", &m_PrimaryColor.x, colorPickerFlags);
		ImGui::ColorPicker4("Secondary Color", &m_SecondaryColor.x, colorPickerFlags);
		ImGui::PopItemWidth();
		
		ImGui::End();
	}

	void OnEvent(Mango::Event& event) override
	{
		Mango::EventDispatcher dispatcher(event);
	}

private:
	std::shared_ptr<Mango::Shader> m_Shader;
	std::shared_ptr<Mango::VertexArray> m_VertexArray;

	std::shared_ptr<Mango::Shader> m_FlatColorShader;
	std::shared_ptr<Mango::VertexArray> m_SquareVA;

	Mango::OrthographicCamera m_Camera;

	glm::vec3 m_CameraPosition = glm::vec3(0);
	float m_CameraMoveSpeed = 5.0f;

	float m_CameraRotation = 0;
	float m_CameraRotationSpeed = 180.0f;

	// Properties
	glm::vec4 m_PrimaryColor = { 0.8f, 0.2f, 0.3f, 1.0f };
	glm::vec4 m_SecondaryColor = { 0.2f, 0.3f, 0.8f, 1.0f };
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