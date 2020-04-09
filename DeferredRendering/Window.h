#pragma once

#include <memory>
#include <string>

struct GLFWwindow;

class InputManager;

class Window
{
public:
	Window();
	
	void Open(std::string title, int width, int height);
	void Close();
	bool IsOpen();
	void PollEvents();
	void SwapBuffers();
	
	int GetWidth();
	int GetHeight();

	std::shared_ptr<InputManager> GetInputManager();

private:
	std::shared_ptr<GLFWwindow> handle;
	std::shared_ptr<InputManager> inputManager;
};
