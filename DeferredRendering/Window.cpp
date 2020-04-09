#include "Window.h"

#include <stdexcept>
#include <memory>

#include <GLFW/glfw3.h>

#include "InputManager.h"

class WindowInputManager : public InputManager
{
public:
	KeyState GetKeyState(KeyCode keyCode) override
	{
		if (windowHandle != nullptr)
		{
			switch (glfwGetKey(windowHandle, ConvertKeyCode(keyCode)))
			{
			case GLFW_PRESS:
				return KeyState::Pressed;
			case GLFW_RELEASE:
				return KeyState::Released;
			default: ;
			}
		}

		return KeyState::Released;
	}

	void SetWindowHandle(GLFWwindow* windowHandle)
	{
		this->windowHandle = windowHandle;
	}

private:
	constexpr int ConvertKeyCode(KeyCode keyCode)
	{
		switch (keyCode)
		{
		case KeyCode::_1: return GLFW_KEY_1;
		case KeyCode::_2: return GLFW_KEY_2;
		case KeyCode::_3: return GLFW_KEY_3;
		case KeyCode::_4: return GLFW_KEY_4;
		case KeyCode::_5: return GLFW_KEY_5;
		case KeyCode::_6: return GLFW_KEY_6;
		case KeyCode::_7: return GLFW_KEY_7;
		case KeyCode::_8: return GLFW_KEY_8;
		case KeyCode::_9: return GLFW_KEY_9;
		case KeyCode::_0: return GLFW_KEY_0;
		case KeyCode::A: return GLFW_KEY_A;
		case KeyCode::B: return GLFW_KEY_B;
		case KeyCode::C: return GLFW_KEY_C;
		case KeyCode::D: return GLFW_KEY_D;
		case KeyCode::E: return GLFW_KEY_E;
		case KeyCode::F: return GLFW_KEY_F;
		case KeyCode::G: return GLFW_KEY_G;
		case KeyCode::H: return GLFW_KEY_H;
		case KeyCode::I: return GLFW_KEY_I;
		case KeyCode::J: return GLFW_KEY_J;
		case KeyCode::K: return GLFW_KEY_K;
		case KeyCode::L: return GLFW_KEY_L;
		case KeyCode::M: return GLFW_KEY_M;
		case KeyCode::N: return GLFW_KEY_N;
		case KeyCode::O: return GLFW_KEY_O;
		case KeyCode::P: return GLFW_KEY_P;
		case KeyCode::Q: return GLFW_KEY_Q;
		case KeyCode::R: return GLFW_KEY_R;
		case KeyCode::S: return GLFW_KEY_S;
		case KeyCode::T: return GLFW_KEY_T;
		case KeyCode::U: return GLFW_KEY_U;
		case KeyCode::V: return GLFW_KEY_V;
		case KeyCode::W: return GLFW_KEY_W;
		case KeyCode::X: return GLFW_KEY_X;
		case KeyCode::Y: return GLFW_KEY_Y;
		case KeyCode::Z: return GLFW_KEY_Z;
		case KeyCode::Tab: return GLFW_KEY_TAB;
		case KeyCode::CapsLock: return GLFW_KEY_CAPS_LOCK;
		case KeyCode::Enter: return GLFW_KEY_ENTER;
		case KeyCode::LeftShift: return GLFW_KEY_LEFT_SHIFT;
		case KeyCode::RightShift: return GLFW_KEY_RIGHT_SHIFT;
		case KeyCode::LeftAlt: return GLFW_KEY_LEFT_ALT;
		case KeyCode::RightAlt: return GLFW_KEY_RIGHT_ALT;
		case KeyCode::LeftCtrl: return GLFW_KEY_LEFT_CONTROL;
		case KeyCode::RightCtrl: return GLFW_KEY_RIGHT_CONTROL;
		case KeyCode::Space: return GLFW_KEY_SPACE;
		case KeyCode::UpArrow: return GLFW_KEY_UP;
		case KeyCode::LeftArrow: return GLFW_KEY_LEFT;
		case KeyCode::RightArrow: return GLFW_KEY_RIGHT;
		case KeyCode::DownArrow: return GLFW_KEY_DOWN;
		default: return -1;
		}
	}

	GLFWwindow* windowHandle = nullptr;
};

Window::Window()
{
	inputManager = std::make_shared<WindowInputManager>();
}

void Window::Open(std::string title, int width, int height)
{
	if (!glfwInit())
	{
		throw std::runtime_error("Unable to initialize GLFW");
	}

	glfwDefaultWindowHints();
	handle = std::shared_ptr<GLFWwindow>(
		glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr),
		[](GLFWwindow* window)
		{
			glfwDestroyWindow(window);
			glfwTerminate();
		}
	);

	if (handle == nullptr)
	{
		const char* lastGlfwError;
		glfwGetError(&lastGlfwError);
		std::string errorMessage = "Error while opening window: " + std::string(lastGlfwError);

		glfwTerminate();
		throw std::runtime_error(errorMessage);
	}

	std::static_pointer_cast<WindowInputManager>(inputManager)->SetWindowHandle(handle.get());
	glfwMakeContextCurrent(handle.get());
}

void Window::Close()
{
	if (handle)
	{
		glfwSetWindowShouldClose(handle.get(), GLFW_TRUE);
	}
}

bool Window::IsOpen()
{
	return handle && glfwWindowShouldClose(handle.get()) == GLFW_FALSE;
}

void Window::PollEvents()
{
	if (handle)
	{
		glfwPollEvents();
	}
}

void Window::SwapBuffers()
{
	if (handle)
	{
		glfwSwapBuffers(handle.get());
	}
}

int Window::GetWidth()
{
	int width;
	glfwGetFramebufferSize(handle.get(), &width, nullptr);
	return width;
}

int Window::GetHeight()
{
	int height;
	glfwGetFramebufferSize(handle.get(), nullptr, &height);
	return height;
}

std::shared_ptr<InputManager> Window::GetInputManager()
{
	return inputManager;
}
