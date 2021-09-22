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
		QK_INFO("Examplelayer::Update");
	}

	void OnEvent(Quark::Event& event) override
	{
		QK_TRACE("{0}", event);
	}
};

class Sandbox : public Quark::Application
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

Quark::Application* Quark::CreateApplication()
{
	return new Sandbox();
}
