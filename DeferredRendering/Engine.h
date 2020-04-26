#pragma once
#include <memory>

class InputManager;
class Renderer;
class Scene;

class Engine
{
public:
	Engine();

	static Engine Instance;

	void Init();
	void Shutdown();

	void Update();
	
	std::shared_ptr<InputManager> GetInputManager() const;
	void SetInputManager(std::shared_ptr<InputManager> input_manager);
	std::shared_ptr<Renderer> GetRenderer() const;
	void SetRenderer(std::shared_ptr<Renderer> renderer);
	std::shared_ptr<Scene> GetScene() const;
	void SetScene(std::shared_ptr<Scene> scene);
private:
	std::shared_ptr<InputManager> inputManager;
	std::shared_ptr<Renderer> renderer;
	std::shared_ptr<Scene> scene;
};

