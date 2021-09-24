#include <Quark.hpp>

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

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

	void OnEvent(Quark::Event& event) override
	{
		// QK_TRACE("{0}", event);
		Quark::EventDispatcher d(event);
		d.Dispatch<Quark::KeyPressedEvent>([](Quark::KeyPressedEvent e) 
		{
				QK_TRACE("Quark KeyCode: {0}, API KeyCode: {1}", e.GetKeyCode(), Quark::GetAPIKeyCode(e.GetKeyCode()));

			return false;
		});
	}
};

class Sandbox : public Quark::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
		PushOverlay(new Quark::ImGuiLayer());
	}

	~Sandbox()
	{

	}

};

Quark::Application* Quark::CreateApplication()
{
	return new Sandbox();
}
