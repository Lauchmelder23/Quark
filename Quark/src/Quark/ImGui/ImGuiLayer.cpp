#include "qkpch.hpp"
#include "ImGuiLayer.hpp"

#include "imgui.h"
#include "Platform/OpenGL/ImGuiOpenGLRenderer.hpp"
#include "Quark/Application.hpp"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Quark
{
	ImGuiLayer::ImGuiLayer() :
		Layer("ImGuiLayer")
	{

	}

	ImGuiLayer::~ImGuiLayer()
	{

	}

	void ImGuiLayer::OnAttach()
	{
		ImGui::CreateContext();
		ImGui::StyleColorsDark();

		ImGuiIO& io = ImGui::GetIO();
		io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
		io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

		io.KeyMap[ImGuiKey_Tab] = GLFW_KEY_TAB;
		io.KeyMap[ImGuiKey_LeftArrow] = GLFW_KEY_LEFT;
		io.KeyMap[ImGuiKey_RightArrow] = GLFW_KEY_RIGHT;
		io.KeyMap[ImGuiKey_UpArrow] = GLFW_KEY_UP;
		io.KeyMap[ImGuiKey_DownArrow] = GLFW_KEY_DOWN;
		io.KeyMap[ImGuiKey_PageUp] = GLFW_KEY_PAGE_UP;
		io.KeyMap[ImGuiKey_PageDown] = GLFW_KEY_PAGE_DOWN;
		io.KeyMap[ImGuiKey_Home] = GLFW_KEY_HOME;
		io.KeyMap[ImGuiKey_End] = GLFW_KEY_END;
		io.KeyMap[ImGuiKey_Insert] = GLFW_KEY_INSERT;
		io.KeyMap[ImGuiKey_Delete] = GLFW_KEY_DELETE;
		io.KeyMap[ImGuiKey_Backspace] = GLFW_KEY_BACKSPACE;
		io.KeyMap[ImGuiKey_Space] = GLFW_KEY_SPACE;
		io.KeyMap[ImGuiKey_Enter] = GLFW_KEY_ENTER;
		io.KeyMap[ImGuiKey_Escape] = GLFW_KEY_ESCAPE;
		io.KeyMap[ImGuiKey_KeyPadEnter] = GLFW_KEY_KP_ENTER;
		io.KeyMap[ImGuiKey_A] = GLFW_KEY_A;
		io.KeyMap[ImGuiKey_C] = GLFW_KEY_C;
		io.KeyMap[ImGuiKey_V] = GLFW_KEY_V;
		io.KeyMap[ImGuiKey_X] = GLFW_KEY_X;
		io.KeyMap[ImGuiKey_Y] = GLFW_KEY_Y;
		io.KeyMap[ImGuiKey_Z] = GLFW_KEY_Z;

		ImGui_ImplOpenGL3_Init("#version 410");
	}

	void ImGuiLayer::OnDetach()
	{

	}

	void ImGuiLayer::OnUpdate()
	{
		ImGuiIO& io = ImGui::GetIO();
		Application& app = Application::Get();
		io.DisplaySize = ImVec2(app.GetWindow().GetWidth(), app.GetWindow().GetHeight());

		float time = (float)glfwGetTime();
		io.DeltaTime = m_Time > 0.0 ? (time - m_Time) : (1.0f / 60.0f);
		m_Time = time;

		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();

		static bool show = true;
		ImGui::ShowDemoWindow(&show);

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void ImGuiLayer::OnEvent(Event& event)
	{
		EventDispatcher dispatcher(event);

		dispatcher.Dispatch<MouseMovedEvent>(QK_BIND_EVENT(ImGuiLayer::OnMouseMoved));
		dispatcher.Dispatch<MouseButtonPressedEvent>(QK_BIND_EVENT(ImGuiLayer::OnMouseButtonPressed));
		dispatcher.Dispatch<MouseButtonReleasedEvent>(QK_BIND_EVENT(ImGuiLayer::OnMouseButtonReleased));
		dispatcher.Dispatch<MouseScrolledEvent>(QK_BIND_EVENT(ImGuiLayer::OnMouseWheelScrolled));
		dispatcher.Dispatch<KeyPressedEvent>(QK_BIND_EVENT(ImGuiLayer::OnKeyDown));
		dispatcher.Dispatch<KeyReleasedEvent>(QK_BIND_EVENT(ImGuiLayer::OnKeyUp));
		dispatcher.Dispatch<KeyTypedEvent>(QK_BIND_EVENT(ImGuiLayer::OnKeyTyped));
		dispatcher.Dispatch<WindowResizeEvent>(QK_BIND_EVENT(ImGuiLayer::OnWindowResized));
	}

	bool ImGuiLayer::OnMouseButtonPressed(MouseButtonPressedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[e.GetMouseButton()] = true;

		return false;
	}

	bool ImGuiLayer::OnMouseButtonReleased(MouseButtonReleasedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[e.GetMouseButton()] = false;

		return false;
	}

	bool ImGuiLayer::OnMouseWheelScrolled(MouseScrolledEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseWheel += e.GetOffsetY();
		io.MouseWheelH += e.GetOffsetX();

		return false;
	}

	bool ImGuiLayer::OnMouseMoved(MouseMovedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MousePos = ImVec2(e.GetX(), e.GetY());

		return false;
	}

	bool ImGuiLayer::OnKeyDown(KeyPressedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.KeysDown[e.GetKeyCode()] = true;

		io.KeyCtrl = io.KeysDown[GLFW_KEY_LEFT_CONTROL];
		io.KeyShift = io.KeysDown[GLFW_KEY_LEFT_SHIFT];
		io.KeyAlt = io.KeysDown[GLFW_KEY_LEFT_ALT];
		io.KeySuper = io.KeysDown[GLFW_KEY_LEFT_SUPER];

		return false;
	}

	bool ImGuiLayer::OnKeyUp(KeyReleasedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.KeysDown[e.GetKeyCode()] = false;

		io.KeyCtrl = io.KeysDown[GLFW_KEY_LEFT_CONTROL];
		io.KeyShift = io.KeysDown[GLFW_KEY_LEFT_SHIFT];
		io.KeyAlt = io.KeysDown[GLFW_KEY_LEFT_ALT];
		io.KeySuper = io.KeysDown[GLFW_KEY_LEFT_SUPER];

		return false;
	}

	bool ImGuiLayer::OnKeyTyped(KeyTypedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		int c = e.GetKeyCode();
		if (c > 0 && c < 0x10000)
			io.AddInputCharacter((unsigned short)c);

		return false;
	}

	bool ImGuiLayer::OnWindowResized(WindowResizeEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.DisplaySize = ImVec2(e.GetWidth(), e.GetHeight());
		io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
		glViewport(0, 0, io.DisplaySize.x, io.DisplaySize.y);

		return false;
	}
}