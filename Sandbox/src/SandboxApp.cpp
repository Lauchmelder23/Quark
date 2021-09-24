#include <Quark.hpp>

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
