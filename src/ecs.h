#ifndef ECS_H
#define ECS_H

#include <vector>
#include <memory>
#include <unordered_map>
#include <variant>
#include <iostream>
#include "raylib.h"

struct TransformComponent {
	Vector2 position;
	Vector2 velocity;
};

class ECS;

using ComponentVariant = std::variant<TransformComponent>;

class Entity{
public:
	int id;
	std::vector<int> component_types;
	std::vector<int> component_ids;

	int GetId();
	void SetId(int id);
	std::vector<int> GetComponentTypes();
	std::vector<int> GetComponentIds();

    ECS* ecs;  // Pointer to ECS instance
    Entity(ECS* ecsInstance) : ecs(ecsInstance) {}

    template <typename T>
    int AddComponent(int componentTypeId, T component);
	void RemoveComponent(int ComponentTypeId);
};

class ECS {
public:
	std::vector<Entity> entities;
	int entityId = 0;
	std::vector<ComponentVariant> componentTypesArray;			//holds every component type
	std::vector<TransformComponent> transformComponentsArray;	//holds the unique instances of one component type
	std::unordered_map<int, std::vector<std::shared_ptr<void>>> componentArrays;	// Use an unordered_map to manage different component arrays

	void Initialize();
	Entity CreateEntity();
	void DeleteEntity(int id);
	void Update();
	void Shutdown();

    // Register component type arrays
    template <typename T>
    void RegisterComponentType(int componentTypeId);
};

// Register a component type by ID
template <typename T>
void ECS::RegisterComponentType(int componentTypeId) {
    if (componentArrays.find(componentTypeId) == componentArrays.end()) {
        componentArrays[componentTypeId] = std::vector<std::shared_ptr<void>>();
    }
}

// Add a component to an entity
template <typename T>
int Entity::AddComponent(int componentTypeId, T component) {
    if (ecs->componentArrays.find(componentTypeId) != ecs->componentArrays.end()) {
        auto& componentArray = ecs->componentArrays[componentTypeId];
        int componentId = componentArray.size();
        componentArray.push_back(std::make_shared<T>(component));
        this->component_types.push_back(componentTypeId);
        this->component_ids.push_back(componentId);
        return componentId;
    }
    return -1; // Error if component type not found
}

#endif // ECS_H
