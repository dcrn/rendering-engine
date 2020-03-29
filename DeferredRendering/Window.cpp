#include "Window.h"

#include <stdexcept>
#include <memory>

#include <GLFW/glfw3.h>

#include "Renderer.h"

void Window::Open(std::string title, int width, int height)
{
	if (!glfwInit())
	{
		throw std::runtime_error("Unable to initialize GLFW");
	}

	glfwDefaultWindowHints();
	window = std::shared_ptr<GLFWwindow>(
		glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr),
		[](GLFWwindow* window)
		{
			glfwDestroyWindow(window);
			glfwTerminate();
		}
	);
	
	if (window == nullptr)
	{
		const char* lastGlfwError;
		glfwGetError(&lastGlfwError);
		std::string errorMessage = "Error while opening window: " + std::string(lastGlfwError);

		glfwTerminate();
		throw std::runtime_error(errorMessage);
	}

	glfwMakeContextCurrent(window.get());
}

void Window::Close()
{
	if (window)
	{
		glfwSetWindowShouldClose(window.get(), GLFW_TRUE);
	}
}

bool Window::IsOpen()
{
	return window && glfwWindowShouldClose(window.get()) == GLFW_FALSE;
}

void Window::PollEvents()
{
	if (window)
	{
		glfwPollEvents();
	}
}

void Window::SwapBuffers()
{
	if (window) {
		glfwSwapBuffers(window.get());
	}
}

int Window::GetWidth()
{
	int width;
	glfwGetFramebufferSize(window.get(), &width, nullptr);
	return width;
}

int Window::GetHeight()
{
	int height;
	glfwGetFramebufferSize(window.get(), nullptr, &height);
	return height;
}
