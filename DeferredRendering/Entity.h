#pragma once

#include <memory>
#include <unordered_map>

class Component;

class Entity
{
public:
	template<typename T>
	void AddComponent(std::shared_ptr<T> component)
	{
		components[T::TYPE] = std::static_pointer_cast<Component>(component);
	}
	
	template<typename T>
	std::shared_ptr<T> GetComponent()
	{
		auto it = components.find(T::TYPE);
		if (it == components.end())
		{
			return nullptr;
		}

		return std::dynamic_pointer_cast<T>(it->second);
	}

	void Update(float deltaTime);
	
private:
	std::unordered_map<const char *, std::shared_ptr<Component>> components;
};

