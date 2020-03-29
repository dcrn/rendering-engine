#include <iostream>

#include <GLFW/glfw3.h>

#include "Renderer.h"
#include "Window.h"

class App
{
	const int WINDOW_WIDTH = 800;
	const int WINDOW_HEIGHT = 600;
	
public:
	void Init()
	{
		window.Open("OpenGL Rendering Demo", WINDOW_WIDTH, WINDOW_HEIGHT);
		
		renderer.Init();
		renderer.Resize(window.GetWidth(), window.GetHeight());
	}
	
	void Run()
	{
		// Render once for now
		renderer.Draw();
		window.SwapBuffers();
		
		while (window.IsOpen())
		{
			window.PollEvents();
			//renderer.Draw();
			//window.SwapBuffers();
		}
	}

private:
	Window window;
	Renderer renderer;
};


int main()
{
	App app;

	try
	{
		app.Init();
		app.Run();
	}
	catch (const std::exception& ex)
	{
		std::cerr << "Fatal error" << std::endl;
		std::cerr << ex.what() << std::endl;

		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
