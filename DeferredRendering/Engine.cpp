#include "Engine.h"

#include "Scene.h"
#include "Renderer.h"

Engine Engine::Instance = Engine();

Engine::Engine()
{
}

void Engine::Init()
{
}

void Engine::Shutdown()
{
	inputManager = nullptr;
	renderer = nullptr;
}

void Engine::Update()
{
	scene->Update();
	renderer->BeginDraw();
	scene->Render(renderer.get());
	renderer->EndDraw();
}

std::shared_ptr<InputManager> Engine::GetInputManager() const
{
	return inputManager;
}

void Engine::SetInputManager(std::shared_ptr<InputManager> input_manager)
{
	inputManager = std::move(input_manager);
}

std::shared_ptr<Renderer> Engine::GetRenderer() const
{
	return renderer;
}

void Engine::SetRenderer(std::shared_ptr<Renderer> renderer)
{
	this->renderer = std::move(renderer);
}

std::shared_ptr<Scene> Engine::GetScene() const
{
	return scene;
}

void Engine::SetScene(std::shared_ptr<Scene> scene)
{
	this->scene = std::move(scene);
}
