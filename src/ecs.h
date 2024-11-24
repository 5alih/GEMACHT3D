#ifndef ECS_H
#define ECS_H

#include <vector>
#include <memory>
#include <unordered_map>
#include <variant>
#include <bits/stdc++.h>
#include "raylib.h"

enum componentsEnum{TRANSFORM_COMPONENT};

struct TransformComponent {
	Vector2 position;
	Vector2 velocity;
};

class ECS;

using ComponentVariant = std::variant<TransformComponent>;

class Entity {
public:
	int id;
	ECS* ecs;
	std::vector<int> component_types;
	std::vector<int> component_ids;

	int GetId();
	void SetId(int id);
	std::vector<int> GetComponentTypes();
	int GetComponentType(int index);
	std::vector<int> GetComponentIds();
	int GetComponentId(int index);
    Entity(ECS* ecsInstance) : ecs(ecsInstance) {}

    template <typename T>
    int AddComponent(int componentTypeId, T component);
	void RemoveComponent(int componentTypeId);
};

class System {
public:
    virtual void Update(ECS& ecs) = 0; // Pure virtual function for updating components
};

class ECS {
public:
	std::vector<Entity> entities;
	int entityId = 0;
	std::unordered_map<int, std::vector<std::shared_ptr<void>>> componentArrays;	// Use an unordered_map to manage different component arrays
	std::vector<std::shared_ptr<System>> systems;  									// List of systems

	void Initialize();
	Entity CreateEntity();
	void DeleteEntity(int id);
	void Update();
	void Shutdown();

    template <typename T>
    void RegisterComponentType(int componentTypeId);
	void AddSystem(std::shared_ptr<System> system);
};

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

// Register a component type by ID
template <typename T>
void ECS::RegisterComponentType(int componentTypeId) {
    if (componentArrays.find(componentTypeId) == componentArrays.end()) {
        componentArrays[componentTypeId] = std::vector<std::shared_ptr<void>>();
    }
}

class MovementSystem: public System {
public:
    void Update(ECS& ecs) override{
        for (Entity& entity : ecs.entities) {								// Iterate over all entities in the ECS
            for (size_t i = 0; i < entity.component_types.size(); ++i) {	// Check if the entity has a TransformComponent
                if (entity.component_types[i] == TRANSFORM_COMPONENT) {  	// Assuming 0 is TransformComponent's type ID
                    int componentId = entity.component_ids[i];
					
					// Retrieve the TransformComponent
                    auto& componentArray = ecs.componentArrays[0]; 			// TransformComponent array
                    auto transformComponent = std::static_pointer_cast<TransformComponent>(componentArray[componentId]);
                    
                    if (transformComponent) {                    			// Update TransformComponent logic (e.g., move entity based on velocity)
                        transformComponent->position.x += transformComponent->velocity.x;
                        transformComponent->position.y += transformComponent->velocity.y;
                    }
                }
            }
        }
    }
};

#endif // ECS_H
