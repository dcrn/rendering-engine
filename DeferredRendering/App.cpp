#include <iostream>

#include "Renderer.h"
#include "Window.h"
#include "DefaultScene.h"
#include "Engine.h"

class App
{
	const int WINDOW_WIDTH = 1200;
	const int WINDOW_HEIGHT = 900;
	
public:
	void Init()
	{
		window.Open("OpenGL Rendering Demo", WINDOW_WIDTH, WINDOW_HEIGHT);

		std::shared_ptr<Renderer> renderer = std::make_shared<Renderer>();
		renderer->Resize(window.GetWidth(), window.GetHeight());

		std::shared_ptr<Scene> scene = std::make_shared<DefaultScene>();

		Engine::Instance.SetInputManager(window.GetInputManager());
		Engine::Instance.SetRenderer(renderer);
		Engine::Instance.SetScene(scene);
	}
	
	void Run()
	{
		while (window.IsOpen())
		{
			window.PollEvents();
			Engine::Instance.Update();
			window.SwapBuffers();
		}
	}

private:
	Window window;
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
