#include <iostream>

#include "Renderer.h"
#include "Window.h"
#include "DefaultScene.h"

class App
{
	const int WINDOW_WIDTH = 1200;
	const int WINDOW_HEIGHT = 900;
	
public:
	void Init()
	{
		window.Open("OpenGL Rendering Demo", WINDOW_WIDTH, WINDOW_HEIGHT);

		renderer.Init();
		renderer.Resize(window.GetWidth(), window.GetHeight());

		scene = std::static_pointer_cast<Scene>(std::make_shared<DefaultScene>());
		scene->SetInputManager(window.GetInputManager());
	}
	
	void Run()
	{
		while (window.IsOpen())
		{
			window.PollEvents();
			scene->Update();
			renderer.BeginDraw();
			scene->Render(&renderer);
			renderer.EndDraw();
			window.SwapBuffers();
		}
	}

private:
	Window window;
	Renderer renderer;
	std::shared_ptr<Scene> scene;
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
