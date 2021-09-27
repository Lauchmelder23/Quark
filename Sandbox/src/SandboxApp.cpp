#include <Quark.hpp>

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "imgui.h"
#include "shaders/ShaderBinaries.hpp"

glm::mat4 camera(float Translate, const glm::vec2& Rotate)
{
	glm::mat4 Projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
	glm::mat4 View = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -Translate));
	View = glm::rotate(View, Rotate.y, glm::vec3(-1.0f, 0.0f, 0.0f));
	View = glm::rotate(View, Rotate.x, glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 Model = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f));

	return Projection * View * Model;
}

class ExampleLayer : public Quark::Layer
{
public:
	ExampleLayer() :
		Layer("Example")
	{
	}

	void OnUpdate() override
	{

	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Test");
		ImGui::Text("Hello, World!");
		ImGui::End();
	}

	void OnEvent(Quark::Event& event) override
	{
		
	}
};

class Sandbox : public Quark::Application
{
public:
	Sandbox() :
		Quark::Application(SandboxVertexShaders::shader, SandboxFragmentShaders::shader, { Quark::RenderAPI::OpenGL })
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{

	}

};

Quark::Application* Quark::CreateApplication()
{
	return new Sandbox();
}
