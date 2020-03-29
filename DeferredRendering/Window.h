#pragma once

#include <memory>
#include <string>

struct GLFWwindow;

class Window
{
public:
	void Open(std::string title, int width, int height);
	void Close();
	bool IsOpen();
	void PollEvents();
	void SwapBuffers();
	
	int GetWidth();
	int GetHeight();

private:
	std::shared_ptr<GLFWwindow> window;
};
