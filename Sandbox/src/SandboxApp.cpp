#include <Quark.hpp>

class Sandbox : public Quark::Application
{
public:
	Sandbox()
	{

	}

	~Sandbox()
	{

	}

private:

};

Quark::Application* Quark::CreateApplication()
{
	return new Sandbox();
}
